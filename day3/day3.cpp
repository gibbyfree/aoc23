#include "day3.h"
#include <iostream>
#include <vector>
#include "input_utils.h"

// numlength is the length of the current number. a different number of spaces should be checked for adjacency depending on number length.
bool checkForAdjacentSymbol(std::vector<std::vector<char>> grid, int x, int y,
                            int numLength) {
  int offsets[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                       {0, 1},   {1, -1}, {1, 0},  {1, 1}};
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < numLength; j++) {
      int nx = x + offsets[i][0];
      int ny = y + offsets[i][1] - j;  // Adjust for each digit of the number

      // Check if the coordinates are valid and not a dot
      if (nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid[0].size() &&
          grid[nx][ny] != '.' && !isdigit(grid[nx][ny])) {
        return true;  // Found a symbol
      }
    }
  }
  // debug print the number by printing numLength characters from grid ending in x,y
  // std::cout << "Number: ";
  for (int i = 0; i < numLength; i++) {
    std::cout << grid[x][y - i];
  }
  std::cout << std::endl;
  return false;  // No symbol found
}

// 551521 is too low.
// 553463 is too low.
void day3() {
  std::vector<std::vector<char>> grid = readInputToGrid("../input/3.txt");
  std::vector<int> partNumbers;

  for (int x = 0; x < grid.size(); x++) {
    std::vector<int> digits;
    for (int y = 0; y < grid[0].size() + 1; y++) {
      // accumulate numbers into digits. when the number ends (due to end of line or `.`), check for adjacent symbols.
      if (isdigit(grid[x][y])) {
        // append the digit to the vector
        digits.push_back(grid[x][y] - '0');
      } else {
        // the number ends
        if (!digits.empty()) {
          // check if the number is a part number
          if (checkForAdjacentSymbol(grid, x, y - 1, digits.size())) {
            // convert the vector of digits to an integer
            int num = 0;
            for (int d : digits) {
              num = num * 10 + d;
            }
            // add the part number to the vector
            partNumbers.push_back(num);
          }
          // clear the vector of digits
          digits.clear();
        }
      }

      if (y + 1 == grid[0].size() && !digits.empty()) {
        // line ends on next iter
        if (checkForAdjacentSymbol(grid, x, y - 1, digits.size())) {
          // convert the vector of digits to an integer
          int num = 0;
          for (int d : digits) {
            num = num * 10 + d;
          }
          partNumbers.push_back(num);
        }
        // clear the vector of digits
        digits.clear();
      }
    }
  }
  // compute the sum of the part numbers
  int sum = 0;
  for (int n : partNumbers) {
    sum += n;
  }

  // print the result
  std::cout << "The sum of the part numbers is " << sum << std::endl;
}
