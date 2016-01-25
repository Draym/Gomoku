#include "Graphic\Screen\WindowHome.h"


WindowHome::WindowHome()
	: AWindow(new HomeGUI())
{
	this->local = ELocation::HOME;
	this->gui->addObserver(this);
}


WindowHome::~WindowHome()
{
}

void WindowHome::init()
{
	this->background.setTexture(ResourceManager::getImage(EImage::HOME_BACKGROUND));
	this->gui->init();
}

void WindowHome::enter(sf::RenderWindow &screen)
{
	screen.setSize(sf::Vector2u(WindowConfig::getWindowHomeWidth(), WindowConfig::getWindowHomeHeight()));
	screen.setView(sf::View(sf::FloatRect(0, 0, (float)WindowConfig::getWindowHomeWidth(), (float)WindowConfig::getWindowHomeHeight())));
	screen.setPosition(sf::Vector2i(((WindowConfig::getWindowWidth() - WindowConfig::getWindowHomeWidth()) / 2), (WindowConfig::getWindowHeight() - WindowConfig::getWindowHomeHeight()) / 2));
	this->gui->enter();
}

bool WindowHome::canLeave()
{
	return true;
}

void WindowHome::exit()
{
}

void WindowHome::update(Tuple<ELocation, ELocation, GenericTask> message)
{
	if (message.first != this->local) {
		if (message.second == this->local) {

		}
		else {
			this->notifyObserver(message);
		}
	}
}
