#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <string>
#include <vector>

std::vector<std::string> readInputToLines(const std::string& fileName);
std::vector<std::vector<char>> readInputToGrid(const std::string& fileName);
std::vector<int> splitNumberString(const std::string& numberString,
                                   const char& delimiter);

#endif