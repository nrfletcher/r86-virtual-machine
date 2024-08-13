#include <vector>
#include <iterator>
#include <string>
#include <sstream>
#include <string_view>
#include <iostream>
#include <cstdint>

/* Takes delimiter, returns vector of strings split on that delimiter */
std::vector<std::string> split_string(const std::string& s, char delimiter = ' ') {
    std::vector<std::string> tokens;
    std::istringstream iss(s);
    std::string token;
    while(std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

/* Basic print functions */
void print(std::string_view& str) {
    std::cout << str << std::endl;
}

void print(const std::string& str) {
    std::cout << str << std::endl;
}

void print_vector(const std::vector<std::string> strings) {
    for(auto &s: strings) {
        print(s);
    }
}

uint32_t string_to_int32(const std::string& str) {
    return static_cast<uint32_t>(std::stoul(str, nullptr, 0));
}