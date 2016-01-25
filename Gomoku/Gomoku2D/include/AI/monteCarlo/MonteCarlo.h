#pragma once

#include "MonteCarloHeuristic.h"

template<typename T1, typename T2, typename T3>
class myTuple
{
public:
	myTuple(T1 v1, T2 v2, T3 v3)
	{
		this->first = v1;
		this->second = v2;
		this->third = v3;
	}
	void	modify(T1 v1, T2 v2, T3 v3)
	{
		this->first = v1;
		this->second = v2;
		this->third = v3;
	}
public:
	T1	first;
	T2	second;
	T3	third;
};

CellCoordinate monteCarloEasy(Referee<Grid<Cell>> referee, Grid<Cell> map, PlayerId playerId);
CellCoordinate monteCarloMedium(Referee<Grid<Cell>> referee, Grid<Cell> map, PlayerId playerId);
CellCoordinate monteCarloHard(Referee<Grid<Cell>> referee, Grid<Cell> map, PlayerId playerId);
