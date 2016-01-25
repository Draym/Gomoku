#include "Graphic\Screen\WindowOption.h"

WindowOption::WindowOption() : AWindow(new OptionGUI())
{
	this->local = ELocation::OPTION;
	this->gui->addObserver(this);
}


WindowOption::~WindowOption()
{
}

void WindowOption::init()
{
	this->background.setTexture(ResourceManager::getImage(EImage::EMPTY_BACKGROUND));
	this->gui->init();
}

void WindowOption::enter(sf::RenderWindow & screen)
{
	screen.setSize(sf::Vector2u(WindowConfig::getWindowHomeWidth(), WindowConfig::getWindowHomeHeight()));
	screen.setView(sf::View(sf::FloatRect(0, 0, (float)WindowConfig::getWindowHomeWidth(), (float)WindowConfig::getWindowHomeHeight())));
	screen.setPosition(sf::Vector2i(((WindowConfig::getWindowWidth() - WindowConfig::getWindowHomeWidth()) / 2), (WindowConfig::getWindowHeight() - WindowConfig::getWindowHomeHeight()) / 2));
	this->gui->enter();
}

bool WindowOption::canLeave()
{
	return true;
}

void WindowOption::exit()
{
}

void WindowOption::update(Tuple<ELocation, ELocation, GenericTask> message)
{
	if (message.first != this->local) {
		if (message.second == this->local) {
			if (message.third.getTask() == ETask::ACTIVE_RULE && message.third.hasParameters()) {
				RuleManager::reverse(message.third.getParameters()[0]);
			}
		}
		else {
			this->notifyObserver(message);
		}
	}
}
