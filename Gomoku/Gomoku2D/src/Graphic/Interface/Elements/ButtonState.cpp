#include "Graphic\Interface\Elements\ButtonState.h"

ButtonState::ButtonState(float x, float y, float width, float height, ELocation location, ELocation directive, ETask task, std::string parameters, EImage first, EImage second, bool activated)
	: Button(x, y, width, height, location, directive, task, parameters, activated)
{
	this->images = std::make_pair(first, second);
}

ButtonState::ButtonState(std::string id, float x, float y, float width, float height, ELocation location, ELocation directive, ETask task, std::string parameters, EImage first, EImage second, bool activated)
	: Button(id, x, y, width, height, location, directive, task, parameters, activated)
{
	this->images = std::make_pair(first, second);
}

ButtonState::~ButtonState()
{
}

void ButtonState::init()
{
	this->first.setTexture(ResourceManager::getImage(this->images.first));
	this->first.setPosition(this->posX, this->posY);
	this->second.setTexture(ResourceManager::getImage(this->images.second));
	this->second.setPosition(this->posX, this->posY);
}

void ButtonState::draw(sf::RenderWindow & screen)
{
	if (this->activated) {
		this->first.setPosition(this->posX, this->posY);
		screen.draw(this->first);
	}
	else {
		this->second.setPosition(this->posX, this->posY);
		screen.draw(this->second);
	}
}

void ButtonState::draw(sf::RenderWindow & screen, float x, float y)
{
	if (this->activated) {
		this->first.setPosition(this->posX + x, this->posY + y);
		screen.draw(this->first);
	}
	else {
		this->second.setPosition(this->posX + x, this->posY + y);
		screen.draw(this->second);
	}
}

Tuple<ELocation, ELocation, GenericTask> ButtonState::isSelected(int x, int y)
{
	if (x < this->maxPosX() && x > this->getPosX() && y < this->maxPosY() && y > this->getPosY()) {
		GenericTask task(this->task);
		task.addParameter(this->parameters);
		this->activated = !this->activated;
		return TaskFactory::createTask(this->location, this->directive, task);
	}
	return TaskFactory::createEmpty();
}
