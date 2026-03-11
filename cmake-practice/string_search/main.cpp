#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits> // numeric_limits<size_t>::max()
#include <chrono>

// Include your algorithm headers
#include "naive_find.h"
#include "kmp_find.h"
// #include "boyer_moore.h"

void trim_spaces(std::string &txt)
{
    while (!txt.empty() && std::isspace(static_cast<unsigned char>(txt.front())))
        txt.erase(0, 1);
    while (!txt.empty() && std::isspace(static_cast<unsigned char>(txt.back())))
        txt.pop_back();
}

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
    long long total_time = 0;
    
    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
        continue;
        
        std::istringstream iss(line);
        std::string text, pattern, expected_str;
        std::getline(iss, text, '|');
        std::getline(iss, pattern, '|');
        std::getline(iss, expected_str);
        
        trim_spaces(text);
        trim_spaces(pattern);
        trim_spaces(expected_str);
        // Parse expected
        size_t expected;
        if (expected_str == "-1")
        {
            expected = std::string::npos;
        }
        else
        {
            try
            {
                expected = std::stoul(expected_str);
            }
            catch (...)
            {
                std::cerr << "Invalid expected: " << expected_str << "\n";
                continue;
            }
        }
        
        // To check run time
        auto start_time = std::chrono::high_resolution_clock::now();
        
        size_t result = finder(text, pattern, 0);
        
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        total_time+=duration;

        test_num++;
        bool ok = (result == expected);
        if (ok)
            passed++;

        std::cout << "[Test " << test_num << "] "
                  << (ok ? "PASS" : "FAIL") << "  "
                  << "Text: \"" << text << "\"  Pattern: \"" << pattern << "\"  "
                  << "Expected: " << (expected == std::string::npos ? -1 : expected) << "  Got: " << (result == std::string::npos ? -1 : result) << " "
                  << "Time: " << duration << " ns\n";
    }

    std::cout << "\nTests complete: " << passed << " / " << test_num << " passed. Total Time: "<< total_time << "ns. Avg. Time: "<<(total_time) / test_num;

    return (passed == test_num) ? 0 : 1;
}