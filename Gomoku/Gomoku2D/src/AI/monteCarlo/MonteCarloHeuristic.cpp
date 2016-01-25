#include "AI\monteCarlo\MonteCarloHeuristic.h"


MonteCarloHeuristic MonteCarloHeuristic::instance = MonteCarloHeuristic();


MonteCarloHeuristic& MonteCarloHeuristic::get()
{
	return instance;
}

MonteCarloHeuristic::MonteCarloHeuristic()
{
	this->verifMethods[RuleName::Empty()] = Rule::isEmpty;
	this->verifMethods[RuleName::Valid()] = Rule::isValid;
	this->verifMethods[RuleName::InRange()] = Rule::isInRange;
	this->verifMethods[RuleName::InRangeEnemy()] = Rule::isInRangeEnemy;
	this->verifMethods[RuleName::InRangeAlly()] = Rule::isInRangeAlly;
	this->verifMethods[RuleName::BreakIt()] = Rule::isCanBreak;
	this->verifMethods[RuleName::DefendIt()] = Rule::isCanDefend;
	this->verifMethods[RuleName::Winnable()] = Rule::isWinnable;
	this->verifMethods[RuleName::Loseable()] = Rule::isLoseable;
	this->verifMethods[RuleName::Winnable3Trap()] = Rule::isWinnable3Trap;
	this->verifMethods[RuleName::Loseable3Trap()] = Rule::isLoseable3Trap;
}

MonteCarloHeuristic::~MonteCarloHeuristic()
{
}

// TOOLS
int	MonteCarloHeuristic::Tools::toInt(std::string value) {
	if (value != "") {
		int nb;

		std::istringstream(value) >> nb;
		return nb;
	}
	return 0;
}

float MonteCarloHeuristic::Tools::coordDistance(float x1, float y1, float x2, float y2)
{
	float result = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	//	if ((int)result <= 1)
	//		std::cout << "[" << x1 << ", " << y1 << "] - [" << x2 << ", " << y2 << "] -> " << result << std::endl;
	return result;
}

int MonteCarloHeuristic::Tools::countItem(const Grid<Cell>& map, const PlayerId & id)
{
	int result = 0;
	for (int y = 0; y < (int)map.height(); ++y) {
		for (int x = 0; x < (int)map.width(); ++x) {
			if (map.at(x, y).player_id == id)
				++result;
		}
	}
	return result;
}

bool MonteCarloHeuristic::Tools::hasBreakableSpecificItemInRange(const CellCoordinate & pos, const Grid<Cell>& map, PlayerId id)
{
	int startX = pos.at(0);
	int startY = pos.at(1);
	int	sizeX = 1;
	int sizeY = 1;

	startX = (startX > 0 ? startX - 1 : 0);
	startY = (startY > 0 ? startY - 1 : 0);
	sizeX += 2;
	sizeY += 2;
	sizeX = (startX + sizeX >= (int)map.width() ? map.width() - startX - 1 : sizeX);
	sizeY = (startY + sizeY >= (int)map.height() ? map.height() - startY - 1 : sizeY);

	int x = startX;
	int y = startY;

	while (x < startX + sizeX)
	{
		if (map.at(x, y).player_id == id && map.at(x, y).breakable) {
			int diffX = x - pos.at(0);
			int diffY = y - pos.at(1);
			//std::cout << "in [" << x << ", " << y << "] pos [" << pos.at(0) << ", " << pos.at(1) << "] {" << diffX << ", " << diffY << "} -> [" << x + diffX << ", " << y + diffY << "]" << std::endl;
			if (x + diffX >= 0 && x + diffX < (int)map.width()
				&& y + diffY >= 0 && y + diffY < (int)map.height()
				&& map.at(x + diffX, y + diffY).breakable) {
				return true;
			}
		}
		++x;
	}
	--x;
	y = startY;
	while (y < startY + sizeY)
	{
		if (map.at(x, y).player_id == id && map.at(x, y).breakable) {
			int diffX = x - pos.at(0);
			int diffY = y - pos.at(1);
			if (x + diffX >= 0 && x + diffX < (int)map.width()
				&& y + diffY >= 0 && y + diffY < (int)map.height()
				&& map.at(x + diffX, y + diffY).breakable) {
				return true;
			}
		}
		++y;
	}
	--y;
	while (x != startX)
	{
		if (map.at(x, y).player_id == id && map.at(x, y).breakable) {
			int diffX = x - pos.at(0);
			int diffY = y - pos.at(1);
			if (x + diffX >= 0 && x + diffX < (int)map.width()
				&& y + diffY >= 0 && y + diffY < (int)map.height()
				&& map.at(x + diffX, y + diffY).breakable) {
				return true;
			}
		}
		--x;
	}
	while (y != startY)
	{
		if (map.at(x, y).player_id == id && map.at(x, y).breakable) {
			int diffX = x - pos.at(0);
			int diffY = y - pos.at(1);
			if (x + diffX >= 0 && x + diffX < (int)map.width()
				&& y + diffY >= 0 && y + diffY < (int)map.height()
				&& map.at(x + diffX, y + diffY).breakable) {
				return true;
			}
		}
		--y;
	}
	return false;
}

