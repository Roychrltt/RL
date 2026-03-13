#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iostream>
#include <map>
#include <fstream>
#include <optional>
#include <random>
#include <ranges>
#include <span>
#include <stdexcept>
#include <utility>
#include <vector>
#include "Types.hpp"

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define GRAY "\033[90m"
# define BOLD "\033[1m"
# define UNDER "\033[4m"
# define BLINK "\033[5m"
# define ERASE = "\033[2K\r"
# define RESET "\033[0m"

constexpr Direction turnLeft(Direction d) noexcept
{
	constexpr std::array<Direction, 4> lut = {
		Direction::Left, Direction::Right, Direction::Down, Direction::Up
	};
	return lut[static_cast<uint8_t>(d)];
}

constexpr Direction turnRight(Direction d) noexcept
{
	constexpr std::array<Direction, 4> lut = {
		Direction::Right, Direction::Left, Direction::Up, Direction::Down
	};
	return lut[static_cast<uint8_t>(d)];
}

constexpr Direction applyAction(Direction current, Action a) noexcept
{
	switch (a)
	{
		case Action::TurnLeft:  return turnLeft(current);
		case Action::TurnRight: return turnRight(current);
		default:                return current;
	}
}

constexpr bool inBounds(std::pair<int, int> p) noexcept
{
	return p.first >= 0 && p.first < GRID_H && p.second >= 0 && p.second < GRID_W;
}

constexpr std::pair<int, int> dirToPar(Direction d) noexcept
{
    switch (d)
	{
        case Direction::Up:    return { -1, 0};
        case Direction::Down:  return { 1,  0};
        case Direction::Left:  return {0,  -1};
        case Direction::Right: return {0,  1};
    }
}
