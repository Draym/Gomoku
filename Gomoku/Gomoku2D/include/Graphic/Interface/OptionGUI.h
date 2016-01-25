#pragma once

#include "Graphic\Interface\UserInterface.h"

class OptionGUI : public UserInterface
{
public:
	OptionGUI();
	~OptionGUI();

public:
	virtual void	init();
	virtual void	initOnEnter();
};

