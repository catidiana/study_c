#include "unsigned_big_integer.h"

//*************
//CONSTRUCTORS
//*************

Unsigned_Big_Integer :: Unsigned_Big_Integer () {
    num_size = 0;
}

Unsigned_Big_Integer :: Unsigned_Big_Integer (unsigned long long k) {
    num_size = 0;
    do {
        int i = k%10;
        number.push_back(i);
        num_size++;
        k /= 10;
    } while (k > 0);
}

Unsigned_Big_Integer :: Unsigned_Big_Integer (string s) {
    num_size = static_cast<int>(s.size());
    reverse(begin(s), end(s));
    for(const char& c: s) {
        int i = c - '0';
        number.push_back(i);
    }
}

//**************
//PUBLIC METHODS
//**************

int Unsigned_Big_Integer :: Get_Digit (int d) const {
    if (d < 0) throw invalid_argument("Digit should be positive");
    if (d >= num_size) return 0;
    return number.at(static_cast<size_t>(d));
}

int& Unsigned_Big_Integer :: Get_Digit (int d) {
    if (d < 0) throw invalid_argument("Digit should be positive");
    if (d >= num_size) throw invalid_argument("Number length exceeded");
    return number.at(static_cast<size_t>(d));
}

int Unsigned_Big_Integer :: Number_Length () const {
    return num_size;
}

int Unsigned_Big_Integer :: Digits_Sum () const {
    int result = 0;
    for (int i = 0;i <num_size;i++) {
        result = result + number.at(static_cast<size_t>(i));
    }
    return result;
}

void Unsigned_Big_Integer :: Add_Digit (int m) {
    if (m < 0 || m > 9) throw invalid_argument("Digit should be between 1 and 9");
    num_size++;
    number.push_back(m);
}

void Unsigned_Big_Integer :: Add_Zeroes (int k) {
    if (k < 0) throw invalid_argument("Digit should be positive");
    if (k == 0) return;
    for (int i = 0;i < k;i++) {
        num_size++;
        number.insert(number.begin(), 0);
    }
}

void Unsigned_Big_Integer :: Erase_Digit () {
    if (num_size > 0) {
    num_size--;
    number.pop_back();
    }
}

//********************
//OPERATORS DEFINITION
//********************

bool operator == (const Unsigned_Big_Integer& one, const Unsigned_Big_Integer& two) {
    if (one.Number_Length() != two.Number_Length()) return false;
    int number_size = one.Number_Length();
    for (int i = 0;i < number_size; i++) {
        if (one.Get_Digit(i)!=two.Get_Digit(i)) return false;
    }
    return true;
}

bool operator < (const Unsigned_Big_Integer& one, const Unsigned_Big_Integer& two) {
    if (one.Number_Length() < two.Number_Length()) return true;
    if (one.Number_Length() > two.Number_Length()) return false;
    int number_size = one.Number_Length();
    for (int i = number_size - 1;i >= 0; i--) {
        if (one.Get_Digit(i) < two.Get_Digit(i)) return true;
        if (one.Get_Digit(i) > two.Get_Digit(i)) return false;
    }
    return false;
}

Unsigned_Big_Integer operator + (const Unsigned_Big_Integer& one, const Unsigned_Big_Integer& two) {
    Unsigned_Big_Integer result = one;
    int length = max(one.Number_Length(), two.Number_Length());
    for (int i = 0;i < length;i++) {
        if (i >= result.Number_Length()) result.Add_Digit(two.Get_Digit(i));
        else {
            result.Get_Digit(i) = result.Get_Digit(i) + two.Get_Digit(i);
            if (result.Get_Digit(i) > 9) {
                if (i == result.Number_Length() - 1) result.Add_Digit(result.Get_Digit(i)/10);
                else result.Get_Digit(i+1) = result.Get_Digit(i+1) + result.Get_Digit(i)/10;
                result.Get_Digit(i) %= 10;
            }
        }
    }
    return result;
}

Unsigned_Big_Integer operator + (const Unsigned_Big_Integer& one, const unsigned long long& two) {
    Unsigned_Big_Integer two_b(two);
    return one + two_b;
}

Unsigned_Big_Integer operator + (const unsigned long long& one, const Unsigned_Big_Integer& two) {
    Unsigned_Big_Integer one_b(one);
    return one_b + two;
}

Unsigned_Big_Integer operator - (const Unsigned_Big_Integer& one, const Unsigned_Big_Integer& two) {
    if (one < two) throw logic_error("Result is negative for unsigned type");
    if (one == two) return Unsigned_Big_Integer(0);
    Unsigned_Big_Integer result = one;
    int length = two.Number_Length();
    for (int i = 0;i < length;i++) {
        if (result.Get_Digit(i) >= two.Get_Digit(i)) {
            result.Get_Digit(i) = result.Get_Digit(i) - two.Get_Digit(i);
        } else {
            --result.Get_Digit(i+1);
            result.Get_Digit(i) = result.Get_Digit(i) + 10 - two.Get_Digit(i);
        }
    }
    if (result.Get_Digit(result.Number_Length() - 1) == 0) {
        int j = result.Number_Length() - 1;
        while (result.Get_Digit(j) == 0) {
            result.Erase_Digit();
            j--;
        }
    }
    return result;
}

Unsigned_Big_Integer operator - (const Unsigned_Big_Integer& one, const unsigned long long& two) {
    Unsigned_Big_Integer two_b(two);
    return one - two_b;
}

Unsigned_Big_Integer multiplicator (const Unsigned_Big_Integer& number, int digit) {
    Unsigned_Big_Integer one = number;
    if (digit < 0 || digit > 9) throw logic_error("Put a digit from 0 to 9");
    if (digit == 0) return Unsigned_Big_Integer(0);
    int limit = one.Number_Length();
    int temp = 0;
    for (int i = 0;i < limit;i++) {
        one.Get_Digit(i) = one.Get_Digit(i)*digit + temp;
        if (one.Get_Digit(i) > 9) {
            if (i == limit - 1) one.Add_Digit(one.Get_Digit(i)/10);
            else temp = one.Get_Digit(i)/10;
            one.Get_Digit(i) %= 10;
        } else {
            temp = 0;
        }
    }
    return one;
}

Unsigned_Big_Integer operator * (const Unsigned_Big_Integer& one, int two) {
    if (two < 0) throw logic_error("Result is negative for unsigned type");
    if (two == 0) return Unsigned_Big_Integer(0);
    Unsigned_Big_Integer result;
    int power = 0;
    while (two > 0) {
        int i = two%10;
        Unsigned_Big_Integer temp = multiplicator(one, i);
        temp.Add_Zeroes(power);
        result = result + temp;
        power++;
        two /= 10;
    }
    return result;
}

istream& operator >> (istream& in, Unsigned_Big_Integer& number) {
    string s;
    in >> s;
    number = Unsigned_Big_Integer(s);
    return in;
}

ostream& operator << (ostream& out, const Unsigned_Big_Integer& number) {
    int start = number.Number_Length() - 1;
    for (int i = start;i >= 0;--i) {
        out << number.Get_Digit(i);
    }
    return out;
}

//*********
//FUNCTIONS
//*********

Unsigned_Big_Integer Big_Power (int a, int b) {
   Unsigned_Big_Integer result(1);
   for (int i = 0;i < b;i++) {
       result = result*a;
   }
   return result;
}

Unsigned_Big_Integer factorial (int n) {
    if (n == 0 || n == 1) return Unsigned_Big_Integer(1);
        else return factorial(n-1)*n;
}
