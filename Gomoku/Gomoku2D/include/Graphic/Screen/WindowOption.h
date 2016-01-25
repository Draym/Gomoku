#pragma once

#include "Graphic\Screen\AWindow.h"
#include "Graphic\Interface\OptionGUI.h"

class WindowOption : public AWindow
{
public:
	WindowOption();
	~WindowOption();
public:
	virtual void	init();
	virtual void	enter(sf::RenderWindow &screen);
	virtual bool	canLeave();
	virtual void	exit();
public:
	virtual void	update(Tuple<ELocation, ELocation, GenericTask> message);
};