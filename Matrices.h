#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>

using namespace std;

namespace Matrices
{
    class Matrix
    {
    public:
        ///Construct a matrix of the specified size.
        ///Initialize each element to 0.
        Matrix(int _rows, int _cols);

        ///Read element at row i, column j
        ///usage:  double x = a(i,j);
        const double& operator()(int i, int j) const
        {
            return a.at(i).at(j);
        }

        ///Assign element at row i, column j
        ///usage:  a(i,j) = x;
        double& operator()(int i, int j)
        {
            return a.at(i).at(j);
        }

        int getRows() const { return rows; }
        int getCols() const { return cols; }

    protected:
        ///changed to protected so subclasses can modify
        vector<vector<double>> a;
    private:
        int rows;
        int cols;
    };

    ///Add each corresponding element.
    ///usage:  c = a + b;
    Matrix operator+(const Matrix& a, const Matrix& b);

    ///Matrix multiply.  See description.
    ///usage:  c = a * b;
    Matrix operator*(const Matrix& a, const Matrix& b);

    ///Matrix comparison.
    ///usage:  a == b
    bool operator==(const Matrix& a, const Matrix& b);

    ///Matrix comparison.
    ///usage:  a != b
    bool operator!=(const Matrix& a, const Matrix& b);

    ///Output matrix.
    ///Separate columns by ' ' and rows by '\n'
    ostream& operator<<(ostream& os, const Matrix& a);

    /*******************************************************************************/

    ///2D rotation matrix
    ///usage:  A = R * A rotates A theta radians counter-clockwise
    class RotationMatrix : public Matrix
    {
    public:
        RotationMatrix(double theta);
    };

    ///2D scaling matrix
    ///usage:  A = S * A expands or contracts A by the specified scaling factor
    class ScalingMatrix : public Matrix
    {
    public:
        ScalingMatrix(double scale);
    };

    ///2D Translation matrix
    ///usage:  A = T + A will shift all coordinates of A by (xShift, yShift)
    class TranslationMatrix : public Matrix
    {
    public:
        TranslationMatrix(double xShift, double yShift, int nCols);
    };
}

#endif // MATRIX_H_INCLUDED