int MonteCarloHeuristic::Tools::getTheClosestItem(const CellCoordinate & pos, const Grid<Cell>& map, const int &maxLevel)
{
	int startX = pos.at(0);
	int startY = pos.at(1);
	int	sizeX = 1;
	int sizeY = 1;
	int currentLevel = 0;

	while (currentLevel < maxLevel) {

		startX = (startX > 0 ? startX - 1 : 0);
		startY = (startY > 0 ? startY - 1 : 0);
		sizeX += 2;
		sizeY += 2;
		sizeX = (startX + sizeX >= (int)map.width() ? map.width() - startX - 1 : sizeX);
		sizeY = (startY + sizeY >= (int)map.height() ? map.height() - startY - 1 : sizeY);

		int x = startX;
		int y = startY;

		while (x < startX + sizeX)
		{
			if (map.at(x, y).player_id != PlayerId::None) {
				return (int)coordDistance((float)pos.at(0), (float)pos.at(1), (float)x, (float)y);
			}
			++x;
		}
		--x;
		y = startY;
		while (y < startY + sizeY)
		{
			if (map.at(x, y).player_id != PlayerId::None) {
				return (int)coordDistance((float)pos.at(0), (float)pos.at(1), (float)x, (float)y);
			}
			++y;
		}
		--y;
		while (x != startX)
		{
			if (map.at(x, y).player_id != PlayerId::None) {
				return (int)coordDistance((float)pos.at(0), (float)pos.at(1), (float)x, (float)y);
			}
			--x;
		}
		while (y != startY)
		{
			if (map.at(x, y).player_id != PlayerId::None) {
				return (int)coordDistance((float)pos.at(0), (float)pos.at(1), (float)x, (float)y);
			}
			--y;
		}
		++currentLevel;
	}
	return -1;
}

int MonteCarloHeuristic::Tools::getTheClosestSpecifiedItem(const CellCoordinate & pos, const Grid<Cell>& map, const int &maxLevel, PlayerId id)
{
	int startX = pos.at(0);
	int startY = pos.at(1);
	int	sizeX = 1;
	int sizeY = 1;
	int currentLevel = 0;

	while (currentLevel < maxLevel) {

		startX = (startX > 0 ? startX - 1 : 0);
		startY = (startY > 0 ? startY - 1 : 0);
		sizeX += 2;
		sizeY += 2;
		sizeX = (startX + sizeX >= (int)map.width() ? map.width() - startX - 1 : sizeX);
		sizeY = (startY + sizeY >= (int)map.height() ? map.height() - startY - 1 : sizeY);

		int x = startX;
		int y = startY;

		while (x < startX + sizeX)
		{
			if (map.at(x, y).player_id == id) {
				return (int)coordDistance((float)pos.at(0), (float)pos.at(1), (float)x, (float)y);
			}
			++x;
		}
		--x;
		y = startY;
		while (y < startY + sizeY)
		{
			if (map.at(x, y).player_id == id) {
				return (int)coordDistance((float)pos.at(0), (float)pos.at(1), (float)x, (float)y);
			}
			++y;
		}
		--y;
		while (x != startX)
		{
			if (map.at(x, y).player_id == id) {
				return (int)coordDistance((float)pos.at(0), (float)pos.at(1), (float)x, (float)y);
			}
			--x;
		}
		while (y != startY)
		{
			if (map.at(x, y).player_id == id) {
				return (int)coordDistance((float)pos.at(0), (float)pos.at(1), (float)x, (float)y);
			}
			--y;
		}
		++currentLevel;
	}
	return -1;
}

// RULES
bool MonteCarloHeuristic::Rule::isEmpty(const CellCoordinate & pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId & player_id, std::string optional)
{
	return (map.at(pos.at(0), pos.at(1)).player_id == PlayerId::None);
}

bool MonteCarloHeuristic::Rule::isValid(const CellCoordinate & pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId & player_id, std::string optional)
{
	return referee.is_valid(pos.at(0), pos.at(1), player_id, map);
}

bool MonteCarloHeuristic::Rule::isInRange(const CellCoordinate & pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId & player_id, std::string optional)
{
	int required = Tools::toInt(optional);

	if (required != 0)
	{
		int result = Tools::getTheClosestItem(pos, map, required);
		if (result != -1 && required >= result) {
			return true;
		}
	}
	return false;
}

bool MonteCarloHeuristic::Rule::isInRangeEnemy(const CellCoordinate & pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId & player_id, std::string optional)
{
	int required = Tools::toInt(optional);

	if (required != 0)
	{
		int result = Tools::getTheClosestSpecifiedItem(pos, map, required, (player_id == PlayerId::P1 ? PlayerId::P2 : PlayerId::P1));
		if (result != -1 && required >= result) {
			return true;
		}
	}
	return false;
}

bool MonteCarloHeuristic::Rule::isInRangeAlly(const CellCoordinate & pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId & player_id, std::string optional)
{
	int required = Tools::toInt(optional);

	if (required != 0)
	{
		int result = Tools::getTheClosestSpecifiedItem(pos, map, required, player_id);
		if (result != -1 && required >= result) {
			return true;
		}
	}
	return false;
}

