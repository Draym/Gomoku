#include "Graphic\Interface\Elements\Button.h"


Button::Button(float x, float y, float width, float height, ELocation location, ELocation directive, ETask task, std::string parameters, bool activated)
	: GuiElement(EGuiElement::BUTTON, x, y, width, height, activated)
	, location(location)
	, directive(directive)
	, task(task)
	, parameters(parameters)
	, imgType(EImage::NONE)
	, focusedImgType(EImage::NONE)
{
}

Button::Button(float x, float y, float width, float height, ELocation location, ELocation directive, ETask task, std::string parameters, EImage type, EImage focusedType, bool activated)
	: GuiElement(EGuiElement::BUTTON, x, y, width, height, activated)
	, location(location)
	, directive(directive)
	, task(task)
	, parameters(parameters)
	, imgType(type)
	, focusedImgType(focusedType)
{
}

Button::Button(std::string id, float x, float y, float width, float height, ELocation location, ELocation directive, ETask task, std::string parameters, bool activated)
	: GuiElement(EGuiElement::BUTTON, id, x, y, width, height, activated)
	, location(location)
	, directive(directive)
	, task(task)
	, parameters(parameters)
	, imgType(EImage::NONE)
	, focusedImgType(EImage::NONE)
{
}

Button::Button(std::string id, float x, float y, float width, float height, ELocation location, ELocation directive, ETask task, std::string parameters, EImage type, EImage focusedType, bool activated)
	: GuiElement(EGuiElement::BUTTON, id, x, y, width, height, activated)
	, location(location)
	, directive(directive)
	, task(task)
	, parameters(parameters)
	, imgType(type)
	, focusedImgType(focusedType)
{
}

Button::~Button()
{
}

void	Button::init()
{
	if (this->imgType != EImage::NONE) {
		this->image.setTexture(ResourceManager::getImage(this->imgType));
		this->image.setPosition(this->posX, this->posY);
	}
	if (this->focusedImgType != EImage::NONE) {
		this->focusedImage.setTexture(ResourceManager::getImage(this->focusedImgType));
		this->focusedImage.setPosition(this->posX, this->posY);
	}
}

void Button::draw(sf::RenderWindow & screen)
{
	if (this->activated) {
		if (this->focused) {
			this->focusedImage.setPosition(this->posX, this->posY);
			screen.draw(this->focusedImage);
		}
		else {
			this->image.setPosition(this->posX, this->posY);
			screen.draw(this->image);
		}
	}
}

void Button::draw(sf::RenderWindow & screen, float x, float y)
{
	if (this->activated) {
		if (this->focused) {
			this->focusedImage.setPosition(this->posX + x, this->posY + y);
			screen.draw(this->focusedImage);
		}
		else {
			this->image.setPosition(this->posX + x, this->posY + y);
			screen.draw(this->image);
		}
	}
}

bool	Button::isOnFocus(int x, int y)
{
	this->focused = false;
	if (this->activated) {
		if (x < this->maxPosX() && x > this->getPosX() && y < this->maxPosY() && y > this->getPosY()) {
			this->focused = true;
		}
	}
	return this->focused;
}

Tuple<ELocation, ELocation, GenericTask> Button::event(sf::Event event)
{
	return TaskFactory::createEmpty();
}

Tuple<ELocation, ELocation, GenericTask> Button::isSelected(int x, int y)
{
	if (this->activated) {
		if (x < this->maxPosX() && x > this->getPosX() && y < this->maxPosY() && y > this->getPosY()) {
			GenericTask task(this->task);
			task.addParameter(this->parameters);
			return TaskFactory::createTask(this->location, this->directive, task);
		}
	}
	return TaskFactory::createEmpty();
}
