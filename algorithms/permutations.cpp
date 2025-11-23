#include <vector>

std::vector<int> applyPermutation(std::vector<int> sequence, std::vector<int> permutation) {
    std::vector<int> newSequence(sequence.size());
    for(int i = 0; i < (int) sequence.size(); i++) {
        newSequence[i] = sequence[permutation[i]];
    }
    return newSequence;
}

std::vector<int> permute(std::vector<int> sequence, std::vector<int> permutation, long long k) {
    while (k > 0) {
        if (k & 1) {
            sequence = applyPermutation(sequence, permutation);
        }
        permutation = applyPermutation(permutation, permutation);
        k >>= 1;
    }
    return sequence;
}