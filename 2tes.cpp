    // State q0("q0", false, {Rule("q1", true, Symbol('x', 'x')), Rule("q2", true, Symbol('B', 'B'))});
    // State q1("q1", false, {Rule("q0", true, Symbol('x', 'x'))});
    // State q2("q2", true, {});
    // unordered_map<string, State> map;
    // map["q0"] = q0;
    // map["q1"] = q1;
    // map["q2"] = q2;

    // TuringMachine tes("xxB", 0, "q0");

    // tes.readTapeWhole(map);

    // State q0("q0", false, {Rule("q1", true, Symbol('0', 'x')), Rule("q3", true, Symbol('y', 'y'))});
    // State q1("q1", false, {Rule("q1", true, Symbol('y', 'y')), Rule("q1", true, Symbol('0', '0')), Rule("q2", false, Symbol('1', 'y'))});
    // State q2("q2", false, {Rule("q2", false, Symbol('y', 'y')), Rule("q2", false, Symbol('0', '0')), Rule("q0", true, Symbol('x', 'x'))});
    // State q3("q3", false, {Rule("q3", true, Symbol('y', 'y')), Rule("q4", true, Symbol('B', 'B'))});
    // State q4("q4", true, {});

    // unordered_map<string, State> map;
    // map["q0"] = q0;
    // map["q1"] = q1;
    // map["q2"] = q2;
    // map["q3"] = q3;
    // map["q4"] = q4;
    // TuringMachine tes("0011B", 0, "q0");

    // tes.readTapeWhole(map);