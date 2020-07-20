/* --------------------------------------------------------------------------
 * File:    basicImageManipulation.cpp
 * Created: 2015-09-23
 * --------------------------------------------------------------------------
 *
 *
 *
 * ------------------------------------------------------------------------*/


#include "basicImageManipulation.h"
using namespace std;


// --------- HANDOUT PS05 ------------------------------
// -----------------------------------------------------
//
Image22 scaleNN(const Image22 &im, float factor){
    // --------- HANDOUT  PS05 ------------------------------
    // create a new image that is factor times bigger than the input by using
    // nearest neighbor interpolation.
    // return im;

    // --------- SOLUTION PS05 ------------------------------
    int ys, xs; // coordinate in the source image

    // Initialize a new Image22 factor times bigger (or smaller if factor <1)
    int nWidth  = floor(factor*im.width());
    int nHeight = floor(factor*im.height());
    Image22 out(nWidth, nHeight, im.channels());

    // For each pixel in the output
    for (int z=0; z<im.channels(); z++)
    for (int y=0; y<nHeight; y++)
    for (int x=0; x<nWidth; x++)
    {
        // Get the source pixel value.
        // If the output is factor times bigger, the source is 1/factor times
        // bigger...
        ys = round(1/factor * y);
        xs = round(1/factor * x);
        out(x,y,z) = im.smartAccessor(xs,ys,z,true);
    }

    return out;
}

float interpolateLin(const Image22 &im, float x, float y, int z, bool clamp){
     // --------- HANDOUT  PS05 ------------------------------
     // bilinear interpolation samples the value of a non-integral
     // position (x,y) from its four "on-grid" neighboring pixels.
     //  |           |
     // -1-----------2-
     //  |           |  *: my coordinates (x,y) are not integral
     //  |  *        |     since I am not on the pixel grid :(
     //  |           |  1: top-left
     //  |           |  2: top-right
     //  |           |  3: bottom-right
     // -4-----------3- 4: bottom-left, what are our coordinates?
     //  |           |    We are willing to share some color
     //                   information with * ! Of course, the pixel
     //                   closest to * should influence it more.
     //return 0.0f;

    // --------- SOLUTION PS05 ------------------------------
    // get the neighboring points
    int xf = floor(x); // floor
    int yf = floor(y);
    int xc = xf+1; //and ceil
    int yc = yf+1;

    // compute the distances of the point to the floor-extreme point
    float yalpha = y - yf;
    float xalpha = x - xf;

    // obtain the values at those points
    float tl = im.smartAccessor(xf, yf, z, clamp); // top-left
    float tr = im.smartAccessor(xc, yf, z, clamp); // ...
    float bl = im.smartAccessor(xf, yc, z, clamp);
    float br = im.smartAccessor(xc, yc, z, clamp);

    // compute the interpolations on the top and bottom
    float topL = tr*xalpha + tl*(1.0f - xalpha);
    float botL = br*xalpha + bl*(1.0f - xalpha);

    // compute the overall interpolation
    float retv = botL*yalpha + topL*(1.0f - yalpha);

    // return final float value
    return retv;
}

Image22 scaleLin(const Image22 &im, float factor){
    // --------- HANDOUT  PS05 ------------------------------
    // create a new image that is factor times bigger than the input by using
    // bilinear interpolation
    // return im;

    // --------- SOLUTION PS05 ------------------------------
    float ys, xs; // coordinate in the source image

    // Initialize a new Image22 factor times bigger (or smaller if factor <1)
    int nWidth  = floor(factor*im.width());
    int nHeight = floor(factor*im.height());
    Image22 im2(nWidth, nHeight, im.channels());

    // For each pixel in the output
    for (int z=0; z<im.channels(); z++)
    for (int y=0; y<nHeight; y++)
    for (int x=0; x<nWidth; x++)
    {
        // Get the source pixel value.
        ys = 1/factor * y;
        xs = 1/factor * x;
        im2(x,y,z) = interpolateLin(im, xs, ys, z);
    }

    // return new image
    return im2;
}

