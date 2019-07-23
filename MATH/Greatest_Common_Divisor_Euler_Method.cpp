
int GreatestCommonDivisor(int x, int y) {
      int a = abs(x);
      int b = abs(y);
      while ( a > 0 && b > 0) {
                  if (a > b) a = a%b;
                  else b = b%a;
              }
              return a + b;
  }

