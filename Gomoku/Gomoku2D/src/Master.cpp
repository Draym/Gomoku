#include "Master.h"

using namespace std::placeholders;

Master::Master()
	: windows{
		{ EWindows::WINDOW_HOME, new WindowHome() },
		{ EWindows::WINDOW_OPTION, new WindowOption() },
		{ EWindows::WINDOW_SELECTPLAY, new WindowSelectPlay() },
		{ EWindows::WINDOW_GAME, new WindowGame() } }
	, local(ELocation::MASTER)
	, current(EWindows::NONE)
{
	this->screen.create(sf::VideoMode(100, 100), "Gomoku");
	for (std::map<EWindows, AWindow*>::iterator it = this->windows.begin(); it != this->windows.end(); ++it) {
		it->second->addObserver(this);
	}
}


Master::~Master()
{
}

void Master::init()
{
	WindowConfig::init();
	RuleManager::init();
	ResourceManager::createResources();
	IAManager::init();
	SoundMixer::init();
	for (std::map<EWindows, AWindow*>::iterator it = this->windows.begin(); it != this->windows.end(); ++it) {
		it->second->init();
	}
	this->switchScreen(EWindows::WINDOW_HOME);
	SoundMixer::launch(ESound::DREAMTEMPLE);
}

void Master::quit()
{
	this->screen.close();
}

void Master::run()
{
	while (this->screen.isOpen())
	{
		this->update();
		this->gestEvent();
		this->render();
	}
}

void	Master::update(Tuple<ELocation, ELocation, GenericTask> message)
{
	if (message.first != this->local && message.second == this->local) {
		if (message.third.getTask() == ETask::SWITCH_SCREEN && message.third.hasParameters()) {
			EWindows value = this->getScreen(message.third.getParameters()[0]);

			if (value != EWindows::NONE)
				this->switchScreen(value);
		}
		else if (message.third.getTask() == ETask::ACTIVE_MUSIC) {
			SoundMixer::reverseMute();

			GuiElement *elem = nullptr;
			if (message.first == ELocation::GAME_GUI) {
				elem = this->windows[EWindows::WINDOW_HOME]->getUserInterface()->getElementById("buttonMusicHome");
			}
			else if (message.first == ELocation::HOME_GUI) {
				elem = this->windows[EWindows::WINDOW_GAME]->getUserInterface()->getElementById("buttonMusicGame");
			}
			if (elem != nullptr) {
				elem->doTask(GenericTask(ETask::SWITCH_ACTIVATED));
			}
		}
		else if (message.third.getTask() == ETask::SWITCH_MUSIC) {
			SoundMixer::launchNext();
		}
		else if (message.third.getTask() == ETask::CHANGE_IA_METHOD && message.third.hasParameters()) {
			std::vector<std::string>	param = message.third.getParameters();

			if (param.size() > 1) {
				if (param[0] == "A1") {
					RuleManager::p1IAMethod = param[1];
				}
				else if (param[0] == "A2") {
					RuleManager::p2IAMethod = param[1];
				}
			}
		}
	}
}

void			Master::gestEvent()
{
	sf::Event	event;

	while (this->screen.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			this->screen.close();
		else
			this->windows[this->current]->event(event);
	}
}

void	Master::update()
{
	this->windows[this->current]->update();
}

void	Master::render()
{
	this->screen.clear();
	this->windows[this->current]->render(this->screen);
	this->screen.display();
}

void Master::switchScreen(EWindows id)
{
	if (this->current != EWindows::NONE && !this->windows[this->current]->canLeave()) {
		return;
	}
	if (this->current != EWindows::NONE) {
		this->windows[this->current]->exit();
	}
	this->current = id;
	this->windows[this->current]->enter(this->screen);
}

EWindows	Master::getScreen(std::string value)
{
	static const int			max = 4;
	static const std::string	screens[max] = { "HOME", "OPTION", "SELECTPLAY", "GAME" };
	EWindows					result = EWindows::NONE;

	for (int i = 0; i < 4; ++i)
	{
		if (screens[i] == value)
			return static_cast<EWindows>(i + 1);
	}
	return result;
}