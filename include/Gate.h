#ifndef GATE_H
#define GATE_H

#include <vector>
#include <cmath>
#include <complex>
#include "Matrix.h"

class Gate{
  private:
    int target_qubit;
    int control_qubit;

    Matrix<std::complex <double> > gate_matrix;

    bool is_control_gate;

  public:

    //Empty gate (i.e. Identity matrix)
    Gate();

    //Clifford gates contructors
    Gate(const Matrix<std::complex <double> > matrix, bool is_control_gate);
    Gate(const std::complex <double> matrix_valuesp[2][2], bool is_control_gate);

    void set_target(int qubit_number);
    int get_target();

    void set_control(int qubit_number);
    int get_control();

    Matrix<std::complex <double> > get_matrix();

    void print_gate();

    bool operator!=(const Gate& other) const;

};

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

