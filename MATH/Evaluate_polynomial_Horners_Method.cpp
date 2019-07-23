//evaluate polynomial a[n]*x^n + ... + a[2]*x^2 + a[1]*x + a[0]
// N - array size, n = N-1
double HornersMethod(double *a, int N, double x) {
    double result = a[N-1];
    for (int i = N-2;i>=0;i--) {
        result = result*x + a[i];
    }
    return result;
}