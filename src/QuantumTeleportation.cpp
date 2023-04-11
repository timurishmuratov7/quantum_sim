#include <iostream>
#include <cmath>
#include <complex>
#include <vector>
#include "Gate.h"
#include "QuantumCircuit.h"

using namespace std;


typedef complex<double> complexd;
typedef vector<complex <double> > cvector;
typedef vector<cvector> cmatrix;

// Define the initial state
cvector psi = {1, 0, 0, 0, 0, 0, 0, 0}; // Alice's state

int main() {

    QuantumCircuit qc(3);

    // Set the initial state of the qubits to |01⟩
    std::vector<std::complex <double> > initial_state = psi;
    qc.setInitialState(initial_state);

    qc.applyOperator(1, H);

    qc.applyOperator(1, 2, CNOT);

    qc.applyOperator(0, 1, CNOT);

    qc.applyOperator(0, H);

    qc.nextLayer();

    qc.applyOperator(1, 2, CNOT);

    qc.applyOperator(0, 2, CZ);

    qc.measure_final_state().print();

    qc.print_circuit();

    std::cout << std::endl;

    qc.contruct_total_unitary().print();

    //TODO: add disentabglement logic for complete quantum teleportation. See: https://qiskit.org/documentation/stable/0.32/_modules/qiskit/extensions/quantum_initializer/initializer.html#Initialize.gates_to_uncompute
    
    return 0;
}

// Compute