Image22 scaleBicubic(const Image22 &im, float factor, float B, float C) {
    // --------- HANDOUT  PS05 ------------------------------
    // create a new image that is factor times bigger than the input by using
    // a bicubic filter kernel with Mitchell and Netravali's parametrization
    // see "Reconstruction filters in computer graphics", Mitchell and Netravali 1988
    // or http://entropymine.com/imageworsener/bicubic/
    // return im;

    //pre-compute coefficients
    float A3 =   2 -      1.5f * B -  C;
    float A2 = - 3 +         2 * B +  C;
    float A0 =   1 -  0.33333f * B;

    float B3 = -0.166666f * B -     C;
    float B2 =              B + 5 * C;
    float B1 =         -2 * B - 8 * C;
    float B0 =  1.333333f * B + 4 * C;

    //lambda function to compute the kernel weight
    auto computeK = [&](float x)->float {
        float kx = 0.0f;
        float xabs = abs(x);
        float x3 = pow(xabs, 3);
        float x2 = pow(xabs, 2);
        if( xabs < 1.0f) {
          kx = A3 * x3 + A2 * x2 + A0;
        }else if( 1 <= xabs && xabs < 2.0f)  {
          kx = B3 * x3 + B2 * x2 + B1 * xabs + B0;
        }
        return kx;
    };

    int nWidth  = floor(factor*im.width());
    int nHeight = floor(factor*im.height());
    Image22 out(nWidth, nHeight, im.channels());

    for(int y=0; y<nHeight; y++)
    for(int x=0; x<nWidth; x++)
    {
        // Get the source pixel value.
        float ysrc = 1/factor * y;
        float xsrc = 1/factor * x;
        int xstart = (int) (floor(xsrc) - 2);
        int xend   = (int) (floor(xsrc) + 2);
        int ystart = (int) (floor(ysrc) - 2);
        int yend   = (int) (floor(ysrc) + 2);
        for(int xs = xstart; xs <= xend; ++xs)
        for(int ys = ystart; ys <= yend; ++ys)
        {
            float w = computeK(xsrc - xs) * computeK(ysrc - ys);
            for(int z=0; z<im.channels(); z++)
                out(x,y,z) += im.smartAccessor(xs, ys, z, false) * w;
        }
    }

    return out;

}

Image22 scaleLanczos(const Image22 &im, float factor, float a) {
    // --------- HANDOUT  PS05 ------------------------------
    // create a new image that is factor times bigger than the input by using
    // a Lanczos filter kernel
    // return im;

    //lambda function to compute the kernel weight
    float PI2 = pow(M_PI,2);
    float PI_A = M_PI / a;
    auto computeK = [&](float x)->float {
        float kx = 1.0f;
        if( x!= 0.0f &&  -a <= x && x < a) {
            kx = a * sin(M_PI * x) * sin(x * PI_A) /( PI2 * x * x);
        }
        return kx;
    };

    int nWidth  = floor(factor*im.width());
    int nHeight = floor(factor*im.height());
    Image22 out(nWidth, nHeight, im.channels());

    for(int y=0; y<nHeight; y++)
    for(int x=0; x<nWidth; x++)
    {
        // Get the source pixel value.
        float ysrc = 1/factor * y;
        float xsrc = 1/factor * x;
        int xstart = (int) (floor(xsrc) - a + 1);
        int xend   = (int) (floor(xsrc) + a);
        int ystart = (int) (floor(ysrc) - a + 1);
        int yend   = (int) (floor(ysrc) + a);
        for(int xs = xstart; xs <= xend; ++xs)
        for(int ys = ystart; ys <= yend; ++ys)
        {
            float w = computeK(xsrc - xs) * computeK(ysrc - ys);
            for (int z=0; z<im.channels(); z++)
              out(x,y,z) += im.smartAccessor(xs, ys, z, false) * w;
        }
    }

    return out;
}

