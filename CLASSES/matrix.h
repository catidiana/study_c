#pragma once
#ifndef MATRIX_H
#define MATRIX_H


#include <iostream>
#include <exception>
#include <vector>
#include <iomanip>

using namespace std;

class Matrix {
public:
    Matrix(); //Create matrix with 0 rows and columns
    Matrix(int r, int c); //Create matrix with r rows and  c columns
    double& get(int r, int c); // Return element in a row #r and a column #c
    double get(int r, int c) const;
    vector<double> get_row (int r) const; //Return vector from a row #r
    vector<double> get_column (int c) const; //Return vector from a column #c
    int size_rows() const; //Return amount of rows
    int size_columns() const; //Return amount of columns
    int size() const; //Return amount of elements
    void push_back_row (const vector<double>& v); //add vector as a new row
    void push_back_column (const vector<double>& v); //add vector as a new column
    void insert_down (const Matrix& new_matrix); // add new matrix as rows to existing one
    void insert_right (const Matrix& new_matrix); // add new matrix as columns to existing one
    void swap_rows (int r1, int r2); // swap rows #r1 and #r2
private:
    int rows;
    int columns;
    vector<vector<double>> elements;
};

bool operator==(const Matrix& one, const Matrix& two);

Matrix operator+(const Matrix& one, const Matrix& two);

Matrix operator-(const Matrix& one, const Matrix& two);

Matrix operator*(const Matrix& one, const Matrix& two);

Matrix operator*(double alfa, const Matrix& matrix);

istream& operator>>(istream& stream, Matrix& matrix);

ostream& operator<<(ostream& stream, const Matrix& matrix);






#endif // MATRIX_H
