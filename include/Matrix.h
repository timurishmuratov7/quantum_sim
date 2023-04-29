#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <cmath>
#include <complex>

class Matrix{

private:
    int rows, cols;
    std::vector<std::vector< std::complex<double> > > mat;

    std::string name;

public:

    Matrix() {
        this->rows = 0;
        this->cols = 0;
    }


    Matrix(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        mat.resize(rows, std::vector<std::complex<double>>(cols, 0));
    }

    Matrix(std::complex<double> inputMatrix[2][2]) {
        this->rows = 2;
        this->cols = 2;
        mat.resize(rows, std::vector<std::complex<double>>(cols, 0));
        for (size_t i = 0; i < 2; i++) {
            for (size_t j = 0; j < 2; j++) {
                mat[i][j] = inputMatrix[i][j];
            }
        }
    }

    Matrix(const std::complex<double> inputMatrix[2][2]) {
        this->rows = 2;
        this->cols = 2;
        mat.resize(rows, std::vector<std::complex<double>>(cols, 0));
        for (size_t i = 0; i < 2; i++) {
            for (size_t j = 0; j < 2; j++) {
                mat[i][j] = inputMatrix[i][j];
            }
        }
    }

    Matrix(const std::complex<double> inputMatrix[2][2], std::string name) {
        this->rows = 2;
        this->cols = 2;
        this->name = name;
        mat.resize(rows, std::vector<std::complex<double>>(cols, 0));
        for (size_t i = 0; i < 2; i++) {
            for (size_t j = 0; j < 2; j++) {
                mat[i][j] = inputMatrix[i][j];
            }
        }
    }

    Matrix(std::complex<double> inputMatrix[4][4]) {
        this->rows = 4;
        this->cols = 4;
        mat.resize(rows, std::vector<std::complex<double>>(cols, 0));
        for (size_t i = 0; i < 4; i++) {
            for (size_t j = 0; j < 4; j++) {
                mat[i][j] = inputMatrix[i][j];
            }
        }
    }


    Matrix(const std::complex<double> inputMatrix[4][4]) {
        this->rows = 4;
        this->cols = 4;
        mat.resize(rows, std::vector<std::complex<double>>(cols, 0));
        for (size_t i = 0; i < 4; i++) {
            for (size_t j = 0; j < 4; j++) {
                mat[i][j] = inputMatrix[i][j];
            }
        }
    }

    Matrix(const std::complex<double> inputMatrix[4][4], std::string name) {
        this->rows = 4;
        this->cols = 4;
        this->name = name;
        mat.resize(rows, std::vector<std::complex<double>>(cols, 0));
        for (size_t i = 0; i < 4; i++) {
            for (size_t j = 0; j < 4; j++) {
                mat[i][j] = inputMatrix[i][j];
            }
        }
    }

    void set(int i, int j, std::complex<double>  val) {
        mat[i][j] = val;
    }

    std::complex<double> get(int i, int j) const {
        return mat[i][j];
    }

    std::string get_name() const {
        return this->name;
    }

    class MatrixRow {
    private:
        std::vector<std::complex<double>>& row;
    public:
        MatrixRow(std::vector<std::complex<double>>& r) : row(r) {}

        std::complex<double>& operator[](int j) {
            return row[j];
        }
    };

    MatrixRow operator[](int i) {
        return MatrixRow(mat[i]);
    }

    Matrix operator+(const Matrix& other) const {
        Matrix res(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                res.set(i, j, mat[i][j] + other.get(i, j));
            }
        }
        return res;
    }

    Matrix multiply(const Matrix& other) const {
        Matrix res(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                res.set(i, j, this->get(i, j) * other.get(i, j));
            }
        }
        return res;
    }

    Matrix multiply(const std::vector<std::complex<double>>& other) const {
        Matrix res(rows, 1);
        for (int i = 0; i < rows; i++) {
            std::complex<double> sum = 0;
            for (int k = 0; k < cols; k++) {
                sum += mat[i][k] * other[k];
            }
            res.set(i, 0, sum);
        }
        return res;
    }

    Matrix operator*(const Matrix& other) const {
        Matrix res(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                std::complex<double>  sum = 0;
                for (int k = 0; k < cols; k++) {
                    sum += mat[i][k] * other.get(k, j);
                }
                res.set(i, j, sum);
            }
        }
        return res;
    }

    Matrix operator*(std::complex<double> other) const {
        Matrix res(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                res.set(i, j, mat[i][j] * other);
            }
        }
        return res;
    }

    Matrix operator/(std::complex<double> other) const {
        Matrix res(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                res.set(i, j, mat[i][j] / other);
            }
        }
        return res;
    }

    Matrix operator*=(std::complex<double> other) const {
        Matrix res(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                res.set(i, j, mat[i][j] * other);
            }
        }
        return res;
    }

    Matrix operator/=(std::complex<double> other) const {
        Matrix res(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                res.set(i, j, mat[i][j] / other);
            }
        }
        return res;
    }

    bool operator!=(const Matrix& other) const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                if(mat[i][j] != other.get(i, j)){
                    return false;
                }
            }
        }
        return true;
    }

    int get_n_rows() const {
        return rows;
    }

    int get_n_cols() const {
        return cols;
    }

    void print() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << mat[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }


    static Matrix tensor(const Matrix matrix1, const Matrix other) {

        int other_rows = other.get_n_rows();
        int other_cols = other.get_n_cols();
        int rows = matrix1.get_n_rows();
        int cols = matrix1.get_n_cols();

        Matrix result(other_rows*rows, other_cols*cols);

        for (int i = 0; i < other_rows; i++) {
            for (int j = 0; j < other_cols; j++){
                // Internal loop
                std::complex<double> current = other.get(i, j);
                std::complex<double> res = 0;
                for(int internal_i = 0; internal_i<rows; internal_i++) {
                    for(int internal_j = 0; internal_j<cols; internal_j++) {
                        res = matrix1.get(internal_i, internal_j) * current;
                        int row_idx = internal_i+cols*j;
                        int col_idx = internal_j+rows*i;
                        result.set(row_idx, col_idx, res);       
                    }  
                }
            }
        }

        return result;
    }


};

#endif