#include <cassert>
#include <numeric>
#include <iostream>
#include "algorithms.hpp"

int main() {
    assert(greatest_common_divisor(10, 5) == 5);
    assert(greatest_common_divisor(54, 24) == 6);
    assert(greatest_common_divisor(7, 13) == 1);
    assert(greatest_common_divisor(0, 5) == 5);
    assert(greatest_common_divisor(5, 0) == 5);
    assert(greatest_common_divisor(0, 0) == 0);
    assert(greatest_common_divisor(48, 180) == 12);

    std::cout << "OK\n";
}