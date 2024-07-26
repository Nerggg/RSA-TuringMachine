#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

string highlightCharacter(const string& input, int position) {
    const string yellow = "\033[33m";
    const string reset = "\033[0m";

    if (position < 0 || position >= input.size()) {
        return input;
    }

    string result = input.substr(0, position) + yellow + input[position] + reset + input.substr(position + 1);
    return result;
}

struct Symbol {
    char read;
    char substitute;
    Symbol() {};
    Symbol(char read, char substitute) : read(read), substitute(substitute) {}
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
    TuringMachine(string tape, int readIdx, string currentState) : tape(tape), readIdx(readIdx), currentState(currentState) {}

    void readTapeOneStep(unordered_map<string, State> map) {
        for (int i = 0; i < map[currentState].rules.size(); i++) {
            if (tape[readIdx] == map[currentState].rules[i].symbol.read) {
                tape[readIdx] = map[currentState].rules[i].symbol.substitute;
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
                if (tape[readIdx] == map[currentState].rules[i].symbol.read) {
                    tape[readIdx] = map[currentState].rules[i].symbol.substitute;
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

int main() {
    State q0("q0", false, {Rule("q1", true, Symbol('0', 'x')), Rule("q3", true, Symbol('y', 'y'))});
    State q1("q1", false, {Rule("q1", true, Symbol('y', 'y')), Rule("q1", true, Symbol('0', '0')), Rule("q2", false, Symbol('1', 'y'))});
    State q2("q2", false, {Rule("q2", false, Symbol('y', 'y')), Rule("q2", false, Symbol('0', '0')), Rule("q0", true, Symbol('x', 'x'))});
    State q3("q3", false, {Rule("q3", true, Symbol('y', 'y')), Rule("q4", true, Symbol('B', 'B'))});
    State q4("q4", true, {});

    unordered_map<string, State> map;
    map["q0"] = q0;
    map["q1"] = q1;
    map["q2"] = q2;
    map["q3"] = q3;
    map["q4"] = q4;
    TuringMachine tes("0011B", 0, "q0");

    tes.readTapeWhole(map);
}