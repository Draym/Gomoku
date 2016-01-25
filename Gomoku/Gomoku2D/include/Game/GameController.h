#pragma once

#include <map>
#include "Player\HumanPlayer.h"
#include "Player\IAPlayer.h"
#include "map\Grid.hpp"
#include "map\Cell.h"
#include "referee\Referee.hpp"
#include "AI\AI.hpp"
#include "Utils\IAManager.h"
#include "Utils\Tuple.h"
#include "Utils\RuleManager.h"
#include "Observer\Observable.h"

#define MAP_WIDTH	19
#define MAP_HEIGHT	19

enum ETurn { WHITE, BLACK };
enum EStatus { RUNNING, WAITING };

class GameController : public Observable
{
public:
	GameController();
	~GameController();
public:
	void									enter();
	bool									reset();
	bool									resetMap();
	void									update();
	bool									undoAction();
	bool									redoAction();
	bool									newAction(int x, int y);
private:
	void									doAction(APlayer *player, int x, int y);
	void									endOfTheGame();
	void									processTurn(GameTurn &turn, bool mode);
	void									addPawn(int x, int y);
	void									deletePawn(int x, int y);
public:
	void									setWaitingRequest(bool value);
	std::vector<Tuple<ETurn, int, int> >	getPawns() const;
	ETurn									getCurrentTurn() const;
	bool									isFinished() const;
	bool									isCalculating() const;
	bool									currentIsHuman();
private:
	bool									haveToWait;
	bool									whiteTurn;
	bool									finished;
	Grid<Cell>								gameMap;
	Referee<Grid<Cell>>						referee;
	std::map<ETurn, APlayer*>				players;
	std::vector<Tuple<ETurn, int, int> >	pawns;
	GameHistory								history;
	int										current;
	EStatus									state;
};