Image22 rotate(const Image22 &im, float theta) {
    // --------- HANDOUT  PS05 ------------------------------
    // rotate an image around its center by theta

    // // center around which to rotate
    // float centerX = (im.width()-1.0)/2.0;
    // float centerY = (im.height()-1.0)/2.0;

    // return im; // changeme

    // --------- SOLUTION PS05 ------------------------------

    // center around which to rotate
    float centerX = (im.width()-1.0)/2.0;
    float centerY = (im.height()-1.0)/2.0;

    // get new image
    Image22 imR(im.width(), im.height(), im.channels());

    // For each pixel in the output
    float yR, xR; // rotated coordinates
    for (int x=0; x<im.width(); x++)
    for (int y=0; y<im.height(); y++)
    for (int z=0; z<im.channels(); z++)
    {

        // compute the x and y values from the original image
        xR = (static_cast<float>(x) - centerX)*cos(theta) + (centerY - static_cast<float>(y))*sin(theta) + centerX;
        yR = centerY - ( -(static_cast<float>(x) - centerX)*sin(theta) + (centerY - static_cast<float>(y))*cos(theta) );

        // interpolate the point
        imR(x,y,z) = interpolateLin(im, xR, yR, z);
    }

    return imR;
}

// -----------------------------------------------------
// --------- END --- PS05 ------------------------------


// --------- HANDOUT PS01 ------------------------------
// -----------------------------------------------------

// Change the brightness of the image
// const Image22 & means a reference to im will get passed to the function,
// but the compiler won't let you modify it within the function.
// So you will return a new image
Image22 brightness(const Image22 &im, float factor) {
    // // --------- HANDOUT  PS01 ------------------------------
    // // Image22 output(im.width(), im.height(), im.channels());
    // // Modify image brightness
    // // return output;
    // return Image22(1,1,1); // Change this

    // --------- SOLUTION PS01 ------------------------------
    return im * factor;
}

Image22 contrast(const Image22 &im, float factor, float midpoint) {
    // // --------- HANDOUT  PS01 ------------------------------
    // // Image22 output(im.width(), im.height(), im.channels());
    // // Modify image contrast
    // // return output;
    // return Image22(1,1,1); //Change this

    // --------- SOLUTION PS01 ------------------------------
    return (im - midpoint) * factor + midpoint;
}

Image22 color2gray(const Image22 &im, const std::vector<float> &weights) {
    // // --------- HANDOUT  PS01 ------------------------------
    // // Image22 output(im.width(), im.height(), 1);
    // // Convert to grayscale
    // return Image22(1,1,1); //Change this

    // --------- SOLUTION PS01 ------------------------------
    Image22 output(im.width(), im.height(), 1);
    for (int i = 0 ; i < im.width(); i++ ) {
        for (int j = 0 ; j < im.height(); j++ ) {
            output(i,j,0) = im(i,j,0) * weights[0] + im(i,j,1) * weights[1] + im(i,j,2) *weights[2];
        }
    }
    return output;
}

// For this function, we want two outputs, a single channel luminance image
// and a three channel chrominance image. Return them in a vector with luminance first
std::vector<Image22> lumiChromi(const Image22 &im) {
    // // --------- HANDOUT  PS01 ------------------------------
    // // Create the luminance image
    // // Create the chrominance image
    // // Create the output vector as (luminance, chrominance)
    // return std::vector<Image22>(); //Change this

    // --------- SOLUTION PS01 ------------------------------

    // Create the luminance
    Image22 im_luminance = color2gray(im);

    // Create chrominance images
    // We copy the input as starting point for the chrominance
    Image22 im_chrominance = im;
    for (int c = 0 ; c < im.channels(); c++ ) {
        for (int y = 0 ; y < im.height(); y++) {
            for (int x = 0 ; x < im.width(); x++) {
                im_chrominance(x,y,c) = im_chrominance(x,y,c) / im_luminance(x,y);
            }
        }
    }

    // Stack luminance and chrominance in the output vector, luminance first
    return std::vector<Image22>{im_luminance, im_chrominance};
}

