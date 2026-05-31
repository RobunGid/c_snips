#include <cmath>
#include "algorithms.hpp"

double calculate_chudnovsky_pi(long n) {
	long double sum = 0.0L;

    for (long k = 0; k < n; ++k)
    {
        long double f6 = 1.0L, f3 = 1.0L, fk = 1.0L;

        for (long i = 1; i <= 6 * k; ++i) f6 *= i;
        for (long i = 1; i <= 3 * k; ++i) f3 *= i;
        for (long i = 1; i <= k; ++i) fk *= i;

        long double num = (k % 2 ? -1.0L : 1.0L) * f6 * (13591409.0L + 545140134.0L * k);
        long double den = f3 * fk * fk * fk * pow(640320.0L, 3.0L * k + 1.5L);

        sum += num / den;
    }

    return (double)(1.0L / (12.0L * sum));
}

double calculate_ramanujan_pi(long n) {
    long double sum = 0.0L;

    for (long k = 0; k < n; ++k)
    {
        long double f4k = 1.0L, fk = 1.0L;

        for (long i = 1; i <= 4 * k; ++i) f4k *= i;
        for (long i = 1; i <= k; ++i) fk *= i;

        long double num = f4k * (1103.0L + 26390.0L * k);
        long double den = pow(fk, 4.0L) * pow(396.0L, 4.0L * k);

        sum += num / den;
    }

    long double factor = (2.0L * sqrt(2.0L) / 9801.0L);
    return (double)(1.0L / (factor * sum));
}

double calculate_gauss_legendre_pi(long n) {
    long double a = 1.0L;
    long double b = 1.0L / sqrt(2.0L);
    long double t = 0.25L;
    long double p = 1.0L;

    for (long i = 0; i < n; ++i)
    {
        long double an = (a + b) / 2.0L;
        long double bn = sqrt(a * b);
        long double tn = t - p * (a - an) * (a - an);
        long double pn = 2.0L * p;

        a = an;
        b = bn;
        t = tn;
        p = pn;
    }

    return (double)((a + b) * (a + b) / (4.0L * t));
}

double calculate_bbp_pi(long n) {
    long double sum = 0.0L;

    for (long k = 0; k < n; ++k)
    {
        long double ak = 1.0L / pow(16.0L, k);

        long double term =
            ak * (
                4.0L / (8.0L * k + 1.0L) -
                2.0L / (8.0L * k + 4.0L) -
                1.0L / (8.0L * k + 5.0L) -
                1.0L / (8.0L * k + 6.0L)
            );

        sum += term;
    }

    return (double)sum;
}