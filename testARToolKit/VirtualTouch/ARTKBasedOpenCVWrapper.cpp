#include "ARTKBasedOpenCVWrapper.h"

ARPattern patt;

/* �J�����p�����[�^ */
static char	*cparamName = "Data/camera_para.dat";		// �J�����p�����[�^�t�@�C��
ARParam	cparam;										// �J�����p�����[�^

//	ARTK�̏�����
bool arSetup(Mat& camImg)
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
//		printf("�J�����p�����[�^�̓ǂݍ��݂Ɏ��s���܂���\n");
		return false;
	}

	// �J�����p�����[�^�̃T�C�Y����
	arParamChangeSize(&wparam, xsize, ysize, &cparam);
	// �J�����p�����[�^�̏�����
	arInitCparam(&cparam);
//	printf("*** Camera Parameter ***\n");
//	arParamDisp(&cparam);

	// �p�^�[���t�@�C���̃��[�h
	if ((patt.id = arLoadPatt(patt.name)) < 0)
	{
//		printf("�p�^�[���t�@�C���̓ǂݍ��݂Ɏ��s���܂���\n");
		return false;
	}
	// gsub���C�u�����̏�����
	argInit(&cparam, 1.0, 0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	return true;
}

//	AR�`��J�n�R�}���h
//	�g�����͎��̒ʂ�
//
//	arBeginObjectRender();
//	{
//		modelDraw();
//	}
//	arEndObjectRender();
void arBeginObjectRender(void)
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
}

//	AR�`��I���R�}���h
void arEndObjectRender(void)
{
	glDisable(GL_LIGHTING);			// ���C�e�B���O�E����
	glDisable(GL_DEPTH_TEST);		// �f�v�X�e�X�g�E����
}

//	cv::Mat -> ARUint8( -> OpenGL�o�b�t�@)
void cvtImageCV2AR(Mat& cvImg, ARUint8* arImg)
{
	Mat cvTemp;
	cvtColor(cvImg, cvTemp, CV_BGR2BGRA);		//	ARTK�ɓn�����߂̕ϊ�
	arImg = (ARUint8*)(cvTemp.data);			//	ARTK�ɉ摜�f�[�^�̂ݓn��
	// �J�����摜�̃o�b�t�@�ւ̕`��
	argDrawMode2D();
	argDispImage(arImg, 0, 0);
}

//	ARUint8 -> cv::Mat
void cvtImageAR2CV(ARUint8* arImg, Mat& cvImg)
{
	memcpy(cvImg.data, arImg, cvImg.rows * cvImg.cols * cvImg.channels());
}

// OpenGL�o�b�t�@�̓��e���摜�Ƃ��Ď擾
void readImageBuffer(Mat& cvImg)
{
	glReadBuffer(GL_BACK);
	glReadPixels(
		0, 0,
		cvImg.cols, cvImg.rows,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		cvImg.data);							// RGBA�Ŏ擾
	//	�ȉ��͎g�p����J�����ɂ���ēK�X�ς���
	cvtColor(cvImg, cvImg, CV_RGBA2BGR);		// OpenCV��BGR���тɕϊ�
	flip(cvImg, cvImg, 0);						// OpenCV�ɍ��킹�ď㉺���]
}
//	��Â̎�@��臒l��Ԃ��֐�
int thresholdOtsu(Mat &srcImg)
{
	Mat grayImg;
	cvtColor(srcImg, grayImg, CV_BGR2GRAY);
	return (int)threshold(grayImg, grayImg, 128, 255, THRESH_BINARY | THRESH_OTSU);
}