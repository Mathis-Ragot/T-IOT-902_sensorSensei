#include <unity.h>
#include "Utils.h"

void test_printBits() {
    Utils::printBits(0b10101010, 8);
}

void test_countSignificantBits() {
    TEST_ASSERT_EQUAL(8, Utils::countSignificantBits(0b10101010));
}

void test_printBytesAsCharacters() {
    std::vector<uint8_t> bytes = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x01, 0x10, 0x00};
    Utils::printBytesAsCharacters(bytes);
}

void test_printBytesAsIntegers() {
    std::vector<uint8_t> bytes = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x10, 0x00};
    Utils::printBytesAsIntegers(bytes);
}

void test_printBytesAsHex() {
    std::vector<uint8_t> bytes = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x10, 0x00};
    Utils::printBytesAsHex(bytes);
}