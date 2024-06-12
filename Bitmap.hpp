#include "Vector.hpp"

class Bitmap: public Vector<unsigned char>{
private:
    int N;
    unsigned char* M;
public:
    // n is the number of bits; N is the number of bytes;
    Bitmap(int n = 8) {
        M = new unsigned char[N = (n + 7) / 8];
        memset(M, 0, N);
    }
    ~Bitmap() {
        delete [] M;
        M = nullptr;
    }
    void set(int k);
    void clear(int k);
    bool test(int k);
};