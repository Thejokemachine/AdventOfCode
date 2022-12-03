//
//  Day02.cpp
//  AdventOfCode
//
//  Created by Joakim on 2022-12-02.
//

#include "Day02.hpp"

#include <unordered_map>
#include <string>

using namespace AdventOfCode_2022;

#define ROCK 1
#define PAPER 2
#define SCISSOR 3

#define WIN 6
#define DRAW 3
#define LOSS 0

int getOutcome(int opponent, int you)
{
  static std::unordered_map<int, int> Outcomes {
    {2, WIN},
    {1, LOSS},
    {0, DRAW},
    {-1, WIN},
    {-2, LOSS},
  };
  
  return Outcomes[opponent - you];
}

int getMatchScore(int opponent, int you)
{

  int score = you;
  score += getOutcome(opponent, you);
  
  return score;
}

std::string Day02::challenge01(std::ifstream &input)
{
  std::unordered_map<char, int> ToValue = {
    {'A', ROCK},{'B', PAPER},{'C', SCISSOR},
    {'X', ROCK},{'Y', PAPER},{'Z', SCISSOR}
  };
  
  std::string line;
  
  int totalScore = 0;
  while (std::getline(input, line))
  {
    char opponent = line[0];
    char you = line[2];
    totalScore += getMatchScore(ToValue[opponent], ToValue[you]);
  }
  
  return "The total amount of points when following the instructions should be: " + std::to_string(totalScore);
}

std::string Day02::challenge02(std::ifstream &input)
{
  std::unordered_map<char, int> ToValue = {
    {'A', ROCK},{'B', PAPER},{'C', SCISSOR},
    {'X', LOSS},{'Y', DRAW},{'Z', WIN}
  };
  
  std::string line;
  
  int totalScore = 0;
  while (std::getline(input, line))
  {
    int opponent = ToValue[line[0]];
    int neededOutcome = ToValue[line[2]];
    
    for (int i = ROCK; i <= SCISSOR; ++i)
    {
        if (getOutcome(opponent, i) == neededOutcome)
        {
          totalScore += getMatchScore(opponent, i);
          break;
        }
    }
  }
  
  return "The total amount of points when following the instructions should be: " + std::to_string(totalScore);
}
