#pragma once

#include "Graphic\Sfml.h"
#include <functional>
#include <vector>
#include "Utils\Exception.h"
#include "Utils\IAManager.h"
#include "Utils\RuleManager.h"
#include "Observer\Observable.h"
#include "Elements\ButtonState.h"
#include "Elements\PrintableElement.h"
#include "Elements\ComplexElement.h"
#include "Elements\DropDownMenu.h"

class UserInterface : public Observable
{
protected:
	UserInterface();
public:
	virtual ~UserInterface();
public:
	virtual void				init() = 0;
	virtual void				initOnEnter() = 0;
	virtual void				update();
	virtual void				enter();
	virtual void				render(sf::RenderWindow &screen);
	virtual void				event(sf::Event event);
	virtual bool				isOnFocus(int x, int y);
	virtual bool				isSelected(int x, int y);
	virtual GuiElement*			getElementById(std::string id);
protected:
	virtual void				initElements();
protected:
	ELocation					local;
	std::vector<GuiElement*>	elements;
};

