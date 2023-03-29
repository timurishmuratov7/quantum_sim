#include <iostream>
#include <vector>
#include "Matrix.h"
#include "QuantumCircuit.h"
#include "Gates.h"

template<typename Num, size_t rows, size_t cols, size_t other_rows, size_t other_cols>
Matrix<Num, rows*other_rows, cols*other_cols> tensor(Matrix<Num, rows, cols> matrix1, Matrix<Num, other_rows, other_cols> other) {

        Matrix<Num, rows*other_rows, cols*other_cols> result(other_rows*rows, other_cols*cols);

        for (int i = 0; i < other_rows; i++) {

            for (int j = 0; j < other_cols; j++){
                // Internal loop
                Num current_num = other.get(i, j);
                Num res = 0;
                for(int internal_i = 0; internal_i<rows; internal_i++) {
                    for(int internal_j = 0; internal_j<cols; internal_j++) {
                        res = matrix1.get(internal_i, internal_j) * current_num;
                        std::cout << "row_idx: " <<  internal_i+cols*j << ", col_idx: " << internal_j+rows*i << std::endl;
                        result.set(internal_i+cols*j, internal_j+rows*i, res);                       
                    }  
                }
            }
        }

        return result;

    }

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

    Matrix<std::complex <double>, 4, 4>  newM = tensor(H, Identity);
    Matrix<std::complex <double>, 8, 8>  newestM = tensor(newM, Identity);

    std::cout << "Newest matrix: " <<std::endl;
    newestM.print();

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