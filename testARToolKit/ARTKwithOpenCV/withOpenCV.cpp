#include "ARToolKitAdapter.h"
#include "OpenCVAdapter.h"

int thresholdOtsu(Mat&);
void arSetup(Mat&);
void drawObject(void);
void setupLighting(void);
void setupMaterial(void);

static bool		isFirstDetect = true;
ARPattern patt;

/* �J�����p�����[�^ */
char	*cparamName = "Data/camera_para.dat";		// �J�����p�����[�^�t�@�C��
ARParam	cparam;

int main(int argc, char** argv)
{
	VideoCapture cap(0);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	if (!cap.isOpened()) return -1;

	namedWindow("capture image", CV_WINDOW_AUTOSIZE);
	
	Mat				cvImg, frame;	//	OpenCV���̃t���[���ۊǃo�b�t�@
	ARUint8			*arImg;			//	ARToolKit���̉摜�ۊǃo�b�t�@
	ARMarkerInfo	*markerInfo;	//	ARTK�̃}�[�J�[���(�����̏ꍇ�͔z��ɂȂ�)
	cap >> frame;
	arSetup(frame);

	while (1)
	{
		cap >> frame;
		cvtColor(frame, cvImg, CV_BGR2BGRA);		//	ARTK�ɓn�����߂̕ϊ�
		arImg = (ARUint8*)(cvImg.data);				//	ARTK�ɉ摜�f�[�^�̂ݓn��

		// �J�����摜�̃o�b�t�@�ւ̕`��
		argDrawMode2D();
		argDispImage(arImg, 0, 0);

		int	markerNum;								//	���o���ꂽ�}�[�J�[��
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
			drawObject();
		}

		// OpenGL�o�b�t�@�̓��e���摜�Ƃ��Ď擾
		glReadBuffer(GL_BACK);
		glReadPixels(
			0, 0,
			cvImg.cols, cvImg.rows,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			cvImg.data); // RGBA�Ŏ擾
		cvtColor(cvImg, cvImg, CV_RGBA2BGR);		// OpenCV��BGR���тɕϊ�
		flip(cvImg, cvImg, 0);						// OpenCV �ɍ��킹�ď㉺���]
		imshow("capture image", cvImg);
		if (waitKey(15) == ' ') break;
		
	}
	destroyAllWindows();
}
//=======================================================
// ���C�e�B���O
//=======================================================
void setupLighting(void)
{
	// ���C�g�̒�`
	GLfloat lt0_position[] = { 100.0, -200.0, 200.0, 0.0 };	// ���C�g0�̈ʒu
	GLfloat lt0_ambient[] = { 0.1, 0.1, 0.1, 1.0 };			// �@�@�@�@ ����
	GLfloat lt0_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };			// �@�@�@�@ �g�U��

	// ���C�g�̐ݒ�
	glLightfv(GL_LIGHT0, GL_POSITION, lt0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lt0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lt0_diffuse);
}


//=======================================================
// �}�e���A���̐ݒ�
//=======================================================
void setupMaterial(void)
{
	// �I�u�W�F�N�g�̍ގ�
	GLfloat mat_ambient[] = { 0.0, 0.0, 1.0, 1.0 };	// �ގ��̊���
	GLfloat mat_specular[] = { 0.0, 0.0, 1.0, 1.0 };	// ���ʌ�
	GLfloat mat_shininess[] = { 50.0 };				// ���ʌW��

	// �}�e���A���̐ݒ�
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

//	�I�u�W�F�N�g�̕`��
void drawObject(void)
{
	double glParam[16];		//	ARTK -> OpenGL�ϊ��s��

	// 3D�I�u�W�F�N�g��`�悷�邽�߂̏���
	argDrawMode3D();
	argDraw3dCamera(0, 0);

	// �A�ʏ���
	glClearDepth(1.0);					// �f�v�X�o�b�t�@�̏����l
	glClear(GL_DEPTH_BUFFER_BIT);		// �f�v�X�o�b�t�@�̏�����
	glEnable(GL_DEPTH_TEST);			// �A�ʏ����E�L��
	glDepthFunc(GL_LEQUAL);			// �f�v�X�e�X�g

	// �ϊ��s��̓K�p
	argConvGlpara(patt.trans, glParam);	// ARToolKit����OpenGL�̍s��ɕϊ�
	glMatrixMode(GL_MODELVIEW);			// �s��ϊ����[�h�E���f���r���[
	glLoadMatrixd(glParam);				// �ǂݍ��ލs����w��

	// �}�[�J���r���[���W�ϊ��s���\��
	static int h_count;
	if (h_count > 10){		// ��ʂɏo�Ă���̖h�~�p
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

	// ���C�e�B���O
	setupLighting();			// ���C�g�̒�`
	glEnable(GL_LIGHTING);		// ���C�e�B���O�E�L��
	glEnable(GL_LIGHT0);		// ���C�g0�E�I��

	// �I�u�W�F�N�g�̍ގ�
	setupMaterial();

	// 3D�I�u�W�F�N�g�̕`��
	glRotated(90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, 20.0);	// �}�[�J�̏�ɍڂ��邽�߂�Z�����i�}�[�J����j��20.0[mm]�ړ�
	glutSolidTeapot(50.0);			// �\���b�h�L���[�u��`��i1�ӂ̃T�C�Y50[mm]�j

	// �I������
	glDisable(GL_LIGHTING);			// ���C�e�B���O�E����
	glDisable(GL_DEPTH_TEST);		// �f�v�X�e�X�g�E����

}
//	ARTK�̏�����
void arSetup(Mat& camImg)
{
	ARParam wparam;		// �J�����p�����[�^
	int xsize, ysize;

	//	AR�p�^�[���̃Z�b�g�A�b�v
	patt.name = "Data/patt.hiro";
	patt.center[0] = 0.0; patt.center[1] = 0.0;
	patt.width = 80.0;

	// �E�B���h�E�T�C�Y�̎擾
	xsize = camImg.cols; ysize = camImg.rows;

	// �J�����p�����[�^�̐ݒ�
	if (arParamLoad(cparamName, 1, &wparam) < 0)
	{
		printf("�J�����p�����[�^�̓ǂݍ��݂Ɏ��s���܂���\n");
		exit(0);
	}

	// �J�����p�����[�^�̃T�C�Y����
	arParamChangeSize(&wparam, xsize, ysize, &cparam);
	// �J�����p�����[�^�̏�����
	arInitCparam(&cparam);
	printf("*** Camera Parameter ***\n");
	arParamDisp(&cparam);

	// �p�^�[���t�@�C���̃��[�h
	if ((patt.id = arLoadPatt(patt.name)) < 0)
	{
		printf("�p�^�[���t�@�C���̓ǂݍ��݂Ɏ��s���܂���\n");
		exit(0);
	}
	// gsub���C�u�����̏�����
	argInit(&cparam, 1.0, 0, 0, 0, 0);


}
//	��Â̎�@��臒l��Ԃ��֐�
int thresholdOtsu(Mat &srcImg)
{
	Mat grayImg;
	cvtColor(srcImg, grayImg, CV_BGR2GRAY);
	return (int)threshold(grayImg, grayImg, 128, 255, THRESH_BINARY | THRESH_OTSU);
}