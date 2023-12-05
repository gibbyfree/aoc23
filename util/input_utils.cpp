#include "input_utils.h"
#include <fstream>
#include <iostream>

std::vector<std::string> readInputToLines(const std::string& fileName) {
  std::vector<std::string> lines;
  std::ifstream file(fileName);

  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      lines.push_back(line);
    }
    file.close();
  } else {
    std::cerr << "Unable to open file: " << fileName << std::endl;
  }

  return lines;
}

std::vector<std::vector<char>> readInputToGrid(const std::string& fileName) {
  std::vector<std::vector<char>> grid;
  std::ifstream file(fileName);

  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      std::vector<char> row;
      for (char c : line) {
        if (!std::isspace(c)) {
          row.push_back(c);
        }
      }
      grid.push_back(row);
    }
    file.close();
  } else {
    std::cerr << "Unable to open file: " << fileName << std::endl;
  }

  return grid;
}