#ifndef INITIALSTATE_H
#define INITIALSTATE_H

#include <vector>
#include <iostream>

#include "RegularAmplitude.h"
#include "QuantumBit.h"

class InitialState {
public:

    // Constructor 
    InitialState(std::vector<QuantumBit> qubits);

    // Public methods
    void print_initial_state();

private: 
    std::vector<QuantumBit> qubits;
};

InitialState::InitialState(std::vector<QuantumBit> qubits) {
    this->qubits = qubits;
}
void InitialState::print_initial_state() {
    for (const QuantumBit q : this->qubits) {
        std::cout << q;
    }
}


#endif
