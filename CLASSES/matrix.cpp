#include "matrix.h"

//**************
//PUBLIC METHODS
//**************

Matrix :: Matrix(){
    rows = 0;
    columns = 0;
}
Matrix :: Matrix(int r, int c){
    if (r < 0 || c < 0 ) {
        throw logic_error("Invalid matrix dimension");
    } else if (r == 0 || c == 0) {
        rows = 0;
        columns = 0;
    } else {
        rows = r;
        columns = c;
        elements.assign(static_cast<size_t>(rows), vector<double>(static_cast<size_t>(columns)));
    }
}
double& Matrix :: get(int r, int c) {
    if (r < 0 || c < 0) {
        throw logic_error("Invalid matrix dimension");
    } else if (r >= rows || c >= columns) {
        throw logic_error("Out of range");
    }
    return elements.at(static_cast<size_t>(r)).at(static_cast<size_t>(c));
}
double Matrix :: Matrix :: get(int r, int c) const {
    if (r < 0 || c < 0) {
        throw logic_error("Invalid matrix dimension");
    } else if (r >= rows || c >= columns) {
        throw logic_error("Out of range");
    }
    return elements.at(static_cast<size_t>(r)).at(static_cast<size_t>(c));
}
vector<double> Matrix :: get_row (int r) const {
    if (r < 0) {
        throw logic_error("Invalid matrix dimension");
    } else if (r >= rows) {
        throw logic_error("Out of range");
    }
    vector<double> result = elements.at(static_cast<size_t>(r));
    return result;
}
vector<double>  Matrix :: get_column (int c) const {
    if (c < 0) {
        throw logic_error("Invalid matrix dimension");
    } else if (c >= columns) {
        throw logic_error("Out of range");
    }
    vector<double> result;
    for (int i = 0;i < rows;i++) {
        result.push_back(elements.at(static_cast<size_t>(i)).at(static_cast<size_t>(c)));
    }
    return result;
}
int Matrix :: size_rows() const {
    return rows;
}
int Matrix :: size_columns() const {
    return columns;
}
int Matrix :: size() const {
    return rows*columns;
}
void Matrix :: push_back_row (const vector<double>& v) {
    if(static_cast<int>(v.size()) != columns) {
        throw logic_error("Invalid vector dimension");}
    rows++;
    elements.push_back(v);
}
void Matrix :: push_back_column (const vector<double>& v) {
    if(static_cast<int>(v.size()) != rows) {
        throw logic_error("Invalid vector dimension");}
    columns++;
    for (int i = 0;i < rows;i++) {
        elements[i].push_back(v[i]);
    }
}
void Matrix :: insert_down (const Matrix& new_matrix) {
    if (new_matrix.size_columns() != columns) {
        throw logic_error("Invalid matrix dimension");
    }
    rows = rows + new_matrix.size_rows();
    for (int i = 0; i < new_matrix.size_rows(); i++) {
        vector<double> add = new_matrix.get_row(i);
        elements.push_back(add);
    }
}
void Matrix :: insert_right (const Matrix& new_matrix) {
    if (new_matrix.size_rows() != rows) {
        throw logic_error("Invalid matrix dimension");
    }
    for (int i = 0; i < new_matrix.size_columns(); i++) {
        vector<double> add = new_matrix.get_column(i);
        push_back_column(add);
    }
}
void Matrix :: swap_rows (int r1, int r2) {
    if (r1 < 0 || r2 < 0) {
        throw logic_error("Invalid matrix dimension");
    } else if (r1 >= rows || r2 >= rows) {
        throw logic_error("Out of range");
    }
    for (int i = 0; i < columns; i++) {
        double temp = get(r1, i);
        get(r1, i) = get(r2, i);
        get(r2, i) = temp;
    }
}
void Matrix :: swap_columns (int c1, int c2) {
    if (c1 < 0 || c2 < 0) {
        throw logic_error("Invalid matrix dimension");
    } else if (c1 >= columns || c2 >= columns) {
        throw logic_error("Out of range");
    }
    for (int i = 0;i < rows;i++) {
        double temp = get(i, c1);
        get(i, c1) = get(i, c2);
        get(i, c2) = temp;
    }
}
void Matrix :: erase_row (int r) {
    if (r < 0) {
        throw logic_error("Invalid matrix dimension");
    } else if (r >= rows) {
        throw logic_error("Out of range");
    }
    elements.erase(elements.begin() + r);
    rows--;
}
void Matrix :: erase_column (int c) {
    if (c < 0) {
        throw logic_error("Invalid matrix dimension");
    } else if (c >= columns) {
        throw logic_error("Out of range");
    }
    for (int i = 0;i < rows;i++) {
        elements[i].erase(elements[i].begin() + c);
    }
    columns--;
}
void Matrix :: make_zero() {
    for (int i = 0;i < rows;i++) {
        elements[i].assign(static_cast<size_t>(columns), 0.0);
    }
}
void Matrix :: make_identity(int n) {
    if (n < 0)
        throw logic_error("Invalid matrix dimension");
    rows = n;
    columns = n;
    elements.assign(static_cast<size_t>(n), vector<double>(static_cast<size_t>(n)));
    for (int i = 0;i < n; i++) {
        get(i, i) = 1;
    }
}
void Matrix :: transpose() {
    Matrix result(columns, rows);
    for (int i = 0;i<rows;i++) {
        for (int j = 0; j < columns;j++) {
            result.get(j, i) = get(i, j);
        }
    }
    int temp = columns;
    columns = rows;
    rows = temp;
    elements.assign(static_cast<size_t>(rows), vector<double>(static_cast<size_t>(columns)));
        for (int i = 0;i<rows;i++) {
            for (int j = 0; j < columns;j++) {
                get(i, j) = result.get(i, j);
            }
    }
}


