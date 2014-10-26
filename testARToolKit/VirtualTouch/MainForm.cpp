#include "MainForm.h"

#define WINDOW_W	640
#define WINDOW_H	480
#define VIB_NUM		5

using namespace VirtualTouch;
using namespace System::Runtime::InteropServices;

//----------------------
//	�K�v�ȃO���[�o���ϐ�
//----------------------
bool	camStop = true;			//	�ꎞ��~����true
bool	camIsOpen = false;		//	�J�������J���Ă����Ԃ�true
Mat		depthMap;				//	�擾�����f�v�X�}�b�v
static cv::Point vibrator[VIB_NUM]= {
	cv::Point(380, 270),			//	�e�w
	cv::Point(350, 220),			//	�l���w
	cv::Point(320, 200),			//	���w
	cv::Point(290, 210),			//	��w
	cv::Point(260, 240)				//	���w
};

//=============================================================
//		���C���t�H�[���̓���
//=============================================================
System::Void MainForm::MainForm_Load(System::Object^  sender, System::EventArgs^  e) 
{

}
System::Void MainForm::MainForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
{
	if (MessageBox::Show("�A�v���P�[�V�������I�����܂����H",
		"�m�F",
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
//		�s�N�`���{�b�N�X�ɉ摜��\������֐�
//-------------------------------------------------------------------------------------------------
System::Void winShowImage(System::Windows::Forms::PictureBox^ picturebox, cv::Mat cvImg)
{
	Bitmap^ bmp = gcnew Bitmap(picturebox->Width, picturebox->Height);
	Mat cvTemp;
	resize(cvImg, cvTemp, cv::Size(picturebox->Width, picturebox->Height));
	IntPtr ip(cvTemp.ptr());							// OpenCV�̉摜�o�b�t�@��int�|�C���^�ɕϊ�

	picturebox->Image = bmp;
	Graphics^g = Graphics::FromImage(picturebox->Image);		//	picturebox��Image����O���t�B�b�N�I�u�W�F�N�g�쐬 

	bmp = gcnew Bitmap(cvTemp.cols, cvTemp.rows, cvTemp.step, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ip);

	// bmp->Save("test.jpg");�@// ����̓f�o�b�O�p�B�o�b�t�@���R�s�[����Ă��邩�m�F�B
	g->DrawImage(bmp, 0, 0, cvTemp.cols, cvTemp.rows);
	//picturebox->Refresh();		// ����͏��O�B���悾�Ɖ�ʂ�������B
	picturebox->Invalidate();

	delete g;
	delete bmp;
}

//=============================================================
//		�t�@�C��
//=============================================================
System::Void MainForm::�I��ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->Close();
}
//=============================================================
//		�R���g���[��->�J����
//=============================================================
System::Void MainForm::����ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	VideoCapture cap(1);
	//	�J�����̑��݂��`�F�b�N
	if (!cap.isOpened())
	{
		MessageBox::Show("�J�������J���܂���ł���");
		return;
	}
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	Threading::Thread::Sleep(1000);

	Mat				cvImg, frame;			//	OpenCV���̉摜�ۊǃo�b�t�@
	ARUint8			*arImg;					//	ARToolKit���̉摜�ۊǃo�b�t�@
	ARMarkerInfo	*markerInfo;			//	ARTK�̃}�[�J�[���(�����̏ꍇ�͔z��ɂȂ�)
	static bool		isFirstDetect = true;
	cap >> frame;
	if (!arSetup(frame))
	{
		MessageBox::Show("�f�[�^�t�@�C����������܂���ł���");
		return;
	}
	camIsOpen = true;
	camStop = false;

	while (camIsOpen)
	{
		cap >> frame;
		//cvtImageCV2AR(frame, arImg);
		cvtColor(frame, cvImg, CV_BGR2BGRA);	//	ARTK�ɓn�����߂̕ϊ�
		arImg = (ARUint8*)(cvImg.data);			//	ARTK�ɉ摜�f�[�^�̂ݓn��
		// �J�����摜�̃o�b�t�@�ւ̕`��
		argDrawMode2D();
		argDispImage(arImg, 0, 0);

		int	markerNum;							//	���o���ꂽ�}�[�J�[��
		// �}�[�J�̌��o�ƔF��
		if (arDetectMarker(arImg, thresholdOtsu(frame), &markerInfo, &markerNum) < 0) break;

		// �}�[�J�̈�v�x�̔�r �ł���v�x�̍����}�[�J�[��k�Ԗڂɑ��݂���
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
			// �}�[�J�̈ʒu�E�p���i���W�ϊ��s��j�̌v�Z
			if (isFirstDetect)
				arGetTransMat(&markerInfo[k], patt.center, patt.width, patt.trans);
			else
				arGetTransMatCont(&markerInfo[k], patt.trans, patt.center, patt.width, patt.trans);

			isFirstDetect = false;
			// 3D�I�u�W�F�N�g�̃o�b�t�@�ւ̕`��
			arBeginObjectRender();
			{
				// ���C�e�B���O
				// ���C�g�̒�`
				GLfloat lt0_position[] = { 100.0, -200.0, 200.0, 0.0 };	//	���C�g0�̈ʒu
				GLfloat lt0_ambient[] = { 0.1, 0.1, 0.1, 1.0 };			//	����
				GLfloat lt0_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };			//	�g�U��
				// ���C�g�̐ݒ�
				glLightfv(GL_LIGHT0, GL_POSITION, lt0_position);
				glLightfv(GL_LIGHT0, GL_AMBIENT, lt0_ambient);
				glLightfv(GL_LIGHT0, GL_DIFFUSE, lt0_diffuse);

				glEnable(GL_LIGHTING);		// ���C�e�B���O�E�L��
				glEnable(GL_LIGHT0);		// ���C�g0�E�I��

				// �I�u�W�F�N�g�̍ގ�
				// �I�u�W�F�N�g�̍ގ�
				GLfloat mat_ambient[] = { 0.0, 0.0, 1.0, 1.0 };		// �ގ��̊���
				GLfloat mat_specular[] = { 0.0, 0.0, 1.0, 1.0 };	// ���ʌ�
				GLfloat mat_shininess[] = { 50.0 };					// ���ʌW��

				// �}�e���A���̐ݒ�
				glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
				glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
				glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

				// 3D�I�u�W�F�N�g�̕`��
				glPushMatrix();					//	�J�����g�ϊ��s���ۑ�
				glTranslatef(0.0, 0.0, 20.0);	// �}�[�J�̏�ɍڂ��邽�߂�Z�����i�}�[�J����j��20.0[mm]�ړ�
				glRotated(90.0, 1.0, 0.0, 0.0);
				glutSolidTeapot(50.0);			// �\���b�h�L���[�u��`��i1�ӂ̃T�C�Y50[mm]�j
				glPopMatrix();					//	�J�����g�ϊ��s����Ăяo��

				//	�f�v�X�}�b�v�擾
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
		readImageBuffer(cvImg);					//	OpenGL�o�b�t�@���烌���_�����O��̉摜��ǂݎ��

		//	�U���q�ʒu�̕`��
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
System::Void MainForm::�ꎞ��~ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	//	�����ŕς��Ă��������̂͑����Ă���
	if (camIsOpen)
	{
		if (�ꎞ��~ToolStripMenuItem->Text == "�ꎞ��~")
		{
			camStop = true;
			�ꎞ��~ToolStripMenuItem->Text = "�ĊJ";
		}
		else
		{
			camStop = false;
			�ꎞ��~ToolStripMenuItem->Text = "�ꎞ��~";
		}
	}
}
System::Void MainForm::�X�i�b�v��ۑ�ToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e)
{
	camStop = true;

	//[���O��t���ĕۑ�]�_�C�A���O�{�b�N�X�N��
	saveFileDialog1->Filter =
		"JPEG�t�@�C��(*.jpg)|*.jpg|Bitmap�t�@�C��(*.bmp)|*.bmp|PNG�t�@�C��(*.png)|*.png";
	if (saveFileDialog1->ShowDialog() != Windows::Forms::DialogResult::OK)
		return;
	pictureBox1->Image->Save(saveFileDialog1->FileName);

	if (�ꎞ��~ToolStripMenuItem->Text == "�ꎞ��~")
	{
		camStop = false;
	}
	
}
System::Void MainForm::�I��ToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e)
{
	//	���S�ɏ������~�߂�
	camStop = true;
	camIsOpen = false;
}

//=============================================================
//		�E�C���h�E
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