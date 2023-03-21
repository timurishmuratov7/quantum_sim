#include <iostream>
#include <vector>
#include "InitialState.h"
#include "Matrix.h"
#include "QuantumCircuit.h"

int main()
{
    QuantumBit qbit1;
    QuantumBit qbit2;

    RegularAmplitude regamp(0, 1);
    qbit1.setAmplitude(regamp);
    qbit2.setAmplitude(regamp);

    std::vector<QuantumBit> qubits;

    qubits.push_back(qbit1);
    qubits.push_back(qbit2);

    InitialState initialState(qubits);
    
    initialState.print_initial_state();

    std::cout << '\n' << "Welcome to quantum" << std::endl;

    Identity.print();

    std::cout << '\n';

    H.print();
}