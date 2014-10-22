#include "ARToolKitAdapter.h"

// �O���[�o���ϐ�
/* �J�����\�� */
char *vconf_name = "Data/WDM_camera_flipV.xml";	// �r�f�I�f�o�C�X�̐ݒ�t�@�C��
int  xsize;											// �E�B���h�E�T�C�Y
int  ysize;											// �E�B���h�E�T�C�Y
int  thresh = 100;									// 2�l����臒l
int  count = 0;										// �����t���[����

/* �J�����p�����[�^ */
char *cparam_name = "Data/camera_para.dat";			// �J�����p�����[�^�t�@�C��
ARParam cparam;										// �J�����p�����[�^

/* �p�^�[���t�@�C�� */
char   *patt_name = "Data/patt.hiro";				// �p�^�[���t�@�C��
int    patt_id;										// �p�^�[����ID
double patt_trans[3][4];							// ���W�ϊ��s��
double patt_center[2] = { 0.0, 0.0 };				// �p�^�[���̒��S���W
double patt_width = 80.0;						// �p�^�[���̃T�C�Y�i�P�ʁF�����j

// �v���g�^�C�v�錾
void Init(void);
void MainLoop(void);
void SetupLighting(void);
void SetupMaterial(void);
void KeyEvent(unsigned char key, int x, int y);
void MouseEvent(int button, int state, int x, int y);
void Cleanup(void);
void DrawObject(void);

