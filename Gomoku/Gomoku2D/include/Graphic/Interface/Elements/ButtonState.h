#pragma once
#include "Graphic\Interface\Elements\Button.h"

class ButtonState : public Button
{
public:
	ButtonState(float x, float y, float width, float height, ELocation location, ELocation directive, ETask task, std::string parameters, EImage first, EImage second, bool activated = true);
	ButtonState(std::string id, float x, float y, float width, float height, ELocation location, ELocation directive, ETask task, std::string parameters, EImage first, EImage second, bool activated = true);
	virtual ~ButtonState();
public:
	virtual void										init();
	virtual void										draw(sf::RenderWindow &screen);
	virtual void										draw(sf::RenderWindow &screen, float x, float y);
	virtual Tuple<ELocation, ELocation, GenericTask>	isSelected(int x, int y);
protected:
	std::pair<EImage, EImage>	images;
	sf::Sprite					first;
	sf::Sprite					second;
};

