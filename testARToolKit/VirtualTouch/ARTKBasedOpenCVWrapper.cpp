#include "ARTKBasedOpenCVWrapper.h"

ARPattern patt;

/* カメラパラメータ */
static char	*cparamName = "Data/camera_para.dat";		// カメラパラメータファイル
ARParam	cparam;										// カメラパラメータ

//	ARTKの初期化
bool arSetup(Mat& camImg)
{
	ARParam wparam;		// カメラパラメータ
	int xsize, ysize;

	//	ARパターンのセットアップ
	patt.name = "Data/patt.hiro";
	patt.center[0] = 0.0; patt.center[1] = 0.0;
	patt.width = 200.0;								//	ARマーカーの一辺の長さ(mm)

	// ウィンドウサイズの取得
	xsize = camImg.cols; ysize = camImg.rows;

	// カメラパラメータの設定
	if (arParamLoad(cparamName, 1, &wparam) < 0)
	{
//		printf("カメラパラメータの読み込みに失敗しました\n");
		return false;
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
		return false;
	}
	// gsubライブラリの初期化
	argInit(&cparam, 1.0, 0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	return true;
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
}

//	ARUint8 -> cv::Mat
void cvtImageAR2CV(ARUint8* arImg, Mat& cvImg)
{
	memcpy(cvImg.data, arImg, cvImg.rows * cvImg.cols * cvImg.channels());
}

void writeImageBuffer(Mat& cvImg)
{
	Mat cvTemp;
	ARUint8* arImg;
	cvtColor(cvImg, cvTemp, CV_BGR2BGRA);		//	ARTKに渡すための変換
	arImg = (ARUint8*)(cvTemp.data);			//	ARTKに画像データのみ渡す
	// カメラ画像のバッファへの描画
	argDrawMode2D();
	argDispImage(arImg, 0, 0);
}
//	OpenGLバッファの内容をBGR画像として取得
//	引数cvImgはカメラ画像と同じ大きさの4ch画像（CV_8UC4）を渡す
void readImageBuffer(Mat& cvImg)
{
	glReadBuffer(GL_BACK);
	glReadPixels(
		0, 0,
		cvImg.cols, cvImg.rows,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		cvImg.data);							// RGBAで取得
	//	以下は使用するカメラによって適宜変える
	cvtColor(cvImg, cvImg, CV_RGBA2BGR);		// OpenCVのBGR並びに変換
	flip(cvImg, cvImg, 0);						// OpenCVに合わせて上下反転
}
//	デプスマップ(0(near), 1(far))を取得
//	引数dmapはカメラ画像と同じ大きさの1ch画像(CV_32FC1)を用意する
//	距離(mm)を得るにはここから変換する必要がある
void getDepthMap(Mat &dmap)
{
	if (dmap.depth() != CV_32F) dmap.convertTo(dmap, CV_32F);
	glReadPixels(0, 0, dmap.cols, dmap.rows, GL_DEPTH_COMPONENT, GL_FLOAT, dmap.data);	//	デプスマップ読み込み
	flip(dmap, dmap, 0);
	//dmap = f*n/(f - dmap * (f - n));
}
void getClip(double &n, double &f)
{
	float m[16];

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	glGetFloatv(GL_PROJECTION_MATRIX, m);	//	デプスバッファから距離を算出するため射影行列をロード
	f = m[14] / (m[10] - 1.0);			//	far clipping
	n = m[14] / (m[10] + 1.0);			//	near clipping
}
void cvtDepth2Z(Mat &dmap, Mat &zmap)
{
	double f, n;
	getClip(n, f);
	zmap = dmap.clone();
	zmap = f*n / (dmap * (f - n) - f);
/*	for (int y = 0; y < dmap.rows; y++)
	{
		for (int x = 0; x < dmap.cols; x++)
		{
			zmap.at<float>(x, y) = f * n / (dmap.at<float>(x, y) * (f - n) - f);
		}
	}*/
}
void getDepthImage(Mat &dmap, Mat &dimg)
{
	Mat depthImg = dmap.clone();
	depthImg = 255.0 - (depthImg * 255.0);
	depthImg.convertTo(depthImg, CV_8U);
	cvtColor(depthImg, dimg, CV_GRAY2BGR);
}
//	大津の手法の閾値を返す関数
int thresholdOtsu(Mat &srcImg)
{
	Mat grayImg;
	cvtColor(srcImg, grayImg, CV_BGR2GRAY);
	return (int)threshold(grayImg, grayImg, 128, 255, THRESH_BINARY | THRESH_OTSU);
}

//	円柱を描画するOpenGL関数
//	円柱はglutにはないので自作
//	axis : 0...x軸方向, 1...y軸方向, 2...z軸方向（デフォルト）
void glutSolidCylinder(GLdouble radius, GLdouble length, GLint axis, GLint slices)
{
	GLUquadric *qobj;
	qobj = gluNewQuadric();

	glPushMatrix();
	switch (axis)
	{
	case 0:
		glRotated(-90.0, 0.0, 1.0, 0.0);
		glTranslated(0.0, 0.0, -0.5*length);
		break;
	case 1:
		glRotated(-90.0, 1.0, 0.0, 0.0);
		glTranslated(0.0, 0.0, -0.5*length);
		break;
	case 2:
		glTranslated(0.0, 0.0, -0.5*length);
		break;
	default:
		glTranslated(0.0, 0.0, -0.5*length);
	}

	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluCylinder(qobj, radius, radius, length, slices, slices);

	//	Bottom Disk
	glPushMatrix();
	glRotated(180.0, 1.0, 0.0, 0.0);
	gluDisk(qobj, 0.0, radius, slices, slices);
	glPopMatrix();

	//	Top Disk
	glPushMatrix();
	glTranslated(0.0, 0.0, length);
	gluDisk(qobj, 0.0, radius, slices, slices);
	glPopMatrix();

	glPopMatrix();
}