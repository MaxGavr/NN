#pragma once

#include <armadillo>
#include <vector>

using namespace std;
using namespace arma;

class ImageSegment {
  private:
    int startX;
    int startY;

    vector<double> vectorX;
    mat X;

  public:
    ImageSegment(int startX, int startY);

    void createMatrixX();

    void addElement(double newElement);

    int  getStartX() const;

    int  getStartY() const;

    mat getX() const;
};
