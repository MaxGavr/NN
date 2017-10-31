#pragma once

#include <vector>
#include <iostream>

class Matrix
{
public:
    typedef std::vector<int> nvector;

    friend std::ostream& operator<<(std::ostream& stream, const Matrix& matrix);

    Matrix(int height, int width);
    ~Matrix();

    size_t getHeight() const;
    size_t getWidth() const;
    bool equalSize(const Matrix& matrix) const;

    bool setElement(int x, int y, int value);

    nvector& operator[](int i);
    const nvector& operator[](int i) const;

    Matrix operator+(const Matrix& matrix) const;
    Matrix operator-(const Matrix& matrix) const;
    Matrix operator*(const Matrix& matrix) const;

    Matrix getTransposed() const;
    //Matrix getReversed();

private:
    std::vector< nvector > mMatrix;
};

std::ostream& operator<<(std::ostream& stream, const Matrix& matrix);
