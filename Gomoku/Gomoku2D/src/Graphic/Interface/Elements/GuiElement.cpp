#include "Graphic\Interface\Elements\GuiElement.h"

GuiElement::GuiElement(EGuiElement type, float x, float y, float width, float height, bool activated)
	: id("unknown")
	, activated(activated)
	, focused(false)
	, type(type)
	, posX(x)
	, posY(y)
	, width(width)
	, height(height)
{
}

GuiElement::GuiElement(EGuiElement type, std::string id, float x, float y, float width, float height, bool activated)
	: id(id)
	, activated(activated)
	, focused(false)
	, type(type)
	, posX(x)
	, posY(y)
	, width(width)
	, height(height)
{
}

GuiElement::~GuiElement()
{
}

void GuiElement::init()
{
}

void GuiElement::update()
{
}

void GuiElement::enter()
{
}

void GuiElement::doTask(GenericTask task)
{
	if (task.getTask() == ETask::SWITCH_ACTIVATED) {
		this->activated = !this->activated;
	}
}

void GuiElement::draw(sf::RenderWindow & screen)
{
}

void GuiElement::draw(sf::RenderWindow & screen, float x, float y)
{
}

bool GuiElement::isOnFocus(int x, int y)
{
	this->focused = false;
	if (this->activated) {
		if (x < this->maxPosX() && x > this->getPosX() && y < this->maxPosY() && y > this->getPosY()) {
			this->focused = true;
		}
	}
	return this->focused;
}

bool GuiElement::isActivated() const
{
	return this->activated;
}

bool GuiElement::isFocused() const
{
	return this->focused;
}

float GuiElement::maxPosX() const
{
	return this->posX + this->width;
}

float GuiElement::maxPosY() const
{
	return this->posY + this->height;
}

float GuiElement::getWidth() const
{
	return this->width;
}

float GuiElement::getHeight() const
{
	return this->height;
}

float GuiElement::getPosX() const
{
	return this->posX;
}

float GuiElement::getPosY() const
{
	return this->posY;
}

std::string GuiElement::getId() const
{
	return this->id;
}

EGuiElement	GuiElement::getType() const
{
	return this->type;
}

GuiElement * GuiElement::getFromId(std::string id)
{
	if (this->getId() == id) {
		return this;
	}
	return nullptr;
}

void GuiElement::setActivated(bool value)
{
	this->activated = value;
}

void GuiElement::setPosX(float value)
{
	this->posX = value;
}

void GuiElement::setPosY(float value)
{
	this->posY = value;
}

void GuiElement::setId(std::string value)
{
	this->id = value;
}