Image22 lumiChromi2rgb(const vector<Image22> & lc) {
    // luminance is lc[0]
    // chrominance is lc[1]

    // Create chrominance images
    // We copy the input as starting point for the chrominance
    Image22 im = Image22(lc[1].width(), lc[1].height(), lc[1].channels());
    for (int c = 0 ; c < im.channels(); c++ ) {
      for (int y = 0 ; y < im.height(); y++) {
        for (int x = 0 ; x < im.width(); x++) {
            im(x,y,c) = lc[1](x,y,c) * lc[0](x,y);
        }
      }
    }
    return im;
}


// Modify brightness then contrast
Image22 brightnessContrastLumi(const Image22 &im, float brightF, float contrastF, float midpoint) {
    // // --------- HANDOUT  PS01 ------------------------------
    // // Modify brightness, then contrast of luminance image
    // return Image22(1,1,1); // Change this

    // --------- SOLUTION PS01 ------------------------------
    // Separate luminance and chrominance
    std::vector<Image22> lumi_chromi = lumiChromi(im);
    Image22 im_luminance             = lumi_chromi[0];
    Image22 im_chrominance           = lumi_chromi[1];

    // Process the luminance channel
    im_luminance = brightness(im_luminance, brightF);
    im_luminance = contrast(im_luminance, contrastF, midpoint);

    // Multiply the chrominance with the new luminance to get the final image
    for (int i = 0 ; i < im.width(); i++ ){
        for (int j = 0 ; j < im.height(); j++) {
            for (int c = 0; c < im.channels(); c++) {
                im_chrominance(i,j,c) = im_chrominance(i,j,c) * im_luminance(i,j);
            }
        }
    }
    // At this point, im_chrominance olds the complete processed image
    return im_chrominance;
}


Image22 rgb2yuv(const Image22 &im) {
    // // --------- HANDOUT  PS01 ------------------------------
    // // Create output image of appropriate size
    // // Change colorspace
    // return Image22(1,1,1); // Change this

    // --------- SOLUTION PS01 ------------------------------
    Image22 output(im.width(), im.height(), im.channels());
    for (int j = 0 ; j < im.height(); j++) {
        for (int i = 0 ; i < im.width(); i++) {
            output(i,j,0) =   0.299 * im(i,j,0) + 0.587 * im(i,j,1) + 0.114 * im(i,j,2);
            output(i,j,1) = - 0.147 * im(i,j,0) - 0.289 * im(i,j,1) + 0.436 * im(i,j,2);
            output(i,j,2) =   0.615 * im(i,j,0) - 0.515 * im(i,j,1) - 0.100 * im(i,j,2);
        }
    }
    return output;
}


Image22 yuv2rgb(const Image22 &im) {
    // // --------- HANDOUT  PS01 ------------------------------
    // // Create output image of appropriate size
    // // Change colorspace
    // return Image22(1,1,1); // Change this

    // --------- SOLUTION PS01 ------------------------------
    Image22 output(im.width(), im.height(), im.channels());
    for (int j = 0 ; j < im.height(); j++) {
        for (int i = 0; i < im.width(); i++)
        {
            output(i,j,0) =  im(i,j,0) + 0     * im(i,j,1) + 1.14  * im(i,j,2);
            output(i,j,1) =  im(i,j,0) - 0.395 * im(i,j,1) - 0.581 * im(i,j,2);
            output(i,j,2) =  im(i,j,0) + 2.032 * im(i,j,1) + 0     * im(i,j,2);
        }
    }
    return output;
}


