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
    std::vector<std::complex <double> > initial_state = {1, 0, 0, 0, 0, 0, 0, 0};
    qc.setInitialState(initial_state);

    std::complex <double> state_vals[2][1] = {{1}, {0}};
    Matrix<std::complex <double>, 2, 1> initial_qubit(state_vals);

    Matrix<std::complex <double>, 2, 1> second_qubit(state_vals);

    std::cout << "|00>: " << std::endl;
    Matrix<std::complex <double>, 4, 2>  newwestM = tensor(Identity, initial_qubit);
    //newwestM.print();
    Identity.print();


    Matrix<std::complex <double>, 4, 4>  newM = tensor(H, Identity);
    //Matrix<std::complex <double>, 8, 8>  newestM = tensor(newM, Identity);

    std::cout << "Newest matrix: " <<std::endl;
    newM.print();

    Identity.print();
    

    qc.applyOperator(0, H);

    std::cout << "H(0):" << std::endl;
    std::cout << qc << std::endl;

    qc.applyCNOT(0,1);

    std::cout << "Before measurement:" << std::endl;
    std::cout << qc << std::endl;

    int result = qc.measure(0);
    std::cout << "Measured " << result << std::endl;

    std::cout << "After measurement:" << std::endl;
    std::cout << qc << std::endl;
}