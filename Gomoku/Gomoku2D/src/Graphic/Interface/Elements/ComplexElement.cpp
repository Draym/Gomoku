#include "Graphic\Interface\Elements\ComplexElement.h"

ComplexElement::ComplexElement(std::string id, float x, float y, float width, float height, bool activated)
	: GuiElement(EGuiElement::COMPLEX, id, x, y, width, height, activated)
{
}


ComplexElement::~ComplexElement()
{
}

void ComplexElement::init()
{
	for (std::size_t i = 0; i < this->items.size(); ++i)
		this->items[i]->init();
}

void ComplexElement::update()
{
	for (std::size_t i = 0; i < this->items.size(); ++i)
		this->items[i]->update();
}

void ComplexElement::enter() {
}

void ComplexElement::doTask(GenericTask task)
{
	if (task.getTask() == ETask::ADD_TITLE && task.hasParameters()) {
		std::vector<std::string>	param = task.getParameters();
		if (param.size() > 2) {
			GuiElement *elem = this->getElementById(param[0]);

			if (elem != nullptr) {
				GenericTask task(ETask::ADD_TITLE);

				for (std::size_t i = 1; i < param.size(); ++i)
					task.addParameter(param[i]);
				elem->doTask(task);
			}
		}
	}
}

void ComplexElement::draw(sf::RenderWindow & screen)
{
	if (this->activated) {
		for (std::size_t i = 0; i < this->items.size(); ++i)
			this->items[i]->draw(screen, this->posX, this->posY);
	}
}

void ComplexElement::draw(sf::RenderWindow & screen, float x, float y)
{
	if (this->activated) {
		for (std::size_t i = 0; i < this->items.size(); ++i)
			this->items[i]->draw(screen, this->posX + x, this->posY + y);
	}
}

bool ComplexElement::isOnFocus(int x, int y)
{
	this->focused = false;
	if (this->activated) {
		for (std::size_t i = 0; i < this->items.size(); ++i)
		{
			if (this->items[i]->isOnFocus(x - (int)this->posX, y - (int)this->posY)) {
				this->focused = true;
			}
		}
	}
	return this->focused;
}

Tuple<ELocation, ELocation, GenericTask> ComplexElement::event(sf::Event event)
{
	if (this->activated) {
		for (std::size_t i = 0; i < this->items.size(); ++i)
		{
			Tuple<ELocation, ELocation, GenericTask> result = this->items[i]->event(event);
			if (result.first != ELocation::NONE)
				return result;
		}
	}
	return TaskFactory::createEmpty();
}

Tuple<ELocation, ELocation, GenericTask> ComplexElement::isSelected(int x, int y)
{
	if (this->activated) {
		for (std::size_t i = 0; i < this->items.size(); ++i)
		{
			Tuple<ELocation, ELocation, GenericTask> result = this->items[i]->isSelected(x - (int)this->posX, y - (int)this->posY);
			if (!TaskFactory::isEmpty(result))
				return result;
		}
	}
	return TaskFactory::createEmpty();
}

GuiElement * ComplexElement::getFromId(std::string id)
{
	if (this->getId() == id) {
		return this;
	}
	for (GuiElement *item : this->items) {
		GuiElement *tmp = item->getFromId(id);
		if (tmp != nullptr) {
			return tmp;
		}
	}
	return nullptr;
}

void ComplexElement::addItem(GuiElement * item)
{
	if (item != nullptr) {
		this->items.push_back(item);
	}
}

void ComplexElement::addItems(std::vector<GuiElement*> items)
{
	for (GuiElement * item : items) {
		this->addItem(item);
	}
}

void ComplexElement::deleteItem(GuiElement * item)
{
	this->deleteItem(item->getId());
}

void ComplexElement::deleteItem(std::string id)
{
	int pos = 0;

	if ((pos = this->getElementPositionById(id)) != -1) {
		this->items.erase(this->items.begin() + pos);
	}
}

void ComplexElement::deleteItems()
{
	this->items.clear();
}

std::vector<GuiElement*> ComplexElement::getItems()
{
	return this->items;
}
GuiElement*	ComplexElement::getElementById(std::string id) {
	for (std::size_t i = 0; i < this->items.size(); ++i) {
		if (this->items[i]->getId() == id)
			return this->items[i];
	}
	return nullptr;
}

GuiElement*	ComplexElement::getFirstElementByType(EGuiElement type) {
	for (std::size_t i = 0; i < this->items.size(); ++i) {
		if (this->items[i]->getType() == type)
			return this->items[i];
	}
	return nullptr;
}

int	ComplexElement::getElementPositionById(std::string id) {
	for (std::size_t i = 0; i < this->items.size(); ++i) {
		if (this->items[i]->getId() == id)
			return i;
	}
	return -1;
}
