#ifndef RIPPLINGCOMPUTE_H_
#define RIPPLINGCOMPUTE_H_

__device__
void computeRippling ( uchar4& ptrColor, int dim, int i, int j, float t ) {
  float fx = i - dim / 2.;
  float fy = j - dim / 2.;

  float d = sqrt ( fx * fx + fy * fy );

  float rip = 128 + 127 * ( cos ( ( d / 10. ) - ( t / 7 ) ) / ( ( d / 10 ) + 1 ) );
  ptrColor.x = ptrColor.y = ptrColor.z = rip;
  ptrColor.w = 255;
}
/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
#endif
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
