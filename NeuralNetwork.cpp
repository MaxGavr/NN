#include <iostream> // C++ Standard Template Library
#include <cmath> // C standard library

#include "NeuralNetwork.h"

using namespace arma;

NeuralNetwork::NeuralNetwork(int _n, int _m, int _p, double _e)
    : n(_n), m(_m), p(_p), e(_e),
      S(3), N(n * m * S)
{
}

void NeuralNetwork::loadImage(const char* pathToImage)
{
    sourceImage.read(pathToImage);

    imageWidth = sourceImage.get_width();
    imageHeight = sourceImage.get_height();

    for (int x = 0; x < imageWidth; x += m)
        for (int y = 0; y < imageHeight; y += n)
            segments.push_back(readSegment(x, y));

    L = segments.size();

    initWeightMatrix();
}

void NeuralNetwork::processImage()
{
    double step, step_;
    double E;
    size_t iteration = 0;

    mat X, Y, X_, dX;
    do
    {
        E = 0;

        for (int i = 0; i < L; i++)
        {
            X = segments[i].vector;
            Y = X * W;

            //X_ = Y * W_;
            //dX = X_ - X;
            dX = (Y * W_) - X;

            // calculate learning step
            step = calcAdaptiveStep(X);
            step_ = calcAdaptiveStep(Y);

            // correct weights
            W  = W  - (step  * X.t() * dX * W_.t());
            W_ = W_ - (step_ * Y.t() * dX);
        }

        // calculate error
        for (int i = 0; i < L; i++)
        {
            X = segments[i].vector;
            Y = X * W;

            //X_ = Y * W_;
            //dX = X_ - X;

            //E += calcError(dX);
            E += calcError((Y * W_) - X);
        }

        std::cout << "Итерация " << iteration++
                  << ". Ошибка: " << E << std::endl;

    } while (E > e);

    std::cout << std::endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

    std::cout << "Коэффициент сжатия (Z): " << calcCompression() << std::endl;;
    std::cout << "Количество итераций: " << iteration << std::endl;
}

void NeuralNetwork::restoreImage()
{
    PngImage outputImage(imageWidth, imageHeight);

    mat X, Y, X_;

    for (int i = 0; i < L; i++)
    {
        Segment& seg = segments[i];

        X = seg.vector;
        Y = X * W;
        X_ = Y * W_;

        int element = 0;
        for (int i = seg.X; i < seg.X + m; i++)
        {
            for (int j = seg.Y; j < seg.Y + n; j++)
                if (i < imageWidth && j < imageHeight)
                {
                    outputImage[j][i].red = restoreColor(X_(0, element++));
                    outputImage[j][i].green = restoreColor(X_(0, element++));
                    outputImage[j][i].blue = restoreColor(X_(0, element++));
                }
        }
    }

    outputImage.write("output.png");
}

Segment NeuralNetwork::readSegment(int posX, int posY)
{
    Segment segment;
    segment.X = posX;
    segment.Y = posY;

    std::vector<double> colors;

    for (int i = posX; i < posX + m; i++)
    {
        for (int j = posY; j < posY + n; j++)
        {
            if (i < imageWidth && j < imageHeight)
            {
                colors.push_back(convertColor(sourceImage[j][i].red));
                colors.push_back(convertColor(sourceImage[j][i].green));
                colors.push_back(convertColor(sourceImage[j][i].blue));
            }
            else
                colors.insert(colors.end(), {-1, -1, -1});
        }
    }
    segment.vector = arma::rowvec(colors);

    return segment;
}

void NeuralNetwork::initWeightMatrix()
{
    W = mat(N, p);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < p; j++)
            W(i, j) =(((double)rand() / RAND_MAX) * 2 - 1) * 0.1;

    W_ = W.t();
}

double NeuralNetwork::convertColor(int color) const
{
    return ((2 * (double)color / 255) - 1);
}

int NeuralNetwork::restoreColor(double color) const
{
    return (int)(255 * (color + 1) / 2);
}

double NeuralNetwork::calcError(const mat& dX) const
{
    return accu(square(dX));
}

double NeuralNetwork::calcAdaptiveStep(const mat& matrix) const
{
    // TODO: check for 0
    return 1 / accu(matrix * matrix.t());
}

double NeuralNetwork::calcCompression() const
{
    double Z = ((double)n * m * S * L) / ((n * m * S + L) * p + 2);
    return Z;
}
