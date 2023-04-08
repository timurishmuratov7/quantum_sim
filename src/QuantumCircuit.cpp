#include "QuantumCircuit.h"

QuantumCircuit::QuantumCircuit(int num_qubits) : m_num_qubits(num_qubits), m_state(1 << num_qubits) {}

void QuantumCircuit::setInitialState(const std::vector<std::complex <double> >& initial_state) {
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


void QuantumCircuit::applyOperator(int target_qubit, const Matrix<std::complex <double> > Operator) {
    if (target_qubit < 0 || target_qubit >= m_num_qubits) {
        std::cerr << "Error: Invalid target qubit" << std::endl;
        return;
    }

    std::vector<Gate> layer;

    Gate operator_gate(Operator, false);
    Gate empty_gate = Gate();

    if (layer_cursor > unitary.size()) {
        for (int row = 0; row < m_num_qubits; row++){
            layer.push_back(empty_gate);
        }
        unitary.push_back(layer);
    }

    // If something was before the operator -> put operator on the next layer
    if(unitary[layer_cursor-1][target_qubit] != empty_gate){
        layer_cursor++;
        if(layer_cursor > unitary.size()) {
            for (int row = 0; row < m_num_qubits; row++){
                layer.push_back(empty_gate);
            }
            unitary.push_back(layer);
        }
        operator_gate.set_target(target_qubit);
        unitary[layer_cursor][target_qubit] = operator_gate;
    } else {
        // If nothing was against putting this Operator on the same layer -> put it.
        operator_gate.set_target(target_qubit);
        unitary[layer_cursor][target_qubit] = operator_gate;
    }
        
}

void QuantumCircuit::applyOperator(int control_qubit, int target_qubit, const Matrix<std::complex <double> > Operator) {
    if (target_qubit < 0 || target_qubit >= m_num_qubits || control_qubit == target_qubit) {
        std::cerr << "Error: Invalid target qubit" << std::endl;
        return;
    }

    if (control_qubit < 0 || control_qubit >= m_num_qubits) {
        std::cerr << "Error: Invalid control qubit" << std::endl;
        return;
    }

    Gate operator_gate(Operator, true);
    Gate empty_gate = Gate();

    std::vector<Gate> layer;

    if (layer_cursor > unitary.size()) {
        for (int row = 0; row < m_num_qubits; row++){
            layer.push_back(empty_gate);
        }
        unitary.push_back(layer);
    }

    // If something was before the operator -> put operator on the next layer
    if(unitary[layer_cursor-1][target_qubit] != empty_gate){
        layer_cursor++;
        if (layer_cursor > unitary.size()) {
            for (int row = 0; row < m_num_qubits; row++){
                layer.push_back(empty_gate);
            }
            unitary.push_back(layer);
        }
        operator_gate.set_control(control_qubit);
        operator_gate.set_target(target_qubit);
        unitary[layer_cursor][control_qubit] = operator_gate;
        unitary[layer_cursor][target_qubit] = operator_gate;
    } else {
        // If nothing was against putting this Operator on the same layer -> put it.
        operator_gate.set_control(control_qubit);
        operator_gate.set_target(target_qubit);
        unitary[layer_cursor][control_qubit] = operator_gate;
        unitary[layer_cursor][target_qubit] = operator_gate;
    }
}

void QuantumCircuit::nextLayer(){
    this->layer_cursor++;
}

int QuantumCircuit::measure(int target_qubit) {
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


