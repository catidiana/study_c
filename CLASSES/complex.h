#ifndef COMPLEX_H
#define COMPLEX_H


#include <exception>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

class Complex {
public:
    double re; //REAL PART
    double im; //IMAGINARY PART
    Complex (); // create 0;
    Complex (double a); // create a;
    Complex (double a, double b); //create a+ib;
};

istream& operator >> (istream& stream, Complex& number);

ostream& operator << (ostream& stream, const Complex& number);

Complex operator + (const Complex& lhs, const Complex& rhs);

Complex operator - (const Complex& lhs, const Complex& rhs);

Complex operator * (const Complex& lhs, const Complex& rhs);

Complex operator / (const Complex& lhs, const Complex& rhs);

bool operator == (const Complex& lhs, const Complex& rhs);

//FUNCTIONS

double complex_modulus (const Complex& num);

#endif // COMPLEX_H
