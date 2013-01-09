#ifndef KERNELFILTERIMAGECUDAVIEWER_H_
#define KERNELFILTERIMAGECUDAVIEWER_H_
#include "ImageCudaMOOs_A.h"
#include "CaptureVideo.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class KernelFilterImageCudaViewer: public ImageCudaMOOs_A {
public:
  KernelFilterImageCudaViewer ( unsigned int w, unsigned int h, const std::string filename );
  virtual ~KernelFilterImageCudaViewer () {}
  void animationStep ( bool& isNeedUpdateView );
private:
  void fillImageGL ( uchar4* ptrDevImageGL, int w, int h );
  std::string _filename;
  CaptureVideo _capture;
};

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
