#pragma once

#include <sstream>
#include <string>
#include <math.h>
#include "map\Cell.h"
#include "map\Grid.hpp"
#include "referee\Referee.hpp"

class MonteCarloHeuristic
{
protected:
	MonteCarloHeuristic();
	~MonteCarloHeuristic();
public:
	using Method = std::function<bool(const CellCoordinate&, const Grid<Cell>&, const Referee<Grid<Cell>>&, const PlayerId &player_id, std::string)>;
	class Tools
	{
	public:
		static int		toInt(std::string value);
		static float	coordDistance(float x1, float y1, float x2, float y2);
	public:
		static int		countItem(const Grid<Cell>& map, const PlayerId &id);
		static bool		hasBreakableSpecificItemInRange(const CellCoordinate &pos, const Grid<Cell>& map, PlayerId id);
		static int		getTheClosestItem(const CellCoordinate &pos, const Grid<Cell>& map, const int &maxLevel);
		static int		getTheClosestSpecifiedItem(const CellCoordinate &pos, const Grid<Cell>& map, const int &maxLevel, PlayerId id);
	};
	class RuleName {
	public:
		static std::string Empty() { return "isEmpty"; }
		static std::string Valid() { return "isValid"; }
		static std::string InRange() { return "isInRange"; }
		static std::string InRangeEnemy() { return "isInRangeEnemy"; }
		static std::string InRangeAlly() { return "isInRangeAlly"; }
		static std::string Winnable() { return "isWinnable"; }
		static std::string Loseable() { return "isLoseable"; }
		static std::string BreakIt() { return "isCanBreak"; }
		static std::string DefendIt() { return "isCanDefend"; }
		static std::string Winnable3Trap() { return "isWinnable3Trap"; }
		static std::string Loseable3Trap() { return "isLoseable3Trap"; }
	};
	class Rule
	{
	public:
		static bool		isEmpty(const CellCoordinate &pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId &player_id, std::string optional = "");
		static bool		isValid(const CellCoordinate &pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId &player_id, std::string optional = "");
		static bool		isInRange(const CellCoordinate &pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId &player_id, std::string optional = "");
		static bool		isInRangeEnemy(const CellCoordinate &pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId &player_id, std::string optional = "");
		static bool		isInRangeAlly(const CellCoordinate &pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId &player_id, std::string optional = "");
		static bool		isCanBreak(const CellCoordinate &pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId &player_id, std::string optional = "");
		static bool		isCanDefend(const CellCoordinate &pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId &player_id, std::string optional = "");
		static bool		isWinnable(const CellCoordinate &pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId &player_id, std::string optional = "");
		static bool		isLoseable(const CellCoordinate &pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId &player_id, std::string optional = "");
		static bool		isWinnable3Trap(const CellCoordinate &pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId &player_id, std::string optional = "");
		static bool		isLoseable3Trap(const CellCoordinate &pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId &player_id, std::string optional = "");
	};
	bool		respectAll(const CellCoordinate &pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId &player_id, const std::vector<std::string> rules);
	int			respectOneOf(const CellCoordinate &pos, const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId &player_id, const std::vector<std::string> rules);

	std::vector<CellCoordinate>	find(const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId &player_id, std::vector<std::string> rules, std::vector<std::string> restriction = {});
	std::vector<CellCoordinate>	findAdditionOf(const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId &player_id, std::vector<std::string> rules, std::vector<std::string> restriction = {});
	std::vector<CellCoordinate>	findFirstOf(const Grid<Cell>& map, const Referee<Grid<Cell>>& referee, const PlayerId &player_id, std::vector<std::string> rules, std::vector<std::string> restriction = {});

private:
	std::map<std::string, Method> verifMethods;

	// SINGLETON
public:
	static MonteCarloHeuristic& get();
private:
	MonteCarloHeuristic& operator= (const MonteCarloHeuristic&) {}
	MonteCarloHeuristic(const MonteCarloHeuristic&) {}
	static MonteCarloHeuristic instance;
};

