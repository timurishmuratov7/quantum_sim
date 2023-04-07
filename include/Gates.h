#ifndef GATES_H
#define GATES_H

#include <vector>
#include <cmath>
#include "Matrix.h"

const std::complex <double> identity_vals[2][2] = {
    {1, 0},
    {0, 1}
};
const Matrix<std::complex <double> > Identity(identity_vals);

const std::complex <double> x_vals[2][2] = {
    {0, 1},
    {1, 0}
};
const Matrix<std::complex <double> > X(x_vals);

const std::complex <double> z_vals[2][2] = {
    {1, 0},
    {0, -1}
};
const Matrix<std::complex <double> > Z(z_vals);

const std::complex <double> h_vals[2][2] = {
    {1 / sqrt(2), 1 / sqrt(2)},
    {1 / sqrt(2), -1 / sqrt(2)}
};
const Matrix<std::complex <double> > H(h_vals);

const std::complex <double> cnot_vals[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 0, 1},
    {0, 0, 1, 0}
};
const Matrix<std::complex <double> > CNOT(cnot_vals);

const std::complex <double> cz_vals[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, -1}
};
const Matrix<std::complex <double> > CZ(cz_vals);

#endif

