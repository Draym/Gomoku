#pragma once

#include "Graphic\Interface\Elements\GuiElement.h"

class ComplexElement : public GuiElement
{
public:
	ComplexElement(std::string id, float x, float y, float width, float height, bool activated = true);
	~ComplexElement();
public:
	virtual void										init();
	virtual void										update();
	virtual void										enter();
	virtual void										doTask(GenericTask task);
	virtual void										draw(sf::RenderWindow &screen);
	virtual void										draw(sf::RenderWindow &screen, float x, float y);
	virtual bool										isOnFocus(int x, int y);
	virtual Tuple<ELocation, ELocation, GenericTask>	event(sf::Event event);
	virtual Tuple<ELocation, ELocation, GenericTask>	isSelected(int x, int y);
	virtual GuiElement*									getFromId(std::string id);
public:
	void												addItem(GuiElement *item);
	void												addItems(std::vector<GuiElement*> items);
	void												deleteItem(GuiElement *item);
	void												deleteItem(std::string id);
	void												deleteItems();
public:
	std::vector<GuiElement*>	getItems();
	GuiElement*					getElementById(std::string id);
	GuiElement*					getFirstElementByType(EGuiElement type);
	int							getElementPositionById(std::string id);
private:
	std::vector<GuiElement*>	items;
};

