//
//  AdventOfCode.cpp
//  AdventOfCode
//
//  Created by Joakim on 2022-12-01.
//

#include "AdventOfCode.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

#include <vector>

#include "Day06.hpp"

#define TESTING 0

AdventOfCode::AdventOfCode()
{
#if TESTING
  std::ifstream stream("input_debug.txt");
#else
  std::ifstream stream("input.txt");
#endif
  
  std::cout << AdventOfCode_2022::Day06::challenge01(stream) << std::endl;
}