//=======================================================
// main�֐�
//=======================================================
int main(int argc, char **argv)
{
	// GLUT�̏�����
	glutInit(&argc, argv);

	// AR�A�v���P�[�V�����̏�����
	Init();

	// �r�f�I�L���v�`���̊J�n
	arVideoCapStart();

	// ���C�����[�v�̊J�n
	argMainLoop(MouseEvent, KeyEvent, MainLoop);

	return 0;
}
//=======================================================
// �������֐�
//=======================================================
void Init(void)
{
	ARParam wparam;		// �J�����p�����[�^

	// �r�f�I�f�o�C�X�̐ݒ�
	if (arVideoOpen(vconf_name) < 0){
		printf("�r�f�I�f�o�C�X�̃G���[\n");
		exit(0);
	}

	// �E�B���h�E�T�C�Y�̎擾
	if (arVideoInqSize(&xsize, &ysize) < 0) exit(0);
	printf("Image size (x,y) = (%d,$d)\n", xsize, ysize);

	// �J�����p�����[�^�̐ݒ�
	if (arParamLoad(cparam_name, 1, &wparam) < 0){
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
	if ((patt_id = arLoadPatt(patt_name)) < 0){
		printf("�p�^�[���t�@�C���̓ǂݍ��݂Ɏ��s���܂���\n");
		exit(0);
	}

	// gsub���C�u�����̏�����
	argInit(&cparam, 1.0, 0, 0, 0, 0);

	// �E�B���h�E�^�C�g���̐ݒ�
	glutSetWindowTitle("ARTK_basic");
}
//=======================================================
// ���C�����[�v�֐�
//=======================================================
void MainLoop(void)
{
	ARUint8          *image;			// �J�����L���v�`���摜
	ARMarkerInfo     *marker_info;		// �}�[�J���
	int              marker_num;		// ���o���ꂽ�}�[�J�̐�
	int              j, k;
	static bool		 isFirstDetect = true;

	// �J�����摜�̎擾
	if ((image = (ARUint8 *)arVideoGetImage()) == NULL){
		arUtilSleep(2);
		return;
	}
	if (count == 0) arUtilTimerReset();
	count++;

	// �J�����摜�̕`��
	argDrawMode2D();
	argDispImage(image, 0, 0);

	// �}�[�J�̌��o�ƔF��
	if (arDetectMarker(image, thresh, &marker_info, &marker_num) < 0){
		Cleanup();
		exit(0);
	}

	// ���̉摜�̃L���v�`���w��
	arVideoCapNext();

	// �}�[�J�̈�v�x�̔�r
	k = -1;
	for (j = 0; j < marker_num; j++){
		if (patt_id == marker_info[j].id){
			if (k == -1) k = j;
			else if (marker_info[k].cf < marker_info[j].cf) k = j;
		}
	}

	// �}�[�J�[��������Ȃ������Ƃ�
	if (k == -1){
		argSwapBuffers();
		return;
	}

	// �}�[�J�̈ʒu�E�p���i���W�ϊ��s��j�̌v�Z
	if (isFirstDetect)
	{
		arGetTransMat(&marker_info[k], patt_center, patt_width, patt_trans);
	}
	else
	{
		arGetTransMatCont(&marker_info[k], patt_trans, patt_center, patt_width, patt_trans);
	}
	isFirstDetect = false;
	// 3D�I�u�W�F�N�g�̕`��
	DrawObject();

	// �o�b�t�@�̓��e����ʂɕ\��
	argSwapBuffers();
}
//=======================================================
// 3D�I�u�W�F�N�g�̕`����s���֐�
//=======================================================
void DrawObject(void)
{
	double gl_para[16];	// ARToolKit->OpenGL�ϊ��s��

	// 3D�I�u�W�F�N�g��`�悷�邽�߂̏���
	argDrawMode3D();
	argDraw3dCamera(0, 0);

	// �A�ʏ���
	glClearDepth(1.0);					// �f�v�X�o�b�t�@�̏����l
	glClear(GL_DEPTH_BUFFER_BIT);		// �f�v�X�o�b�t�@�̏�����
	glEnable(GL_DEPTH_TEST);			// �A�ʏ����E�L��
	glDepthFunc(GL_LEQUAL);			// �f�v�X�e�X�g

	// �ϊ��s��̓K�p
	argConvGlpara(patt_trans, gl_para);	// ARToolKit����OpenGL�̍s��ɕϊ�
	glMatrixMode(GL_MODELVIEW);			// �s��ϊ����[�h�E���f���r���[
	glLoadMatrixd(gl_para);				// �ǂݍ��ލs����w��

	// �}�[�J���r���[���W�ϊ��s���\��
	static int h_count;
	if (h_count > 10){		// ��ʂɏo�Ă���̖h�~�p
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

	// ���C�e�B���O
	SetupLighting();			// ���C�g�̒�`
	glEnable(GL_LIGHTING);	// ���C�e�B���O�E�L��
	glEnable(GL_LIGHT0);		// ���C�g0�E�I��

	// �I�u�W�F�N�g�̍ގ�
	SetupMaterial();

	// 3D�I�u�W�F�N�g�̕`��
	glRotated(90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, 20.0);	// �}�[�J�̏�ɍڂ��邽�߂�Z�����i�}�[�J����j��20.0[mm]�ړ�
	glutSolidTeapot(50.0);			// �\���b�h�L���[�u��`��i1�ӂ̃T�C�Y50[mm]�j

	// �I������
	glDisable(GL_LIGHTING);		// ���C�e�B���O�E����
	glDisable(GL_DEPTH_TEST);		// �f�v�X�e�X�g�E����
}

//=======================================================
// ���C�e�B���O
//=======================================================
void SetupLighting(void)
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
void SetupMaterial(void)
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


//=======================================================
// �L�[�{�[�h���͏����֐�
//=======================================================
void KeyEvent(unsigned char key, int x, int y)
{
	// ESC�L�[����͂�����A�v���P�[�V�����I��
	if (key == 0x1b){
		printf("*** %f (frame/sec)\n", (double)count / arUtilTimer());
		Cleanup();
		exit(0);
	}
}


//=======================================================
// �}�E�X���͏����֐�
//=======================================================
void MouseEvent(int button, int state, int x, int y)
{
	// ���͏�Ԃ�\��
	printf("�{�^���F%d ��ԁF%d ���W�F(x,y)=(%d,%d) \n", button, state, x, y);
}


//=======================================================
// �I�������֐�
//=======================================================
void Cleanup(void)
{
	arVideoCapStop();	// �r�f�I�L���v�`���̒�~
	arVideoClose();		// �r�f�I�f�o�C�X�̏I��
	argCleanup();		// ARToolKit�̏I������
}