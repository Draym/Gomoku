#pragma once

#include <array>
#include "..\referee\History.h"

typedef struct Cell
{
	PlayerId player_id : 2;
	bool breakable : 1;
	bool p1_win : 1;
	bool p2_win : 1;
	/* Checked if px_win is false */
	bool p1_will_win : 1;
	bool p2_will_win : 1;
	unsigned char data : 1;
} Cell;

typedef std::array<int, 2> CellCoordinate;