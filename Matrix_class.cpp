#include <iostream>
#include <exception>
#include <vector>
#include <iomanip>

using namespace std;

class Matrix {
public:
    Matrix(){
        rows = 0;
        columns = 0;
    }
    Matrix(int r, int c){
        if (r < 0 || c < 0 ) {
            throw "Invalid matrix dimension";
        } else if (r == 0 || c == 0) {
            rows = 0;
            columns = 0;
        } else {
            rows = r;
            columns = c;
            elements.assign(static_cast<size_t>(rows), vector<double>(static_cast<size_t>(columns)));
        }
    }
    double& get(int r, int c) {
        if (r < 0 || c < 0) {
            throw "Invalid matrix dimension";
        } else if (r >= rows || c >= columns) {
            throw "Out of range";
        }
        return elements.at(static_cast<size_t>(r)).at(static_cast<size_t>(c));
    }
    double get(int r, int c) const {
        if (r < 0 || c < 0) {
            throw "Invalid matrix dimension";
        } else if (r >= rows || c >= columns) {
            throw "Out of range";
        }
        return elements.at(static_cast<size_t>(r)).at(static_cast<size_t>(c));
    }
    int size_rows() const {
        return rows;
    }
    int size_columns() const {
        return columns;
    }
    int size() const {
        return rows*columns;
    }
    template<typename T>
    void push_back_row (const vector<T>& v) {
        if(static_cast<int>(v.size()) != columns) {
            throw "Invalid vector dimension";}
        rows++;
        vector<double> add;
        for (auto c: v) {
            add.push_back(c);
        }
        elements.push_back(add);
    }
    template<typename T>
    void push_back_column (const vector<T>& v) {
        if(static_cast<int>(v.size()) != rows) {
            throw "Invalid vector dimension";}
        columns++;
        for (int i = 0;i < rows;i++) {
            elements[i].push_back(v[i]);
        }
    }
private:
    int rows;
    int columns;
    vector<vector<double>> elements;
};

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

template <typename T>
Matrix operator*(T alfa, const Matrix& matrix) {
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


int main()
{
    Matrix a(2, 2);
    vector<int> n = {12, 1};
    a.push_back_column(n);
    cout << a;
    cout << "Hello World!" << endl;
    return 0;
}
