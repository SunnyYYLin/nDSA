#include "Bitmap.hpp"

void Bitmap::set(int k) {
    expand(k);
    M[k >> 3] |= (0x80 >> (k & 0x07));
    // k & 0x07 is equivalent to k % 8;
    // 0b10000000 >> k'
}

void Bitmap::clear(int k) {
    expand(k);
    M[k >> 3] &= ~(0x80 >> (k & 0x07));
}

bool Bitmap::test(int k) {
    expand(k);
    return M[k >> 3] & (0x80 >> (k & 0x07));
}

/*
    关键在于
    如何将查询词表转换为某一集合
    ——留作习题
*/

// Eratosthenes筛法
void Eratosthenes(Bitmap& B, int n) {
    B.set(0);
    B.set(1);
    for (int i = 2; i * i < n; i++) { // O(n/logn)
    // i -> i*i : numbers greater than sqrt(n) is not a factor of n
        if (!B.test(i)) {
            for (int j = i * i; j < n; j += i) { // O(n/i)
            // 2*i -> i*i : numbers less than i*i have been filtered
                B.set(j);
            }
        }
    }
}