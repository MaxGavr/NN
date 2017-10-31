#include "matrix.h"
#include <stdexcept>

Matrix::Matrix(int height, int width)
    : mMatrix(height, nvector(width))
{
}

Matrix::~Matrix()
{
    mMatrix.clear();
}

std::ostream& operator<<(std::ostream& stream, const Matrix& matrix)
{
    for (size_t i = 0; i < matrix.getHeight(); ++i)
    {
        for (size_t j = 0; j < matrix.getWidth(); ++j)
            stream << matrix[i][j];
        stream << std::endl;
    }
    return stream;
}

size_t Matrix::getHeight() const
{
    return mMatrix.size();
}

size_t Matrix::getWidth() const
{
    return mMatrix.size() == 0 ? 0 : mMatrix.at(0).size();
}

bool Matrix::equalSize(const Matrix& matrix) const
{
    bool sameHeight = (this->getHeight() == matrix.getHeight());
    bool sameWidth = (this->getWidth() == matrix.getWidth());
    return (sameHeight && sameWidth);
}

bool Matrix::setElement(int x, int y, int value)
{
    try
    {
        mMatrix.at(x).at(y) = value;
        return true;
    }
    catch (std::out_of_range e)
    {
        return false;
    }
}

Matrix::nvector& Matrix::operator[](int i)
{
    return mMatrix.at(i);
}

const Matrix::nvector& Matrix::operator[](int i) const
{
    return mMatrix.at(i);
}

Matrix Matrix::operator+(const Matrix& matrix) const
{
    if (!this->equalSize(matrix))
    // TODO: replace with custom
        throw std::out_of_range("");

    Matrix sum(getHeight(), getWidth());
    for (size_t i = 0; i < this->getHeight(); ++i)
        for (size_t j = 0; j < this->getWidth(); ++j)
            sum[i][j] = mMatrix[i][j] + matrix.mMatrix[i][j];

    return sum;
}

Matrix Matrix::operator-(const Matrix& matrix) const
{
    if (!this->equalSize(matrix))
        throw std::out_of_range("");

    Matrix diff(getHeight(), getWidth());
    for (size_t i = 0; i < this->getHeight(); ++i)
        for (size_t j = 0; j < this->getWidth(); ++j)
            diff[i][j] = mMatrix[i][j] - matrix.mMatrix[i][j];

    return diff;
}

Matrix Matrix::operator*(const Matrix& matrix) const
{
    if (this->getWidth() != matrix.getHeight())
        throw std::out_of_range("");

    Matrix prod(getHeight(), matrix.getWidth());
    for (size_t i = 0; i < this->getHeight(); ++i)
        for (size_t j = 0; j < matrix.getWidth(); ++j)
        {
            prod[i][j] = 0;
            for (size_t k = 0; k < getWidth(); ++k)
                prod[i][j] += mMatrix[i][k] * matrix.mMatrix[k][j];
        }

    return prod;
}

Matrix Matrix::getTransposed() const
{
    Matrix transposed(getWidth(), getHeight());

    for (size_t i = 0; i < getHeight(); ++i)
        for (size_t j = 0; j < getWidth(); ++j)
            transposed[j][i] = mMatrix[i][j];

    return transposed;
}
