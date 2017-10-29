#include "Rectangle.h"

#include <armadillo>
#include <vector>

using namespace std;
using namespace arma;

ImageSegment::ImageSegment(int _startX, int _startY) : startX(_startX), startY(_startY) {}

void ImageSegment::createMatrixX() {
    X = mat(vectorX).t();
}

void ImageSegment::addElement(double newElement) {
    vectorX.push_back(newElement);
}

int ImageSegment::getStartX() const {
    return startX;
}

int ImageSegment::getStartY() const {
    return startY;
}

mat ImageSegment::getX() const {
    return X;
}
