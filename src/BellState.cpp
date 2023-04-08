#include <iostream>
#include <vector>
#include "Matrix.h"
#include "QuantumCircuit.h"
#include "Gate.h"

int main()
{

    std::cout << '\n' << "Welcome to quantum" << std::endl;

    std::cout << '\n';

    QuantumCircuit qc(3);

    // Set the initial state of the qubits to |01⟩
    std::vector<std::complex <double> > initial_state = {1, 0, 0, 0};
    qc.setInitialState(initial_state);

    Matrix<std::complex <double> > Unitary = tensor(Identity, H);

    std::cout << "Newest matrix: " <<std::endl;
    Unitary.print();

    Matrix<std::complex <double> > final_Operator = CNOT * Unitary;

    std::cout << "final_Operator matrix: " <<std::endl;

    final_Operator.print(); 

    final_Operator = final_Operator.multiply(initial_state);
    
    std::cout << "RESULT: " <<std::endl;
    final_Operator.print();
}