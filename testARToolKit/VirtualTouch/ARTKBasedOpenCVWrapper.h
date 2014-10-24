#ifndef _ARTKBasedOpenCVWrapper_H
#define _ARTKBasedOpenCVWrapper_H

#include "ARToolKitAdapter.h"
#include "OpenCVAdapter.h"

extern ARPattern patt;
extern ARParam	cparam;

bool arSetup(Mat&);
void arBeginObjectRender(void);
void arEndObjectRender(void);
void cvtImageCV2AR(Mat&, ARUint8*);
void cvtImageAR2CV(ARUint8*, Mat&);
void readImageBuffer(Mat&);
int thresholdOtsu(Mat&);

#endif //_ARTKBasedOpenCVWrapper_H