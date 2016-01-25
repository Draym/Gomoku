#pragma once

#include "UserInterface.h"

class GameGUI : public UserInterface
{
public:
	GameGUI();
	~GameGUI();
public:
	virtual void	init();
	virtual void	initOnEnter();
};

