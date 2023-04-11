#include <iostream>
#include <vector>
#include "Matrix.h"
#include "QuantumCircuit.h"
#include "Gate.h"

int main()
{

    std::cout << '\n' << "Welcome to quantum" << std::endl;

    //Identity.print();

    std::cout << '\n';

    Gate hadamard(H, false);

    //H.print();

    QuantumCircuit qc(2);

     std::cout << '\n' << "All good 22" << std::endl;

    // Set the initial state of the qubits to |01⟩
    std::vector<std::complex <double> > initial_state = {1, 0, 0, 0};
    qc.setInitialState(initial_state);

    std::cout << '\n' << "All good 28" << std::endl;

    qc.applyOperator(0, H);

    qc.applyOperator(0, 1, CNOT);

    Matrix<std::complex<double>> zero_unitary = qc.contruct_layer_unitary(0);
    
    std::cout << '\n' << "ZERO UNITARY: " << std::endl;
    zero_unitary.print();
    std::cout << std::endl;

    Matrix<std::complex<double>> one_unitary = qc.contruct_layer_unitary(1);
    
    std::cout << '\n' << "ONE UNITARY: " << std::endl;
    one_unitary.print();
    std::cout << std::endl;

    Matrix<std::complex<double>> final_unitary = qc.contruct_total_unitary();
    
    std::cout << '\n' << "FINAL UNITARY: " << std::endl;
    final_unitary.print();
    std::cout << std::endl;

    std::cout << '\n' << "FINAL STATE: " << std::endl;
    Matrix<std::complex<double>> final_state = qc.measure_final_state();
    final_state.print();

    std::cout << std::endl;

    qc.print_circuit();
}