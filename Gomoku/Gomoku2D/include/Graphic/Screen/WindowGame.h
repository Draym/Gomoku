#pragma once

#include "AWindow.h"
#include "Graphic\Interface\GameGUI.h"
#include "Game\GameController.h"

enum EState { SET = 0, UNSET, LAST};

class WindowGame : public AWindow
{
public:
	WindowGame();
	~WindowGame();
public:
	virtual void	init();
	virtual void	enter(sf::RenderWindow &screen);
	virtual bool	canLeave();
	virtual void	exit();
	virtual void	update();
	virtual void	render(sf::RenderWindow &screen);
	virtual void	drawPawns(sf::RenderWindow &screen);
	virtual void	drawCurrentPawn(sf::RenderWindow &screen);
	virtual void	event(sf::Event event);
public:
	virtual void	update(Tuple<ELocation, ELocation, GenericTask> message);
private:
	float			getXInTheBoard(int x);
	float			getYInTheBoard(int y);
private:
	GameController						gameController;
	std::map<EState, sf::Sprite>		pState[2];
	std::map<ETurn, sf::Sprite>			turn;
	std::pair<int, int>					pCurrent;
};