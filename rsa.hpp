#ifndef RSA_H
#define RSA_H

#include "misc.hpp"

void rsa(string tape, int opt) {
    int eValue = 0, dValue = 0, nValue = 0;
    string temp = "", text = "";

    for (int i = 0; i < tape.length(); i++) {
        if (tape[i] != '_' && tape[i] != '$') {
            temp += tape[i];
        }
        else if (!eValue) {
            eValue = stoi(temp);
            temp = "";
        }
        else if (!dValue) {
            dValue = stoi(temp);
            temp = "";
        }
        else if (!nValue) {
            nValue = stoi(temp);
            temp = "";
        }
        else if (text.length() == 0) {
            text = temp;
            temp = "";
        }
    }

    if (opt == 1) { // encrypt
        for (int i = 0; i < text.length(); i++) {
            string calc = to_string(encryptRSA(eValue, nValue, int(text[i])));
            temp = calc + '|';
            text.replace(i, 1, temp);
            temp = "";
            i += calc.length();
        }
    }

    else { // decrypt
        for (int i = 0; i < text.length(); i++) {
            if (text[i] != '|') {
                temp += text[i];
            }
            else {
                int calc = decryptRSA(dValue, nValue, stoi(temp));
                string c;
                c += char(calc);
                text.replace(i - temp.length(), temp.length() + 1, c);
                i -= temp.length();
                temp = "";
            }
        }
    }

    cout << "e: " << eValue << endl;
    cout << "d: " << dValue << endl;
    cout << "n: " << nValue << endl;
    cout << "result: " << text << endl;
}

#endif