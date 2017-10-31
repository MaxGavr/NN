#pragma once

#include <vector>
#include <armadillo>
#include <png++/png.hpp>

#include "Rectangle.h"

using namespace std;

class NeuralNetwork
{
    using PngImage = png::image<png::rgb_pixel>;
    using Pixel = png::rgb_pixel;

public:
    NeuralNetwork(const char* pathToImage, int n, int m, int p, double e, double a);

    void processImage();
    void createOutputImage();

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

    vector<Segment> imageSegments;

    arma::mat W;
    arma::mat W_;

    Segment readSegment(const PngImage& image, int startX, int startY);

    double convertColor(int color);
    int convertColorReverse(double rgb);

    void createWeightMatrix();

    double getErrorDegree(arma::mat deltaX);

    void normalizeMatrix(arma::mat matrix);
    void normalizeMatrixs();
};
