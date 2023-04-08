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

    //H.print();

    QuantumCircuit qc(3);

    // Set the initial state of the qubits to |01⟩
    std::vector<std::complex <double> > initial_state = {0, 0, 0, 0, 0, 0, 0, 1};
    qc.setInitialState(initial_state);

    qc.applyOperator(0, H);
    qc.applyOperator(1,H);

    std::cout << "Before measurement:" << std::endl;
    std::cout << qc << std::endl;

    int result = qc.measure(0);
    std::cout << "Measured " << result << std::endl;

    std::cout << "After measurement:" << std::endl;
    std::cout << qc << std::endl;
}