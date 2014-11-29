#include "MainForm.h"
#include "SerialPortForm.h"
#include <math.h>

#define WINDOW_W	640
#define WINDOW_H	480
#define VIB_NUM		10
#define MODEL_SIZE	500.0
#define CAP_NUM		0

using namespace VirtualTouch;
using namespace System::Runtime::InteropServices;

//----------------------
//	必要なグローバル変数
//----------------------
bool	camStop = true;				//	一時停止中にtrue
bool	camIsOpen = false;			//	カメラが開いている状態でtrue
Mat		depthMap;					//	取得したデプスマップ
Mat		ZMap;						//	デプスマップを変換して得られる距離
bool	serialPortIsSet = false;	//	シリアルポート用
int		objectNum = 0;				//	描画する3Dモデルの番号
unsigned char	motorState[2][VIB_NUM] = { {0x06}, {0x00} };

static cv::Point vibrator[VIB_NUM] = {
	cv::Point(350, 235),			//	親指
	cv::Point(335, 210),			//	人差指
	cv::Point(320, 200),			//	中指
	cv::Point(305, 205),			//	薬指
	cv::Point(290, 220),			//	小指

	cv::Point(330, 240),			//	人差指付根
	cv::Point(310, 242),			//	薬指付根
	cv::Point(335, 270),			//	親指付根
	cv::Point(320, 280),			//	掌中央下
	cv::Point(300, 250)				//	小指下
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
	serialPort1->Close();
	this->Close();
}
//=============================================================
//		設定
//=============================================================
System::Void MainForm::シリアルポートToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (serialPort1->IsOpen)
		serialPortIsSet = false;
	SerialPortForm^ spform = gcnew SerialPortForm();
	spform->ShowDialog(this);

	if (serialPortIsSet)
	{
		try
		{
			serialPort1->PortName = spform->comboBox1->SelectedItem->ToString();
			serialPort1->BaudRate = int::Parse(spform->comboBox2->SelectedItem->ToString());
			serialPort1->Open();
			serialPortIsSet = false;
			this->Text = "MainForm - 接続中";
		}
		catch (System::NullReferenceException^ ex)
		{
			MessageBox::Show(ex->Message + "\n注釈：ポート名が設定されていない可能性があります", "エラー", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	else
	{
		this->Text = "MainForm";
		serialPort1->Close();
	}
	return;
}
//	通信用関数
System::Void MainForm::serialPort1_DataReceived(System::Object^  sender, System::IO::Ports::SerialDataReceivedEventArgs^  e)
{
	if (serialPort1->ReadChar() == 'N')
	{
		array<unsigned char>^ motor = gcnew array<unsigned char>(VIB_NUM + 2);
		motor[0] = '\n';
		for (int i = 0; i < VIB_NUM; i++)
			motor[i + 1] = (motorState[0][i] << 2) | motorState[1][i];
		motor[VIB_NUM + 1] = '\r';

		try
		{
			serialPort1->Write(motor, 0, VIB_NUM + 2);
			delete motor;
		}
		catch (System::InvalidOperationException^ ex)
		{
			MessageBox::Show(ex->Message, "エラー", MessageBoxButtons::OK, MessageBoxIcon::Error);
			delete motor;
			return;
		}
	}
}
System::Void setMotorState(Mat& zmap)
{
	double refV, znear, zfar;
	getClip(znear, zfar);
	for (int i = 0; i < VIB_NUM; i++)
	{
		double z = - zmap.at<float>(vibrator[i]);
		refV = 170.0 - 170.0 / (zfar - znear)*(z - znear);		//	距離‐振動数一次変換式
		//refV = 170.0 * (-500) / z;
		refV = 0.0002*refV*refV - 0.0043*refV + 0.4719;								//	振動数‐電圧変換式
		motorState[0][i] = (int)(refV / 0.08);
		if (motorState[0][i] < 0x06) motorState[0][i] = 0x06;
		else if (motorState[0][i] > 0x3f) motorState[0][i] = 0x3f;
	}
}
//=============================================================
//		コントロール->モード
//=============================================================
System::Void MainForm::振動ONToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (振動ONToolStripMenuItem->Checked)
	{
		振動ONToolStripMenuItem->Checked = false;
		for (int i = 0; i < VIB_NUM; i++)
			motorState[1][i] = 0x00;
	}
	else
	{
		振動ONToolStripMenuItem->Checked = true;
		for (int i = 0; i < VIB_NUM; i++)
			motorState[1][i] = 0x01;
	}
}
System::Void MainForm::デプスマップToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
//	if (デプスマップToolStripMenuItem->Checked) デプスマップToolStripMenuItem->Checked = false;
//	else デプスマップToolStripMenuItem->Checked = true;
}
//=============================================================
//		コントロール->カメラ
//=============================================================
System::Void MainForm::入力ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	VideoCapture cap(CAP_NUM);
	//	カメラの存在をチェック
	if (!cap.isOpened())
	{
		MessageBox::Show("カメラが開けませんでした");
		return;
	}
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	Threading::Thread::Sleep(1000);

	Mat				cvImg, frame;			//	OpenCV側の画像保管バッファ(出力用、入力)
	ARUint8			*arImg;					//	ARToolKit側の画像保管バッファ
	ARMarkerInfo	*markerInfo;			//	ARTKのマーカー情報(複数の場合は配列になる)
	static bool		isFirstDetect = true;
	double			farClip, nearClip;

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
		cvtColor(frame, cvImg, CV_BGR2BGRA);	//	ARTKに渡すための変換
		arImg = (ARUint8*)(cvImg.data);			//	ARTKに画像データのみ渡す
		// カメラ画像のバッファへの描画
		argDrawMode2D();
		argDispImage(arImg, 0, 0);
		//depthMap = Mat(cv::Size(frame.rows, frame.cols), CV_32FC1, Scalar(1.0)).clone();
		cvtColor(frame, depthMap, CV_BGR2GRAY);

		int	markerNum;							//	検出されたマーカー数
		// マーカの検出と認識
		if (arDetectMarker(arImg, thresholdOtsu(frame), &markerInfo, &markerNum) < 0) break;
		//if (arDetectMarker(arImg, 30, &markerInfo, &markerNum) < 0) break;

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
		//	一致度の高いマーカーが見つかった場合
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
				lighting();
				// 3Dオブジェクトの描画
				draw3DObject(objectNum);
				//	デプスマップ取得
				getDepthMap(depthMap);
			}
			arEndObjectRender();

			//	デプスマップモードの場合にはデプスマップを表示
			if (デプスマップToolStripMenuItem->Checked)
				getDepthImage(depthMap, cvImg);			//	深度画像の取得
			else
				readImageBuffer(cvImg);					//	OpenGLバッファからレンダリング後の画像を読み取る
		}
		//	マーカーが見つからなかった場合
		else
		{
			isFirstDetect = false;
			//	デプスマップ取得
			arBeginObjectRender();
			{
				getDepthMap(depthMap);
			}
			arEndObjectRender();
			readImageBuffer(cvImg);					//	OpenGLバッファからレンダリング後の画像を読み取る
		}

		//	距離情報をもとに振動子をセット
		cvtDepth2Z(depthMap, ZMap);
		//Mat tempMap;
		//Laplacian(ZMap, tempMap, CV_32F, 3);
		//ZMap = abs(tempMap);
		//GaussianBlur(ZMap, ZMap, cv::Size(11, 11), 10, 10);
		//ZMap = 5000.0 - ZMap;
		setMotorState(ZMap);

		//	振動子位置の描画
		if (振動子位置表示ToolStripMenuItem->Checked)
		{
			for (int i = 0; i < VIB_NUM; i++)
			{
				float depth = ZMap.at<float>(vibrator[i]);
				//depth = farClip * nearClip / (depth * (farClip - nearClip) - farClip);
				char s[256];
				sprintf_s(s, 20, "%.2f", depth);
				putText(cvImg, s, cv::Point(10, 18 * (i + 1)), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1, CV_AA);
				circle(cvImg, vibrator[i], 4, Scalar(0, 0, 255), 1, CV_AA);
			}
		}

		//	停止していなければ描画
		if (!camStop)
		{
			if (モデル表示ToolStripMenuItem->Checked == false)
				cvImg = frame;
			winShowImage(pictureBox1, cvImg);
		}
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
//		コントロール->3Dモデル
//=============================================================
System::Void MainForm::球ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	objectNum = 1;
}
System::Void MainForm::立方体ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	objectNum = 2;
}
System::Void MainForm::円柱ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	objectNum = 3;
}
System::Void MainForm::円錐ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	objectNum = 4;
}
System::Void MainForm::トーラスToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	objectNum = 5;
}
System::Void MainForm::正八面体ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	objectNum = 6;
}
System::Void MainForm::ティーポットToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	objectNum = 7;
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
//=============================================================
//		その他
//=============================================================
void lighting(void)
{
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
}
System::Void MainForm::draw3DObject(int objNum)
{
	switch (objNum)
	{
	case 1:		//	球
		glPushMatrix();											//	カレント変換行列を保存
		glTranslatef(0.0, 0.0, MODEL_SIZE / sqrt(CV_PI));		// マーカの上に載せるためにZ方向（マーカ上方）に20.0[mm]移動
		//glRotated(90.0, 1.0, 0.0, 0.0);
		glutSolidSphere(MODEL_SIZE / sqrt(CV_PI), 20, 20);
		glPopMatrix();											//	カレント変換行列を呼び出し
		break;
	case 2:		//	立方体
		glPushMatrix();
		glTranslatef(0.0, 0.0, MODEL_SIZE / 2.0);
		//glRotated(90.0, 1.0, 0.0, 0.0);
		glutSolidCube(MODEL_SIZE);
		glPopMatrix();
		break;
	case 3:		//	円柱
		glPushMatrix();
		glTranslatef(0.0, 0.0, MODEL_SIZE / 2.0);
		//glRotated(90.0, 1.0, 0.0, 0.0);
		glutSolidCylinder(MODEL_SIZE / 2.0, MODEL_SIZE, 2, 20);
		glPopMatrix();
		break;
	case 4:		//	円錐
		glPushMatrix();
		//glRotated(-90.0, 1.0, 0.0, 0.0);
		//glTranslatef(0.0, MODEL_SIZE / sqrt(2.0), MODEL_SIZE / sqrt(2.0));
		glutSolidCone(MODEL_SIZE / sqrt(2.0), MODEL_SIZE * sqrt(2.0), 20, 20);
		glPopMatrix();
		break;
	case 5:		//	トーラス
		glPushMatrix();
		glTranslatef(0.0, 0.0, -MODEL_SIZE / sqrt(CV_PI) / 2.0);
		//glRotated(90.0, 1.0, 0.0, 0.0);
		glutSolidTorus(MODEL_SIZE / sqrt(CV_PI) * 0.25, MODEL_SIZE / sqrt(CV_PI) * 0.75, 20, 40);
		glPopMatrix();
		break;
	case 6:		//	正八面体
		glPushMatrix();
		glTranslatef(0.0, 0.0, -MODEL_SIZE / sqrt(2.0));
		//glRotated(90.0, 1.0, 0.0, 0.0);
		glutSolidSphere(MODEL_SIZE / sqrt(2.0), 4, 2);
		glPopMatrix();
		break;
	case 7:		//	ティーポット
		glPushMatrix();
		glTranslatef(0.0, 0.0, MODEL_SIZE * 0.3);
//		glRotated(90.0, 1.0, 0.0, 0.0);
		glutSolidTeapot(MODEL_SIZE * 0.6);
		glPopMatrix();
		break;
		
	default:	//	3軸
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glBegin(GL_LINES);
		{
			glPointSize(MODEL_SIZE / 50.0);
			//	X Axis
			glColor3d(1.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(MODEL_SIZE / 5.0, 0.0, 0.0);
			//	Y Axis
			glColor3d(0.0, 1.0, 0.0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, MODEL_SIZE / 5.0, 0.0);
			//	Z Axis
			glColor3d(0.0, 0.0, 1.0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, MODEL_SIZE / 5.0);
		}
		glEnd();
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}
}