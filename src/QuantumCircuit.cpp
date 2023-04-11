#include "QuantumCircuit.h"

QuantumCircuit::QuantumCircuit(int num_qubits) : m_num_qubits(num_qubits), m_state(1 << num_qubits) {
    this->layer_cursor = 0;

}

void QuantumCircuit::setInitialState(const std::vector<std::complex <double> >& initial_state) {
    // Check that the initial state has the correct size
    if (initial_state.size() != m_state.size()) {
        std::cerr << "Error: initial state size does not match number of qubits" << std::endl;
        return;
    }

    // Normalize the initial state vector
    double norm = 0;
    for (const auto& amplitude : initial_state) {
        norm += std::norm(amplitude);
    }
    norm = std::sqrt(norm);
    std::vector<std::complex <double> > normalized_state;
    for (const auto& amplitude : initial_state) {
        normalized_state.push_back(amplitude / norm);
    }

    // Set the initial state of the qubits
    m_state = normalized_state;
}


void QuantumCircuit::applyOperator(int target_qubit, const Matrix<std::complex <double> > Operator) {
    if (target_qubit < 0 || target_qubit >= m_num_qubits) {
        std::cerr << "Error: Invalid target qubit" << std::endl;
        return;
    }

    std::vector<Gate> layer;

    Gate operator_gate(Operator, false);
    Gate empty_gate = Gate();

    if (layer_cursor >= unitary.size()) {
        for (int row = 0; row < m_num_qubits; row++){
            layer.push_back(empty_gate);
        }
        unitary.push_back(layer);
    }

    // If something was before the operator -> put operator on the next layer
    if(unitary[layer_cursor][target_qubit].get_name() != "I"){
        layer_cursor++;

        for (int row = 0; row < m_num_qubits; row++){
            layer.push_back(empty_gate);
        }
        unitary.push_back(layer);
        
        operator_gate.set_target(target_qubit);
        unitary[layer_cursor][target_qubit] = operator_gate;
    } else {
        // If nothing was against putting this Operator on the same layer -> put it.
        operator_gate.set_target(target_qubit);
        unitary[layer_cursor][target_qubit] = operator_gate;
    }
        
}

void QuantumCircuit::applyOperator(int control_qubit, int target_qubit, const Matrix<std::complex <double> > Operator) {
    if (target_qubit < 0 || target_qubit >= m_num_qubits || control_qubit == target_qubit) {
        std::cerr << "Error: Invalid target qubit" << std::endl;
        return;
    }

    if (control_qubit < 0 || control_qubit >= m_num_qubits) {
        std::cerr << "Error: Invalid control qubit" << std::endl;
        return;
    }

    Gate operator_gate(Operator, true);
    operator_gate.set_name(operator_gate.get_name() + std::to_string(control_qubit) + std::to_string(target_qubit));

    Gate empty_gate = Gate();

    std::vector<Gate> layer;

    if (layer_cursor > unitary.size()) {
        for (int row = 0; row < m_num_qubits; row++){
            layer.push_back(empty_gate);
        }
        unitary.push_back(layer);
    }

    // If something was before the operator -> put operator on the next layer
    if(unitary[layer_cursor][target_qubit].get_name() != "I" || unitary[layer_cursor][control_qubit].get_name() != "I"){
        layer_cursor++;

        for (int row = 0; row < m_num_qubits; row++){
            layer.push_back(empty_gate);
        }
        unitary.push_back(layer);

        operator_gate.set_control(control_qubit);
        operator_gate.set_target(target_qubit);
        unitary[layer_cursor][control_qubit] = operator_gate;
        unitary[layer_cursor][target_qubit] = operator_gate;
    } else {
        // If nothing was against putting this Operator on the same layer -> put it.
        operator_gate.set_control(control_qubit);
        operator_gate.set_target(target_qubit);
        unitary[layer_cursor][control_qubit] = operator_gate;
        unitary[layer_cursor][target_qubit] = operator_gate;
    }
}

void QuantumCircuit::nextLayer(){
    this->layer_cursor++;
}

Matrix<std::complex <double> > QuantumCircuit::measure_final_state(){

    return contruct_total_unitary().multiply(m_state);

}

Matrix<std::complex<double>> QuantumCircuit::contruct_total_unitary(){
    Matrix<std::complex<double>> final_unitary = contruct_layer_unitary(layer_cursor);

    for(int i=layer_cursor-1; i>=0; i--){
        final_unitary = final_unitary * contruct_layer_unitary(i);
    }

    return final_unitary;
}

