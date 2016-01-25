#pragma once

#include "Graphic\Screen\AWindow.h"
#include "Graphic\Interface\SelectPlayGUI.h"

class WindowSelectPlay : public AWindow
{
public:
	WindowSelectPlay();
	~WindowSelectPlay();
public:
	virtual void	init();
	virtual void	enter(sf::RenderWindow &screen);
	virtual bool	canLeave();
	virtual void	exit();
public:
	virtual void	update(Tuple<ELocation, ELocation, GenericTask> message);
};

