#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

void convertStringToNumber(std::string& input) {
    std::string result;
    for (char c : input) {
        // Mengambil nilai ASCII dari karakter
        int ascii_value = static_cast<int>(c);
        // Menggunakan stringstream untuk mengubah angka menjadi string 3 digit
        std::ostringstream oss;
        oss << std::setw(3) << std::setfill('0') << ascii_value;
        // Menambahkan string 3 digit ke hasil
        result += oss.str();
    }
    input = result;
}

int main() {
    std::string input = "ABC";
    convertStringToNumber(input);
    std::cout << "Converted string: " << input << std::endl;
    return 0;
}
