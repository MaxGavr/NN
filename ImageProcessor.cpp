#include <iostream>
#include <vector>
#include <cmath>

#include "ImageProcessor.h"
#include "Rectangle.h"

using namespace std;

ImageProcessor::ImageProcessor(char const *path, int _n, int _m, int _p, double _e, double _a)
    : RGB(3), n(_n), m(_m), p(_p), e(_e), a(_a) {

    png::image<png::rgb_pixel>  src(path);
    imageWidth = src.get_width();
    imageHeight = src.get_height();

    for(int startX = 0; startX < imageWidth; startX += m) {
        for(int startY = 0; startY < imageHeight; startY += n) {
            ImageSegment segment(startX, startY);
            for(int i = startX; i < startX + m; i++) {
                for(int j = startY; j < startY + n; j++) {
                    if(i < imageWidth && j < imageHeight) {
                        segment.addElement(convertColor(src[j][i].red));
                        segment.addElement(convertColor(src[j][i].green));
                        segment.addElement(convertColor(src[j][i].blue));
                    } else {
                        segment.addElement(-1);
                        segment.addElement(-1);
                        segment.addElement(-1);
                    }
                }
            }
            segment.createMatrixX();
            imageSegments.push_back(segment);
        }
    }
    L = imageSegments.size();
    nmRGB = n * m * RGB;
    createWeightMatrix();
}

void ImageProcessor::run() {
    double step;
    double step_;
    double E;
    int iteration = 0;
    do {
        E = 0;
        for(int index = 0; index < L; index++) {
            mat X = imageSegments[index].getX();
            mat Y = X * W;
            mat X_ = Y * W_;
            mat deltaX = X_ - X;

            step_ = step = a;

            W = W - (step * X.t() * deltaX * W_.t());
            W_ = W_ - (step_ * Y.t() * deltaX);
        }
        // count error after correction
        for(int index = 0; index < L; index++) {
            mat X = imageSegments[index].getX();
            mat Y = X * W;
            mat X_ = Y * W_;
            mat deltaX = X_ - X;
            E += getErrorDegree(deltaX);
        }
        iteration++;
        cout << "Iteration: " << iteration << " Error: " << E << endl;
    } while(E > e);
    double z = (1.0 * n * m * RGB * L) / ((n * m * RGB + L) * p + 2);
    cout << "Z = " << z << endl;;
}

void ImageProcessor::createOutputImage() {
    png::image<png::rgb_pixel> image(imageWidth, imageHeight);
    float color[3];
    for(int index = 0; index < L; index++) {
        int startX = imageSegments[index].getStartX();
        int startY = imageSegments[index].getStartY();
        mat X = imageSegments[index].getX();
        mat Y = X * W;
        mat X_ = Y * W_;
        int pixel = 0;
        for(int i = startX; i < m + startX; i++) {
            for(int j = startY; j < n + startY; j++) {
                color[0] = convertRGBToOutput(X_(0, pixel++));
                color[1] = convertRGBToOutput(X_(0, pixel++));
                color[2] = convertRGBToOutput(X_(0, pixel++));
                if(i < imageWidth && j < imageHeight) {
                    image.set_pixel(i, j, png::rgb_pixel(color[0], color[1], color[2]));
                }
            }
        }
    }
    image.write("output.png");
}

int ImageProcessor::convertRGBToOutput(double color) {
    double ans = (255 * (color + 1) / 2);
    if(ans < 0) {
        ans = 0;
    }
    if(ans > 255) {
        ans = 255;
    }
    return (int)ans;
}

double ImageProcessor::getErrorDegree(mat deltaX) {
    double err = 0;
    for(int i = 0; i < nmRGB; i++) {
        err += pow(deltaX(0, i), 2);
    }
    return err;
}

void ImageProcessor::createWeightMatrix() {
    srand(time(nullptr));
    W = randu<mat>(nmRGB, p);
    for(int i = 0; i < nmRGB; i++) {
        for(int j = 0; j < p; j++)
            W(i, j) = (((double)rand() / RAND_MAX) * 2 - 1) * 0.1;;
    }
    W_ = W.t();
}

double ImageProcessor::convertColor(int color) {
    return ((2.0 * color / 255) - 1);
}
