/* -----------------------------------------------------------------
 * File:    filtering.h
 * Created: 2015-09-22
 * -----------------------------------------------------------------
 *
 * Image22 convolution and filtering
 *
 * ---------------------------------------------------------------*/


#ifndef __morphing__h
#define __morphing__h

#include <cmath>
#include <iostream>

#include "basicImageManipulation.h"
#include "Image22.h"

using namespace std;

// --------- HANDOUT  PS02 ------------------------------
class Filter {
public:
    //Constructor
    Filter(const vector<float> &fData, int fWidth, int fHeight);
    Filter(int fWidth, int fHeight); // kernel with all zero

    // Destructor. Because there is no explicit memory management here, this doesn't do anything
    ~Filter();

    // function to convolve your filter with an image
    Image22 convolve(const Image22 &im, bool clamp = true);

    // Accessors of the filter values
    const float & operator()(int x, int y) const;
    float & operator()(int x, int y);

// The following are functions and variables that are not accessible from outside the class
private:
    std::vector<float> kernel;
    int width;
    int height;
};
Image22 median_filter(const Image22 &im, int k, bool clamp = true);

// Box Blurring
Image22 boxBlur(const Image22 &im, int k, bool clamp = true);
Image22 boxBlur_filterClass(const Image22 &im, int k, bool clamp = true);

// Gradient Filter
Image22 gradientMagnitude(const Image22 &im, bool clamp = true);

// Gaussian Blurring
vector<float> gauss1DFilterValues(float sigma, float truncate);
vector<float> gauss2DFilterValues(float sigma, float truncate);
Image22 gaussianBlur_horizontal(const Image22 &im,
                              float sigma,
                              float truncate = 3.0,
                              bool clamp = true);
Image22 gaussianBlur_separable(const Image22 &im,
                             float sigma,
                             float truncate = 3.0,
                             bool clamp = true);
Image22 gaussianBlur_2D(const Image22 &im,
                      float sigma,
                      float truncate = 3.0,
                      bool clamp = true);

// Sharpen an Image22
Image22 unsharpMask(const Image22 &im,
                  float sigma,
                  float truncate = 3.0,
                  float strength = 1.0,
                  bool clamp = true);

// Bilaterial Filtering
Image22 bilateral(const Image22 &im,
                float sigmaRange = 0.1,
                float sigmaDomain = 1.0,
                float truncateDomain = 3.0,
                bool clamp = true);
Image22 bilaYUV(const Image22 &im,
              float sigmaRange = 0.1,
              float sigmaY = 1.0,
              float sigmaUV = 4.0,
              float truncateDomain = 3.0,
              bool clamp = true);

// Return impulse image of size k x k x 1
// returned image is all zeros (except at the center where it is white)
Image22 impulseImg(int k);
// ------------------------------------------------------


// --------- HANDOUT PS07 ------------------------------
Image22 maximum_filter(const Image22 &im, float maxiDiam);
Image22 gradientX(const Image22 &im, bool clamp = true);
Image22 gradientY(const Image22 &im, bool clamp = true);
// ------------------------------------------------------

#endif
