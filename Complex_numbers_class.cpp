#include <exception>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

class Complex {
public:
    double real;
    double imaginary;
    Complex () {
        real = 0;
        imaginary = 0;
    }
    Complex (double a) {
        real = a;
        imaginary = 0;
    }
    Complex (double a, double b) {
        real = a;
        imaginary = b;
    }
};

inline double complex_modulus (const Complex& num) {
    return sqrt(num.real*num.real + num.imaginary*num.imaginary);
}

inline istream& operator >> (istream& stream, Complex& number) {
    string n;
    stream >> n;
    int len = static_cast<int>(n.size());
    int sign_position = -1;
    int i_position = -1;
    for (int j = 0;j < len;j++) {
        if (n[j] == '+' || n[j] == '-') sign_position = j;
        else if(n[j] == 'i') i_position = j;
    }
    if (i_position == -1 && sign_position <= 0) {
        number.real = stod(n);
        number.imaginary = 0;
    } else if (i_position == -1 && sign_position > 0)
        throw invalid_argument("wrong number format");
    else if (i_position != len - 1)
        throw invalid_argument("wrong number format");
    else if (i_position == 0) {
        number.real = 0;
        number.imaginary = 1;
    } else if (i_position == 1 && sign_position == 0) {
        if (n[0] == '+') {
            number.real = 0;
            number.imaginary = 1;
        } else {
            number.real = 0;
            number.imaginary = -1;
        }
    } else if (i_position > 0 && sign_position <=0) {
        n.pop_back();
        number.real = 0;
        number.imaginary = stod(n);
    } else {
string n1 = n.substr(0, sign_position);
string n2 = n.substr(sign_position, len - sign_position);
number.real = stod(n1);
if (n2 == "+i") number.imaginary = 1;
else if (n2 == "-i") number.imaginary = -1;
else number.imaginary = stod(n2);
}
    return stream;
}

inline ostream& operator << (ostream& stream, const Complex& number) {
    if (number.imaginary == 0.0) stream << number.real;
    else if(number.real == 0.0 && number.imaginary != 0) {
        if (number.imaginary == 1.0) stream << "i";
        else if (number.imaginary == -1.0) stream << "-i";
        else stream << number.imaginary << "i";
    }
    else {
        stream << number.real;
        if (number.imaginary == 1.0) stream << "+i";
        else if (number.imaginary == -1.0) stream << "-i";
        else if (number.imaginary > 0.0) stream << "+" << number.imaginary << "i";
        else stream << number.imaginary << "i";
    }
    return stream;
}

inline Complex operator + (const Complex& lhs, const Complex& rhs) {
    Complex result(lhs.real+rhs.real, lhs.imaginary+rhs.imaginary);
    return result;
}

inline Complex operator - (const Complex& lhs, const Complex& rhs) {
    Complex result(lhs.real-rhs.real, lhs.imaginary-rhs.imaginary);
    return result;
}

inline Complex operator * (const Complex& lhs, const Complex& rhs) {
    Complex result(lhs.real*rhs.real - lhs.imaginary*rhs.imaginary, lhs.real*rhs.imaginary + lhs.imaginary*rhs.real);
    return result;
}

inline Complex operator / (const Complex& lhs, const Complex& rhs) {
    if (rhs.real == 0.0 && rhs.imaginary == 0.0)
        throw invalid_argument("Division by zero");
    Complex result((lhs.real*rhs.real + lhs.imaginary*rhs.imaginary)/(rhs.real*rhs.real + rhs.imaginary*rhs.imaginary),
                   (lhs.imaginary*rhs.real - lhs.real*rhs.imaginary)/(rhs.real*rhs.real + rhs.imaginary*rhs.imaginary));
    return result;
}

inline bool operator == (const Complex& lhs, const Complex& rhs) {
    return lhs.real == rhs.real &&
           lhs.imaginary == rhs.imaginary;
}
