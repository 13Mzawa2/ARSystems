#include "ARToolKitAdapter.h"

//-------------------------------------------------------
//	プロトタイプ宣言
//-------------------------------------------------------
void Init(void);
void MainLoop(void);
void DrawObject(void);
void SetupLighting(void);
void SetupMaterial(void);
void KeyEvent(unsigned char, int, int);
void MouseEvent(int, int, int, int);
void Cleanup(void);

// グローバル変数
/* カメラ構成 */
char *vconf_name = "Data/WDM_camera_flipV.xml";	// ビデオデバイスの設定ファイル
int  xsize;											// ウィンドウサイズ
int  ysize;											// ウィンドウサイズ
int  thresh = 100;									// 2値化の閾値
int  count = 0;										// 処理フレーム数

/* カメラパラメータ */
char *cparam_name = "Data/camera_para.dat";			// カメラパラメータファイル
ARParam cparam;										// カメラパラメータ

/* パターンファイル */
char   *patt_name = "Data/patt.hiro";				// パターンファイル
int    patt_id;										// パターンのID
double patt_trans[3][4];							// 座標変換行列
double patt_center[2] = { 0.0, 0.0 };				// パターンの中心座標
double patt_width = 80.0;						// パターンのサイズ（単位：ｍｍ）


//=======================================================
// main関数
//=======================================================
int main(int argc, char **argv)
{
	// GLUTの初期化
	glutInit(&argc, argv);

	// ARアプリケーションの初期化
	Init();

	// ビデオキャプチャの開始
	arVideoCapStart();

	// メインループの開始
	argMainLoop(MouseEvent, KeyEvent, MainLoop);

	return 0;
}
//=======================================================
// 初期化関数
//=======================================================
void Init(void)
{
	ARParam wparam;		// カメラパラメータ

	// ビデオデバイスの設定
	if (arVideoOpen(vconf_name) < 0){
		printf("ビデオデバイスのエラー\n");
		exit(0);
	}

	// ウィンドウサイズの取得
	if (arVideoInqSize(&xsize, &ysize) < 0) exit(0);
	printf("Image size (x,y) = (%d,$d)\n", xsize, ysize);

	// カメラパラメータの設定
	if (arParamLoad(cparam_name, 1, &wparam) < 0){
		printf("カメラパラメータの読み込みに失敗しました\n");
		exit(0);
	}

	// カメラパラメータのサイズ調整
	arParamChangeSize(&wparam, xsize, ysize, &cparam);
	// カメラパラメータの初期化
	arInitCparam(&cparam);
	printf("*** Camera Parameter ***\n");
	arParamDisp(&cparam);

	// パターンファイルのロード
	if ((patt_id = arLoadPatt(patt_name)) < 0){
		printf("パターンファイルの読み込みに失敗しました\n");
		exit(0);
	}

	// gsubライブラリの初期化
	argInit(&cparam, 1.0, 0, 0, 0, 0);

	// ウィンドウタイトルの設定
	glutSetWindowTitle("ARTK_basic");
}
//=======================================================
// メインループ関数
//=======================================================
void MainLoop(void)
{
	ARUint8          *image;			// カメラキャプチャ画像
	ARMarkerInfo     *marker_info;		// マーカ情報
	int              marker_num;		// 検出されたマーカの数
	int              j, k;

	// カメラ画像の取得
	if ((image = (ARUint8 *)arVideoGetImage()) == NULL){
		arUtilSleep(2);
		return;
	}
	if (count == 0) arUtilTimerReset();
	count++;

	// カメラ画像の描画
	argDrawMode2D();
	argDispImage(image, 0, 0);

	// マーカの検出と認識
	if (arDetectMarker(image, thresh, &marker_info, &marker_num) < 0){
		Cleanup();
		exit(0);
	}

	// 次の画像のキャプチャ指示
	arVideoCapNext();

	// マーカの一致度の比較
	k = -1;
	for (j = 0; j < marker_num; j++){
		if (patt_id == marker_info[j].id){
			if (k == -1) k = j;
			else if (marker_info[k].cf < marker_info[j].cf) k = j;
		}
	}

	// マーカーが見つからなかったとき
	if (k == -1){
		argSwapBuffers();
		return;
	}

	// マーカの位置・姿勢（座標変換行列）の計算
	arGetTransMat(&marker_info[k], patt_center, patt_width, patt_trans);

	// 3Dオブジェクトの描画
	DrawObject();

	// バッファの内容を画面に表示
	argSwapBuffers();
}
//=======================================================
// 3Dオブジェクトの描画を行う関数
//=======================================================
void DrawObject(void)
{
	double gl_para[16];	// ARToolKit->OpenGL変換行列

	// 3Dオブジェクトを描画するための準備
	argDrawMode3D();
	argDraw3dCamera(0, 0);

	// 陰面消去
	glClearDepth(1.0);					// デプスバッファの消去値
	glClear(GL_DEPTH_BUFFER_BIT);		// デプスバッファの初期化
	glEnable(GL_DEPTH_TEST);			// 陰面消去・有効
	glDepthFunc(GL_LEQUAL);			// デプステスト

	// 変換行列の適用
	argConvGlpara(patt_trans, gl_para);	// ARToolKitからOpenGLの行列に変換
	glMatrixMode(GL_MODELVIEW);			// 行列変換モード・モデルビュー
	glLoadMatrixd(gl_para);				// 読み込む行列を指定

	// マーカ→ビュー座標変換行列を表示
	static int h_count;
	if (h_count > 10){		// 大量に出てくるの防止用
		for (int i = 0; i < 4; i++){
			printf(" ( ");
			for (int j = 0; j < 4; j++){
				printf("%10.4lf", gl_para[(j * 4) + i]);
			}
			printf(" ) \n");
		}
		h_count = 0;
		printf("\n");
	}
	h_count++;

	// ライティング
	SetupLighting();			// ライトの定義
	glEnable(GL_LIGHTING);	// ライティング・有効
	glEnable(GL_LIGHT0);		// ライト0・オン

	// オブジェクトの材質
	SetupMaterial();

	// 3Dオブジェクトの描画
	glTranslatef(0.0, 0.0, 20.0);	// マーカの上に載せるためにZ方向（マーカ上方）に20.0[mm]移動
	glutSolidCube(50.0);			// ソリッドキューブを描画（1辺のサイズ50[mm]）

	// 終了処理
	glDisable(GL_LIGHTING);		// ライティング・無効
	glDisable(GL_DEPTH_TEST);		// デプステスト・無効
}

