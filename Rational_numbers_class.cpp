#include <exception>
#include <string>
#include <iostream>

using namespace std;

class Rational {
public:
    Rational() {
        p = 0;
        q = 1;
    }
    Rational (int numerator) {
        p = numerator;
        q = 1;
    }
    Rational(int numerator, int denominator) {
        if (denominator == 0)
            throw invalid_argument("zero denominator");
        int gcd = GreatestCommonDivisor(numerator, denominator);
        // keep only irreducible fraction
        numerator = numerator/gcd;
        denominator = denominator/gcd;
        //numerator keeps fraction sign
        if (denominator > 0)
        {
            p = numerator;
            q = denominator;
        } else {
            p = - numerator;
            q = - denominator;
        }
    }

    int Numerator() const {
        return p;
    }
    int Denominator() const {
        return q;
    }
    double to_double () {
        double n = static_cast<double>(p)/static_cast<double>(q);
        return n;
    }
private:
  int GreatestCommonDivisor(int x, int y) {
      int a = abs(x);
      int b = abs(y);
      while ( a > 0 && b > 0) {
                  if (a > b) a = a%b;
                  else b = b%a;
              }
              return a + b;
  }
  int p;
  int q;
};


istream& operator >> (istream& stream, Rational& fraction) {
    string n;
    stream >> n;
    int len = static_cast<int>(n.size());
    int slash_position = -1;
    for (int i = 0;i < len;i++) {
        if (n[i] == '/') {
            slash_position = i;
            break;
        }
    }
    if (slash_position == -1 && stream) {
        fraction = Rational(stoi(n));
    }
    else if (slash_position == 0)
        throw invalid_argument("missed numerator");
    else {
        string n1 = n.substr(0, slash_position);
        string n2 = n.substr(slash_position+1, len-1);
        fraction = Rational(stoi(n1), stoi(n2));
    }
    return stream;
}

ostream& operator << (ostream& stream, const Rational& fraction) {
    if (fraction.Denominator() != 1) stream << fraction.Numerator() << '/' << fraction.Denominator();
    else stream << fraction.Numerator();
    return stream;
}

Rational operator + (const Rational& lhs, const Rational& rhs) {
    Rational result(lhs.Numerator()*rhs.Denominator() + rhs.Numerator()*lhs.Denominator(), lhs.Denominator()*rhs.Denominator());
    return result;
}

Rational operator - (const Rational& lhs, const Rational& rhs) {
    Rational result(lhs.Numerator()*rhs.Denominator() - rhs.Numerator()*lhs.Denominator(), lhs.Denominator()*rhs.Denominator());
    return result;
}

Rational operator * (const Rational& lhs, const Rational& rhs) {
    Rational result(lhs.Numerator()*rhs.Numerator(), lhs.Denominator()*rhs.Denominator());
    return result;
}

Rational operator / (const Rational& lhs, const Rational& rhs) {
    if (rhs.Numerator() == 0)
        throw invalid_argument("Division by zero");
    Rational result(lhs.Numerator()*rhs.Denominator(), lhs.Denominator()*rhs.Numerator());
    return result;
}

bool operator == (const Rational& lhs, const Rational& rhs) {
    return lhs.Numerator() == rhs.Numerator() &&
           lhs.Denominator() == rhs.Denominator();
}

bool operator < (const Rational& lhs, const Rational& rhs) {
    Rational dif = lhs - rhs;
    return dif.Numerator() < 0;
}
