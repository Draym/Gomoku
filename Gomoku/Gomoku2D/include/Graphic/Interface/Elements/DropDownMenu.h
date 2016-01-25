#pragma once

#include "Graphic\Interface\Elements\ComplexElement.h"
#include "Graphic\Interface\Elements\Button.h"
#include "Graphic\Interface\Elements\PrintableElement.h"

class DropDownMenu : public GuiElement
{
public:
	DropDownMenu(float x, float y, ELocation location, ELocation directive, ETask task, std::string parameters, bool activated = true);
	DropDownMenu(std::string id, float x, float y, ELocation location, ELocation directive, ETask task, std::string parameters, bool activated = true);
	~DropDownMenu();
public:
	void	addToHeader(GuiElement *element, bool decalX, bool decalY);
	void	addChoice(std::string choice);
	void	addChoices(std::vector<std::string> choices);
	void	addChoices(std::string choices[], int size);
	void	changeCurrent(std::string id);
private:
	void	activeAll();
	void	deactivateAll();
	void	deactivateByVisibility();
private:
	void	downVisibility();
	void	upVisibility();
private:
	ComplexElement*	getElementId(std::string id);
	float			getNewItemPosX();
	float			getNewItemPosY();
	float			getItemPosX(int pos);
	float			getItemPosY(int pos);
	int				getItemPosition(ComplexElement* item);
	int				getItemPosition(std::string id);
	int				getItemPositionWithActivity(ComplexElement* item);
	int				getItemPositionWithActivity(std::string id);
	void			updateItemsPosition();
public:
	virtual void										init();
	virtual void										draw(sf::RenderWindow &screen);
	virtual void										draw(sf::RenderWindow &screen, float x, float y);
	virtual bool										isOnFocus(int x, int y);
	virtual Tuple<ELocation, ELocation, GenericTask>	event(sf::Event event);
	virtual Tuple<ELocation, ELocation, GenericTask>	isSelected(int x, int y);
	virtual GuiElement*									getFromId(std::string id);
protected:
	std::vector<ComplexElement*>	choices;
	ComplexElement*					menu;
	ComplexElement*					header;
	bool							canChoice;
	ELocation						location;
	ELocation						directive;
	ETask							task;
	std::string						parameters;
	std::pair<int, int>				visibility;
	int								visibilityInterval;
};

