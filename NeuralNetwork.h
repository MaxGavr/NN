#pragma once

#include <vector> // C++ Standard Template Library
#include <armadillo> // C++ linear algebra library
                     // Conrad Sanderson, Ryan Curtin
#include <png++/png.hpp> // C++ Wrapper for libpng - library for manipulating PNG images
                         // Alex Shulgin
                         // Guy Eric Schalnat, Andreas Dilger, John Bowler, Glenn Randers-Pehrson


struct Segment
{
    int X;
    int Y;
    arma::rowvec vector;
};


class NeuralNetwork
{
    using PngImage = png::image<png::rgb_pixel>;
    using Pixel = png::rgb_pixel;

public:
    NeuralNetwork(int n, int m, int p, double e);

    void loadImage(const char* pathToImage);
    void processImage();
    void restoreImage();

private:
    Segment readSegment(int posX, int posY);

    inline double convertColor(int color) const;
    inline int restoreColor(double color) const;

    void initWeightMatrix();

    inline double calcError(const arma::mat& dX) const;
    inline double calcAdaptiveStep(const arma::mat& matrix) const;
    double calcCompression() const;

private:
    PngImage sourceImage;

    int imageWidth;
    int imageHeight;

    std::vector<Segment> segments;

    int n;
    int m;
    int p;
    double e;
    int L;

    const int S;
    const int N;

    arma::mat W;
    arma::mat W_;
};
