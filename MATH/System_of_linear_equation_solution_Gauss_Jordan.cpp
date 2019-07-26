#include <iostream>
#include <exception>
#include <matrix.h>

using namespace std;
// this function solves a system of linear equations:
// a00*x0 + ... + a0n*xn = b0;
// a10*x0 + ... + a1n*xn = b1;
// ...........
// an0*x0 + ... + ann*xn = bn;
// Using Gauss- Jordan Elimination algorithm
// input: matrix a(n, n), vector b(n);
// output: vector of solution x(n);
// please connect class "matrix.h" and "matrix.cpp" from the folder "CLASSES"

vector<double> GaussJordanElimination(const Matrix& coefficients, const vector<double>& constant) {
    if (coefficients.size_rows() > coefficients.size_columns()) throw logic_error("Not enough equations");
    if (coefficients.size_rows() < coefficients.size_columns()) throw logic_error("System is redundant");
    Matrix unighted = coefficients;
    unighted.push_back_column(constant);
    for (int i = 0;i < unighted.size_rows();i++) {
        double s = unighted.get(i, i);
        if (s == 0.0) {
            vector<double> check_row = unighted.get_row(i);
            check_row.pop_back();
            double sum = 0;
            for (const auto& c: check_row) {
                sum = sum + c;
            }
            if (sum == 0.0) throw logic_error("System doesn't have solution");
            int swap_step1 = 1;
            while (swap_step1 < unighted.size_rows() - i) {
                unighted.swap_rows(i, i + swap_step1);
                swap_step1++;
                if (unighted.get(i, i) != 0.0) break;
            }
            s = unighted.get(i, i);
            if (s == 0.0) {
                int swap_step2 = 0;
                while (swap_step2 < i) {
                    unighted.swap_rows(i, swap_step2);
                    if (unighted.get(i, i) != 0.0) break;
                    swap_step2++;
                }
                s = unighted.get(i, i);
                if (s == 0.0) {
                    throw logic_error("System doesn't have solution");
                } else {
                    i = 0;
                    s = unighted.get(i, i);
                }
            }
        }
        for (int j = 0;j < unighted.size_columns();j++) {
            unighted.get(i, j) = unighted.get(i, j)/s;
        }
        for (int k = 0; k < unighted.size_rows(); k++) {
            if (k != i) {
                double m = unighted.get(k, i);
                for (int l = 0; l < unighted.size_columns(); l++) {
                    unighted.get(k, l) = unighted.get(k,l) - m*unighted.get(i, l);
                }
            }
        }
    }
    return unighted.get_column(unighted.size_columns()-1);
}
