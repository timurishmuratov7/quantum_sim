#ifndef QUANTUMCIRCUIT_H
#define QUANTUMCIRCUIT_H

#include <iostream>
#include <vector>
#include <complex>

#include "Gates.h"


class QuantumCircuit {
public:
    QuantumCircuit(int num_qubits) : m_num_qubits(num_qubits), m_state(1 << num_qubits) {}

    void applyOperator(int target_qubit) {
        if (target_qubit < 0 || target_qubit >= m_num_qubits) {
            std::cerr << "Error: Invalid target qubit" << std::endl;
            return;
        }

        const std::complex<double> factor = 1.0 / sqrt(2.0);
        const std::complex<double> H[2][2] = {{factor, factor}, {factor, -factor}};

        int num_states = m_state.size();
        for (int i = 0; i < num_states; i++) {
            if ((i >> target_qubit) & 1) {
                int j = i ^ (1 << target_qubit);
                std::complex<double> a = H[0][0] * m_state[i] + H[0][1] * m_state[j];
                std::complex<double> b = H[1][0] * m_state[i] + H[1][1] * m_state[j];
                m_state[i] = a;
                m_state[j] = b;
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const QuantumCircuit& qc) {
        for (int i = 0; i < qc.m_state.size(); i++) {
            os << qc.m_state[i] << std::endl;
        }
        return os;
    }

private:
    int m_num_qubits;
    std::vector< std::complex<double> > m_state;
};


#endif