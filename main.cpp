#include "turing.hpp"
using namespace std;
using namespace boost::multiprecision;

int main() {
    unsigned short opt;
    cout << "Enter your option" << endl;
    cout << "[1] Encryption" << endl;
    cout << "[2] Decryption" << endl;
    do {
        cin >> opt;
    } while (opt != 1 && opt != 2);

    unordered_map<string, State> map;
    if (opt == 1) {
        State q0("q0", false, {Rule("q0", true, Symbol("0", "0")), Rule("q0", true, Symbol("1", "1")), Rule("q0", true, Symbol("2", "2")), Rule("q0", true, Symbol("3", "3")), Rule("q0", true, Symbol("4", "4")), Rule("q0", true, Symbol("5", "5")), Rule("q0", true, Symbol("6", "6")), Rule("q0", true, Symbol("7", "7")), Rule("q0", true, Symbol("8", "8")), Rule("q0", true, Symbol("9", "9")), Rule("q1", true, Symbol("_", "_"))});
        State q1("q1", false, {Rule("q1", true, Symbol("0", "0")), Rule("q1", true, Symbol("1", "1")), Rule("q1", true, Symbol("2", "2")), Rule("q1", true, Symbol("3", "3")), Rule("q1", true, Symbol("4", "4")), Rule("q1", true, Symbol("5", "5")), Rule("q1", true, Symbol("6", "6")), Rule("q1", true, Symbol("7", "7")), Rule("q1", true, Symbol("8", "8")), Rule("q1", true, Symbol("9", "9")), Rule("q2", true, Symbol("_", "_"))});
        State q2("q2", false, {Rule("q2", true, Symbol("0", "0")), Rule("q2", true, Symbol("1", "1")), Rule("q2", true, Symbol("2", "2")), Rule("q2", true, Symbol("3", "3")), Rule("q2", true, Symbol("4", "4")), Rule("q2", true, Symbol("5", "5")), Rule("q2", true, Symbol("6", "6")), Rule("q2", true, Symbol("7", "7")), Rule("q2", true, Symbol("8", "8")), Rule("q2", true, Symbol("9", "9")), Rule("q3", true, Symbol("_", "_"))});
        State q3("q3", false, {Rule("q3", true, Symbol("allChar", "encrypt")), Rule("q4", true, Symbol("$", "$"))});
        State q4("q4", true, {});
        map["q0"] = q0;
        map["q1"] = q1;
        map["q2"] = q2;
        map["q3"] = q3;
        map["q4"] = q4;
    }
    else {
        State q0("q0", false, {Rule("q0", true, Symbol("0", "0")), Rule("q0", true, Symbol("1", "1")), Rule("q0", true, Symbol("2", "2")), Rule("q0", true, Symbol("3", "3")), Rule("q0", true, Symbol("4", "4")), Rule("q0", true, Symbol("5", "5")), Rule("q0", true, Symbol("6", "6")), Rule("q0", true, Symbol("7", "7")), Rule("q0", true, Symbol("8", "8")), Rule("q0", true, Symbol("9", "9")), Rule("q1", true, Symbol("_", "_"))});
        State q1("q1", false, {Rule("q1", true, Symbol("0", "0")), Rule("q1", true, Symbol("1", "1")), Rule("q1", true, Symbol("2", "2")), Rule("q1", true, Symbol("3", "3")), Rule("q1", true, Symbol("4", "4")), Rule("q1", true, Symbol("5", "5")), Rule("q1", true, Symbol("6", "6")), Rule("q1", true, Symbol("7", "7")), Rule("q1", true, Symbol("8", "8")), Rule("q1", true, Symbol("9", "9")), Rule("q2", true, Symbol("_", "_"))});
        State q2("q2", false, {Rule("q2", true, Symbol("0", "0")), Rule("q2", true, Symbol("1", "1")), Rule("q2", true, Symbol("2", "2")), Rule("q2", true, Symbol("3", "3")), Rule("q2", true, Symbol("4", "4")), Rule("q2", true, Symbol("5", "5")), Rule("q2", true, Symbol("6", "6")), Rule("q2", true, Symbol("7", "7")), Rule("q2", true, Symbol("8", "8")), Rule("q2", true, Symbol("9", "9")), Rule("q3", true, Symbol("_", "_"))});
        State q3("q3", false, {Rule("q4", true, Symbol("allChar", "read")), Rule("q6", true, Symbol("$", "$"))});
        State q4("q4", false, {Rule("q5", true, Symbol("allChar", "read"))});
        State q5("q5", false, {Rule("q3", true, Symbol("allChar", "decrypt"))});
        State q6("q6", true, {});
        map["q0"] = q0;
        map["q1"] = q1;
        map["q2"] = q2;
        map["q3"] = q3;
        map["q4"] = q4;
        map["q5"] = q5;
        map["q6"] = q6;
    }

    cin.ignore();
    string tape;
    cout << "Enter your tape with the format of (e value)_(d value)_(n value)_(text)$" << endl;
    getline(cin, tape);
    TuringMachine t(tape, 0, "q0");

    opt = 0;
    cout << "Do you want to see the step by step process or skip to the output?" << endl;
    cout << "[1] Step by step" << endl;
    cout << "[2] Skip to the output" << endl;
    do {
        cin >> opt;
    } while (opt != 1 && opt != 2);

    if (opt == 1) {
        while (t.readIdx != t.tape.length()) {
            cin.get();
            t.readTapeOneStep(map);
        }
    }
    else {
        t.readTapeWhole(map);
    }

    // TuringMachine t("7_1183_2867_anjay mabar$", 0, "q0");
    // TuringMachine t("7_103_143_anjay mabar$", 0, "q0");
    // TuringMachine t("7_103_143_059033050059121098021059032059049$", 0, "q0");

    // TuringMachine t("7_103_143_hello$", 0, "q0");
    // TuringMachine t("7_103_143_091062004004045$", 0, "q0");
}