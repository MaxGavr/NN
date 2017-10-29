#pragma once

#include <iostream>
#include <vector>
#include <armadillo>
#include <png++/png.hpp>

#include "Rectangle.h"

using namespace std;
using namespace arma;

class ImageProcessor {
  private:
    int RGB;
    int imageWidth;
    int imageHeight;
    int n;
    int m;
    int p;
    double e;
    int L;
    int nmRGB;
    double a;

    vector<ImageSegment> imageSegments;

    mat W;
    mat W_;


    int convertRGBToOutput(double rgb);
    double getErrorDegree(mat deltaX);
    void createWeightMatrix();
    double convertColor(int color);
    void normalizeMatrix(mat matrix);
    void normalizeMatrixs();

  public:
    ImageProcessor(char const *patch, int n, int m, int p, double e, double a);

    void run();
    void createOutputImage();
};
