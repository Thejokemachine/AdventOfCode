//
//  Day08.cpp
//  AdventOfCode
//
//  Created by Joakim on 2022-12-08.
//

#include "Day08.hpp"

#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <functional>

using namespace AdventOfCode_2022;

using Grid = std::vector<std::vector<int>>;

size_t createHash(int x, int y)
{
  std::string s = std::to_string(x) + ":" + std::to_string(y);
  return std::hash<std::string>{}(s);
}

std::string Day08::challenge01(std::ifstream& input)
{
  std::string line;

  Grid trees;

  while (std::getline(input, line))
  {
    trees.push_back({});
    
    for (auto c : line)
    {
      trees.back().push_back(c);
    }
  }

  const size_t WIDTH = trees.front().size();
  const size_t HEIGHT = trees.size();
  
  std::unordered_set<size_t> visible;
  
  for (int y = 0; y < HEIGHT; ++y)
  {
    int highest = 0;
    
    for (int x = 0; x < WIDTH; ++x)
    {
      int height = trees[y][x];
      
      if (highest < height)
      {
        visible.insert(createHash(x, y));
        highest = height;
      }
    }
    
    highest = 0;
    
    for (int x = WIDTH-1; x >= 0; --x)
    {
      int height = trees[y][x];
      
      if (highest < height)
      {
        visible.insert(createHash(x, y));
        highest = height;
      }
    }
  }
  
  for (int x = 0; x < WIDTH; ++x)
  {
    int highest = 0;
    
    for (int y = 0; y < HEIGHT; ++y)
    {
      int height = trees[y][x];
      
      if (highest < height)
      {
        visible.insert(createHash(x, y));
        highest = height;
      }
    }
    
    highest = 0;
    
    for (int y = HEIGHT-1; y >= 0; --y)
    {
      int height = trees[y][x];
      
      if (highest < height)
      {
        visible.insert(createHash(x, y));
        highest = height;
      }
    }
  }

  return std::to_string(visible.size());
}

int calculateScenicScore(const Grid& grid, int x, int y)
{
  int left, right, up, down;
  left = right = up = down = 0;
  
  int marginsLeft = x+1;
  int marginsRight = grid[y].size() - x;
  int marginsUp = y+1;
  int marginsDown = grid.size() - y;
  
  int height = grid[y][x];
  
  for (int i = 0; i < marginsLeft; ++i)
  {
    int other = grid[y][x-i];
    if (other >= height && i > 0)
    {
      break;
    }
    ++left;
  }
  
  for (int i = 0; i < marginsRight; ++i)
  {
    int other = grid[y][x+i];
    if (other >= height && i > 0)
    {
      break;
    }
    ++right;
  }
  
  for (int i = 0; i < marginsUp; ++i)
  {
    int other = grid[y-i][x];
    if (other >= height && i > 0)
    {
      break;
    }
    ++up;
  }
  
  for (int i = 0; i < marginsDown; ++i)
  {
    int other = grid[y+i][x];
    if (other >= height && i > 0)
    {
      break;
    }
    ++down;
  }
  
  left = std::min(left, marginsLeft-1);
  right = std::min(right, marginsRight-1);
  up = std::min(up, marginsUp-1);
  down = std::min(down, marginsDown-1);
  
  return left * right * up * down;
}

std::string Day08::challenge02(std::ifstream& input)
{
  std::string line;

  Grid trees;

  while (std::getline(input, line))
  {
    trees.push_back({});
    
    for (auto c : line)
    {
      trees.back().push_back(c - '0');
    }
  }
  
  int highestScenicScore = 0;
  
  for (int y = 0; y < trees.size(); ++y)
  {
    for (int x = 0; x < trees[y].size(); ++x)
    {
      int scenicScore = calculateScenicScore(trees, x, y);
      if (scenicScore > highestScenicScore)
      {
        highestScenicScore = scenicScore;
      }
    }
  }
  
  return std::to_string(highestScenicScore);
}
