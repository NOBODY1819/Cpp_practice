#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits> // numeric_limits<size_t>::max()

// Include your algorithm headers
#include "naive_find.h"
#include "kmp_find.h"
// #include "boyer_moore.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <function_file> <test_file>\n";
        std::cerr << "Example: " << argv[0] << " naive test1.txt\n";
        return 1;
    }

    std::string func_name = argv[1];
    std::string test_file = argv[2];

    // Very simple dispatch (you can use map or switch later)
    using FindFunc = size_t (*)(const std::string &, const std::string &, size_t start);

    FindFunc finder = nullptr;

    if (func_name == "naive")
    {
        finder = naive_find;
    }
    else if (func_name == "kmp")
    {
        finder = kmp_find;
    }
    // else if (func_name == "bmh") finder = boyer_moore_horspool;
    else
    {
        std::cerr << "Unknown function: " << func_name << "\n";
        std::cerr << "Supported: naive";
        // , kmp, bmh
        std::cerr << "\n";
        return 1;
    }

    // Read test cases
    std::ifstream file(test_file);
    if (!file.is_open())
    {
        std::cerr << "Cannot open test file: " << test_file << "\n";
        return 1;
    }

    std::string line;
    int test_num = 0;
    int passed = 0;

    while (std::getline(file, line)) {
    if (line.empty() || line[0] == '#') continue;

    std::istringstream iss(line);
    std::string text, expected_str;

    // Read text until the last two tokens
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }

    if (tokens.size() < 3) {
        std::cerr << "Invalid line (too few tokens): " << line << "\n";
        continue;
    }

    // Last token = expected
    expected_str = tokens.back();

    // Second last = pattern
    std::string pattern = tokens[tokens.size() - 2];

    // Everything before that = text
    text.clear();
    for (size_t k = 0; k < tokens.size() - 2; ++k) {
        if (k > 0) text += " ";
        text += tokens[k];
    }

    // Parse expected
    size_t expected;
    if (expected_str == "-1") {
        expected = std::string::npos;
    } else {
        try {
            expected = std::stoul(expected_str);
        } catch (...) {
            std::cerr << "Invalid expected: " << expected_str << "\n";
            continue;
        }
    }    size_t result = finder(text, pattern, 0);

        test_num++;
        bool ok = (result == expected);
        if (ok)
            passed++;

        std::cout << "[Test " << test_num << "] "
                  << (ok ? "PASS" : "FAIL") << "  "
                  << "Text: \"" << text << "\"  Pattern: \"" << pattern << "\"  "
                  << "Expected: " << expected << "  Got: " << result << "\n";
    }

    std::cout << "\nTests complete: " << passed << " / " << test_num << " passed\n";

    return (passed == test_num) ? 0 : 1;
}