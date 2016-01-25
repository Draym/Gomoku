
#include "Graphic\Screen\WindowSelectPlay.h"

WindowSelectPlay::WindowSelectPlay() : AWindow(new SelectPlayGUI())
{
	this->local = ELocation::SELECTPLAY;
	this->gui->addObserver(this);
}


WindowSelectPlay::~WindowSelectPlay()
{
}

void WindowSelectPlay::init()
{
	this->background.setTexture(ResourceManager::getImage(EImage::EMPTY_BACKGROUND));
	this->gui->init();
}

void WindowSelectPlay::enter(sf::RenderWindow & screen)
{
	screen.setSize(sf::Vector2u(WindowConfig::getWindowHomeWidth(), WindowConfig::getWindowHomeHeight()));
	screen.setView(sf::View(sf::FloatRect(0, 0, (float)WindowConfig::getWindowHomeWidth(), (float)WindowConfig::getWindowHomeHeight())));
	screen.setPosition(sf::Vector2i(((WindowConfig::getWindowWidth() - WindowConfig::getWindowHomeWidth()) / 2), (WindowConfig::getWindowHeight() - WindowConfig::getWindowHomeHeight()) / 2));
	this->gui->enter();
}

bool WindowSelectPlay::canLeave()
{
	return true;
}

void WindowSelectPlay::exit()
{
}

void WindowSelectPlay::update(Tuple<ELocation, ELocation, GenericTask> message)
{
	if (message.first != this->local) {
		if (message.second == this->local) {
			if (message.third.getTask() == ETask::CHANGE_PLAYER && message.third.hasParameters()) {
				std::vector<std::string>	param = message.third.getParameters();

				if (param.size() > 1) {
					bool	newVal = ConvertTools::convertToBool(param[1]);
					if (param[0] == "P1") {
						RuleManager::p1 = newVal;
					}
					else if (param[0] == "P2") {
						RuleManager::p2 = newVal;
					}
					
					if (param.size() % 2 == 0) {
						for (std::size_t i = 2; i < param.size(); i += 2) {
							GuiElement *elem = this->gui->getElementById(param[i]);
							if (elem != nullptr) {
								elem->setActivated(ConvertTools::convertToBool(param[i + 1]));
							}
						}
					}
				}
			}
		}
		else {
			this->notifyObserver(message);
		}
	}
}