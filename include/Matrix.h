#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

// Need a template here cus we have real and imaginary nums
template<typename Num, size_t rows_size, size_t columns_size>
class Matrix {
private:
    int rows, cols;
    std::vector< std::vector<Num> > mat;

public:
    Matrix(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        mat.resize(rows, std::vector<Num>(cols, 0));
    }


    Matrix(Num inputMatrix[rows_size][columns_size]) {
        this->rows = rows_size;
        this->cols = columns_size;
        mat.resize(rows, std::vector<Num>(cols, 0));
        for (size_t i = 0; i < rows_size; i++) {
            for (size_t j = 0; j < columns_size; j++) {
                mat[i][j] = inputMatrix[i][j];
            }
        }
    }

    void set(int i, int j, Num val) {
        mat[i][j] = val;
    }

    Num get(int i, int j) const {
        return mat[i][j];
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

    Matrix operator*(const Matrix& other) const {
        Matrix res(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                int sum = 0;
                for (int k = 0; k < cols; k++) {
                    sum += mat[i][k] * other.get(k, j);
                }
                res.set(i, j, sum);
            }
        }
        return res;
    }

    Matrix operator*(Num other) const {
        Matrix res(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                res.set(i, j, mat[i][j] * other);
            }
        }
        return res;
    }

    Matrix operator/(Num other) const {
        Matrix res(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                res.set(i, j, mat[i][j] / other);
            }
        }
        return res;
    }

    Matrix operator*=(Num other) const {
        Matrix res(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                res.set(i, j, mat[i][j] * other);
            }
        }
        return res;
    }

    Matrix operator/=(Num other) const {
        Matrix res(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                res.set(i, j, mat[i][j] / other);
            }
        }
        return res;
    }

    void print() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << mat[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};


#endif