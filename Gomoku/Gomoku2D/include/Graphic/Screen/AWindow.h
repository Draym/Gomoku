#pragma once

#include "Graphic\Interface\UserInterface.h"
#include "Graphic\Screen\WindowConfig.h"
#include "Utils\RuleManager.h"
#include "Observer\Observable.h"
#include "Observer\Observer.h"

class AWindow : public Observable, public Observer
{
protected:
	AWindow(UserInterface *gui);
public:
	virtual ~AWindow();
public:
	virtual void			init() = 0;
	virtual void			enter(sf::RenderWindow &screen) = 0;
	virtual bool			canLeave() = 0;
	virtual void			exit() = 0;
	virtual void			reset();
	virtual void			update();
	virtual void			render(sf::RenderWindow &screen);
	virtual void			event(sf::Event event);
	virtual UserInterface	*getUserInterface();
public:
	virtual void	update(Tuple<ELocation, ELocation, GenericTask> message) = 0;
protected:
	ELocation		local;
	UserInterface	*gui;
	sf::Sprite		background;
};

enum class EWindows
{
	NONE = 0,
	WINDOW_HOME,
	WINDOW_OPTION,
	WINDOW_SELECTPLAY,
	WINDOW_GAME
};