Matrix<std::complex<double>> QuantumCircuit::contruct_layer_unitary(int layer_number){

    //Let's first get all the gates on this layer

    std::vector<Gate> gates;

    for(int i=0; i<m_num_qubits; i++){
        gates.push_back(unitary[layer_number][i]);
    }

    std::map<int, int> control2target_qubits = get_control2target(gates);

    std::cout << '\n' << "All good 137" << std::endl;

    // need to do tensor products for matrices
    if(m_num_qubits == 1){
        return unitary[layer_number][0].get_matrix();
    }

    std::vector<std::vector<Gate>> layers_arr;

    clean_gate_layers(gates, layers_arr);

    Matrix<std::complex<double>> final_layer_unitary = total_unitary(layers_arr[0]);
    for(int idx = 1; idx < layers_arr.size(); idx++){
        final_layer_unitary = final_layer_unitary + total_unitary(layers_arr[idx]);
    }

    return final_layer_unitary;

}

void clean_gate_layers(std::vector<Gate> gates, std::vector<std::vector<Gate>>& result){

    std::cout << '\n' << "All good 171" << std::endl;

    std::map<int, int> control2target = get_control2target(gates);

    // Base case: no control gates are found
    if(control2target.empty()){

        std::cout << '\n' << "All good 164" << std::endl;

        result.push_back(gates);
        return;
    }

    // If some control gates are found
    for(auto it = control2target.begin(); it != control2target.end(); ++it){
        int control = it->first;
        int target = it->second;

        Gate zero_gate = Gate(Zero, false);
        Gate identity_gate = Gate();
        Gate one_gate = Gate(One, false);
        Gate flip_gate = Gate(X, false);

        zero_gate.set_target(control);
        one_gate.set_target(control);


        identity_gate.set_target(target);
        flip_gate.set_target(target);

        std::vector<Gate> tmp_left = gates;
        tmp_left[control] = zero_gate;
        tmp_left[target] = identity_gate;

        std::vector<Gate> tmp_right = gates;
        tmp_right[control] = one_gate;
        tmp_right[target] = flip_gate;

        clean_gate_layers(tmp_left, result);
        clean_gate_layers(tmp_right, result);
    }

    return;
}


std::map<int, int> get_control2target(std::vector<Gate> gates){
    std::map<int, int> control2target_qubits;

    for(int i=0; i<gates.size(); i++){
        Gate tmp_gate = gates[i];
        if(tmp_gate.get_is_control()){
            control2target_qubits[tmp_gate.get_control()] = tmp_gate.get_target();
        }
    }

    return control2target_qubits;
}


Matrix<std::complex<double>> total_unitary(std::vector<Gate> gates){
    Matrix<std::complex<double>> final_layer_unitary = gates[0].get_matrix();
    
    for(int i=1; i<gates.size(); i++){
        final_layer_unitary = tensor(gates[i].get_matrix(), final_layer_unitary);
    }

    return final_layer_unitary;
}


void QuantumCircuit::print_circuit(){
    if(this->unitary.size() == 0){
        std::cout << "No operators presented in the circuit, so printing initial state: " << std::endl;
        for (int i = 0; i < this->m_state.size(); i++) {
            std::cout << this->m_state[i] << std::endl;
        }
    } else {
        std::cout << "Current circuit looks like this: " << std::endl;
        for(int qubit=0; qubit < m_num_qubits; qubit++){
            for(int op=0;  op<=layer_cursor; op++){
                std::cout << "-" << unitary[op][qubit].get_name() << "-";
            }
            std::cout << std::endl;
        }
    }
}

int QuantumCircuit::measure(int target_qubit) {
    if (target_qubit < 0 || target_qubit >= m_num_qubits) {
        std::cerr << "Error: Invalid target qubit" << std::endl;
        return -1;
    }

    // Calculate the probability distribution for the target qubit
    std::vector<double> probabilities(2);
    int num_states = m_state.size();
    for (int i = 0; i < num_states; i++) {
        int bit = (i >> target_qubit) & 1;
        probabilities[bit] += std::norm(m_state[i]);
    }

    // Randomly choose a measurement outcome based on the probability distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);
    double r = dis(gen);
    int outcome = (r < probabilities[0]) ? 0 : 1;

    // Update the state of the quantum system based on the measurement outcome
    for (int i = 0; i < num_states; i++) {
        int bit = (i >> target_qubit) & 1;
        if (bit != outcome) {
            m_state[i] = 0;
        } else {
            m_state[i] /= sqrt(probabilities[outcome]);
        }
    }

    return outcome;
}