//------------------------------------------------------------
//　ライティング
//------------------------------------------------------------
static void SetupLighting(void)
{
	/* ライトの定義 */
	GLfloat lt0_position[] = { 100.0, -200.0, 200.0, 0.0 }; // ライト0の位置
	GLfloat lt0_ambient[] = { 0.1, 0.1, 0.1, 1.0 }; // 環境光
	GLfloat lt0_diffuse[] = { 0.8, 0.8, 0.8, 1.0 }; // 拡散光
	//
	GLfloat lt1_position[] = { -100.0, 200.0, 200.0, 0.0 }; // ライト1の位置
	GLfloat lt1_ambient[] = { 0.1, 0.1, 0.1, 1.0 }; // 環境光
	GLfloat lt1_diffuse[] = { 0.8, 0.8, 0.8, 1.0 }; // 拡散光

	/* ライトの設定 */
	glLightfv(GL_LIGHT0, GL_POSITION, lt0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lt0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lt0_diffuse);
	//
	glLightfv(GL_LIGHT1, GL_POSITION, lt1_position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lt1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lt1_diffuse);
}
//------------------------------------------------------------
//　オブジェクトの材質
//------------------------------------------------------------
static void SetupMaterial(void)
{
	/* オブジェクトの材質 */
	GLfloat mat_ambient[] = { 0.0, 0.0, 1.0, 1.0 }; // 材質の環境光
	GLfloat mat_specular[] = { 0.0, 0.0, 1.0, 1.0 }; // 鏡面光
	GLfloat mat_shininess[] = { 50.0 }; // 鏡面係数
	//
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}
//=======================================================
// キーボード入力処理関数
//=======================================================
void KeyEvent(unsigned char key, int x, int y)
{
	// ESCキーを入力したらアプリケーション終了
	if (key == 0x1b){
		printf("*** %f (frame/sec)\n", (double)count / arUtilTimer());
		Cleanup();
		exit(0);
	}
}
//=======================================================
// マウス入力処理関数
//=======================================================
void MouseEvent(int button, int state, int x, int y)
{
	// 入力状態を表示
	printf("ボタン：%d 状態：%d 座標：(x,y)=(%d,%d) \n", button, state, x, y);
}


//=======================================================
// 終了処理関数
//=======================================================
void Cleanup(void)
{
	arVideoCapStop();	// ビデオキャプチャの停止
	arVideoClose();		// ビデオデバイスの終了
	argCleanup();		// ARToolKitの終了処理
}