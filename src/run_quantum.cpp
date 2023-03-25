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

    //Identity.print();

    std::cout << '\n';

    //H.print();

    QuantumCircuit qc(2);

    // Set the initial state of the qubits to |01⟩
    std::vector<std::complex <double> > initial_state = {0, 0, 0, 1};
    qc.setInitialState(initial_state);

    qc.applyOperator(0, H);
    qc.applyOperator(1, H);

    std::cout << "Before measurement:" << std::endl;
    std::cout << qc << std::endl;

    int result = qc.measure(0);
    std::cout << "Measured " << result << std::endl;

    std::cout << "After measurement:" << std::endl;
    std::cout << qc << std::endl;
}