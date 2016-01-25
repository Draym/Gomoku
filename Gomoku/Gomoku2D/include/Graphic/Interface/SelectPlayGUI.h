#pragma once

#include "Graphic\Interface\UserInterface.h"

class SelectPlayGUI : public UserInterface
{
public:
	SelectPlayGUI();
	~SelectPlayGUI();

public:
	virtual void	init();
	virtual void	initOnEnter();
};