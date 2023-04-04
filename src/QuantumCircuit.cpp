#include "QuantumCircuit.h"

QuantumCircuit::QuantumCircuit(int num_qubits) : m_num_qubits(num_qubits), m_state(1 << num_qubits) {}

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


void QuantumCircuit::applyOperator(int target_qubit, Matrix<std::complex <double> > Operator) {
    if (target_qubit < 0 || target_qubit >= m_num_qubits) {
        std::cerr << "Error: Invalid target qubit" << std::endl;
        return;
    }

    int num_states = m_state.size();
    for (int i = 0; i < num_states; i++) {
        if ((i >> target_qubit) & 1) {
            int j = i ^ (1 << target_qubit);
            std::complex <double> a = Operator.get(0, 0) * m_state[i] + Operator.get(0, 1) * m_state[j];
            std::complex <double> b = Operator.get(1, 0) * m_state[i] + Operator.get(1, 1) * m_state[j];
            m_state[i] = a;
            m_state[j] = b;
        }
    }
}

void QuantumCircuit::applyCNOT(int control_qubit, int target_qubit) {
    // Check that the control and target qubits are valid
    if (control_qubit < 0 || control_qubit >= m_num_qubits ||
        target_qubit < 0 || target_qubit >= m_num_qubits) {
        std::cerr << "Error: invalid qubit index" << std::endl;
        return;
    }


    // Compute the CNOT matrix
    int dim = m_state.size();
    std::vector<std::complex<double>> cnot_matrix(dim * dim, 0);
    for (int i = 0; i < dim; i++) {
        if (((i >> control_qubit) & 1) == 1 && ((i >> target_qubit) & 1) == 0) {
            cnot_matrix[i * dim + i] = 0;
            cnot_matrix[i * dim + i ^ (1 << target_qubit) ^ (1 << control_qubit)] = 1;
            cnot_matrix[i * dim + i ^ (1 << target_qubit)] = 0;
            cnot_matrix[i * dim + i ^ (1 << control_qubit)] = 1;
        }
        else if (((i >> control_qubit) & 1) == 0 && ((i >> target_qubit) & 1) == 1) {
            cnot_matrix[i * dim + i] = 0.0;
            cnot_matrix[i * dim + i ^ (1 << target_qubit) ^ (1 << control_qubit)] = 1;
            cnot_matrix[i * dim + i ^ (1 << target_qubit)] = 1;
            cnot_matrix[i * dim + i ^ (1 << control_qubit)] = 0;
        }
        else {
            cnot_matrix[i * dim + i] = 1.0;
        }
    }

    std::cout.precision(0);

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            int idx = i * dim + j;
            std::cout << std::fixed << cnot_matrix[idx].real() << " ";
        }
        std::cout << std::endl;
    }
     std::cout << std::endl;


    // Update the state vector with the CNOT matrix
    std::vector<std::complex<double>> new_state(dim, 0.0);
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            new_state[i] += cnot_matrix[i * dim + j] * m_state[j];
        }
    }
    m_state = new_state;
}


void QuantumCircuit::applyCZ(int control_qubit, int target_qubit) {
    // Check that the control and target qubits are valid
    if (control_qubit < 0 || control_qubit >= m_num_qubits ||
        target_qubit < 0 || target_qubit >= m_num_qubits) {
        std::cerr << "Error: invalid qubit index" << std::endl;
        return;
    }

    std::complex<double> z_vals[2][2] = {
    {1, 0},
    {0, -1}
    };
    Matrix<std::complex <double> > cz_matrix(z_vals);
    // Define the CZ matrix as a 2x2 array

    // Compute the tensor product of identity matrices and CZ matrix
    int n = m_num_qubits;
    std::vector<std::complex<double>> tensor_product_state(1 << n);
    for (int i = 0; i < tensor_product_state.size(); i++) {
        tensor_product_state[i] = 1.0;
    }
    for (int q = 0; q < n; q++) {
        if (q == control_qubit) {
            for (int i = 0; i < (1 << n); i++) {
                int row = (i >> q) & 1;
                for (int j = 0; j < (1 << q); j++) {
                    int index = (i & ~(1 << q)) | (j << q);
                    tensor_product_state[index + row*(1 << q)] = cz_matrix.get(row, row);
                    tensor_product_state[index + (1-row)*(1 << q)] = cz_matrix.get(row, 1-row);
                }
            }
        }
        else if (q == target_qubit) {
            for (int i = 0; i < (1 << n); i++) {
                int col = (i >> q) & 1;
                for (int j = 0; j < (1 << q); j++) {
                    int index = (i & ~(1 << q)) | (j << q);
                    tensor_product_state[index + col*(1 << q)] = cz_matrix.get(col, col);
                }
            }
        }
        else {
            for (int i = 0; i < (1 << n); i++) {
                int bit = (i >> q) & 1;
                for (int j = 0; j < (1 << q); j++) {
                    int index = (i & ~(1 << q)) | (j << q);
                    if (bit == 0) {
                        tensor_product_state[index] *= 1.0;
                    }
                }
            }
        }
    }

    // Update the state vector with the tensor product state
    m_state = tensor_product_state;
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


