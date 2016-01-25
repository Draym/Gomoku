#include "Graphic\Interface\UserInterface.h"

UserInterface::UserInterface()
{
}

UserInterface::~UserInterface()
{
}

void UserInterface::update()
{
	for (std::size_t i = 0; i < this->elements.size(); ++i) {
		this->elements[i]->update();
	}
}

void UserInterface::enter()
{
	this->initOnEnter();
	for (std::size_t i = 0; i < this->elements.size(); ++i) {
		this->elements[i]->enter();
	}
}

void UserInterface::render(sf::RenderWindow &screen)
{
	for (std::size_t i = 0; i < this->elements.size(); ++i) {
		this->elements[i]->draw(screen);
	}
}

void	UserInterface::event(sf::Event event)
{
	for (std::size_t i = 0; i < this->elements.size(); ++i) {
		Tuple<ELocation, ELocation, GenericTask> result = this->elements[i]->event(event);
		if (!TaskFactory::isEmpty(result))
			this->notifyObserver(result);
	}
}

bool		UserInterface::isOnFocus(int x, int y)
{
	bool	result = false;

	for (std::size_t i = 0; i < this->elements.size(); ++i) {
		if (this->elements[i]->isOnFocus(x, y))
			result = true;
	}
	return result;
}

bool	UserInterface::isSelected(int x, int y)
{
	for (std::size_t i = 0; i < this->elements.size(); ++i) {
		Tuple<ELocation, ELocation, GenericTask> result = this->elements[i]->isSelected(x, y);
		if (!TaskFactory::isEmpty(result)) {
			this->notifyObserver(result);
			return true;
		}
	}
	return false;
}

void	UserInterface::initElements()
{
	for (std::size_t i = 0; i < this->elements.size(); ++i) {
		this->elements[i]->init();
	}
}

GuiElement*	UserInterface::getElementById(std::string id) {
	for (std::size_t i = 0; i < this->elements.size(); ++i) {
		GuiElement * tmp = this->elements[i]->getFromId(id);
		if (tmp != nullptr)
			return tmp;
	}
	return nullptr;
}