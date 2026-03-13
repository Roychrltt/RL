#pragma once
#include "Types.hpp"
#include "Utils.hpp"

class Board
{
	private:
		std::array<Cell, GRID_W * GRID_H> grid{};

	public:

		Board() {};
		void				init()
		{
			grid.fill(Cell::Empty);
			set({5, 0}, Cell::SnakeBody);
			set({5, 1}, Cell::SnakeBody);
			set({5, 2}, Cell::SnakeBody);
			placeApple(Cell::GreenApple);
			placeApple(Cell::GreenApple);
			placeApple(Cell::RedApple);
		}
		[[nodiscard]] Cell	get(std::pair<int, int> p) const noexcept { return grid[p.first * GRID_W + p.second]; }
		void 				set(std::pair<int, int> p, Cell c) noexcept { grid[p.first * GRID_W + p.second] = c; }
		void				placeApple(Cell type)
		{
			std::vector<std::pair<int, int>> emptyCells;
			for (int i = 0; i < GRID_W * GRID_H; ++i)
				if (grid[i] == Cell::Empty) emptyCells.push_back({i / GRID_W, i % GRID_W});

			if (emptyCells.empty()) return;
			static std::mt19937 rng(std::random_device{}());
			std::uniform_int_distribution<int> dist(0, emptyCells.size() - 1);
			std::pair<int, int> chosen = emptyCells[dist(rng)];
			set(chosen, type);
		}
		void				printBoard(void) const
		{
			for (int i = 0; i < GRID_H; i++)
			{
				for (int j = 0; j < GRID_W; j++)
				{
					if (grid[i * GRID_W + j] == Cell::Empty) std::cout << "x ";
					else if (grid[i * GRID_W + j] == Cell::GreenApple) std::cout << "G ";
					else if (grid[i * GRID_W + j] == Cell::SnakeBody) std::cout << "S ";
					else if (grid[i * GRID_W + j] == Cell::RedApple) std::cout << "R ";
				}
				std::cout << std::endl;
			}
		}
		Cell look(std::pair<int, int> h, Direction d) const
		{
			auto [dx, dy] = dirToPar(d);
			std::pair<int, int> next = {h.first + dx, h.second + dy};
			unsigned int idx = (h.first + dx) * GRID_W + h.second + dy;
			if (!inBounds(next) || grid[idx] == Cell::SnakeBody) return Cell::SnakeBody;
			if (grid[idx] == Cell::RedApple) return Cell::RedApple;
			while (inBounds(next))
			{
				idx = next.first * GRID_W + next.second;
				if (grid[idx] != Cell::Empty)
					return grid[idx] == Cell::GreenApple? Cell::GreenApple : Cell::Empty;
				next.first += dx;
				next.second += dy;
			}
			return Cell::Empty;
		}
};

