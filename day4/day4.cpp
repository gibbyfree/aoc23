#include "day4.h"
#include <chrono>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include "input_utils.h"

int countCommonElements(std::vector<int> v1, std::vector<int> v2) {
  std::unordered_set<int> s1(v1.begin(), v1.end());
  std::unordered_set<int> s2(v2.begin(), v2.end());
  int count = 0;
  for (int i : s1) {
    if (s2.find(i) != s2.end()) {
      count++;
    }
  }
  return count;
}

void part2(std::vector<std::string> lines) {
  int originalCards = 0;
  long total = 0;
  int currentCard = 1;
  std::unordered_map<int, int> cardCopies;
  for (std::string line : lines) {
    originalCards++;
    std::string cards = line.substr(line.find(":") + 2);
    std::string winning = cards.substr(0, cards.find("|") - 1);
    std::string losing = cards.substr(cards.find("|") + 1);

    std::vector<int> winningCards = splitNumberString(winning, ' ');
    std::vector<int> losingCards = splitNumberString(losing, ' ');

    int copiesOfCurrent = cardCopies[currentCard] + 1;

    for (int i = 0; i < copiesOfCurrent; i++) {
      int common = countCommonElements(winningCards, losingCards);
      for (int j = 1; j < common + 1; j++) {
        cardCopies[currentCard + j] += 1;
      }
      total += common;
    }

    currentCard++;
  }

  std::cout << "🔔 Day 4.2: " << total + originalCards << std::endl;
}

void part1(std::vector<std::string> lines) {
  int points = 0;
  for (std::string line : lines) {
    int localPoints = 0;
    std::string cards = line.substr(line.find(":") + 2);
    std::string winning = cards.substr(0, cards.find("|") - 1);
    std::string losing = cards.substr(cards.find("|") + 1);

    std::vector<int> winningCards = splitNumberString(winning, ' ');
    std::vector<int> losingCards = splitNumberString(losing, ' ');

    int common = countCommonElements(winningCards, losingCards);

    if (common > 0) {
      localPoints = 1;
    }

    for (int i = 0; i < common - 1; i++) {
      localPoints *= 2;
    }

    points += localPoints;
  }

  std::cout << "🔔 Day 4.1: " << points << "" << std::endl;
}

void day4(bool useExample) {
  std::string path = "../input/4.txt";
  if (useExample) {
    path = "../input/4example.txt";
  }
  std::vector<std::string> lines = readInputToLines(path);
  auto start = std::chrono::high_resolution_clock::now();
  part1(lines);
  part2(lines);
  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double, std::milli> elapsed = end - start;
  std::cout << "🔔 Day4 runtime: " << elapsed.count() << "ms" << std::endl;
}