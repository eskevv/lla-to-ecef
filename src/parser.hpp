#pragma once

#include "models.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace wgs {
template <typename T> // utility class parses each csv line into a unique object
class ParseConstructor {
public:
  virtual auto create(const std::vector<std::string> &) -> T = 0;
};

// LLA_Entry creater from CSV
class LLA_Parser : public ParseConstructor<LLA_Entry> {
public:
  auto create(const std::vector<std::string> &line) -> LLA_Entry override {
    return LLA_Entry{std::stod(line[0]), std::stod(line[1]), std::stod(line[2]), std::stod(line[3])};
  }
};

// I could have also replaced all this abstarct logic for a simple lambda as an arguement
// but it is more extendable this way
template <typename T> 
inline auto parse_csv(const std::string &filename, ParseConstructor<T> *transformer) -> std::vector<T> {
  std::vector<T> data;
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Failed to open the file: " << filename << std::endl;
  } else {
    std::string line{};
    while (std::getline(file, line)) { // Read each line from the file
      std::vector<std::string> row;
      std::stringstream lineStream(line);
      std::string cell;
      while (std::getline(lineStream, cell, ',')) { // Parse each cell of the line
        row.push_back(cell);
      }
      data.push_back(transformer->create(row)); // use the transformer to create an object from this line
    }
  }
  file.close();
  return data;
}
} // namespace wgs
