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
    std::vector<std::complex <double> > initial_state = {0, 0, 0, 1};
    qc.setInitialState(initial_state);

    std::cout << '\n' << "All good 28" << std::endl;

    qc.applyOperator(0, H);

    qc.applyOperator(0, 1, CNOT);

    Matrix<std::complex<double>> layer_zero = qc.contruct_layer_unitary(0);
    Matrix<std::complex<double>> layer_one = qc.contruct_layer_unitary(1);

    std::cout << '\n' << "layer 0: " << std::endl;
    layer_zero.print();
    std::cout << std::endl;


    Matrix<std::complex<double>> final_unitary = qc.contruct_total_unitary();
    
    std::cout << '\n' << "FINAL UNITARY: " << std::endl;
    final_unitary.print();


    //std::cout << '\n' << "Layer 0:" << std::endl;
    //layer_zero.print();
    std::cout << std::endl;

    qc.print_circuit();
}