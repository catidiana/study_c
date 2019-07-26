#pragma once
#ifndef RATIONAL_H
#define RATIONAL_H

#include <exception>
#include <string>
#include <iostream>

using namespace std;

//THIS CLASS ALLOWS YOU TO WORK WITH FRACTIONS p/q

class Rational {
public:
    Rational(); //create fraction 0/1
    Rational (int numerator); //create fraction p/1
    Rational(int numerator, int denominator); //create fraction p/q
    int Numerator() const; //return numerator;
    int Denominator() const; //return denominator
    double to_double (); //convert Rational fraction to double type
private:
  int GreatestCommonDivisor(int x, int y);
  int p;
  int q;
};


istream& operator >> (istream& stream, Rational& fraction);

ostream& operator << (ostream& stream, const Rational& fraction);

Rational operator + (const Rational& lhs, const Rational& rhs);

Rational operator - (const Rational& lhs, const Rational& rhs);

Rational operator * (const Rational& lhs, const Rational& rhs);

Rational operator / (const Rational& lhs, const Rational& rhs);

bool operator == (const Rational& lhs, const Rational& rhs);

bool operator < (const Rational& lhs, const Rational& rhs);

bool operator > (const Rational& lhs, const Rational& rhs);


#endif // RATIONAL_H
