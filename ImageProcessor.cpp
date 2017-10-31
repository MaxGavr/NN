#include <iostream>
#include <cmath>

#include "ImageProcessor.h"

using namespace arma;
using namespace std;

NeuralNetwork::NeuralNetwork(const char* pathToImage, int _n, int _m, int _p, double _e, double _a)
    : RGB(3), n(_n), m(_m), p(_p), e(_e), a(_a)
{
    PngImage sourceImage(pathToImage);

    imageWidth = sourceImage.get_width();
    imageHeight = sourceImage.get_height();

    for (int startX = 0; startX < imageWidth; startX += m)
    {
        for (int startY = 0; startY < imageHeight; startY += n)
        {
            Segment segment = readSegment(sourceImage, startX, startY);
            imageSegments.push_back(segment);
        }
    }

    L = imageSegments.size();
    nmRGB = n * m * RGB;

    createWeightMatrix();
}

void NeuralNetwork::processImage()
{
    double step;
    double step_;
    double E;
    int iteration = 0;

    do
    {
        E = 0;
        for (int i = 0; i < L; i++)
        {
            mat X = imageSegments[i].getX();
            mat Y = X * W;
            mat X_ = Y * W_;
            mat deltaX = X_ - X;

            step_ = step = a;

            W = W - (step * X.t() * deltaX * W_.t());
            W_ = W_ - (step_ * Y.t() * deltaX);
        }

        // count error after correction
        for (int i = 0; i < L; i++)
        {
            mat X = imageSegments[i].getX();
            mat Y = X * W;
            mat X_ = Y * W_;
            mat deltaX = X_ - X;
            E += getErrorDegree(deltaX);
        }

        iteration++;
        cout << "Iteration: " << iteration << " Error: " << E << endl;

    } while (E > e);

    double z = (1.0 * n * m * RGB * L) / ((n * m * RGB + L) * p + 2);
    cout << "Z = " << z << endl;;
}

void NeuralNetwork::createOutputImage()
{
    PngImage outputImage(imageWidth, imageHeight);
    float color[3];

    for (int i = 0; i < L; i++)
    {
        int startX = imageSegments[i].getStartX();
        int startY = imageSegments[i].getStartY();

        mat X = imageSegments[i].getX();
        mat Y = X * W;
        mat X_ = Y * W_;

        int pixel = 0;
        for (int i = startX; i < startX + m; i++)
        {
            for (int j = startY; j < startY + n; j++)
            {
                color[0] = convertColorReverse(X_(0, pixel++));
                color[1] = convertColorReverse(X_(0, pixel++));
                color[2] = convertColorReverse(X_(0, pixel++));

                if (i < imageWidth && j < imageHeight)
                    outputImage.set_pixel(i, j, Pixel(color[0], color[1], color[2]));
            }
        }
    }

    outputImage.write("output.png");
}

Segment NeuralNetwork::readSegment(const PngImage& image, int startX, int startY)
{
    Segment segment(startX, startY);
    for (int i = startX; i < startX + m; i++)
    {
        for (int j = startY; j < startY + n; j++)
        {
            if (i < imageWidth && j < imageHeight)
            {
                segment.addElement(convertColor(image[j][i].red));
                segment.addElement(convertColor(image[j][i].green));
                segment.addElement(convertColor(image[j][i].blue));
            }
            else
            {
                segment.addElement(-1);
                segment.addElement(-1);
                segment.addElement(-1);
            }
        }
    }
    segment.createMatrixX();

    return segment;
}

int NeuralNetwork::convertColorReverse(double color)
{
    double result = (255 * (color + 1) / 2);

    if (result < 0)
        result = 0;

    if (result > 255)
        result = 255;

    return (int)result;
}

double NeuralNetwork::getErrorDegree(mat deltaX)
{
    double err = 0;

    for (int i = 0; i < nmRGB; i++)
        err += pow(deltaX(0, i), 2);

    return err;
}

void NeuralNetwork::createWeightMatrix()
{
    W = randu<mat>(nmRGB, p);

    for (int i = 0; i < nmRGB; i++)
    {
        for (int j = 0; j < p; j++)
            // ??? why RAND_MAX
            W(i, j) = ( ((double)rand() / RAND_MAX) * 2 - 1 ) * 0.1;;
    }

    W_ = W.t();
}

double NeuralNetwork::convertColor(int color)
{
    return ((2.0 * color / 255) - 1);
}
