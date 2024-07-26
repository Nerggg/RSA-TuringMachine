#include <iostream>
#include <string>
#include <iomanip>  // Untuk std::setfill dan std::setw

int main() {
    std::string str = "ABC";
    std::string result = str;

    for (std::size_t i = 0; i < str.size(); ++i) {
        // Convert character to its ASCII code and format it as a three-digit number
        std::string ascii_code = std::to_string(static_cast<int>(str[i]));
        while (ascii_code.length() < 3) {
            ascii_code = "0" + ascii_code; // Pad with zeros to make it three digits
        }

        // Replace the character with its ASCII code
        result.replace(i * 3, 1, ascii_code);

        // Print the result for this iteration
        std::cout << result << std::endl;
    }

    return 0;
}
