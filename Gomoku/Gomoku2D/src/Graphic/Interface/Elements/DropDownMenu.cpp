#include "Graphic\Interface\Elements\DropDownMenu.h"



DropDownMenu::DropDownMenu(float x, float y, ELocation location, ELocation directive, ETask task, std::string parameters, bool activated)
	: GuiElement(EGuiElement::DROP_DOWN_MENU, x, y, 195, 39, activated)
	, menu(new ComplexElement("menu", x, y, 160, 32, true))
	, header(new ComplexElement("header", x, y, 150, 39, true))
	, canChoice(false)
	, location(location)
	, directive(directive)
	, task(task)
	, parameters(parameters)
{
	this->visibilityInterval = 4;
	this->visibility = std::make_pair(0, 0 + this->visibilityInterval);
}

DropDownMenu::DropDownMenu(std::string id, float x, float y, ELocation location, ELocation directive, ETask task, std::string parameters, bool activated)
	: GuiElement(EGuiElement::DROP_DOWN_MENU, id, x, y, 195, 39, activated)
	, menu(new ComplexElement("menu", x, y, 160, 32, true))
	, header(new ComplexElement("header", x, y, 150, 39, true))
	, canChoice(false)
	, location(location)
	, directive(directive)
	, task(task)
	, parameters(parameters)
{
	this->visibilityInterval = 4;
	this->visibility = std::make_pair(0, 0 + this->visibilityInterval);
}

DropDownMenu::~DropDownMenu()
{
}

void	DropDownMenu::init()
{
	this->menu->addItem(new Button(0, 0, 160, 32, location, directive, ETask::NONE, "LOCAL", EImage::BUTTON_DROP_DOWN, EImage::BUTTON_DROP_DOWN_FLASH));
	this->menu->init();
}

void DropDownMenu::draw(sf::RenderWindow & screen)
{
	if (this->activated) {
		this->menu->draw(screen);
		this->header->draw(screen);
		if (this->canChoice) {
			for (ComplexElement * button : this->choices) {
				button->draw(screen);
			}
		}
	}
}

void DropDownMenu::draw(sf::RenderWindow & screen, float x, float y)
{
	if (this->activated) {
		this->menu->draw(screen, x, y);
		this->header->draw(screen, x, y);

		if (this->canChoice) {
			for (ComplexElement * button : this->choices) {
				button->draw(screen, x, y);
			}
		}
	}
}

bool	DropDownMenu::isOnFocus(int x, int y)
{
	this->focused = false;
	if (this->activated) {
		this->focused = this->menu->isOnFocus(x, y);

		if (this->header->isOnFocus(x, y))
			this->focused = true;
		if (this->canChoice) {
			for (ComplexElement * button : this->choices) {
				if (button->isOnFocus(x, y)) {
					this->focused = true;
				}
			}
		}
	}
	return this->focused;
}

Tuple<ELocation, ELocation, GenericTask> DropDownMenu::event(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed) {
		if (this->isFocused()) {
			if (event.key.code == sf::Keyboard::Up) {
				this->upVisibility();
				this->activeAll();
			}
			if (event.key.code == sf::Keyboard::Down) {
				this->downVisibility();
				this->activeAll();
			}
		}
	}
	return TaskFactory::createEmpty();
}

Tuple<ELocation, ELocation, GenericTask> DropDownMenu::isSelected(int x, int y)
{
	if (this->activated) {
		Tuple<ELocation, ELocation, GenericTask> task = this->header->isSelected(x, y);

		if (!TaskFactory::isEmpty(task)) {
			return task;
		}
		if (!TaskFactory::isEmpty(this->menu->isSelected(x, y))) {
			this->canChoice = !this->canChoice;
			if (this->canChoice) {
				this->activeAll();
			}
			else {
				this->deactivateAll();
			}
		}
		else if (this->canChoice) {
			for (ComplexElement * button : this->choices) {
				task = button->isSelected(x, y);
				if (!TaskFactory::isEmpty(task)) {
					this->changeCurrent(button->getId());
					this->canChoice = !this->canChoice;
					this->deactivateAll();
					return task;
				}
			}
		}
	}
	return TaskFactory::createEmpty();
}

GuiElement * DropDownMenu::getFromId(std::string id)
{
	if (this->getId() == id) {
		return this;
	}
	for (GuiElement *item : this->choices) {
		GuiElement *tmp = item->getFromId(id);
		if (tmp != nullptr) {
			return tmp;
		}
	}
	return nullptr;
}

void DropDownMenu::changeCurrent(std::string id)
{
	ComplexElement * button = this->getElementId(id);

	if (button != nullptr) {
		button->setActivated(false);
		GuiElement* tmp = this->menu->getFirstElementByType(EGuiElement::PRINTABLE);
		if (tmp != nullptr) {
			this->menu->deleteItem(tmp);
		}

		this->menu->getFirstElementByType(EGuiElement::BUTTON)->setId(button->getFirstElementByType(EGuiElement::BUTTON)->getId());
		this->menu->addItem(button->getFirstElementByType(EGuiElement::PRINTABLE));
	}
}

