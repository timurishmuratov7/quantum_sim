#include <iostream>
#include <cmath>
#include <complex>
#include <vector>
#include "Gates.h"
#include "QuantumCircuit.h"

using namespace std;


typedef complex<double> complexd;
typedef vector<complex <double> > cvector;
typedef vector<cvector> cmatrix;

// Define the initial state
cvector psi = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Alice's state

int main() {

    QuantumCircuit qc(3);

    // Set the initial state of the qubits to |01⟩
    std::vector<std::complex <double> > initial_state = psi;
    qc.setInitialState(initial_state);

    qc.applyOperator(0, X);

    qc.applyOperator(1, H);
    qc.applyCNOT(1, 2);
    qc.applyCNOT(0, 1);
    qc.applyOperator(0, H);
    qc.applyCNOT(1, 2);
    qc.applyCZ(0, 2);

    int result = qc.measure(2);
    cout << "Measured " << result << endl;
 
    cout << "After measurement:" << endl;
    cout << qc << endl;
    
    return 0;
}

// Compute
