#include <cassert>
#include <numeric>
#include <iostream>
#include <iomanip>
#include "algorithms.hpp"

int main() {
	int iterations = 1;
	std::cout << std::setprecision(100) << (double)calculate_chudnovsky_pi(iterations) << std::endl;
	std::cout << std::setprecision(100) << (double)calculate_ramanujan_pi(iterations) << std::endl;
	std::cout << std::setprecision(100) << (double)calculate_gauss_legendre_pi(iterations) << std::endl;
	std::cout << std::setprecision(100) << (double)calculate_bbp_pi(iterations) << std::endl;
}