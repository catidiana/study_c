#include <iostream>
#include <matrix.h>

using namespace std;
// this function solves a system of linear equations:
// a00*x0 + ... + a0n*xn = b0;
// a10*x0 + ... + a1n*xn = b1;
// ...........
// an0*x0 + ... + ann*xn = bn;
// Using CRAMER algorithm
// input: matrix a(n, n), vector b(n);
// output: vector of solution x(n);
// please connect class "matrix.h" and "matrix.cpp" from the folder "CLASSES"
vector<double> CramersRule (const Matrix& coefficients, const vector<double>& constant) {
    if (coefficients.size_rows() > coefficients.size_columns()) throw logic_error("Not enough equations");
    if (coefficients.size_rows() < coefficients.size_columns()) throw logic_error("System is redundant");
    double main_det = Determinant(coefficients);
    if (main_det == 0.0) throw logic_error("System doesn't have solution");
    vector<double> result;
    int len = coefficients.size_rows();
    for (int i = 0; i < len;i++) {
        Matrix additional = coefficients;
        additional.push_back_column(constant);
        additional.swap_columns(i, len);
        additional.erase_column(len);
        double x = Determinant(additional)/main_det;
        result.push_back(x);
    }
    return result;
}
