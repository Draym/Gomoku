#pragma once

#include "Graphic\Sfml.h"
#include "Utils\ConvertTools.h"
#include "Utils\Task\TaskFactory.h"
#include "Graphic\ResourceManager.h"

enum EGuiElement { BUTTON, PRINTABLE, COMPLEX, DROP_DOWN_MENU };

class GuiElement
{
protected:
	GuiElement(EGuiElement type, float x, float y, float width, float height, bool activated = true);
	GuiElement(EGuiElement type, std::string id, float x, float y, float width, float height, bool activated = true);
public:
	virtual ~GuiElement();
public:
	virtual void										init();
	virtual void										update();
	virtual void										enter();
	virtual void										doTask(GenericTask task);
	virtual void										draw(sf::RenderWindow &screen);
	virtual void										draw(sf::RenderWindow &screen, float x, float y);
	virtual bool										isOnFocus(int x, int y);
	virtual Tuple<ELocation, ELocation, GenericTask>	event(sf::Event event) = 0;
	virtual Tuple<ELocation, ELocation, GenericTask>	isSelected(int x, int y) = 0;
public:
	virtual	bool		isActivated() const;
	virtual	bool		isFocused() const;
	virtual float		maxPosX() const;
	virtual float		maxPosY() const;
	virtual float		getWidth() const;
	virtual float		getHeight() const;
	virtual float		getPosX() const;
	virtual float		getPosY() const;
	virtual std::string	getId() const;
	virtual EGuiElement getType() const;
	virtual GuiElement*	getFromId(std::string id);
public:
	virtual void		setActivated(bool value);
	virtual void		setPosX(float value);
	virtual void		setPosY(float value);
	virtual void		setId(std::string value);
protected:
	std::string	id;
	bool		focused;
	bool		activated;
	EGuiElement	type;
	float		posX;
	float		posY;
	float		width;
	float		height;
};