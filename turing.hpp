#ifndef TURING_H
#define TURING_H

#include "misc.hpp"
#include <unordered_map>

struct Symbol {
    string read;
    string substitute;
    Symbol() {};
    Symbol(string read, string substitute) : read(read), substitute(substitute) {}
};

struct Rule {
    string nextState;
    bool direction; // true = kanan, false = kiri
    Symbol symbol;
    Rule() {};
    Rule(string nextState, bool direction, Symbol symbol) : nextState(nextState), direction(direction), symbol(symbol) {}
};

struct State {
    string name;
    bool status; // true = final state, false = not final state
    vector<Rule> rules;
    State() {};
    State(string name, bool status, vector<Rule> rules) : name(name), status(status), rules(rules) {}
};

struct TuringMachine {
    string tape;
    int readIdx;
    string currentState;

    // variable for rsa
    int dValue = 0;
    string dValueTemp = "";
    int eValue = 0;
    string eValueTemp = "";
    int nValue = 0;
    string nValueTemp = "";
    string readTemp = "";
    // end

    TuringMachine(string tape, int readIdx, string currentState) : tape(tape), readIdx(readIdx), currentState(currentState) {}

    void readTapeOneStep(unordered_map<string, State> map) {
        for (int i = 0; i < map[currentState].rules.size(); i++) {
            if (tape[readIdx] == map[currentState].rules[i].symbol.read[0] || map[currentState].rules[i].symbol.read == "allChar") {
                // rsa functionality
                if (currentState == "q0" && !eValue && tape[readIdx] != '_') {
                    eValueTemp += tape[readIdx];
                }
                else if (currentState == "q0" && !eValue && tape[readIdx] == '_') {
                    eValue = stoi(eValueTemp);
                }
                else if (currentState == "q1" && eValue && tape[readIdx] != '_') {
                    dValueTemp += tape[readIdx];
                }
                else if (currentState == "q1" && eValue && tape[readIdx] == '_') {
                    dValue = stoi(dValueTemp);
                }
                else if (currentState == "q2" && eValue && tape[readIdx] != '_') {
                    nValueTemp += tape[readIdx];
                }
                else if (currentState == "q2" && eValue && tape[readIdx] == '_') {
                    nValue = stoi(nValueTemp);
                }

                if (map[currentState].rules[i].symbol.substitute == "toAscii") { 
                    string temp = to_string(int(tape[readIdx]));
                    temp = "|" + temp;
                    tape.replace(readIdx, 1, temp);
                    readIdx += temp.length() - 1;
                }
                else if (map[currentState].rules[i].symbol.substitute == "readEncrypt") {
                    readTemp = tape[readIdx] + readTemp;
                }
                else if (map[currentState].rules[i].symbol.substitute == "encrypt") {
                    string encrypt = to_string(encryptRSA(eValue, nValue, stoi(readTemp)));
                    encrypt += "|";
                    tape.replace(readIdx, readTemp.length() + 1, encrypt);
                    readTemp = "";
                }
                else if (map[currentState].rules[i].symbol.substitute == "readDecrypt") {
                    readTemp = readTemp + tape[readIdx];
                }
                else if (map[currentState].rules[i].symbol.substitute == "decrypt") {
                    string decrypt = to_string(decryptRSA(dValue, nValue, stoi(readTemp)));
                    decrypt = "|" + decrypt;
                    tape.replace(readIdx - readTemp.length(), readTemp.length() + 1, decrypt);
                    readIdx -= absolute(readTemp.length() - (decrypt.length() - 1));
                    readTemp = "";
                }
                else if (map[currentState].rules[i].symbol.substitute == "toChar") {
                    string temp;
                    temp += char(stoi(readTemp));
                    tape.replace(readIdx, readTemp.length() + 1, temp);
                    readTemp = "";
                }
                // end

                else {
                    tape[readIdx] = map[currentState].rules[i].symbol.substitute[0];
                }
                cout << highlightCharacter(tape, readIdx) << endl;
                if (map[currentState].rules[i].direction) {
                    readIdx++;
                }
                else {
                    readIdx--;
                }
                currentState = map[currentState].rules[i].nextState;
                if (map[currentState].status) {
                    cout << "accepted" << endl;
                }
                break;
            }
            if (i == map[currentState].rules.size() - 1) {
                cout << "rejected" << endl;
            }
        }
    }

    void readTapeWhole(unordered_map<string, State> map) {
        while (!map[currentState].status) {
            bool passed = false;
            for (int i = 0; i < map[currentState].rules.size(); i++) {
                if (tape[readIdx] == map[currentState].rules[i].symbol.read[0] || map[currentState].rules[i].symbol.read == "allChar") {
                    // rsa functionality
                    if (currentState == "q0" && !eValue && tape[readIdx] != '_') {
                        eValueTemp += tape[readIdx];
                    }
                    else if (currentState == "q0" && !eValue && tape[readIdx] == '_') {
                        eValue = stoi(eValueTemp);
                    }
                    else if (currentState == "q1" && eValue && tape[readIdx] != '_') {
                        dValueTemp += tape[readIdx];
                    }
                    else if (currentState == "q1" && eValue && tape[readIdx] == '_') {
                        dValue = stoi(dValueTemp);
                    }
                    else if (currentState == "q2" && eValue && tape[readIdx] != '_') {
                        nValueTemp += tape[readIdx];
                    }
                    else if (currentState == "q2" && eValue && tape[readIdx] == '_') {
                        nValue = stoi(nValueTemp);
                    }

                    if (map[currentState].rules[i].symbol.substitute == "toAscii") { 
                        string temp = to_string(int(tape[readIdx]));
                        temp = "|" + temp;
                        tape.replace(readIdx, 1, temp);
                        readIdx += temp.length() - 1;
                    }
                    else if (map[currentState].rules[i].symbol.substitute == "readEncrypt") {
                        readTemp = tape[readIdx] + readTemp;
                    }
                    else if (map[currentState].rules[i].symbol.substitute == "encrypt") {
                        string encrypt = to_string(encryptRSA(eValue, nValue, stoi(readTemp)));
                        encrypt += "|";
                        tape.replace(readIdx, readTemp.length() + 1, encrypt);
                        readTemp = "";
                    }
                    else if (map[currentState].rules[i].symbol.substitute == "readDecrypt") {
                        readTemp = readTemp + tape[readIdx];
                    }
                    else if (map[currentState].rules[i].symbol.substitute == "decrypt") {
                        string decrypt = to_string(decryptRSA(dValue, nValue, stoi(readTemp)));
                        decrypt = "|" + decrypt;
                        tape.replace(readIdx - readTemp.length(), readTemp.length() + 1, decrypt);
                        readIdx -= absolute(readTemp.length() - (decrypt.length() - 1));
                        readTemp = "";
                    }
                    else if (map[currentState].rules[i].symbol.substitute == "toChar") {
                        string temp;
                        temp += char(stoi(readTemp));
                        tape.replace(readIdx, readTemp.length() + 1, temp);
                        readTemp = "";
                    }
                    // end

                    else {
                        tape[readIdx] = map[currentState].rules[i].symbol.substitute[0];
                    }
                    cout << highlightCharacter(tape, readIdx) << endl;
                    if (map[currentState].rules[i].direction) {
                        readIdx++;
                    }
                    else {
                        readIdx--;
                    }
                    currentState = map[currentState].rules[i].nextState;
                    passed = true;
                    if (map[currentState].status) {
                        cout << "accepted" << endl;
                    }
                    break;
                }
            }
            if (!passed) {
                cout << "rejected" << endl;
                break;
            }
        }
    }
};

#endif