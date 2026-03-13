#pragma once
#include "Utils.hpp"

class Snake
{
	private:
		std::deque<std::pair<int, int>> body;
		Direction dir;

		void	reduce(void) { body.pop_back(); };
		void	add(std::pair<int, int> next) { body.push_front(next); };

	public:

		Snake(void): dir(Direction::Right) {};
		void init(void)
		{
			body.emplace_back(5, 2);
			body.emplace_back(5, 1);
			body.emplace_back(5, 0);
		};
		std::pair<int, int>				head(void) const noexcept { return body.front(); };
		std::pair<int, int>				tail(void) const noexcept { return body.back(); };
		Direction						direction(void) const noexcept { return dir; };
		int								length(void) const noexcept { return body.size(); };
		StepEvent						takeAction(Board& board, Action a)
		{
			dir = applyAction(dir, a);
			std::pair<int, int> next = {body.front().first + dirToPar(dir).first, body.front().second + dirToPar(dir).second};
			if (!inBounds(next) || board.get(next) == Cell::SnakeBody) return StepEvent::Died;
			add(next);
			std::pair<int, int> h = head();
			std::pair<int, int> t = tail();
			if (board.get(next) == Cell::GreenApple)
			{
				board.set(h, Cell::SnakeBody);
				board.placeApple(Cell::GreenApple);
				return StepEvent::GreenApple;
			}
			else if (board.get(next) == Cell::RedApple)
			{
				board.set(t, Cell::Empty);
				reduce();
				if (body.empty()) return StepEvent::Died;
				t = tail();
				board.set(t, Cell::Empty);
				reduce();
				board.set(h, Cell::SnakeBody);
				board.placeApple(Cell::RedApple);
				return StepEvent::RedApple;
			}
			else if (board.get(next) == Cell::Empty && board.look(h, dir) == Cell::GreenApple)
			{
				board.set(h, Cell::SnakeBody);
				board.set(t, Cell::Empty);
				reduce();
				return StepEvent::Closer;
			}
			else
			{
				board.set(h, Cell::SnakeBody);
				board.set(t, Cell::Empty);
				reduce();
				return StepEvent::None;
			}
		};
		unsigned int					getState(const Board& board)
		{
			const std::pair<int, int> h = body.front();

			const auto s = static_cast<int>(board.look(h, dir));
			const auto l = static_cast<int>(board.look(h, turnLeft(dir)));
			const auto r = static_cast<int>(board.look(h, turnRight(dir)));

			return s + l * 4 + r * 16;
		}
};
