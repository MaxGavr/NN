#pragma once

#include <armadillo>
#include <vector>

using namespace std;

class Segment
{
private:
    int startX;
    int startY;

    vector<double> vectorX;
    arma::mat X;

public:
    Segment(int startX, int startY);

    void createMatrixX();

    void addElement(double newElement);

    int getStartX() const;

    int getStartY() const;

    arma::mat getX() const;
};
