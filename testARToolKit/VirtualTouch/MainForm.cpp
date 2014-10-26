#include "MainForm.h"

#define WINDOW_W	640
#define WINDOW_H	480
#define VIB_NUM		5

using namespace VirtualTouch;
using namespace System::Runtime::InteropServices;

//----------------------
//	必要なグローバル変数
//----------------------
bool	camStop = true;			//	一時停止中にtrue
bool	camIsOpen = false;		//	カメラが開いている状態でtrue
Mat		depthMap;				//	取得したデプスマップ
static cv::Point vibrator[VIB_NUM]= {
	cv::Point(380, 270),			//	親指
	cv::Point(350, 220),			//	人差指
	cv::Point(320, 200),			//	中指
	cv::Point(290, 210),			//	薬指
	cv::Point(260, 240)				//	小指
};

//=============================================================
//		メインフォームの動作
//=============================================================
System::Void MainForm::MainForm_Load(System::Object^  sender, System::EventArgs^  e) 
{

}
System::Void MainForm::MainForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
{
	if (MessageBox::Show("アプリケーションを終了しますか？",
		"確認",
		MessageBoxButtons::YesNo,
		MessageBoxIcon::Question) == ::DialogResult::No)
		e->Cancel = true;
}
System::Void MainForm::MainForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e)
{
	if (serialPort1->IsOpen) serialPort1->Close();
	camIsOpen = false;
}

//-------------------------------------------------------------------------------------------------
//		ピクチャボックスに画像を表示する関数
//-------------------------------------------------------------------------------------------------
System::Void winShowImage(System::Windows::Forms::PictureBox^ picturebox, cv::Mat cvImg)
{
	Bitmap^ bmp = gcnew Bitmap(picturebox->Width, picturebox->Height);
	Mat cvTemp;
	resize(cvImg, cvTemp, cv::Size(picturebox->Width, picturebox->Height));
	IntPtr ip(cvTemp.ptr());							// OpenCVの画像バッファをintポインタに変換

	picturebox->Image = bmp;
	Graphics^g = Graphics::FromImage(picturebox->Image);		//	pictureboxのImageからグラフィックオブジェクト作成 

	bmp = gcnew Bitmap(cvTemp.cols, cvTemp.rows, cvTemp.step, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ip);

	// bmp->Save("test.jpg");　// これはデバッグ用。バッファがコピーされているか確認。
	g->DrawImage(bmp, 0, 0, cvTemp.cols, cvTemp.rows);
	//picturebox->Refresh();		// これは除外。動画だと画面がちらつく。
	picturebox->Invalidate();

	delete g;
	delete bmp;
}

