#include "day3.h"
#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>
#include "input_utils.h"
#include "num_utils.h"

bool checkForAdjacentSymbol(std::vector<std::vector<char>> grid, int x, int y,
                            int numLength) {
  int offsets[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                       {0, 1},   {1, -1}, {1, 0},  {1, 1}};
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < numLength; j++) {
      int nx = x + offsets[i][0];
      int ny = y + offsets[i][1] - j;  // Adjust for each digit of the number

      if (nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid[0].size() &&
          grid[nx][ny] != '.' && !isdigit(grid[nx][ny])) {
        return true;
      }
    }
  }
  return false;
}

// known from test data: numbers are 3 digits long at most
int getNumberFromGrid(std::vector<std::vector<char>> grid, int x, int y) {
  std::vector<int> digits;
  // left
  int i = y - 1;
  while (i >= 0 && isdigit(grid[x][i]) && digits.size() < 3) {
    digits.insert(digits.begin(), grid[x][i] - '0');
    i--;
  }

  digits.push_back(grid[x][y] - '0');

  // right
  i = y + 1;
  while (i < grid[0].size() && isdigit(grid[x][i]) && digits.size() < 3) {
    digits.push_back(grid[x][i] - '0');
    i++;
  }

  return digitsToNumber(digits);
}

std::pair<int, int> checkForAdjacentNumbers(std::vector<std::vector<char>> grid,
                                            int x, int y) {
  int first = -2;
  int second = -2;

  int offsets[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                       {0, 1},   {1, -1}, {1, 0},  {1, 1}};

  for (int i = 0; i < 8; i++) {
    int nx = x + offsets[i][0];
    int ny = y + offsets[i][1];
    if (isdigit(grid[nx][ny])) {
      int res = getNumberFromGrid(grid, nx, ny);
      if (first == -2) {
        first = res;
      } else if (res == first) {
        continue;
      } else {
        second = res;
        break;
      }
    }
  }

  return std::pair<int, int>{first, second};
}

void part2(std::vector<std::vector<char>> grid) {
  std::vector<std::pair<int, int>> starPairs;
  int tempNum = -2;

  for (int x = 0; x < grid.size(); x++) {
    for (int y = 0; y < grid[0].size() + 1; y++) {
      if (grid[x][y] == '*') {
        std::pair<int, int> pair = checkForAdjacentNumbers(grid, x, y);
        if (pair.first != -2 && pair.second != -2) {
          starPairs.push_back(pair);
        }
        pair = std::pair<int, int>{-2, -2};
      }
    }
  }

  long long int resultSum = 0;
  for (const auto& pair : starPairs) {
    resultSum += static_cast<long long>(pair.first) * pair.second;
  }

  std::cout << "⛄ Day 3.2: " << resultSum << std::endl;
}

void part1(std::vector<std::vector<char>> grid) {
  std::vector<int> partNumbers;

  for (int x = 0; x < grid.size(); x++) {
    std::vector<int> digits;
    for (int y = 0; y < grid[0].size() + 1; y++) {
      if (isdigit(grid[x][y])) {
        digits.push_back(grid[x][y] - '0');
      } else {
        if (!digits.empty()) {
          if (checkForAdjacentSymbol(grid, x, y - 1, digits.size())) {
            int num = digitsToNumber(digits);
            partNumbers.push_back(num);
          }
          digits.clear();
        }
      }

      if (y + 1 == grid[0].size() && !digits.empty()) {
        // line ends on next iter
        if (checkForAdjacentSymbol(grid, x, y - 1, digits.size())) {
          int num = digitsToNumber(digits);
          partNumbers.push_back(num);
        }
        digits.clear();
      }
    }
  }

  std::cout << "⛄ Day 3.1: "
            << std::accumulate(partNumbers.begin(), partNumbers.end(), 0)
            << std::endl;
}

void day3(bool useExample) {
  std::string path = "../input/3.txt";
  if (useExample) {
    path = "../input/3example.txt";
  }
  std::vector<std::vector<char>> grid = readInputToGrid(path);

  auto start = std::chrono::high_resolution_clock::now();
  part1(grid);
  part2(grid);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = end - start;

  std::cout << "⛄ Day3 runtime: " << elapsed.count() << "ms" << std::endl;
}
