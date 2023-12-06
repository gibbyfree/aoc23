#include <iostream>
#include "day1.h"
#include "day2.h"
#include "day3.h"
#include "day4.h"

int main(int argc, char* argv[]) {
  std::cout << "🎄 Advent of Code 2023 🎄" << std::endl;

  bool useExample = false;

  if (argc > 1 && std::string(argv[1]) == "example") {
    useExample = true;
  }

  day1(useExample);
  day2(useExample);
  day3(useExample);
  day4(useExample);
  return 0;
}