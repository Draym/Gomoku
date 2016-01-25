#include <ctime>
#include <future>
#include <vector>

#include "AI\monteCarlo\MonteCarlo.h"

/*
	TOOLS
*/

void initRandom()
{
	std::srand((unsigned int)std::time(nullptr));
}

int getRandom(int max)
{
	return std::rand() % max;
}

bool playTurn(const CellCoordinate &pos, const PlayerId &current, Grid<Cell> &map, Referee<Grid<Cell>> &referee)
{
	if (map.at(pos.at(0), pos.at(1)).player_id == PlayerId::None) {
		referee.play(pos.at(0), pos.at(1), current, map);
		return true;
	}
	return false;
}

bool generateGame(const CellCoordinate &pos, const PlayerId &me, Grid<Cell> map, Referee<Grid<Cell>> &referee)
{
	PlayerId current = me;
	if (!playTurn(pos, current, map, referee))
		return false;
	current = (current == PlayerId::P1 ? PlayerId::P2 : PlayerId::P1);

	std::vector<CellCoordinate> potential = MonteCarloHeuristic::get().find(map, referee, me, { MonteCarloHeuristic::RuleName::Empty() });
	PlayerId winner = PlayerId::None;
	int random = 0;

	while (!potential.empty())
	{
		random = getRandom(potential.size());
		if (playTurn(potential[random], current, map, referee))
		{
			potential.erase(potential.begin() + random);
			if ((winner = referee.get_winner()) != PlayerId::None)
				break;
			current = (current == PlayerId::P1 ? PlayerId::P2 : PlayerId::P1);
		}
	}
	if (winner == me)
		return true;
	return false;
}

std::vector<bool> generateNbGames(int nbr, const CellCoordinate &pos, const PlayerId &playerId, Grid<Cell> &map, Referee<Grid<Cell>> &referee)
{
	std::vector<bool> result;

	for (int i = 0; i < nbr; ++i) {
		result.push_back(generateGame(pos, playerId, map, referee));
	}
	return result;
}

float generateManyGames(int nbr, const CellCoordinate &pos, const PlayerId &playerId, Grid<Cell> &map, Referee<Grid<Cell>> &referee)
{
	std::vector<std::future<std::vector<bool>>> futures;
	std::vector<bool> result;
	int totalSuccess = 0;
	int current = 0;
	int	todo = 0;

	while (current < nbr) {
		todo = (current + 100 > nbr ? nbr - current : 100);
		futures.push_back(std::async(generateNbGames, todo, pos, playerId, map, referee));
		current += todo;
	}

	for (std::size_t i = 0; i < futures.size(); ++i)
	{
		std::vector<bool> tmp = futures[i].get();
		for (std::size_t i2 = 0; i2 < tmp.size(); ++i2) {
			result.push_back(tmp[i2]);
		}
	}

	for (std::size_t i = 0; i < result.size(); ++i)
	{
		if (result[i])
			totalSuccess += 1;
	}
	return ((float)(totalSuccess * 100) / (float)result.size());
}


CellCoordinate	do_monteCarlo(int nbr, const std::vector<CellCoordinate> &potential, Referee<Grid<Cell>> &referee, Grid<Cell> &map, const PlayerId &playerId) {
	std::vector<std::future<float>> futures;

	referee.enable_rule(Rule::OPT_BREAK_FIVE, false);
	referee.enable_rule(Rule::OPT_DOUBLE_THREE, false);
	referee.enable_rule(Rule::OPT_FREESTYLE, false);
	for (std::size_t i = 0; i < potential.size(); ++i)
	{
		futures.push_back(std::async(std::launch::async, generateManyGames, nbr, potential[i], playerId, map, referee));
	}
	float current;
	myTuple<int, int, float> bestPercent = myTuple<int, int, float>(0, 0, 0.0F);
	for (std::size_t i = 0; i < futures.size(); ++i)
	{
		current = futures[i].get();
		if (current >= bestPercent.second)
			bestPercent.modify(potential[i].at(0), potential[i].at(1), current);
		if (current == 100)
			break;
	}
	if (potential.size() > 0)
	{
		return{ bestPercent.first, bestPercent.second };
	}
	else
	{
		return{ -1, -1 };
	}
}

CellCoordinate	getRandomIn(int x, int maxX, int y, int maxY)
{
	if (maxX <= x || maxY <= y)
		return{ 9, 9 };
	return{ getRandom(maxX - x) + x, getRandom(maxY - y) + y };
}

