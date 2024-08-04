#ifndef STRINGS_H
#define STRINGS_H

#include <vector>

/* Utility class providing string argument function handlers */

std::vector<std::string> split_string(const std::string& s, char delimiter = ' ');

#endif