#include <cassert>
#include <numeric>
#include <iostream>
#include "algorithms.hpp"

int main() {
    assert(least_common_multiple(4, 6) == 12);
    assert(least_common_multiple(0, 5) == 0);
    assert(least_common_multiple(7, 3) == 21);
    assert(least_common_multiple(10, 10) == 10);
    assert(least_common_multiple(1, 1) == 1);
    assert(least_common_multiple(15, 20) == 60);

    std::cout << "OK\n";
}