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

#include "Day01.hpp"

AdventOfCode::AdventOfCode()
{
  std::ifstream stream("input.txt");
  
  std::cout << AdventOfCode_2022::Day01::challenge01(stream) << std::endl;
}
