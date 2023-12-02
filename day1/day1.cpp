#include "day1.h"
#include <chrono>
#include <iostream>
#include <numeric>
#include <regex>
#include <unordered_map>
#include "input_utils.h"

const std::unordered_map<std::string, int> wordToNumber = {
    {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
    {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

int parseStringToInt(std::string str) {
  if (str.size() == 1) {
    return str[0] - '0';
  } else {
    return wordToNumber.at(str);
  }
}

void part1(std::vector<std::string> lines) {
  std::vector<int> numbers;
  for (std::string line : lines) {
    char first = ' ';
    char second = ' ';
    int first_idx = -1;
    int count = 0;

    for (char& c : line) {
      if (std::isdigit(c)) {
        first = c;
        first_idx = count;
        break;
      }
      count++;
    }

    for (int i = line.size(); i > first_idx; i--) {
      if (std::isdigit(line[i])) {
        second = line[i];
        break;
      }
    }

    if (second == ' ') {
      second = first;
    }

    int res = (first - '0') * 10 + (second - '0');
    numbers.push_back(res);
  }

  std::cout << "Day1.1: " << std::accumulate(numbers.begin(), numbers.end(), 0)
            << std::endl;
}

void part2(std::vector<std::string> lines) {
  std::vector<int> results;
  for (std::string line : lines) {
    std::vector<int> allDigits;
    for (int i = 0; i < line.size(); i++) {
      if (std::isdigit(line[i])) {
        allDigits.push_back(line[i] - '0');
      }

      for (const auto& element : wordToNumber) {
        if (element.first.size() <= line.size() - i) {
          std::string substr = line.substr(i, element.first.size());
          if (substr == element.first) {
            allDigits.push_back(element.second);
            i += element.first.size() - 2;
            break;
          }
        }
      }
    }

    int res = (allDigits[0] * 10) + allDigits[allDigits.size() - 1];
    results.push_back(res);
  }

  std::cout << "Day1.2: " << std::accumulate(results.begin(), results.end(), 0)
            << std::endl;
}

void day1() {
  std::vector<std::string> lines = readInputToLines("../input/1.txt");

  auto start = std::chrono::high_resolution_clock::now();
  part1(lines);
  part2(lines);
  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double, std::milli> elapsed = end - start;
  std::cout << "Day1 runtime: " << elapsed.count() << "ms" << std::endl;
}