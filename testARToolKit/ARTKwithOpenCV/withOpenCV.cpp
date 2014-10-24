#include "ARToolKitAdapter.h"
#include "OpenCVAdapter.h"

int thresholdOtsu(Mat&);
void arSetup(Mat&);
void drawObject(void);
void setupLighting(void);
void setupMaterial(void);

static bool		isFirstDetect = true;
ARPattern patt;

/* カメラパラメータ */
char	*cparamName = "Data/camera_para.dat";		// カメラパラメータファイル
ARParam	cparam;

int main(int argc, char** argv)
{
	VideoCapture cap(0);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	if (!cap.isOpened()) return -1;

	namedWindow("capture image", CV_WINDOW_AUTOSIZE);
	
	Mat				cvImg, frame;	//	OpenCV側のフレーム保管バッファ
	ARUint8			*arImg;			//	ARToolKit側の画像保管バッファ
	ARMarkerInfo	*markerInfo;	//	ARTKのマーカー情報(複数の場合は配列になる)
	cap >> frame;
	arSetup(frame);

	while (1)
	{
		cap >> frame;
		cvtColor(frame, cvImg, CV_BGR2BGRA);		//	ARTKに渡すための変換
		arImg = (ARUint8*)(cvImg.data);				//	ARTKに画像データのみ渡す

		// カメラ画像のバッファへの描画
		argDrawMode2D();
		argDispImage(arImg, 0, 0);

		int	markerNum;								//	検出されたマーカー数
		// マーカの検出と認識
		if (arDetectMarker(arImg, thresholdOtsu(frame), &markerInfo, &markerNum) < 0) break;

		// マーカの一致度の比較 最も一致度の高いマーカーがk番目に存在する
		int k = -1;
		for (int j = 0; j < markerNum; j++)
		{
			if (patt.id == markerInfo[j].id)
			{
				if (k == -1) k = j;
				else if (markerInfo[k].cf < markerInfo[j].cf) k = j;
			}
		}
		if (k != -1)
		{
			// マーカの位置・姿勢（座標変換行列）の計算
			if (isFirstDetect)
				arGetTransMat(&markerInfo[k], patt.center, patt.width, patt.trans);
			else
				arGetTransMatCont(&markerInfo[k], patt.trans, patt.center, patt.width, patt.trans);
			
			isFirstDetect = false;
			// 3Dオブジェクトのバッファへの描画
			drawObject();
		}

		// OpenGLバッファの内容を画像として取得
		glReadBuffer(GL_BACK);
		glReadPixels(
			0, 0,
			cvImg.cols, cvImg.rows,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			cvImg.data); // RGBAで取得
		cvtColor(cvImg, cvImg, CV_RGBA2BGR);		// OpenCVのBGR並びに変換
		flip(cvImg, cvImg, 0);						// OpenCV に合わせて上下反転
		imshow("capture image", cvImg);
		if (waitKey(15) == ' ') break;
		
	}
	destroyAllWindows();
}
//=======================================================
// ライティング
//=======================================================
void setupLighting(void)
{
	// ライトの定義
	GLfloat lt0_position[] = { 100.0, -200.0, 200.0, 0.0 };	// ライト0の位置
	GLfloat lt0_ambient[] = { 0.1, 0.1, 0.1, 1.0 };			// 　　　　 環境光
	GLfloat lt0_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };			// 　　　　 拡散光

	// ライトの設定
	glLightfv(GL_LIGHT0, GL_POSITION, lt0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lt0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lt0_diffuse);
}


//=======================================================
// マテリアルの設定
//=======================================================
void setupMaterial(void)
{
	// オブジェクトの材質
	GLfloat mat_ambient[] = { 0.0, 0.0, 1.0, 1.0 };	// 材質の環境光
	GLfloat mat_specular[] = { 0.0, 0.0, 1.0, 1.0 };	// 鏡面光
	GLfloat mat_shininess[] = { 50.0 };				// 鏡面係数

	// マテリアルの設定
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

//	オブジェクトの描画
void drawObject(void)
{
	double glParam[16];		//	ARTK -> OpenGL変換行列

	// 3Dオブジェクトを描画するための準備
	argDrawMode3D();
	argDraw3dCamera(0, 0);

	// 陰面消去
	glClearDepth(1.0);					// デプスバッファの消去値
	glClear(GL_DEPTH_BUFFER_BIT);		// デプスバッファの初期化
	glEnable(GL_DEPTH_TEST);			// 陰面消去・有効
	glDepthFunc(GL_LEQUAL);			// デプステスト

	// 変換行列の適用
	argConvGlpara(patt.trans, glParam);	// ARToolKitからOpenGLの行列に変換
	glMatrixMode(GL_MODELVIEW);			// 行列変換モード・モデルビュー
	glLoadMatrixd(glParam);				// 読み込む行列を指定

	// マーカ→ビュー座標変換行列を表示
	static int h_count;
	if (h_count > 10){		// 大量に出てくるの防止用
		for (int i = 0; i < 4; i++){
			printf(" ( ");
			for (int j = 0; j < 4; j++){
				printf("%10.4lf", glParam[(j * 4) + i]);
			}
			printf(" ) \n");
		}
		h_count = 0;
		printf("\n");
	}
	h_count++;

	// ライティング
	setupLighting();			// ライトの定義
	glEnable(GL_LIGHTING);		// ライティング・有効
	glEnable(GL_LIGHT0);		// ライト0・オン

	// オブジェクトの材質
	setupMaterial();

	// 3Dオブジェクトの描画
	glRotated(90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, 20.0);	// マーカの上に載せるためにZ方向（マーカ上方）に20.0[mm]移動
	glutSolidTeapot(50.0);			// ソリッドキューブを描画（1辺のサイズ50[mm]）

	// 終了処理
	glDisable(GL_LIGHTING);			// ライティング・無効
	glDisable(GL_DEPTH_TEST);		// デプステスト・無効

}
//	ARTKの初期化
void arSetup(Mat& camImg)
{
	ARParam wparam;		// カメラパラメータ
	int xsize, ysize;

	//	ARパターンのセットアップ
	patt.name = "Data/patt.hiro";
	patt.center[0] = 0.0; patt.center[1] = 0.0;
	patt.width = 80.0;

	// ウィンドウサイズの取得
	xsize = camImg.cols; ysize = camImg.rows;

	// カメラパラメータの設定
	if (arParamLoad(cparamName, 1, &wparam) < 0)
	{
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
	if ((patt.id = arLoadPatt(patt.name)) < 0)
	{
		printf("パターンファイルの読み込みに失敗しました\n");
		exit(0);
	}
	// gsubライブラリの初期化
	argInit(&cparam, 1.0, 0, 0, 0, 0);


}
//	大津の手法の閾値を返す関数
int thresholdOtsu(Mat &srcImg)
{
	Mat grayImg;
	cvtColor(srcImg, grayImg, CV_BGR2GRAY);
	return (int)threshold(grayImg, grayImg, 128, 255, THRESH_BINARY | THRESH_OTSU);
}