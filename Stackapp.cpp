#include "Stack.hpp"
#include <iostream>

// base convert
void convert_base(int n, int base) {
    Stack<int> S;
    char digit[] = "0123456789ABCDEF";
    while (n > 0) {
        S.push(n % base);
        n /= base;
    }
    while (!S.empty()) {
        std::cout << digit[S.pop()];
    }
    std::cout << std::endl;
}

int main() {
    convert_base(10, 2);
    convert_base(10, 8);
    convert_base(10, 16);
    return 0;
}