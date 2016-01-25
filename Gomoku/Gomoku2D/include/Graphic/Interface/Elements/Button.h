
#pragma once

#include "Graphic\Interface\Elements\GuiElement.h"

class Button : public GuiElement
{
public:
	Button(float x, float y, float width, float height, ELocation location, ELocation directive, ETask task, std::string target, bool activated = true);
	Button(float x, float y, float width, float height, ELocation location, ELocation directive, ETask task, std::string target, EImage type, EImage focusedType, bool activated = true);

	Button(std::string id, float x, float y, float width, float height, ELocation location, ELocation directive, ETask task, std::string parameters, bool activated = true);
	Button(std::string id, float x, float y, float width, float height, ELocation location, ELocation directive, ETask task, std::string parameters, EImage type, EImage focusedType, bool activated = true);
	virtual ~Button();
public:
	virtual void										init();
	virtual void										draw(sf::RenderWindow &screen);
	virtual void										draw(sf::RenderWindow &screen, float x, float y);
	virtual bool										isOnFocus(int x, int y);
	virtual Tuple<ELocation, ELocation, GenericTask>	event(sf::Event event);
	virtual Tuple<ELocation, ELocation, GenericTask>	isSelected(int x, int y);
protected:
	EImage		imgType;
	EImage		focusedImgType;
	ELocation	location;
	ELocation	directive;
	ETask		task;
	std::string	parameters;
	sf::Sprite	image;
	sf::Sprite	focusedImage;
};


