#include <iostream>
#include <fstream>
#include <cstdint>

uint32_t convertEndian(uint32_t value) {
    uint32_t converted = (value & 0xff) << 24;
    converted |= ((value >> 8) & 0xff) << 16;
    converted |= ((value >> 16) & 0xff) << 8;
    converted |= (value >> 24);
    return converted;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: add-nbo <file1> <file2>" << std::endl;
        return 1;
    }

    std::ifstream file1(argv[1], std::ios::binary);
    std::ifstream file2(argv[2], std::ios::binary);

    if (!file1.is_open() || !file2.is_open()) {
        std::cerr << "Error opening file(s)" << std::endl;
        return 1;
    }

    uint32_t number1, number2;
    if (!file1.read(reinterpret_cast<char*>(&number1), sizeof(number1)) ||
        !file2.read(reinterpret_cast<char*>(&number2), sizeof(number2))) {
        std::cerr << "Error reading file(s)" << std::endl;
        return 1;
    }

    number1 = convertEndian(number1);
    number2 = convertEndian(number2);
    uint32_t sum = number1 + number2;

    std::cout << number1 << " (0x" << std::hex << number1 << std::dec << ") + "
              << number2 << " (0x" << std::hex << number2 << std::dec << ") = "
              << sum << " (0x" << std::hex << sum << std::dec << ")" << std::endl;

    return 0;
}

