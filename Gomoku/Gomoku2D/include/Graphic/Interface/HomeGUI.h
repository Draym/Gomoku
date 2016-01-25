#pragma once

#include "UserInterface.h"

class HomeGUI : public UserInterface
{
public:
	HomeGUI();
	~HomeGUI();
public:
	virtual void	init();
	virtual void	initOnEnter();
};

