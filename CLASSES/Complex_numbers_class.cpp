#include <exception>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

class Complex {
public:
    double re;
    double im;
    Complex () {
        re = 0;
        im = 0;
    }
    Complex (double a) {
        re = a;
        im = 0;
    }
    Complex (double a, double b) {
        re = a;
        im = b;
    }
};

inline double complex_modulus (const Complex& num) {
    return sqrt(num.re*num.re + num.im*num.im);
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
        number.re = stod(n);
        number.im = 0;
    } else if (i_position == -1 && sign_position > 0)
        throw invalid_argument("wrong number format");
    else if (i_position != len - 1)
        throw invalid_argument("wrong number format");
    else if (i_position == 0) {
        number.re = 0;
        number.im = 1;
    } else if (i_position == 1 && sign_position == 0) {
        if (n[0] == '+') {
            number.re = 0;
            number.im = 1;
        } else {
            number.re = 0;
            number.im = -1;
        }
    } else if (i_position > 0 && sign_position <=0) {
        n.pop_back();
        number.re = 0;
        number.im = stod(n);
    } else {
string n1 = n.substr(0, sign_position);
string n2 = n.substr(sign_position, len - sign_position);
number.re = stod(n1);
if (n2 == "+i") number.im = 1;
else if (n2 == "-i") number.im = -1;
else number.im = stod(n2);
}
    return stream;
}

inline ostream& operator << (ostream& stream, const Complex& number) {
    if (number.im == 0.0) stream << number.re;
    else if(number.re == 0.0 && number.im != 0) {
        if (number.im == 1.0) stream << "i";
        else if (number.im == -1.0) stream << "-i";
        else stream << number.im << "i";
    }
    else {
        stream << number.re;
        if (number.im == 1.0) stream << "+i";
        else if (number.im == -1.0) stream << "-i";
        else if (number.im > 0.0) stream << "+" << number.im << "i";
        else stream << number.im << "i";
    }
    return stream;
}

inline Complex operator + (const Complex& lhs, const Complex& rhs) {
    Complex result(lhs.re+rhs.re, lhs.im+rhs.im);
    return result;
}

inline Complex operator - (const Complex& lhs, const Complex& rhs) {
    Complex result(lhs.re-rhs.re, lhs.im-rhs.im);
    return result;
}

inline Complex operator * (const Complex& lhs, const Complex& rhs) {
    Complex result(lhs.re*rhs.re - lhs.im*rhs.im, lhs.re*rhs.im + lhs.im*rhs.re);
    return result;
}

inline Complex operator / (const Complex& lhs, const Complex& rhs) {
    if (rhs.re == 0.0 && rhs.im == 0.0)
        throw invalid_argument("Division by zero");
    Complex result((lhs.re*rhs.re + lhs.im*rhs.im)/(rhs.re*rhs.re + rhs.im*rhs.im),
                   (lhs.im*rhs.re - lhs.re*rhs.im)/(rhs.re*rhs.re + rhs.im*rhs.im));
    return result;
}

inline bool operator == (const Complex& lhs, const Complex& rhs) {
    return lhs.re == rhs.re &&
           lhs.im == rhs.im;
}
