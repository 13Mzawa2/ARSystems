#include "ARTKBasedOpenCVWrapper.h"

ARPattern patt;

/* カメラパラメータ */
static char	*cparamName = "Data/camera_para.dat";		// カメラパラメータファイル
ARParam	cparam;										// カメラパラメータ

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
//		printf("カメラパラメータの読み込みに失敗しました\n");
		exit(0);
	}

	// カメラパラメータのサイズ調整
	arParamChangeSize(&wparam, xsize, ysize, &cparam);
	// カメラパラメータの初期化
	arInitCparam(&cparam);
//	printf("*** Camera Parameter ***\n");
//	arParamDisp(&cparam);

	// パターンファイルのロード
	if ((patt.id = arLoadPatt(patt.name)) < 0)
	{
//		printf("パターンファイルの読み込みに失敗しました\n");
		exit(0);
	}
	// gsubライブラリの初期化
	argInit(&cparam, 1.0, 0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
}

//	AR描画開始コマンド
//	使い方は次の通り
//
//	arBeginObjectRender();
//	{
//		modelDraw();
//	}
//	arEndObjectRender();
void arBeginObjectRender(void)
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
}

//	AR描画終了コマンド
void arEndObjectRender(void)
{
	glDisable(GL_LIGHTING);			// ライティング・無効
	glDisable(GL_DEPTH_TEST);		// デプステスト・無効
}

//	cv::Mat -> ARUint8( -> OpenGLバッファ)
void cvtImageCV2AR(Mat& cvImg, ARUint8* arImg)
{
	Mat cvTemp;
	cvtColor(cvImg, cvTemp, CV_BGR2BGRA);		//	ARTKに渡すための変換
	arImg = (ARUint8*)(cvTemp.data);			//	ARTKに画像データのみ渡す
	// カメラ画像のバッファへの描画
	argDrawMode2D();
	argDispImage(arImg, 0, 0);
}

//	ARUint8 -> cv::Mat
void cvtImageAR2CV(ARUint8* arImg, Mat& cvImg)
{
	memcpy(cvImg.data, arImg, cvImg.rows * cvImg.cols * cvImg.channels());
}

// OpenGLバッファの内容を画像として取得
void readImageBuffer(Mat& cvImg)
{
	glReadBuffer(GL_BACK);
	glReadPixels(
		0, 0,
		cvImg.cols, cvImg.rows,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		cvImg.data);							// RGBAで取得
	cvtColor(cvImg, cvImg, CV_RGBA2BGR);		// OpenCVのBGR並びに変換
	flip(cvImg, cvImg, 0);						// OpenCVに合わせて上下反転
}
//	大津の手法の閾値を返す関数
int thresholdOtsu(Mat &srcImg)
{
	Mat grayImg;
	cvtColor(srcImg, grayImg, CV_BGR2GRAY);
	return (int)threshold(grayImg, grayImg, 128, 255, THRESH_BINARY | THRESH_OTSU);
}