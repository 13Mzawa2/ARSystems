#include "MainForm.h"
#include "SerialPortForm.h"
#include <math.h>

#define WINDOW_W	640
#define WINDOW_H	480
#define VIB_NUM		5
#define MODEL_SIZE	500.0

using namespace VirtualTouch;
using namespace System::Runtime::InteropServices;

//----------------------
//	�K�v�ȃO���[�o���ϐ�
//----------------------
bool	camStop = true;				//	�ꎞ��~����true
bool	camIsOpen = false;			//	�J�������J���Ă����Ԃ�true
Mat		depthMap;					//	�擾�����f�v�X�}�b�v
Mat		ZMap;						//	�f�v�X�}�b�v��ϊ����ē����鋗��
bool	serialPortIsSet = false;	//	�V���A���|�[�g�p
int		objectNum = 0;				//	�`�悷��3D���f���̔ԍ�
unsigned char	motorState[2][VIB_NUM] = { {0x06}, {0x00} };

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
	serialPort1->Close();
	this->Close();
}
//=============================================================
//		�ݒ�
//=============================================================
System::Void MainForm::�V���A���|�[�gToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
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
			this->Text = "MainForm - �ڑ���";
		}
		catch (System::NullReferenceException^ ex)
		{
			MessageBox::Show(ex->Message + "\n���߁F�|�[�g�����ݒ肳��Ă��Ȃ��\��������܂�", "�G���[", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	else
	{
		this->Text = "MainForm";
		serialPort1->Close();
	}
	return;
}
//	�ʐM�p�֐�
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
			MessageBox::Show(ex->Message, "�G���[", MessageBoxButtons::OK, MessageBoxIcon::Error);
			delete motor;
			return;
		}
	}
}
System::Void MainForm::setMotorState(void)
{
	double refV, znear, zfar;
	getClip(znear, zfar);
	for (int i = 0; i < VIB_NUM; i++)
	{
		double z = - ZMap.at<float>(vibrator[i]);
		refV = 170.0 - 170.0 / (zfar - znear)*(z - znear);		//	�����]�U�����ꎟ�ϊ���
		refV = 0.0002*refV*refV - 0.0043*refV + 0.4719;								//	�U�����]�d���ϊ���
		motorState[0][i] = (int)(refV / 0.08);
		if (motorState[0][i] < 0x06) motorState[0][i] = 0x06;
		else if (motorState[0][i] > 0x3f) motorState[0][i] = 0x3f;
	}
}
//=============================================================
//		�R���g���[��->���[�h
//=============================================================
System::Void MainForm::�U��ONToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (�U��ONToolStripMenuItem->Checked)
	{
		�U��ONToolStripMenuItem->Checked = false;
		for (int i = 0; i < VIB_NUM; i++)
			motorState[1][i] = 0x00;
	}
	else
	{
		�U��ONToolStripMenuItem->Checked = true;
		for (int i = 0; i < VIB_NUM; i++)
			motorState[1][i] = 0x01;
	}
}
System::Void MainForm::�f�v�X�}�b�vToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
//	if (�f�v�X�}�b�vToolStripMenuItem->Checked) �f�v�X�}�b�vToolStripMenuItem->Checked = false;
//	else �f�v�X�}�b�vToolStripMenuItem->Checked = true;
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

	Mat				cvImg, frame;			//	OpenCV���̉摜�ۊǃo�b�t�@(�o�͗p�A����)
	ARUint8			*arImg;					//	ARToolKit���̉摜�ۊǃo�b�t�@
	ARMarkerInfo	*markerInfo;			//	ARTK�̃}�[�J�[���(�����̏ꍇ�͔z��ɂȂ�)
	static bool		isFirstDetect = true;
	double			farClip, nearClip;

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
		cvtColor(frame, cvImg, CV_BGR2BGRA);	//	ARTK�ɓn�����߂̕ϊ�
		arImg = (ARUint8*)(cvImg.data);			//	ARTK�ɉ摜�f�[�^�̂ݓn��
		// �J�����摜�̃o�b�t�@�ւ̕`��
		argDrawMode2D();
		argDispImage(arImg, 0, 0);

		int	markerNum;							//	���o���ꂽ�}�[�J�[��
		// �}�[�J�̌��o�ƔF��
		//		if (arDetectMarker(arImg, thresholdOtsu(frame), &markerInfo, &markerNum) < 0) break;
		if (arDetectMarker(arImg, 30, &markerInfo, &markerNum) < 0) break;

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
		//	��v�x�̍����}�[�J�[�����������ꍇ
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
				lighting();

				// 3D�I�u�W�F�N�g�̕`��
				draw3DObject(objectNum);

				//	�f�v�X�}�b�v�擾
				cvtColor(frame, depthMap, CV_BGR2GRAY);
				getClip(nearClip, farClip);
				getDepthMap(depthMap);
			}
			arEndObjectRender();

			//	�f�v�X�}�b�v���[�h�̏ꍇ�ɂ̓f�v�X�}�b�v��\��
			if (�f�v�X�}�b�vToolStripMenuItem->Checked)
				getDepthImage(depthMap, cvImg);			//	�[�x�摜�̎擾
			else
				readImageBuffer(cvImg);					//	OpenGL�o�b�t�@���烌���_�����O��̉摜��ǂݎ��
		}
		//	�}�[�J�[��������Ȃ������ꍇ
		else
		{
			isFirstDetect = false;
			cvtColor(frame, depthMap, CV_BGR2GRAY);
			depthMap.convertTo(depthMap, CV_32F);
			depthMap = 1.0;
			readImageBuffer(cvImg);					//	OpenGL�o�b�t�@���烌���_�����O��̉摜��ǂݎ��
		}

		//	�����������ƂɐU���q���Z�b�g
		cvtDepth2Z(depthMap, ZMap);
		setMotorState();

		//	�U���q�ʒu�̕`��
		if (�U���q�ʒu�\��ToolStripMenuItem->Checked)
		{
			for (int i = 0; i < VIB_NUM; i++)
			{
				float depth = ZMap.at<float>(vibrator[i]);
				//depth = farClip * nearClip / (depth * (farClip - nearClip) - farClip);
				char s[256];
				sprintf_s(s, 20, "%.2f", depth);
				putText(cvImg, s, cv::Point(10, 18 * (i + 1)), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1, CV_AA);
				circle(cvImg, vibrator[i], 8, Scalar(0, 0, 255), 2, CV_AA);
			}
		}

		//	��~���Ă��Ȃ���Ε`��
		if (!camStop)
		{
			if (���f���\��ToolStripMenuItem->Checked == false)
				cvImg = frame;
			winShowImage(pictureBox1, cvImg);
		}
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
//		�R���g���[��->3D���f��
//=============================================================
System::Void MainForm::��ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	objectNum = 1;
}
System::Void MainForm::������ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	objectNum = 2;
}
System::Void MainForm::�~��ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	objectNum = 3;
}
System::Void MainForm::�~��ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	objectNum = 4;
}
System::Void MainForm::�g�[���XToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	objectNum = 5;
}
System::Void MainForm::�����ʑ�ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	objectNum = 6;
}
System::Void MainForm::�e�B�[�|�b�gToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	objectNum = 7;
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
//=============================================================
//		���̑�
//=============================================================
void lighting(void)
{
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
}
System::Void MainForm::draw3DObject(int objNum)
{
	switch (objNum)
	{
	case 1:		//	��
		glPushMatrix();											//	�J�����g�ϊ��s���ۑ�
		glTranslatef(0.0, 0.0, -MODEL_SIZE / sqrt(CV_PI));		// �}�[�J�̏�ɍڂ��邽�߂�Z�����i�}�[�J����j��20.0[mm]�ړ�
		//glRotated(90.0, 1.0, 0.0, 0.0);
		glutSolidSphere(MODEL_SIZE / sqrt(CV_PI), 20, 20);
		glPopMatrix();											//	�J�����g�ϊ��s����Ăяo��
		break;
	case 2:		//	������
		glPushMatrix();
		glTranslatef(0.0, 0.0, -MODEL_SIZE / 2.0);
		//glRotated(90.0, 1.0, 0.0, 0.0);
		glutSolidCube(MODEL_SIZE);
		glPopMatrix();
		break;
	case 3:		//	�~��
		glPushMatrix();
		glTranslatef(0.0, 0.0, -MODEL_SIZE / 2.0);
		//glRotated(90.0, 1.0, 0.0, 0.0);
		glutSolidCylinder(MODEL_SIZE / 2.0, MODEL_SIZE, 1, 20);
		glPopMatrix();
		break;
	case 4:		//	�~��
		glPushMatrix();
		glRotated(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(0.0, MODEL_SIZE / sqrt(2.0), -MODEL_SIZE / sqrt(2.0));
		glutSolidCone(MODEL_SIZE / sqrt(2.0), MODEL_SIZE * sqrt(2.0), 20, 20);
		glPopMatrix();
		break;
	case 5:		//	�g�[���X
		glPushMatrix();
		glTranslatef(0.0, 0.0, -MODEL_SIZE / sqrt(CV_PI) / 2.0);
		//glRotated(90.0, 1.0, 0.0, 0.0);
		glutSolidTorus(MODEL_SIZE / sqrt(CV_PI) * 0.25, MODEL_SIZE / sqrt(CV_PI) * 0.75, 20, 40);
		glPopMatrix();
		break;
	case 6:		//	�����ʑ�
		glPushMatrix();
		glTranslatef(0.0, 0.0, -MODEL_SIZE / sqrt(2.0));
		//glRotated(90.0, 1.0, 0.0, 0.0);
		glutSolidSphere(MODEL_SIZE / sqrt(2.0), 4, 2);
		glPopMatrix();
		break;
	case 7:		//	�e�B�[�|�b�g
		glPushMatrix();
		glTranslatef(0.0, 0.0, MODEL_SIZE * 0.3);
//		glRotated(90.0, 1.0, 0.0, 0.0);
		glutSolidTeapot(MODEL_SIZE * 0.6);
		glPopMatrix();
		break;
		
	default:	//	3��
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