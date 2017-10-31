#include "Rectangle.h"

Segment::Segment(int _startX, int _startY)
    : startX(_startX), startY(_startY)
{
}

void Segment::createMatrixX()
{
    // ??? why transposed
    X = arma::mat(vectorX).t();
}

void Segment::addElement(double newElement)
{
    vectorX.push_back(newElement);
}

int Segment::getStartX() const
{
    return startX;
}

int Segment::getStartY() const
{
    return startY;
}

arma::mat Segment::getX() const
{
    return X;
}
