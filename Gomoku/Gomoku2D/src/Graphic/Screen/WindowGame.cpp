#include "Graphic\Screen\WindowGame.h"

WindowGame::WindowGame()
	: AWindow(new GameGUI())
	, gameController()
{
	this->local = ELocation::GAME;
	this->gui->addObserver(this);
	this->gameController.addObserver(this);
	this->pCurrent = std::make_pair(-1, -1);
}

WindowGame::~WindowGame()
{
}

void WindowGame::init()
{
	this->background.setTexture(ResourceManager::getImage(EImage::GAME_BACKGROUND));

	this->pState[ETurn::BLACK][EState::SET].setTexture(ResourceManager::getImage(EImage::P_BLACK));
	this->pState[ETurn::BLACK][EState::UNSET].setTexture(ResourceManager::getImage(EImage::P_BLACK));
	this->pState[ETurn::BLACK][EState::UNSET].setColor(sf::Color(255, 255, 255, 180));
	this->pState[ETurn::BLACK][EState::LAST].setTexture(ResourceManager::getImage(EImage::P_BLACK_LUM));

	this->pState[ETurn::WHITE][EState::SET].setTexture(ResourceManager::getImage(EImage::P_WHITE));
	this->pState[ETurn::WHITE][EState::UNSET].setTexture(ResourceManager::getImage(EImage::P_WHITE));
	this->pState[ETurn::WHITE][EState::UNSET].setColor(sf::Color(255, 255, 255, 180));
	this->pState[ETurn::WHITE][EState::LAST].setTexture(ResourceManager::getImage(EImage::P_WHITE_LUM));

	this->turn[ETurn::BLACK].setTexture(ResourceManager::getImage(EImage::TURN_BLACK));
	this->turn[ETurn::BLACK].setPosition(12, 52);
	this->turn[ETurn::WHITE].setTexture(ResourceManager::getImage(EImage::TURN_WHITE));
	this->turn[ETurn::WHITE].setPosition(12, 52);
	this->gui->init();
}

void WindowGame::enter(sf::RenderWindow &screen)
{
	screen.setSize(sf::Vector2u(WindowConfig::getWindowGameWidth(), WindowConfig::getWindowGameHeight()));
	screen.setView(sf::View(sf::FloatRect(0, 0, (float)WindowConfig::getWindowGameWidth(), (float)WindowConfig::getWindowGameHeight())));
	screen.setPosition(sf::Vector2i(((WindowConfig::getWindowWidth() - WindowConfig::getWindowGameWidth()) / 2), (WindowConfig::getWindowHeight() - WindowConfig::getWindowGameHeight()) / 2));
	this->gameController.enter();
	this->gui->enter();
}

bool WindowGame::canLeave()
{
	return !this->gameController.isCalculating();
}

void WindowGame::update()
{
	this->gui->update();
	this->gameController.update();
}

void WindowGame::exit()
{
	this->gameController.reset();
}

float	WindowGame::getXInTheBoard(int x)
{
	return x * WindowConfig::getBoxWidth() + WindowConfig::getGameBoardX() - 24.0f;
}

float	WindowGame::getYInTheBoard(int y)
{
	return y * WindowConfig::getBoxHeight() + WindowConfig::getGameBoardY() - 24.0f;
}

void WindowGame::render(sf::RenderWindow & screen)
{
	screen.draw(this->background);
	this->drawCurrentPawn(screen);
	this->drawPawns(screen);
	this->gui->render(screen);
}

void WindowGame::drawCurrentPawn(sf::RenderWindow &screen)
{
	ETurn currentTurn = this->gameController.getCurrentTurn();

	screen.draw(this->turn[currentTurn]);
	if (this->pCurrent.first != -1 && this->gameController.currentIsHuman()) {
		this->pState[currentTurn][EState::UNSET].setPosition(this->getXInTheBoard(this->pCurrent.first), this->getYInTheBoard(this->pCurrent.second));
		screen.draw(this->pState[currentTurn][EState::UNSET]);
	}
}

void WindowGame::drawPawns(sf::RenderWindow &screen)
{
	EState state;
	std::vector<Tuple<ETurn, int, int> > pawns = this->gameController.getPawns();
	for (std::size_t i = 0; i < pawns.size(); ++i) {
		if (i == pawns.size() - 1)
			state = EState::LAST;
		else
			state = EState::SET;
		this->pState[pawns[i].first][state].setPosition(this->getXInTheBoard(pawns[i].second), this->getYInTheBoard(pawns[i].third));
		screen.draw(this->pState[pawns[i].first][state]);
	}
}

