/* --------------------------------------------------------------------------
 * File:    basicImageManipulation.h
 * Created: 2015-09-23
 * --------------------------------------------------------------------------
 *
 *
 *
 * ------------------------------------------------------------------------*/


#ifndef __basicImageManipulation__h
#define __basicImageManipulation__h

#include "Image22.h"
#include <iostream>
#include <math.h>

using namespace std;

// --------- HANDOUT PS01 ------------------------------
Image22 brightness(const Image22 &im, float factor);
Image22 contrast(const Image22 &im, float factor, float midpoint = 0.5);

Image22 color2gray(const Image22 &im,
                 const std::vector<float> &weights = std::vector<float>{0.299, 0.587, 0.114});

std::vector<Image22> lumiChromi(const Image22 &im);
Image22 lumiChromi2rgb(const vector<Image22> & lc);
Image22 brightnessContrastLumi(const Image22 &im,
        float brightF, float contrastF, float midpoint = 0.3);
Image22 rgb2yuv(const Image22 &im);
Image22 yuv2rgb(const Image22 &im);
Image22 saturate(const Image22 &im, float k);
std::vector<Image22> spanish(const Image22 &im);
Image22 grayworld(const Image22 & in);
Image22 gamma_code(const Image22 &im, float gamma);
// ------------------------------------------------------

// --------- HANDOUT PS05 ------------------------------
Image22 scaleNN(const Image22 &im, float factor);
float interpolateLin(const Image22 &im, float x, float y, int z, bool clamp=false);
Image22 scaleLin(const Image22 &im, float factor);
Image22 scaleBicubic(const Image22 &im, float factor, float B, float C);
Image22 scaleLanczos(const Image22 &im, float factor, float a);
Image22 rotate(const Image22 &im, float theta);
// ------------------------------------------------------

#endif
