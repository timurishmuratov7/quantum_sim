#include <iostream>
#include <vector>
#include "Matrix.h"
#include "QuantumCircuit.h"
#include "Gates.h"

int main()
{

    std::cout << '\n' << "Welcome to quantum" << std::endl;

    //Identity.print();

    std::cout << '\n';

    //H.print();

    QuantumCircuit qc(3);

    // Set the initial state of the qubits to |01⟩
    std::vector<std::complex <double> > initial_state = {1, 0, 0, 0};
    qc.setInitialState(initial_state);

    Matrix<std::complex <double>, 4, 4> Unitary = tensor(Identity, H);
    //Matrix<std::complex <double>, 8, 8>  newestM = tensor(newM, Identity);

    std::cout << "Newest matrix: " <<std::endl;
    Unitary.print();

    Matrix<std::complex <double>, 4, 4> final_Operator = CNOT * Unitary;

    std::cout << "final_Operator matrix: " <<std::endl;

    final_Operator.print(); 

    final_Operator = final_Operator.multiply(initial_state);
    
    std::cout << "RESULT: " <<std::endl;
    final_Operator.print();
}