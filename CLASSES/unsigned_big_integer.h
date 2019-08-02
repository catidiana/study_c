#pragma once
#ifndef UNSIGNED_BIG_INTEGER_H
#define UNSIGNED_BIG_INTEGER_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>
#include <stdexcept>
using namespace std;

class Unsigned_Big_Integer {
public:
    Unsigned_Big_Integer (); // creates empty vector;
    Unsigned_Big_Integer (unsigned long long k); //creates vector of number k digits (digits order is reversed, if k = 123, vector = {3, 2, 1};
    Unsigned_Big_Integer (string s); //inverts string to vector of digits, if s = "123", vector = {3, 2, 1};
    int Get_Digit (int d) const; //for a number 123: d = 0 returns 3, d = 1 returns 2, d = 2 returns 1;
    int& Get_Digit (int d);
    int Number_Length () const; //returns number length: for 123 is 3;
    int Digits_Sum () const; //returns the the sum of the digits: for 123 it's 1+2+3;
    void Add_Digit (int m); // converts 123 to m123, where m = 1 ... 9;
    void Add_Zeroes (int k); //converts 123 to 12300..0 adding k zeroes;
    void Erase_Digit (); // converts 123 to 23, erase highest digit;
private:
    int num_size;
    vector<int> number;
};

bool operator == (const Unsigned_Big_Integer& one, const Unsigned_Big_Integer& two);

bool operator < (const Unsigned_Big_Integer& one, const Unsigned_Big_Integer& two);

Unsigned_Big_Integer operator + (const Unsigned_Big_Integer& one, const Unsigned_Big_Integer& two);

Unsigned_Big_Integer operator + (const Unsigned_Big_Integer& one, const unsigned long long& two);

Unsigned_Big_Integer operator + (const unsigned long long& one, const Unsigned_Big_Integer& two);

Unsigned_Big_Integer operator - (const Unsigned_Big_Integer& one, const Unsigned_Big_Integer& two);

Unsigned_Big_Integer operator - (const Unsigned_Big_Integer& one, const unsigned long long& two);

//multiplication of a big integer and  a digit = 0 ... 9;
Unsigned_Big_Integer multiplicator (Unsigned_Big_Integer& number, int digit);

Unsigned_Big_Integer operator * (const Unsigned_Big_Integer& one, int two);

istream& operator >> (istream& in, Unsigned_Big_Integer& number);

ostream& operator << (ostream& out, const Unsigned_Big_Integer& number);

//Functions

Unsigned_Big_Integer Big_Power (int a, int b); //returns a^b

Unsigned_Big_Integer factorial (int n);
#endif // UNSIGNED_BIG_INTEGER_H
