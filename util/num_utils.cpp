#include "num_utils.h"

int digitsToNumber(std::vector<int> digits) {
  int num = 0;
  for (int d : digits) {
    num = num * 10 + d;
  }
  return num;
}