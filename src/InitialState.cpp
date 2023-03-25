#include "InitialState.h"

InitialState::InitialState(std::vector<QuantumBit> qubits) {
    this->qubits = qubits;
}

void InitialState::print_initial_state() {
    for (const QuantumBit q : this->qubits) {
        std::cout << q;
    }
}