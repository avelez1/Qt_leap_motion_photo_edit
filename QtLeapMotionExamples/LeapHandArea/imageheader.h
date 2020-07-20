#ifndef IMAGEHEADER_H
#define IMAGEHEADER_H

#include <QObject>
#include <QDir>
#include "Image22.h"
#include "filtering.h"
#include "basicImageManipulation.h"
#include <iostream>

class MyObject : public QObject{
   Q_OBJECT
public:
    explicit MyObject (QObject* parent = 0) : QObject(parent) {}
    string path = "/Users/alexandriavelez/Desktop/QtLeapMotionLibrary/QtLeapMotionExamples/LeapHandArea/image.png";
    string workingpath = "/Users/alexandriavelez/Desktop/QtLeapMotionLibrary/QtLeapMotionExamples/LeapHandArea/working.png";

    Q_INVOKABLE int _brightness_(float factor){
        QString str = QDir::currentPath();
        Image22 im(path);
        Image22 im2 = brightness(im, factor);
        im2.write(workingpath);

        return 1;
    }

    Q_INVOKABLE int _contrast_(float factor, float midpoint){
        Image22 im(path);
        Image22 im2 = contrast(im, factor, midpoint);
        im2.write(workingpath);

        return 1;
    }

    Q_INVOKABLE int _saturate_(float k){
        Image22 im(path);
        Image22 im2 = saturate(im, k);
        im2.write(workingpath);

        return 1;
    }

    Q_INVOKABLE int _color2gray_(){
        Image22 im(path);
        Image22 im2 = color2gray(im);
        im2.write(workingpath);

        return 1;
    }

    Q_INVOKABLE int _gaussianBlur_2D_(float sigma, float truncate){
        Image22 im(path);
        Image22 im2 = gaussianBlur_2D(im, sigma, truncate);
        im2.write(workingpath);

        return 1;
    }

    Q_INVOKABLE int _boxBlur_(int k){
        Image22 im(path);
        Image22 im2 = boxBlur(im, k);
        im2.write(workingpath);

        return 1;
    }

    Q_INVOKABLE int _unsharpMask_(float sigma, float truncate, float strength){
        Image22 im(path);
        Image22 im2 = unsharpMask(im, sigma, truncate, strength);
        im2.write(workingpath);

        return 1;
    }

    Q_INVOKABLE int _median_filter_(int k){
            Image22 im(path);
            Image22 im2 = median_filter(im, k);
            im2.write(workingpath);

        return 1;
    }

    Q_INVOKABLE int _scaleLin_(float k){
            Image22 im(path);
            Image22 im2 = scaleLin(im, k);
            im2.write(workingpath);

        return 1;
   }

    Q_INVOKABLE int create_working_folder(){
        Image22 im(path);
        im.write(workingpath);

        return 1;
    }

    Q_INVOKABLE int save_working_to_file(){
        Image22 im(path);
        im.write(workingpath);

        return 1;
    }
};

#endif // IMAGEHEADER_H
