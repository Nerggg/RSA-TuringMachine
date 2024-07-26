#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using namespace boost::multiprecision;

string highlightCharacter(const string& input, int position) {
    const string yellow = "\033[33m";
    const string reset = "\033[0m";

    if (position < 0 || position >= input.size()) {
        return input;
    }

    string result = input.substr(0, position) + yellow + input[position] + reset + input.substr(position + 1);
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

char encryptChar(int e, int n, char c) {
    cpp_int temp = power(int(c), e);
    return char(temp % n);
}

char decryptChar(int d, int n, char c) {
    cpp_int temp = power(int(c), d);
    return char(temp % n);
}

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

                if (currentState == "q3" && map[currentState].rules[i].symbol.substitute == "encrypt") {
                    tape[readIdx] = encryptChar(eValue, nValue, tape[readIdx]);
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

                    if (currentState == "q3" && map[currentState].rules[i].symbol.substitute == "encrypt") {
                        tape[readIdx] = encryptChar(eValue, nValue, tape[readIdx]);
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
            cout << "private key (d) " << dValue << endl;
            cout << "public key (e) " << eValue << endl;
            cout << "n " << nValue << endl;
        }
    }
};

int main() {
    State q0("q0", false, {Rule("q0", true, Symbol("0", "0")), Rule("q0", true, Symbol("1", "1")), Rule("q0", true, Symbol("2", "2")), Rule("q0", true, Symbol("3", "3")), Rule("q0", true, Symbol("4", "4")), Rule("q0", true, Symbol("5", "5")), Rule("q0", true, Symbol("6", "6")), Rule("q0", true, Symbol("7", "7")), Rule("q0", true, Symbol("8", "8")), Rule("q0", true, Symbol("9", "9")), Rule("q1", true, Symbol("_", "_"))});
    State q1("q1", false, {Rule("q1", true, Symbol("0", "0")), Rule("q1", true, Symbol("1", "1")), Rule("q1", true, Symbol("2", "2")), Rule("q1", true, Symbol("3", "3")), Rule("q1", true, Symbol("4", "4")), Rule("q1", true, Symbol("5", "5")), Rule("q1", true, Symbol("6", "6")), Rule("q1", true, Symbol("7", "7")), Rule("q1", true, Symbol("8", "8")), Rule("q1", true, Symbol("9", "9")), Rule("q2", true, Symbol("_", "_"))});
    State q2("q2", false, {Rule("q2", true, Symbol("0", "0")), Rule("q2", true, Symbol("1", "1")), Rule("q2", true, Symbol("2", "2")), Rule("q2", true, Symbol("3", "3")), Rule("q2", true, Symbol("4", "4")), Rule("q2", true, Symbol("5", "5")), Rule("q2", true, Symbol("6", "6")), Rule("q2", true, Symbol("7", "7")), Rule("q2", true, Symbol("8", "8")), Rule("q2", true, Symbol("9", "9")), Rule("q3", true, Symbol("_", "_"))});
    State q3("q3", false, {Rule("q3", true, Symbol("allChar", "encrypt"))});
    State q4("q4", true, {});
    unordered_map<string, State> map;
    map["q0"] = q0;
    map["q1"] = q1;
    map["q2"] = q2;
    map["q3"] = q3;
    map["q4"] = q4;

    TuringMachine t("7_103_143_hello", 0, "q0");
    // t.readTapeWhole(map);

    // while (true) {
    //     t.readTapeOneStep(map);
    //     cin.get();
    // }
}