Image22 saturate(const Image22 &im, float factor) {
    // // --------- HANDOUT  PS01 ------------------------------
    // // Create output image of appropriate size
    // // Saturate image
    // // return output;
    // return Image22(1,1,1); // Change this

    // --------- SOLUTION PS01 ------------------------------
    Image22 output = rgb2yuv(im); // Change colorspace
    for (int i = 0 ; i < im.width(); i++) {
        for (int j = 0 ; j < im.height(); j++) {
            output(i,j,1) = output(i,j,1) * factor;
            output(i,j,2) = output(i,j,2) * factor;
        }
    }
    output = yuv2rgb(output); // Back to RGB
    return output;
}


// Return two images in a C++ vector
std::vector<Image22> spanish(const Image22 &im) {
    // // --------- HANDOUT  PS01 ------------------------------
    // // Remember to create the output images and the output vector
    // // Push the images onto the vector
    // // Do all the required processing
    // // Return the vector, color image first
    // return std::vector<Image22>(); //Change this

    // --------- SOLUTION PS01 ------------------------------
    // Extract the luminance
    Image22 output_L = color2gray(im);

    // Convert to YUV for manipulation
    Image22 output_C = rgb2yuv(im);

    for (int j = 0; j < im.height(); j++) {
        for (int i = 0; i < im.width(); i++) {
            output_C(i,j,0) = 0.5;              // constant luminance
            output_C(i,j,1) = -output_C(i,j,1); // opposite chrominance
            output_C(i,j,2) = -output_C(i,j,2); // opposite chrominance
        }
    }
    // Convert back to RGB
    output_C = yuv2rgb(output_C);

    // Location of the black dot
    int bdot_x = floor(im.width()/2);
    int bdot_y = floor(im.height()/2);

    // Add the black dot to Luminance, and Chrominance images
    output_L(bdot_x, bdot_y,0) = 0.0f;
    output_C(bdot_x, bdot_y,0) = 0.0f; // black is 0
    output_C(bdot_x, bdot_y,1) = 0.0f;
    output_C(bdot_x, bdot_y,2) = 0.0f;

    // Pack the images in a vector, chrominance first
    return std::vector<Image22>{output_C, output_L} ;
}


// White balances an image using the gray world assumption
Image22 grayworld(const Image22 & im) {
    // // --------- HANDOUT  PS01 ------------------------------
    // Implement automatic white balance by multiplying each channel
    // of the input by a factor such that the three channel of the output image
    // have the same mean value. The mean value of the green channel
    // is taken as reference.
    // return Image22(1,1,1); // Change this

    // --------- SOLUTION PS01 ------------------------------
    // Compute the mean per channel
    float mean_r = 0, mean_g = 0, mean_b = 0;
    float N = im.width()*im.height();
    for (int j = 0 ; j < im.height(); j++) {
        for (int i = 0 ; i < im.width(); i++) {
            mean_r += im(i,j,0);
            mean_g += im(i,j,1);
            mean_b += im(i,j,2);
        }
    }
    mean_r /= N;
    mean_g /= N;
    mean_b /= N;

    Image22 output = im;
    for (int j = 0 ; j < im.height();j ++) {
        for (int i = 0 ; i < im.width(); i++) {
            output(i,j,0) = output(i,j,0)/mean_r*mean_g;
            // dont process output(i,j,1), since the mean of
            // the green channel is already at the right value
            output(i,j,2) = output(i,j,2)/mean_b*mean_g;
        }
    }
    return output;
}


Image22 gamma_code(const Image22 &im, float gamma) {
    // // --------- HANDOUT  PS01 ------------------------------
    // Image22 output(im.width(), im.height(), im.channels());
    // Gamma encodes the image
    // return output;

    // --------- SOLUTION PS01 ------------------------------
    Image22 output = Image22(im.width(), im.height(), im.channels());
    for (int i = 0; i < im.number_of_elements(); ++i){
        output(i) = pow(im(i), (1/gamma));
    }
    return output;
}

// -----------------------------------------------------
// --------- END --- PS01 ------------------------------
