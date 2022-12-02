//
//  Day01.cpp
//  AdventOfCode
//
//  Created by Joakim on 2022-12-01.
//

#include "Day01.hpp"

#include <vector>

using namespace AdventOfCode_2022;

std::string Day01::challenge01(std::ifstream &input)
{
  std::string line;
  std::vector<int> calories = {0};
  
  while (std::getline(input, line))
  {
    if (line.empty())
    {
      calories.emplace_back();
    }
    else
    {
      calories.back() += std::stoi(line);
    }
  }
  
  std::sort(calories.begin(), calories.end());
  
  return "The most any of the Elves is carrying is: " + std::to_string(calories.back()) + " calories.";
}

std::string Day01::challenge02(std::ifstream &input)
{
  std::string line;
  std::vector<int> calories = {0};
  
  while (std::getline(input, line))
  {
    if (line.empty())
    {
      calories.emplace_back();
    }
    else
    {
      calories.back() += std::stoi(line);
    }
  }
  
  std::sort(calories.begin(), calories.end());
  
  int topThreeTotalCalorieCount = 0;
  for (int i = 0; i < 3; ++i)
  {
    topThreeTotalCalorieCount += calories[calories.size()-(1+i)];
  }
  
  return "The three Elves carrying the most are carrying " + std::to_string(topThreeTotalCalorieCount) + " calories in total.";
}
