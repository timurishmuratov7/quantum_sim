#include <iostream>
#include <vector>
#include "Matrix.h"
#include "QuantumCircuit.h"
#include "Gate.h"

int main()
{

    std::cout << '\n' << "Creating Bell state" << std::endl;

    QuantumCircuit qc(2);

    // Set the initial state of the qubits to |00⟩
    std::vector<std::complex <double> > initial_state = {1, 0, 0, 0};
    qc.setInitialState(initial_state);

    qc.applyOperator(0, H);

    qc.applyOperator(0, 1, CNOT);

    std::cout << '\n' << "FINAL STATE: " << std::endl;
    Matrix<std::complex<double>> final_state = qc.measure_final_state();
    final_state.print();

    std::cout << std::endl;

    qc.print_circuit();
}