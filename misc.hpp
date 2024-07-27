#ifndef MISC_H
#define MISC_H

#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using namespace boost::multiprecision;

string highlightCharacter(const string& input, int position) {
    const string red = "\033[31m";
    const string reset = "\033[0m";

    if (position < 0 || position >= input.size()) {
        return input;
    }

    string result = input.substr(0, position) + red + input[position] + reset + input.substr(position + 1);
    return result;
}

cpp_int power(cpp_int base, cpp_int exponent) {
    cpp_int result = 1;
    while (exponent != 0) {
        if (exponent % 2 == 1) {
            result *= base;
        }
        base *= base;
        exponent /= 2;
    }
    return result;
}

int encryptChar(int e, int n, char c) {
    cpp_int temp = power(int(c), e);
    return int(temp % n);
}

char decryptChar(int d, int n, int c) {
    cpp_int temp = power(c, d);
    return char(temp % n);
}

#endif