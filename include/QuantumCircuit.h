#ifndef QUANTUMCIRCUIT_H
#define QUANTUMCIRCUIT_H

#include <iostream>
#include <vector>
#include <complex>
#include <random>

#include "Gates.h"
#include "Matrix.h"


class QuantumCircuit {
public:
    QuantumCircuit(int num_qubits) : m_num_qubits(num_qubits), m_state(1 << num_qubits) {}

    void setInitialState(const std::vector<std::complex <double> >& initial_state) {
        // Check that the initial state has the correct size
        if (initial_state.size() != m_state.size()) {
            std::cerr << "Error: initial state size does not match number of qubits" << std::endl;
            return;
        }

        // Normalize the initial state vector
        double norm = 0;
        for (const auto& amplitude : initial_state) {
            norm += std::norm(amplitude);
        }
        norm = std::sqrt(norm);
        std::vector<std::complex <double> > normalized_state;
        for (const auto& amplitude : initial_state) {
            normalized_state.push_back(amplitude / norm);
        }

        // Set the initial state of the qubits
        m_state = normalized_state;
    }


    void applyOperator(int target_qubit, Matrix<std::complex <double>, 2, 2> Operator) {
        if (target_qubit < 0 || target_qubit >= m_num_qubits) {
            std::cerr << "Error: Invalid target qubit" << std::endl;
            return;
        }

        int num_states = m_state.size();
        for (int i = 0; i < num_states; i++) {
            if ((i >> target_qubit) & 1) {
                int j = i ^ (1 << target_qubit);
                //std::cout << "mstate: " << i << " " << m_state[i] << std::endl;
                //std::cout << "mstate: " << j << " " << m_state[j] << std::endl;
                std::complex <double> a = Operator.get(0, 0) * m_state[i] + Operator.get(0, 1) * m_state[j];
                std::complex <double> b = Operator.get(1, 0) * m_state[i] + Operator.get(1, 1) * m_state[j];
                m_state[i] = a;
                m_state[j] = b;
            }
        }
    }

    int measure(int target_qubit) {
        if (target_qubit < 0 || target_qubit >= m_num_qubits) {
            std::cerr << "Error: Invalid target qubit" << std::endl;
            return -1;
        }

        // Calculate the probability distribution for the target qubit
        std::vector<double> probabilities(2);
        int num_states = m_state.size();
        for (int i = 0; i < num_states; i++) {
            int bit = (i >> target_qubit) & 1;
            probabilities[bit] += std::norm(m_state[i]);
        }

        // Randomly choose a measurement outcome based on the probability distribution
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, 1);
        double r = dis(gen);
        int outcome = (r < probabilities[0]) ? 0 : 1;

        std::cout << "Outcome: " << outcome << '\n';

        // Update the state of the quantum system based on the measurement outcome
        for (int i = 0; i < num_states; i++) {
            int bit = (i >> target_qubit) & 1;
            if (bit != outcome) {
                m_state[i] = 0;
            } else {
                m_state[i] /= sqrt(probabilities[outcome]);
            }
        }

        return outcome;
    }

    friend std::ostream& operator<<(std::ostream& os, const QuantumCircuit& qc) {
        for (int i = 0; i < qc.m_state.size(); i++) {
            os << qc.m_state[i] << std::endl;
        }
        return os;
    }

private:
    int m_num_qubits;
    std::vector< std::complex <double> > m_state;
};


#endif