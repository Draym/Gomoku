#pragma once

#include "Graphic\Interface\Elements\GuiElement.h"

class PrintableElement : public GuiElement
{
public:
	PrintableElement(float x, float y, std::string value, int size, sf::Color color, EFont font, bool activated = true);
	PrintableElement(std::string id, float x, float y, std::string value, int size, sf::Color color, EFont font, bool activated = true);
	PrintableElement(float x, float y, float width, float height, EImage imgId, bool activated = true);
	PrintableElement(float x, float y, float width, float height, std::string value, int size, sf::Color color, EFont font, EImage imgId, bool activated = true);
	virtual ~PrintableElement();
public:
	virtual void										init();
	virtual void										draw(sf::RenderWindow &screen);
	virtual void										draw(sf::RenderWindow &screen, float x, float y);
	virtual void										doTask(GenericTask task);
	virtual Tuple<ELocation, ELocation, GenericTask>	event(sf::Event event);
	virtual Tuple<ELocation, ELocation, GenericTask>	isSelected(int x, int y);
protected:
	std::string	txtVal;
	int			txtSize;
	sf::Color	txtColor;
	EFont		txtFont;
	EImage		imgId;
	sf::Sprite	image;
	sf::Text	text;
};

