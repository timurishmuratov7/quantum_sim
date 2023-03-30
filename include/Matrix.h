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


template<typename Num, size_t rows, size_t cols, size_t other_rows, size_t other_cols>
Matrix<Num, rows*other_rows, cols*other_cols> tensor(const Matrix<Num, rows, cols> matrix1, const Matrix<Num, other_rows, other_cols> other) {

        Matrix<Num, rows*other_rows, cols*other_cols> result(other_rows*rows, other_cols*cols);

        for (int i = 0; i < other_rows; i++) {
            for (int j = 0; j < other_cols; j++){
                // Internal loop
                Num current_num = other.get(i, j);
                Num res = 0;
                for(int internal_i = 0; internal_i<rows; internal_i++) {
                    for(int internal_j = 0; internal_j<cols; internal_j++) {
                        res = matrix1.get(internal_i, internal_j) * current_num;
                        int row_idx = internal_i+cols*j;
                        int col_idx = internal_j+rows*i;
                       // std::cout << "row_idx: " <<  row_idx << ", col_idx: " << col_idx
                       // << ", curr_num * mat_val: " << current_num << "*" << matrix1.get(internal_i, internal_j) << " = " << res << std::endl;

                        result.set(row_idx, col_idx, res);     
                        
                        if (row_idx == 1 && col_idx == 1) {
                            std::cout << "res is set to: " << res << std::endl;
                            result.print();
                        }                  
                    }  
                }
            }
        }
        //result.print();

        return result;

    }


#endif