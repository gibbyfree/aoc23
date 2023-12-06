#include "day2.h"
#include <chrono>
#include <iostream>
#include <numeric>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include "input_utils.h"

int multiplyCubes(std::unordered_map<std::string, int> cubes) {
  int res = 1;
  for (const auto& element : cubes) {
    res *= element.second;
  }
  return res;
}

// (id if valid, cubepowers)
std::tuple<int, int> processGame(std::string gameAndId,
                                 std::vector<std::string> cubeSets) {
  std::unordered_map<std::string, int> maxCubes = {
      {"red", 0}, {"green", 0}, {"blue", 0}};
  int id = 0;

  for (std::string cubeSet : cubeSets) {
    std::vector<std::string> cubes;
    std::stringstream streamCubes(cubeSet);
    std::string cube;

    while (getline(streamCubes, cube, ',')) {
      cubes.push_back(cube);
    }

    for (std::string cube : cubes) {
      std::vector<std::string> cubeValues;
      std::stringstream streamValues(cube);
      std::string value;

      while (getline(streamValues, value, ' ')) {
        cubeValues.push_back(value);
      }

      int numCubes = std::stoi(cubeValues[1]);
      std::string color = cubeValues[2];

      if (numCubes > maxCubes[color]) {
        maxCubes[color] = numCubes;
      }

      if ((numCubes > 12 && color == "red") ||
          (numCubes > 13 && color == "green") ||
          (numCubes > 14 && color == "blue")) {
        id = -1;
      }
    }
  }

  if (id == -1) {
    return std::tuple<int, int>(-1, multiplyCubes(maxCubes));
  } else {
    std::string id_str = gameAndId.substr(5);
    int id = std::stoi(id_str);
    return std::tuple<int, int>(id, multiplyCubes(maxCubes));
  }
}

void part1And2(std::vector<std::string> lines) {
  std::vector<int> ids;
  std::vector<int> powers;

  for (std::string line : lines) {
    std::string gameAndId = line.substr(0, line.find(':'));
    line.erase(0, line.find(':') + 1);

    std::vector<std::string> cubeSets;
    std::stringstream streamSets(line);
    std::string cubeSet;

    while (getline(streamSets, cubeSet, ';')) {
      cubeSets.push_back(cubeSet);
    }

    std::tuple<int, int> result = processGame(gameAndId, cubeSets);
    if (std::get<0>(result) != -1) {
      ids.push_back(std::get<0>(result));
    }
    powers.push_back(std::get<1>(result));
  }

  std::cout << "🎁 Day 2.1: " << std::accumulate(ids.begin(), ids.end(), 0)
            << std::endl;
  std::cout << "🎁 Day 2.2: " << std::accumulate(powers.begin(), powers.end(), 0)
            << std::endl;
}

void day2(bool useExample) {
  std::string path = "../input/2.txt";
  if (useExample) {
    path = "../input/2example.txt";
  }
  std::vector<std::string> lines = readInputToLines(path);
  auto start = std::chrono::high_resolution_clock::now();

  part1And2(lines);

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = end - start;
  std::cout << "🎁 Day2 runtime: " << elapsed.count() << "ms" << std::endl;
}
