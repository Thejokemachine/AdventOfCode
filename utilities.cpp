//
//  utilities.cpp
//  AdventOfCode
//
//  Created by Joakim on 2022-12-05.
//

#include "utilities.hpp"

#include <string>
#include <fstream>
#include <sstream>

using namespace utilities;

std::vector<std::string> utilities::splitString(const std::string& string, const std::string& delim)
{
  std::vector<std::string> strs;
    
  uint64_t start = 0;
  uint64_t end;
  do {
    end = string.find(delim, start);
    strs.emplace_back(string.substr(start, end - start));
    start = end + delim.length();
  } while (end != std::string::npos);
  
  return strs;
}

void utilities::forEachLine(std::ifstream& stream, std::function<void(const std::string&)> func)
{
    std::string line;

    while (std::getline(stream, line))
    {
        func(line);
    }
}

std::string utilities::dumpContents(std::ifstream& stream)
{
    std::stringstream ss;
    ss << stream.rdbuf();
    return ss.str();
}