void WindowGame::event(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonReleased) {
		if (!this->gui->isSelected(event.mouseButton.x, event.mouseButton.y)) {
			if (this->pCurrent.first != -1 && !this->gameController.isFinished())
				this->gameController.newAction(this->pCurrent.first, this->pCurrent.second);
		}
	}
	else if (event.type == sf::Event::MouseMoved) {
		if (!this->gui->isOnFocus(event.mouseMove.x, event.mouseMove.y)) {
			if (!this->gameController.isFinished() && event.mouseMove.x >= WindowConfig::getGameBoardX()
				&& event.mouseMove.x <= (WindowConfig::getGameBoardX() + WindowConfig::getGameBoardWidth())
				&& event.mouseMove.y >= WindowConfig::getGameBoardY()
				&& event.mouseMove.y <= (WindowConfig::getGameBoardY() + WindowConfig::getGameBoardHeight()))
			{
				this->pCurrent.first = (int)round((event.mouseMove.x - WindowConfig::getGameBoardX()) / WindowConfig::getBoxWidth());
				this->pCurrent.second = (int)round((event.mouseMove.y - WindowConfig::getGameBoardY()) / WindowConfig::getBoxHeight());
			}
			else
				this->pCurrent.first = -1;
		}
		else
			this->pCurrent.first = -1;

	}
	else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
		GuiElement *elem = this->gui->getElementById("menuAbout");

		if (elem != nullptr) {
			elem->setActivated(false);
		}
	}
	else if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::F1 || event.key.code == sf::Keyboard::F2)) {
		if (!this->gameController.isCalculating()) {
			//			this->gameController.setWaitingRequest(true);

			GuiElement *elem = nullptr;
			if (event.key.code == sf::Keyboard::F1)
				elem = this->gui->getElementById("menuSelect");
			else if (event.key.code == sf::Keyboard::F2)
				elem = this->gui->getElementById("menuOption");

			if (elem == nullptr)
				return;
			if (!this->gameController.isFinished()) {
				elem->setActivated(!elem->isActivated());
				if (!elem->isActivated()) {
					this->gameController.enter();
				}
			}
			else {
				elem->setActivated(false);
			}
		}
		else {
			std::cout << "calculating" << std::endl;
			this->gameController.setWaitingRequest(true);
		}
	}
	else {
		this->gui->event(event);
	}
}

void WindowGame::update(Tuple<ELocation, ELocation, GenericTask> message)
{
	if (message.first != this->local) {
		if (message.second == this->local) {
			if (message.third.getTask() == ETask::UNDO_ACTION)
				this->gameController.undoAction();
			else if (message.third.getTask() == ETask::REDO_ACTION)
				this->gameController.redoAction();
			else if (message.third.getTask() == ETask::ACTIVE_GUI_ELEM && message.third.hasParameters()) {
				std::vector<std::string>	param = message.third.getParameters();

				if (param.size() > 1) {
					GuiElement *elem = this->gui->getElementById(param[0]);
					if (elem != nullptr) {
						if (param[1] == "reverse")
							elem->setActivated(!elem->isActivated());
						else
							elem->setActivated(ConvertTools::convertToBool(param[1]));
					}
				}
			}
			else if (message.third.getTask() == ETask::GIVE_TASK && message.third.hasParameters()) {
				std::vector<std::string>	param = message.third.getParameters();

				if (param.size() > 1) {
					GuiElement *elem = this->gui->getElementById(param[0]);

					if (elem != nullptr) {
						if (param[1] == "ADD_TITLE") {
							GenericTask task(ETask::ADD_TITLE);

							for (std::size_t i = 2; i < param.size(); ++i)
								task.addParameter(param[i]);
							elem->doTask(task);
						}
					}
				}
			}
			else if (message.third.getTask() == ETask::CHANGE_PLAYER && message.third.hasParameters()) {
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
			else if (message.third.getTask() == ETask::ACTIVE_RULE && message.third.hasParameters()) {
				RuleManager::reverse(message.third.getParameters()[0]);
			}
		}
		else {
			this->notifyObserver(message);
		}
	}
}
