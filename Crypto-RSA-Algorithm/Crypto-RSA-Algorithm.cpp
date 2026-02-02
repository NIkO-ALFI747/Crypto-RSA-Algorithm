#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

template<class any_type>
void swapCustom(any_type& a, any_type& b) {
    any_type tmp = a;
    a = b;
    b = tmp;
}

template<class num_type>
num_type abs(const num_type& x) {
    if (is_same<num_type, unsigned>::value)
        return x;
    else
        return ((x < 0) ? 0 - x : x);
}

template<class int_type>
bool isEven(const int_type& a) {
    return !(a & 1);
}

template<class int_type>
int_type gcd(const int_type& a, const int_type& b) {
    int_type ta = abs(a), tb = abs(b);
    if (ta < tb) swapCustom(ta, tb);
    while (tb) ta %= tb, swapCustom(ta, tb);
    return ta;
}

template<class int_type>
bool isCoprime(const int_type& a, const int_type& b) {
    return (gcd(a, b) == 1);
}

template<class int_type>
int_type invMul(const int_type& valB, const int_type& valA) {
    int a = abs(valA), b = abs(valB), y = 0, y1 = 1, q, t;
    while (b) {
        q = a / b;
        t = a % b,
        a = b;
        b = t;
        t = y - y1 * q, y = y1, y1 = t;
    }
    if (a != 1) return 0;
    if (y < 0) y += abs(valA);
    if (valB < 0) y = -y;
    return int_type(y);
}

template<class int_type>
int_type modMul(const int_type& a, const int_type& b, const int_type& module) {
    return (a * b) % module;
}

template<class int_type>
int_type modPow(const int_type& a, const int_type& n, const int_type& module) {
    if (n == 0) return int_type(1);
    int_type c = a % module;
    if (n < 0) c = invMul(c, module);
    int_type exp = abs(n), f;
    for (f = 1; exp; exp >>= 1, c = modMul(c, c, module))
        if (!isEven(exp)) f = modMul(f, c, module);
    return f;
}

const static unsigned char PRIMES[] = {
    2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,
    53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,
    127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,
    199,211,223,227,229,233,239,241,251
};

int main(int argc, char* argv[]) {
    srand((unsigned)time(NULL));
    unsigned P = PRIMES[rand() % sizeof(PRIMES)];
    cout << "P = " << P << endl;
    unsigned Q = PRIMES[rand() % sizeof(PRIMES)];
    cout << "Q = " << Q << endl;
    unsigned N = P * Q;
    cout << "N = " << N << endl;
    unsigned Phi = (P - 1) * (Q - 1);
    cout << "Phi(N) = " << Phi << endl;
    unsigned e = (rand() % Phi) | 1;
    while (!isCoprime(e, Phi)) e += 2;
    cout << endl << "e = " << e << endl;
    unsigned d = invMul(e, Phi);
    cout << "d = " << d << endl;
    unsigned M;
    cout << endl << "Enter 1 < M < " << N << ": ";
    cin >> M;
    M %= N;
    cout << endl << "M = " << M << endl;
    unsigned C = modPow(M, e, N);
    cout << "C = " << C << endl;
    M = modPow(C, d, N);
    cout << "M = " << M << endl;
    return 0;
}