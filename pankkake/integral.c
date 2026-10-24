#include <stdio.h>
#include <math.h>
#define N 1000000

double f(double x) {
    return x; //<--Здесь указывается функция для интегрирования
}
double integral(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
    for (int i = 1; i < n; i++) {
        sum += f(a + i * h);
    }
    return sum * h;
}
int main() {
    double a, b;
    printf("Enter lower bound (a): ");
    scanf("%lf", &a);
    printf("Enter upper bound (b): ");
    scanf("%lf", &b);
    double result = integral(a, b, N);
    printf("Integral value: %.6f\n", result);
    return 0;
}