void	DropDownMenu::activeAll() {
	GuiElement * ref = this->menu->getFirstElementByType(EGuiElement::BUTTON);

	if (ref != nullptr) {
		for (ComplexElement * button : this->choices) {
			GuiElement * tmp = button->getFirstElementByType(EGuiElement::BUTTON);
			if (tmp != nullptr && tmp->getId() != ref->getId()) {
				button->setActivated(true);
			}
		}
		this->deactivateByVisibility();
		this->updateItemsPosition();
		/*
		std::cout << "AFTER:" << std::endl;
		for (ComplexElement * button : this->choices) {
			std::cout << "-> " << button->getId() << ": {" << button->isActivated() << "}  -  [" << button->getPosX() << ", " << button->getPosY() << "]" << std::endl;
		}
		*/
	}
}

void	DropDownMenu::deactivateByVisibility()
{
	int	pos = 0;
	for (ComplexElement * button : this->choices) {
		if (button->isActivated()) {
			if (!(pos >= this->visibility.first && pos < this->visibility.second))
				button->setActivated(false);
			++pos;
		}
	}
}

void	DropDownMenu::deactivateAll() {
	for (ComplexElement * button : this->choices) {
		button->setActivated(false);
	}
}

// VISIBILITY

void	DropDownMenu::downVisibility() {
	this->visibility.first += 1;
	if (this->visibility.second < (int)this->choices.size())
		this->visibility.second += 1;
	if (this->visibility.second - this->visibility.first != this->visibilityInterval)
		this->visibility.first = this->visibility.second - this->visibilityInterval;
	this->visibility.first = (this->visibility.first < 0 ? 0 : this->visibility.first);
}

void	DropDownMenu::upVisibility() {
	if (this->visibility.first > 0)
		this->visibility.first -= 1;
	this->visibility.second -= 1;
	if (this->visibility.second - this->visibility.first != this->visibilityInterval)
		this->visibility.second = this->visibility.first + this->visibilityInterval;

	this->visibility.second = (this->visibility.second > (int)this->choices.size() ? this->choices.size() : this->visibility.second);
}

// ADD

void DropDownMenu::addToHeader(GuiElement * element, bool decalX, bool decalY)
{
	element->init();
	if (decalX) {
		this->header->setPosX(this->header->getPosX() - element->getWidth());
	}
	if (decalY) {
		this->header->setPosY(this->header->getPosY() - element->getHeight());
	}
	this->header->addItem(element);
}

void	DropDownMenu::addChoice(std::string choice)
{
	ComplexElement *button = new ComplexElement(choice, this->getNewItemPosX(), this->getNewItemPosY(), 160, 26, true);

	std::string value = std::string(choice);
	std::size_t pos = 0;

	if ((pos = value.find("=")) != std::string::npos) {
		value.replace(pos, 1, " - ");
	}
	button->addItem(new Button("button:" + choice, 0, 3, 160, 26, this->location, this->directive, this->task, this->parameters + ":" + choice, EImage::CHOICE_FIELD, EImage::CHOICE_FIELD_FLASH));
	button->addItem(new PrintableElement("field:" + choice, 3, 6, value, 15, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));
	button->init();
	this->choices.push_back(button);
}

void	DropDownMenu::addChoices(std::vector<std::string> choices)
{
	for (std::string choice : choices) {
		this->addChoice(choice);
	}
}

void	DropDownMenu::addChoices(std::string choices[], int size)
{
	for (int i = 0; i < size; ++i) {
		this->addChoice(choices[i]);
	}
}

// POSITION

ComplexElement * DropDownMenu::getElementId(std::string id)
{
	for (ComplexElement *button : this->choices) {
		if (button->getId() == id)
			return button;
	}
	return nullptr;
}

float	DropDownMenu::getNewItemPosX() {
	return this->posX;
}

float	DropDownMenu::getNewItemPosY() {
	int size = this->choices.size();
	return this->posY + this->menu->getHeight() + 1 + (size * 26) - size;
}

float	DropDownMenu::getItemPosX(int pos) {
	return this->posX;
}

float	DropDownMenu::getItemPosY(int pos) {
	return this->posY + this->menu->getHeight() + 1 + (pos * 26) - pos;
}


int		DropDownMenu::getItemPosition(ComplexElement* item) {
	return this->getItemPosition(item->getId());
}

int		DropDownMenu::getItemPosition(std::string id) {
	int	result = 0;

	for (ComplexElement* item : this->choices) {
		if (item->getId() == id)
			return result + 1;
	}
	return -1;
}

int		DropDownMenu::getItemPositionWithActivity(ComplexElement* item) {
	return this->getItemPositionWithActivity(item->getId());
}

int		DropDownMenu::getItemPositionWithActivity(std::string id) {
	int	result = 0;

	for (ComplexElement* item : this->choices) {
		if (item->getId() == id)
			return result;
		if (item->isActivated())
			++result;
	}
	return -1;
}

void	DropDownMenu::updateItemsPosition() {
	for (ComplexElement *item : this->choices) {
		if (item->isActivated()) {
			int pos = this->getItemPositionWithActivity(item);

			item->setPosX(this->getItemPosX(pos));
			item->setPosY(this->getItemPosY(pos));
		}
	}
}