//=============================================================
//		ファイル
//=============================================================
System::Void MainForm::終了ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->Close();
}
//=============================================================
//		コントロール->カメラ
//=============================================================
System::Void MainForm::入力ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	VideoCapture cap(1);
	//	カメラの存在をチェック
	if (!cap.isOpened())
	{
		MessageBox::Show("カメラが開けませんでした");
		return;
	}
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	Threading::Thread::Sleep(1000);

	Mat				cvImg, frame;			//	OpenCV側の画像保管バッファ
	ARUint8			*arImg;					//	ARToolKit側の画像保管バッファ
	ARMarkerInfo	*markerInfo;			//	ARTKのマーカー情報(複数の場合は配列になる)
	static bool		isFirstDetect = true;
	cap >> frame;
	if (!arSetup(frame))
	{
		MessageBox::Show("データファイルが見つかりませんでした");
		return;
	}
	camIsOpen = true;
	camStop = false;

	while (camIsOpen)
	{
		cap >> frame;
		//cvtImageCV2AR(frame, arImg);
		cvtColor(frame, cvImg, CV_BGR2BGRA);	//	ARTKに渡すための変換
		arImg = (ARUint8*)(cvImg.data);			//	ARTKに画像データのみ渡す
		// カメラ画像のバッファへの描画
		argDrawMode2D();
		argDispImage(arImg, 0, 0);

		int	markerNum;							//	検出されたマーカー数
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
			arBeginObjectRender();
			{
				// ライティング
				// ライトの定義
				GLfloat lt0_position[] = { 100.0, -200.0, 200.0, 0.0 };	//	ライト0の位置
				GLfloat lt0_ambient[] = { 0.1, 0.1, 0.1, 1.0 };			//	環境光
				GLfloat lt0_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };			//	拡散光
				// ライトの設定
				glLightfv(GL_LIGHT0, GL_POSITION, lt0_position);
				glLightfv(GL_LIGHT0, GL_AMBIENT, lt0_ambient);
				glLightfv(GL_LIGHT0, GL_DIFFUSE, lt0_diffuse);

				glEnable(GL_LIGHTING);		// ライティング・有効
				glEnable(GL_LIGHT0);		// ライト0・オン

				// オブジェクトの材質
				// オブジェクトの材質
				GLfloat mat_ambient[] = { 0.0, 0.0, 1.0, 1.0 };		// 材質の環境光
				GLfloat mat_specular[] = { 0.0, 0.0, 1.0, 1.0 };	// 鏡面光
				GLfloat mat_shininess[] = { 50.0 };					// 鏡面係数

				// マテリアルの設定
				glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
				glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
				glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

				// 3Dオブジェクトの描画
				glPushMatrix();					//	カレント変換行列を保存
				glTranslatef(0.0, 0.0, 20.0);	// マーカの上に載せるためにZ方向（マーカ上方）に20.0[mm]移動
				glRotated(90.0, 1.0, 0.0, 0.0);
				glutSolidTeapot(50.0);			// ソリッドキューブを描画（1辺のサイズ50[mm]）
				glPopMatrix();					//	カレント変換行列を呼び出し

				//	デプスマップ取得
				cvtColor(frame, depthMap, CV_BGR2GRAY);
				getDepthMap(depthMap);
			}
			arEndObjectRender();
		}
		else
		{
			isFirstDetect = false;
			cvtColor(frame, depthMap, CV_BGR2GRAY);
			depthMap.convertTo(depthMap, CV_32F);
			depthMap = 0.0;
		}
		readImageBuffer(cvImg);					//	OpenGLバッファからレンダリング後の画像を読み取る

		//	振動子位置の描画
		for (int i = 0; i < VIB_NUM; i++)
		{
			float depth = depthMap.at<float>(vibrator[i]);
			char s[256];
			sprintf_s(s, 256, "%.2f", depth);
			putText(cvImg, s, cv::Point(10, 18 * (i+1)), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1, CV_AA);
			circle(cvImg, vibrator[i], 8, Scalar(0, 0, 255), 2, CV_AA);
		}
		if (!camStop)	winShowImage(pictureBox1, cvImg);
		Application::DoEvents();
	}
}
System::Void MainForm::一時停止ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	//	ここで変えても処理自体は続いている
	if (camIsOpen)
	{
		if (一時停止ToolStripMenuItem->Text == "一時停止")
		{
			camStop = true;
			一時停止ToolStripMenuItem->Text = "再開";
		}
		else
		{
			camStop = false;
			一時停止ToolStripMenuItem->Text = "一時停止";
		}
	}
}
System::Void MainForm::スナップを保存ToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e)
{
	camStop = true;

	//[名前を付けて保存]ダイアログボックス起動
	saveFileDialog1->Filter =
		"JPEGファイル(*.jpg)|*.jpg|Bitmapファイル(*.bmp)|*.bmp|PNGファイル(*.png)|*.png";
	if (saveFileDialog1->ShowDialog() != Windows::Forms::DialogResult::OK)
		return;
	pictureBox1->Image->Save(saveFileDialog1->FileName);

	if (一時停止ToolStripMenuItem->Text == "一時停止")
	{
		camStop = false;
	}
	
}
System::Void MainForm::終了ToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e)
{
	//	完全に処理を止める
	camStop = true;
	camIsOpen = false;
}

//=============================================================
//		ウインドウ
//=============================================================
System::Void MainForm::x05ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (x10ToolStripMenuItem->Checked)
	{
		x10ToolStripMenuItem->Checked = false;
		x05ToolStripMenuItem->Checked = true;
		this->Width = WINDOW_W / 2; this->Height = WINDOW_H / 2;
	}
}
System::Void MainForm::x10ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (x05ToolStripMenuItem->Checked)
	{
		x05ToolStripMenuItem->Checked = false;
		x10ToolStripMenuItem->Checked = true;
		this->Width = WINDOW_W; this->Height = WINDOW_H;
	}
}