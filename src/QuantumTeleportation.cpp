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
cvector poeer = {1/sqrt(2), 0, 1/sqrt(2), 0, 0, 0, 0, 0}; // Alice's state

int main() {

    /*

    QuantumCircuit qc(3);

    // Set the initial state of the qubits to |01⟩
    std::vector<std::complex <double> > initial_state = psi;
    qc.setInitialState(initial_state);

    cout << "Initial: " << endl;
    cout << qc << endl;

    qc.applyOperator(1, H);
    cout << "H(1): " << endl;
    cout << qc << endl;

    qc.setInitialState(poeer);
    cout << "New initial state: " << endl;
    cout << qc << endl;

    qc.applyCNOT(1, 2);

    cout << "applyCNOT(1, 2): " << endl;
    cout << qc << endl;

    qc.applyCNOT(0, 1);

    cout << "applyCNOT(0, 1): " << endl;
    cout << qc << endl;

    qc.applyOperator(0, H);

    cout << "H(0): " << endl;
    cout << qc << endl;

    qc.applyCNOT(1, 2);

    cout << "applyCNOT(1, 2): " << endl;
    cout << qc << endl;

    qc.applyCZ(0, 2);

    cout << "applyCZ(0, 2): " << endl;
    cout << qc << endl;

    int result = qc.measure(2);
    cout << "Measured " << result << endl;
 
    cout << "After measurement:" << endl;
    cout << qc << endl;*/

    
    return 0;
}

// Compute
