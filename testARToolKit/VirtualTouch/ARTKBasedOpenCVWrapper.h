#ifndef _ARTKBasedOpenCVWrapper_H
#define _ARTKBasedOpenCVWrapper_H

#include "ARToolKitAdapter.h"
#include "OpenCVAdapter.h"

extern ARPattern patt;
extern ARParam	cparam;

bool arSetup(Mat&);
void arBeginObjectRender(void);
void arEndObjectRender(void);
void cvtImageCV2AR(Mat& cvImg, ARUint8* arImg);
void cvtImageAR2CV(ARUint8* arImg, Mat& cvimg);
void readImageBuffer(Mat& cvImg);
void getDepthMap(Mat& depthMap);
void getClip(double& nearClip, double& farClip);
void cvtDepth2Z(Mat& depthMap, Mat& zMap);
void getDepthImage(Mat& depthMap, Mat& depthImg);
int thresholdOtsu(Mat& srcImg);

#endif //_ARTKBasedOpenCVWrapper_H