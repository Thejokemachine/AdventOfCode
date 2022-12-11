//
//  utilities.hpp
//  AdventOfCode
//
//  Created by Joakim on 2022-12-05.
//

#ifndef utilities_hpp
#define utilities_hpp

#include <stdio.h>

#include <vector>
#include <string>
#include <functional>

namespace utilities
{
  std::vector<std::string> splitString(const std::string& string, const std::string& delim);

  void forEachLine(std::ifstream& stream, std::function<void(const std::string&)> func);

  std::string dumpContents(std::ifstream& stream);
}

#endif /* utilities_hpp */
