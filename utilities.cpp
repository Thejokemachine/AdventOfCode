//
//  utilities.cpp
//  AdventOfCode
//
//  Created by Joakim on 2022-12-05.
//

#include "utilities.hpp"

using namespace utilities;

std::vector<std::string> utilities::splitString(const std::string& string, const char delim)
{
  std::vector<std::string> strs;
    
  uint64_t start = 0;
  uint64_t end;
  do {
    end = string.find(delim, start);
    strs.emplace_back(string.substr(start, end - start));
    start = end + 1;
  } while (end != std::string::npos);
  
  return strs;
}
