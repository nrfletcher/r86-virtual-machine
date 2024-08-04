#include <vector>
#include <iterator>
#include <string>
#include <sstream>

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