#include <iostream>
#include <cmath>
#include <tuple>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

long long modInverse(long long e, long long phi) {
    long long m0 = phi, t, q;
    long long x0 = 0, x1 = 1;

    if (phi == 1)
        return 0;

    while (e > 1) {
        q = e / phi;
        t = phi;
        phi = e % phi;
        e = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

std::tuple<std::pair<long long, long long>, std::pair<long long, long long>> generateKeys(long long p, long long q) {
    long long n = p * q;

    long long phi = (p - 1) * (q - 1);

    long long e = 2;
    while (e < phi && gcd(e, phi) != 1) {
        e++;
    }

    long long d = modInverse(e, phi);

    std::pair<long long, long long> publicKey = {e, n};

    std::pair<long long, long long> privateKey = {d, n};

    return {publicKey, privateKey};
}

int main() {
    long long p, q;

    std::cout << "Enter two prime numbers: ";
    std::cin >> p >> q;

    auto [publicKey, privateKey] = generateKeys(p, q);

    std::cout << "Public Key: (" << publicKey.first << ", " << publicKey.second << ")\n";
    std::cout << "Private Key: (" << privateKey.first << ", " << privateKey.second << ")\n";

    return 0;
}