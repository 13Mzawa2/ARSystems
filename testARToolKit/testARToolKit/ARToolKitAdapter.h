#pragma once

#ifdef _DEBUG
#pragma comment(lib,"libARd.lib")
#pragma comment(lib,"libARgsubd.lib")
#pragma comment(lib,"libARgsub_lited.lib")
#pragma comment(lib,"libARgsubUtild.lib")
#pragma comment(lib,"libARvideod.lib")
#pragma comment(linker,"/NODEFAULTLIB:libcmtd.lib")
#else
//#pragma comment(lib, "glut32.lib")
#pragma comment(lib,"libAR.lib")
#pragma comment(lib,"libARgsub.lib")
#pragma comment(lib,"libARgsub_lite.lib")
#pragma comment(lib,"libARgsubUtil.lib")
#pragma comment(lib,"libARvideo.lib")
#pragma comment(linker,"/NODEFAULTLIB:libcmt.lib")
#endif

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
//#include <iostream>

//#include <GL\GL.h>
//#include <GL\GLU.h>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <AR\ar.h>				//	ARToolKit�̊�{�T�u���[�`��
#include <AR\arMulti.h>			//	�}���`�}�[�J�[�p
#include <AR\gsub.h>			//	OpenGL�ł̕`��T�u���[�`��
#include <AR\gsub_lite.h>		//	ARToolKit�̂��߂̗L�p��OpenGL���[�`��
#include <AR\gsubUtil.h>		//	OpenGL�̃��[�e�B���e�B
#include <AR\matrix.h>			//	�s�񉉎Z���[�`��
#include <AR\param.h>			//	ARToolKit�̃O���[�o���p�����[�^
#include <AR\video.h>			//	�r�f�I�f�o�C�X�T�u���[�`��
