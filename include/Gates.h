#include <vector>
#include <cmath>
#include "Matrix.h"

std::complex <double> identity_vals[2][2] = {
    {1, 0},
    {0, 1}
};
Matrix<std::complex <double> > Identity(identity_vals);

std::complex <double> x_vals[2][2] = {
    {0, 1},
    {1, 0}
};
Matrix<std::complex <double> > X(x_vals);

std::complex <double> z_vals[2][2] = {
    {1, 0},
    {0, -1}
};
Matrix<std::complex <double> > Z(z_vals);

std::complex <double> h_vals[2][2] = {
    {1 / sqrt(2), 1 / sqrt(2)},
    {1 / sqrt(2), -1 / sqrt(2)}
};
Matrix<std::complex <double> > H(h_vals);

std::complex <double> cnot_vals[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 0, 1},
    {0, 0, 1, 0}
};
Matrix<std::complex <double> > CNOT(cnot_vals);

std::complex <double> cz_vals[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, -1}
};
Matrix<std::complex <double> > CZ(cz_vals);



