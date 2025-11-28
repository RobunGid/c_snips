#include <cassert>
#include <numeric>
#include <iostream>
#include "algorithms.hpp"

int main() {

	for (int i = 2; i < 30; i+=2) {
		std::cout << i << " : " << __builtin_ctz(i) << std::endl;
	}

}