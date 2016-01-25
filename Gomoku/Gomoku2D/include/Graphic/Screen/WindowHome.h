#pragma once

#include "AWindow.h"
#include "Graphic\Interface\HomeGUI.h"

class WindowHome : public AWindow
{
public:
	WindowHome();
	~WindowHome();
public:
	virtual void	init();
	virtual void	enter(sf::RenderWindow &screen);
	virtual bool	canLeave();
	virtual void	exit();
public:
	virtual void	update(Tuple<ELocation, ELocation, GenericTask> message);
};
