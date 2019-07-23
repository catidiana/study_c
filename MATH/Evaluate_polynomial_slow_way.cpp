//evaluate polynomial a[n]*x^n + ... + a[2]*x^2 + a[1]*x + a[0]
// N - array size, n = N-1
double Evaluate(double *a, int N, double x) {
    double result = a[0];
    double x_pow = 1;
    for (int i = 1;i < N;i++) {
        x_pow = x_pow*x;
        result = result + a[i]*x_pow;
    }
    return result;
}
