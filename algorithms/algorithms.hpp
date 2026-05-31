
#ifndef algorithms
#define algorithms
#include <vector>

long long binary_exponentation(long long a, long long b);
int greatest_common_divisor (int a, int b);
int least_common_multiple (int a, int b);
std::vector<int> applyPermutation(std::vector<int> sequence, std::vector<int> permutation);
std::vector<int> permute(std::vector<int> sequence, std::vector<int> permutation, long long k);
double calculate_chudnovsky_pi(long n);
double calculate_ramanujan_pi(long n);
double calculate_gauss_legendre_pi(long n);
double calculate_bbp_pi(long n);

#endif