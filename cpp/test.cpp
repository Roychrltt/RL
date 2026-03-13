#include "Game.hpp"

void	update(uint8_t s, uint8_t a, float r, uint8_t s2, std::vector<std::vector<float>>& qtable)
{
	float alpha = 0.1, gamma = 0.4;
	float maxNext = std::max({qtable[s2][0], qtable[s2][1], qtable[s2][2]});
	qtable[s][a] += alpha * (r + gamma * maxNext - qtable[s][a]);
}

int main(int ac, char *av[])
{
	int t = std::stoi(av[1]);
	int len = 0;
	int i = 0;
	std::vector<std::vector<float>> qtable(64, std::vector<float>(3));
	float decay = 0.95;
	float rand = 10.0;
	static std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> roll(0, 1);
	std::uniform_int_distribution<int> ra(0, 2);
	long long int lll = 0;
	while (++i <= t)
	{
		int curLen = 0;
		Board board;
		board.init();
		Snake snake;
		snake.init();
		int stepCnt = 0;
		while (++stepCnt < 500)
		{
			int state = snake.getState(board);
			int a = 0;
			if (qtable[state][1] > qtable[state][a]) a = 1;
			if (qtable[state][2] > qtable[state][a]) a = 2;
			if (i < 1000 && roll(rng) < rand) a = ra(rng);
			auto e = snake.takeAction(board, static_cast<Action>(a));
			float r = 0.0;
			if (e == StepEvent::None) r = -0.1;
			else if (e == StepEvent::GreenApple) r = 50.0;
			else if (e == StepEvent::Closer) r = 0.01;
			else if (e == StepEvent::RedApple) r = -25.0;
			else r = -50;
			int s2 = snake.getState(board);
			update(state, a, r, s2, qtable);
			curLen = std::max(curLen, snake.length());
			if (e == StepEvent::Died) break;
		}
		len = std::max(len, curLen);
		std::cout << "Training loop: " << i << ". Snake length: " << curLen << std::endl;
		rand *= decay;
		lll += curLen;
	}
	std::ofstream output;
	output.open("Q-Table.txt");
	for (auto& v : qtable)
		output << v[0] << " " << v[1] << " " << v[2] << std::endl;
	output.close();
	std::cout << GREEN << t << " training loops finished. Best length: " << len << RESET << std::endl;
	std::cout << GREEN << "Average length: " << lll / t << RESET << std::endl;
	return 0;
}
