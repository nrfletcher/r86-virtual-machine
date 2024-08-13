#ifndef STRINGS_H
#define STRINGS_H

#include <vector>

/* Utility class providing string argument function handlers */

std::vector<std::string> split_string(const std::string& s, char delimiter = ' ');
void print(std::string_view& str);
void print(const std::string& str);
uint32_t string_to_int32(const std::string& str);

#endif