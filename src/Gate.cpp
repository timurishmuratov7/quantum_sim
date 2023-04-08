#include "Gate.h"

Gate::Gate(const Matrix<std::complex <double> > matrix, bool is_control_gate){
    this->gate_matrix = matrix;

    this->is_control_gate = is_control_gate;
}

Gate::Gate(const std::complex <double> matrix_values, bool is_control_gate){

    const Matrix<std::complex <double> > matrix(matrix_values);

    this->gate_matrix = matrix;

    this->is_control_gate = is_control_gate;
}

void Gate::set_target(int qubit_number){
    this.target_qubit = qubit_number;
}

void Gate::get_target(){
    return this.target_qubit;
}

void Gate::set_control(int qubit_number){
    this.control_qubit = qubit_number;
}

void Gate::get_control(int qubit_number){
    return this.control_qubit;
}

Matrix<std::complex <double> > Gate::get_matrix(){
    return this.gate_matrix;
}


void Gate::print_gate(){
    std::cout << "Gate: " << std::endl;

    this.gate_matrix.print();


    std::cout << "Target qubit is: " << this.target_qubit << std::endl;

    if(this.is_control_gate == true){
        std::cout << "Control qubit is: " << this.control_qubit << std::endl;
    }

}