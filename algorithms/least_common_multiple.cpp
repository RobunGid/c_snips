#include "algorithms.hpp"
#include <cassert>
#include <numeric>

int least_common_multiple (int a, int b) {
    return a / greatest_common_divisor(a, b) * b;
}