bool MonteCarloHeuristic::Rule::isCanBreak(const CellCoordinate & pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId & player_id, std::string optional)
{
	return Tools::hasBreakableSpecificItemInRange(pos, map, (player_id == PlayerId::P1 ? PlayerId::P2 : PlayerId::P1));
}

bool MonteCarloHeuristic::Rule::isCanDefend(const CellCoordinate & pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId & player_id, std::string optional)
{
	return Tools::hasBreakableSpecificItemInRange(pos, map, player_id);
}

bool MonteCarloHeuristic::Rule::isWinnable(const CellCoordinate & pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId & player_id, std::string optional)
{
	return (player_id == PlayerId::P1 ? map.at(pos.at(0), pos.at(1)).p1_win : map.at(pos.at(0), pos.at(1)).p2_win);
}

bool MonteCarloHeuristic::Rule::isLoseable(const CellCoordinate & pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId & player_id, std::string optional)
{
	return (player_id == PlayerId::P1 ? map.at(pos.at(0), pos.at(1)).p2_win : map.at(pos.at(0), pos.at(1)).p1_win);
}

bool MonteCarloHeuristic::Rule::isWinnable3Trap(const CellCoordinate & pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId & player_id, std::string optional)
{
	return (player_id == PlayerId::P1 ? map.at(pos.at(0), pos.at(1)).p1_will_win : map.at(pos.at(0), pos.at(1)).p2_will_win);
}

bool MonteCarloHeuristic::Rule::isLoseable3Trap(const CellCoordinate & pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId & player_id, std::string optional)
{
	return (player_id == PlayerId::P1 ? map.at(pos.at(0), pos.at(1)).p2_will_win : map.at(pos.at(0), pos.at(1)).p1_will_win);
}

// HEURISTIC
bool MonteCarloHeuristic::respectAll(const CellCoordinate & pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId & player_id, const std::vector<std::string> rules)
{
	for (std::size_t i = 0; i < rules.size(); ++i) {
		std::size_t index = rules[i].find(":");
		std::string rule = (index != std::string::npos ? rules[i].substr(0, index) : rules[i]);
		std::string optional = (index != std::string::npos ? rules[i].substr(index + 1) : "");

		if (this->verifMethods.find(rule) == this->verifMethods.end())
			return false;
		if (!this->verifMethods[rule](pos, map, referee, player_id, optional))
			return false;
	}
	return true;
}

int MonteCarloHeuristic::respectOneOf(const CellCoordinate & pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId & player_id, const std::vector<std::string> rules)
{
	for (std::size_t i = 0; i < rules.size(); ++i) {
		std::size_t index = rules[i].find(":");
		std::string rule = (index != std::string::npos ? rules[i].substr(0, index) : rules[i]);
		std::string optional = (index != std::string::npos ? rules[i].substr(index + 1) : "");

		if (this->verifMethods.find(rule) == this->verifMethods.end())
			return false;
		if (this->verifMethods[rule](pos, map, referee, player_id, optional))
			return i;
	}
	return -1;
}

std::vector<CellCoordinate> MonteCarloHeuristic::find(const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId &player_id, std::vector<std::string> rules, std::vector<std::string> restriction)
{
	std::vector<CellCoordinate> result;

	for (int y = 0; y < (int)map.height(); ++y) {
		for (int x = 0; x < (int)map.width(); ++x) {
			if (this->respectAll({ x, y }, map, referee, player_id, restriction))
			{
				if (this->respectOneOf({ x, y }, map, referee, player_id, rules) != -1) {
					result.push_back({ x, y });
				}
			}
		}
	}
	return result;
}

std::vector<CellCoordinate> MonteCarloHeuristic::findAdditionOf(const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId &player_id, std::vector<std::string> rules, std::vector<std::string> restriction)
{
	std::vector<CellCoordinate> result;

	for (int y = 0; y < (int)map.height(); ++y) {
		for (int x = 0; x < (int)map.width(); ++x) {
			if (this->respectAll({ x, y }, map, referee, player_id, restriction))
			{
				if (this->respectAll({ x, y }, map, referee, player_id, rules)) {
					result.push_back({ x, y });
				}
			}
		}
	}
	return result;
}

std::vector<CellCoordinate> MonteCarloHeuristic::findFirstOf(const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId &player_id, std::vector<std::string> rules, std::vector<std::string> restriction)
{
	std::vector<CellCoordinate> result;
	int							current = 0;
	int							max = -1;

	for (int y = 0; y < (int)map.height(); ++y) {
		for (int x = 0; x < (int)map.width(); ++x) {
			if (this->respectAll({ x, y }, map, referee, player_id, restriction))
			{
				if ((current = this->respectOneOf({ x, y }, map, referee, player_id, rules)) != -1) {
					if (current < max || max == -1) {
						max = current;
						result.clear();
						rules.resize(max + 1);
					}
					if (current == max)
						result.push_back({ x, y });
				}
			}
		}
	}
	return result;
}