//********************
//OPERATORS DEFINITION
//********************

bool operator==(const Matrix& one, const Matrix& two) {
    if (one.size_rows() != two.size_rows() || one.size_columns() != two.size_columns()) {
        return false;
    }
    for (int r = 0; r < one.size_rows(); r++) {
        for (int c = 0; c < one.size_columns(); c++) {
            if (one.get(r, c) != two.get(r, c)) {
                return false;
            }
        }
    }
    return true;
}

Matrix operator+(const Matrix& one, const Matrix& two) {
    if (one.size_rows() != two.size_rows() || one.size_columns() != two.size_columns()) {
        throw invalid_argument("Mismatched matrix dimensions");
    }
    Matrix result(one.size_rows(), one.size_columns());
    for (int r = 0; r < result.size_rows(); r++) {
        for (int c = 0; c < result.size_columns(); c++) {
            result.get(r, c) = one.get(r, c) + two.get(r, c);
        }
    }
    return result;
}

Matrix operator-(const Matrix& one, const Matrix& two) {
    if (one.size_rows() != two.size_rows() || one.size_columns() != two.size_columns()) {
        throw invalid_argument("Mismatched matrix dimensions");
    }
    Matrix result(one.size_rows(), one.size_columns());
    for (int r = 0; r < result.size_rows(); r++) {
        for (int c = 0; c < result.size_columns(); c++) {
            result.get(r, c) = one.get(r, c) - two.get(r, c);
        }
    }
    return result;
}

Matrix operator*(const Matrix& one, const Matrix& two) {
    if (one.size_columns() != two.size_rows()) {
        throw invalid_argument("Mismatched matrix dimensions");
    }
    Matrix result(one.size_rows(), two.size_columns());
    for (int r = 0; r < one.size_rows(); r++) {
        for (int c = 0; c < two.size_columns(); c++) {
            for (int i = 0;i < one.size_columns();i++) {
                result.get(r, c) = result.get(r, c) + one.get(r, i)*two.get(i, c);
            }
        }
    }
    return result;
}

Matrix operator*(double alfa, const Matrix& matrix) {
    Matrix result(matrix.size_rows(), matrix.size_columns());
    for (int r = 0; r < matrix.size_rows(); r++) {
        for (int c = 0; c < matrix.size_columns(); c++) {
            result.get(r, c) = alfa*matrix.get(r, c);
        }
    }
    return result;
}

istream& operator>>(istream& stream, Matrix& matrix) {
    for (int r = 0; r < matrix.size_rows(); r++) {
        for (int c = 0; c < matrix.size_columns(); c++) {
            stream >> matrix.get(r, c);
        }
    }
    return stream;
}

ostream& operator<<(ostream& stream, const Matrix& matrix) {
    for (int r = 0; r < matrix.size_rows(); r++) {
        for (int c = 0; c < matrix.size_columns(); c++) {
            if (c > 0) {
                stream << " ";
            }
            stream << setw(10) << matrix.get(r, c);
        }
        stream << endl;
    }
    return stream;
}

//*********
//FUNCTIONS
//*********

double Determinant (const Matrix& matrix) {
    if (matrix.size_rows() != matrix.size_columns())
        throw logic_error("Determinant can be calculated only for a square matrix");
    if (matrix.size_rows() == 1) return matrix.get(0, 0);
    double result = 0.0;
    for (int i = 0;i < matrix.size_rows(); i++) {
        int sign = 1;
        Matrix next = matrix;
        next.erase_row(0);
        next.erase_column(i);
        if (i%2 == 1) sign = -1;
        result = result + sign*matrix.get(0, i)*Determinant(next);
    }
    return result;
}

int Rang(Matrix matrix) {
    bool break_flag = false;
    do {
        for (int i = 0;i < matrix.size_rows();i++) {
            double s = matrix.get(i, i);
            if (s == 0.0) {
                vector<double> check_row = matrix.get_row(i);
                check_row.pop_back();
                double sum = 0;
                for (const auto& c: check_row) {
                    sum = sum + c;
                }
                if (sum == 0.0) {
                    matrix.erase_row(i);
                    break_flag = true;
                    break;
                } else {
                    int swap_step1 = 1;
                    while (swap_step1 < matrix.size_rows() - i) {
                        matrix.swap_rows(i, i + swap_step1);
                        swap_step1++;
                        if (matrix.get(i, i) != 0.0) break;
                    }
                    s = matrix.get(i, i);
                    if (s == 0.0) {
                        int swap_step2 = 0;
                        while (swap_step2 < i) {
                            matrix.swap_rows(i, swap_step2);
                            if (matrix.get(i, i) != 0.0) break;
                            swap_step2++;
                        }
                        s = matrix.get(i, i);
                        if (s == 0.0) {
                            matrix.erase_column(i);
                            break_flag = true;
                            break;
                        }
                    }
                }
            }
            for (int j = 0;j < matrix.size_columns();j++) {
                matrix.get(i, j) = matrix.get(i, j)/s;
            }
            for (int k = 0; k < matrix.size_rows(); k++) {
                if (k != i) {
                    double m = matrix.get(k, i);
                    for (int l = 0; l < matrix.size_columns(); l++) {
                        matrix.get(k, l) = matrix.get(k,l) - m*matrix.get(i, l);
                    }
                }
            }
            break_flag = false;
        }
    } while (break_flag == true);
    return min(matrix.size_rows(), matrix.size_columns());
}

double Trace(const Matrix& matrix) {
    if (matrix.size_rows() != matrix.size_columns())
        throw logic_error("Trace can be calculated only for a square matrix");
    double trace = 0;
    for (int i = 0; i < matrix.size_rows(); i++) {
        trace = trace + matrix.get(i, i);
    }
    return trace;
}
