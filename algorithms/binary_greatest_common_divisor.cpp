int binary_greatest_common_divisor(int a, int b) {
    if (!a || !b)
        return a | b;
    unsigned shift = __builtin_ctz(a | b);
    a >>= __builtin_ctz(a);
    do {
        b >>= __builtin_ctz(b);
        if (a > b) {
			a = a + b;
			b = a - b;
			a = a - b;
		}
        b -= a;
    } while (b > 0);
    return a << shift;
}