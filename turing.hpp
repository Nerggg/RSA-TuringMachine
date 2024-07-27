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
    string decryptTemp = "";
    // end

    TuringMachine(string tape, int readIdx, string currentState) : tape(tape), readIdx(readIdx), currentState(currentState) {}

    void readTapeOneStep(unordered_map<string, State> map) {
        for (int i = 0; i < map[currentState].rules.size(); i++) {
            if (tape[readIdx] == map[currentState].rules[i].symbol.read[0] || (map[currentState].rules[i].symbol.read == "allChar" && tape[readIdx] != '$')) {

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

                if (map[currentState].rules[i].symbol.substitute == "encrypt") {
                    string ascii = to_string(encryptChar(eValue, nValue, tape[readIdx]));
                    cout << "asciinya " << ascii << endl;
                    while (ascii.length() < 3) {
                        ascii = "0" + ascii;
                    }
                    tape.replace(readIdx, 1, ascii);
                    readIdx += 2;
                }
                else if (map[currentState].rules[i].symbol.substitute == "read") {
                    decryptTemp = decryptTemp + tape[readIdx];
                }
                else if (map[currentState].rules[i].symbol.substitute == "decrypt") {
                    decryptTemp = decryptTemp + tape[readIdx];
                    string replace;
                    replace += decryptChar(dValue, nValue, stoi(decryptTemp));
                    cout << "decrypt temp nya " << decryptTemp << endl;
                    cout << "replace nya " << replace << endl;
                    decryptTemp = "";
                    readIdx -= 2;
                    tape.replace(readIdx, 3, replace);
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
                if (tape[readIdx] == map[currentState].rules[i].symbol.read[0] || (map[currentState].rules[i].symbol.read == "allChar" && tape[readIdx] != '$')) {

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

                    if (map[currentState].rules[i].symbol.substitute == "encrypt") {
                        string ascii = to_string(encryptChar(eValue, nValue, tape[readIdx]));
                        while (ascii.length() < 3) {
                            ascii = "0" + ascii;
                        }
                        tape.replace(readIdx, 1, ascii);
                        readIdx += 2;
                    }
                    else if (map[currentState].rules[i].symbol.substitute == "read") {
                        decryptTemp = decryptTemp + tape[readIdx];
                    }
                    else if (map[currentState].rules[i].symbol.substitute == "decrypt") {
                        decryptTemp = decryptTemp + tape[readIdx];
                        string replace;
                        replace += decryptChar(dValue, nValue, stoi(decryptTemp));
                        decryptTemp = "";
                        readIdx -= 2;
                        tape.replace(readIdx, 3, replace);
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