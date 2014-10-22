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
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <AR\ar.h>				//	ARToolKitの基本サブルーチン
#include <AR\arMulti.h>			//	マルチマーカー用
#include <AR\gsub.h>			//	OpenGLでの描画サブルーチン
#include <AR\gsub_lite.h>		//	ARToolKitのための有用なOpenGLルーチン
#include <AR\gsubUtil.h>		//	OpenGLのユーティリティ
#include <AR\matrix.h>			//	行列演算ルーチン
#include <AR\param.h>			//	ARToolKitのグローバルパラメータ
#include <AR\video.h>			//	ビデオデバイスサブルーチン
