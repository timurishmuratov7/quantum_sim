#ifndef INITIALSTATE_H
#define INITIALSTATE_H

#include <iostream>
#include <vector>

class Matrix {
private:
    int rows, cols;
    std::vector< std::vector<int> > mat;

public:
    Matrix(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        mat.resize(rows, std::vector<int>(cols, 0));
    }

    void set(int i, int j, int val) {
        mat[i][j] = val;
    }

    int get(int i, int j) const {
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