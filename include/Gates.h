#include <vector>
#include <cmath>
#include "Matrix.h"


int identity_vals[2][2] = {
    {1, 0},
    {0, 1}
};
Matrix<int, 2, 2> Identity(identity_vals);

int x_vals[2][2] = {
    {0, 1},
    {1, 0}
};
Matrix<int, 2, 2> X(x_vals);

int z_vals[2][2] = {
    {1, 0},
    {0, -1}
};
Matrix<int, 2, 2> Z(z_vals);

double h_vals[2][2] = {
    {1 / sqrt(2), 1 / sqrt(2)},
    {1 / sqrt(2), -1 / sqrt(2)}
};
Matrix<double, 2, 2> H(h_vals);

int cnot_vals[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 0, 1},
    {0, 0, 1, 0}
};
Matrix<int, 4, 4> CNOT(cnot_vals);

int cz_vals[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, -1}
};
Matrix<int, 4, 4> CZ(cz_vals);



