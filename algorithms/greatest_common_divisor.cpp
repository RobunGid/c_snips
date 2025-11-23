#include "algorithms.hpp"

int greatest_common_divisor (int a, int b) {
    while (b > 0) {
        a %= b;
		a = a + b;
		b = a - b;
		a = a - b;
    }
    return a;
}
