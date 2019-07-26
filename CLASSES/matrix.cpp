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
    vector<double> row1 = get_row(r1);
    vector<double> row2 = get_row(r2);
    for (int i = 0; i < columns; i++) {
        get(r1, i) = row2.at(i);
        get(r2, i) = row1.at(i);
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

