#include <iostream>
#include <vector>
#include <complex>
#include <random>

#include "Matrix.h"
#include "Gate.h"


class QuantumCircuit {
    public:
        QuantumCircuit(int num_qubits);

        void setInitialState(const std::vector<std::complex <double> >& initial_state);

        void applyOperator(int target_qubit, const Matrix<std::complex <double> > Operator);

        void applyOperator(int control_qubit, int target_qubit, const Matrix<std::complex <double> > Operator);

        void nextLayer();

        Matrix<std::complex<double>> contruct_layer_unitary(int layer_number);

        int measure(int target_qubit);

        void print_circuit();

        friend std::ostream& operator<<(std::ostream& os, const QuantumCircuit& qc) {
            for (int i = 0; i < qc.m_state.size(); i++) {
                os << qc.m_state[i] << std::endl;
            }
            return os;
        }

    private:
        int m_num_qubits;
        int layer_cursor;

        std::vector<std::vector<Gate > > unitary;

        std::vector< std::complex <double> > m_state;
};

std::map<int, int> get_control2target(std::vector<Gate> gates);
Matrix<std::complex<double>> total_unitary(std::vector<Gate> gates);

