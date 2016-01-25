#pragma once

#include <tuple>
#include <vector>

enum class PlayerId : unsigned char
{
	None = 0,
	P1 = 1,
	P2 = 2
};

PlayerId operator~(const PlayerId& value);

enum class GameActionType : unsigned char
{
	ADD,
	DEL
};

GameActionType operator~(const GameActionType& value);

typedef std::tuple<GameActionType, int, int> GameAction;
typedef std::tuple<PlayerId, std::vector<GameAction>> GameTurn;
typedef std::vector<GameTurn> GameHistory;