CellCoordinate monteCarloEasy(Referee<Grid<Cell>> referee, Grid<Cell> map, PlayerId playerId)
{
	std::vector<CellCoordinate> potential = MonteCarloHeuristic::get().findFirstOf(map, referee, playerId,
	{ MonteCarloHeuristic::RuleName::Winnable(),
		MonteCarloHeuristic::RuleName::Loseable(),
		MonteCarloHeuristic::RuleName::Winnable3Trap(),
		MonteCarloHeuristic::RuleName::Loseable3Trap(),
		MonteCarloHeuristic::RuleName::InRange() + ":2" },
	{ MonteCarloHeuristic::RuleName::Valid() });

	initRandom();
	if (potential.size() == 0) {
		return getRandomIn(0, 18, 0, 18);
	}
	else if (potential.size() > 80) {
		potential = MonteCarloHeuristic::get().findAdditionOf(map, referee, playerId, { MonteCarloHeuristic::RuleName::InRange() + ":1", MonteCarloHeuristic::RuleName::Valid() });
	}
	std::cout << "[MonteCarloEasy] potential playable action: " << potential.size() << std::endl;
	if (MonteCarloHeuristic::Tools::countItem(map, playerId) == 0 && MonteCarloHeuristic::Tools::countItem(map, (playerId == PlayerId::P1 ? PlayerId::P2 : PlayerId::P1)) == 0) {
		return getRandomIn(4, 14, 4, 14);
	}
	else {
		return do_monteCarlo(200, potential, referee, map, playerId);
	}
}

CellCoordinate monteCarloMedium(Referee<Grid<Cell>> referee, Grid<Cell> map, PlayerId playerId)
{
	std::vector<CellCoordinate> potential = MonteCarloHeuristic::get().findFirstOf(map, referee, playerId,
	{ MonteCarloHeuristic::RuleName::Winnable(),
		MonteCarloHeuristic::RuleName::Loseable(),
		MonteCarloHeuristic::RuleName::Winnable3Trap(),
		MonteCarloHeuristic::RuleName::Loseable3Trap(),
		MonteCarloHeuristic::RuleName::BreakIt(),
		MonteCarloHeuristic::RuleName::DefendIt(),
		MonteCarloHeuristic::RuleName::InRangeEnemy() + ":2",
		MonteCarloHeuristic::RuleName::Valid() },
		{ MonteCarloHeuristic::RuleName::Valid() });

	initRandom();

	if (potential.size() == 0) {
		return getRandomIn(0, 18, 0, 18);
	}
	else if (potential.size() > 80) {
		potential = MonteCarloHeuristic::get().findAdditionOf(map, referee, playerId, { MonteCarloHeuristic::RuleName::InRange() + ":1", MonteCarloHeuristic::RuleName::Valid() });
	}
	std::cout << "[MonteCarloMedium] potential playable action: " << potential.size() << std::endl;
	if (MonteCarloHeuristic::Tools::countItem(map, playerId) == 0 && MonteCarloHeuristic::Tools::countItem(map, (playerId == PlayerId::P1 ? PlayerId::P2 : PlayerId::P1)) == 0) {
		return getRandomIn(4, 14, 4, 14);
	}
	else {
		return do_monteCarlo(400, potential, referee, map, playerId);
	}
}

CellCoordinate monteCarloHard(Referee<Grid<Cell>> referee, Grid<Cell> map, PlayerId playerId)
{
	std::vector<CellCoordinate> potential = MonteCarloHeuristic::get().findFirstOf(map, referee, playerId,
	{ MonteCarloHeuristic::RuleName::Winnable(),
		MonteCarloHeuristic::RuleName::Loseable(),
		MonteCarloHeuristic::RuleName::Winnable3Trap(),
		MonteCarloHeuristic::RuleName::Loseable3Trap(),
		MonteCarloHeuristic::RuleName::DefendIt(),
		MonteCarloHeuristic::RuleName::InRangeAlly() + ":2",
		MonteCarloHeuristic::RuleName::Valid() },
		{ MonteCarloHeuristic::RuleName::Valid() });

	initRandom();

	if (potential.size() == 0) {
		return getRandomIn(0, 18, 0, 18);
	}
	else if (potential.size() > 80) {
		potential = MonteCarloHeuristic::get().findAdditionOf(map, referee, playerId, { MonteCarloHeuristic::RuleName::InRange() + ":1", MonteCarloHeuristic::RuleName::Valid() });
	}
	std::cout << "[MonteCarloHard] potential playable action: " << potential.size() << std::endl;
	if (MonteCarloHeuristic::Tools::countItem(map, playerId) == 0 && MonteCarloHeuristic::Tools::countItem(map, (playerId == PlayerId::P1 ? PlayerId::P2 : PlayerId::P1)) == 0) {
		return getRandomIn(4, 14, 4, 14);
	}
	else {
		return do_monteCarlo(600, potential, referee, map, playerId);
	}
}
