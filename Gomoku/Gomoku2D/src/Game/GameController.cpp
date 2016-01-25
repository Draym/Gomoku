#include "Game\GameController.h"

GameController::GameController() : whiteTurn(false), finished(false), gameMap(), current(-1)
{
	this->gameMap.resize(MAP_WIDTH, MAP_HEIGHT);
	this->state = EStatus::WAITING;
}

GameController::~GameController()
{
}

void	GameController::update()
{
	if (this->players[this->getCurrentTurn()]->getType() == PlayerType::IA && !this->finished) {
		IAPlayer* ia = (IAPlayer*) this->players[this->getCurrentTurn()];

		//std::cout << "IA TURN {" << ia->isCreated() << ", " << ia->isRunning() << "}" << std::endl;
		if (!ia->isCreated() && !this->haveToWait)
		{
			this->referee.refresh(this->gameMap);
	//		std::cout << "create" << std::endl;
			ia->newAction(this->gameMap, this->referee);
			this->state = EStatus::RUNNING;
		}
		if (ia->isCreated() && !ia->isRunning())
		{
			//std::cout << "end running" << std::endl;
			std::pair<int, int> action = ia->getNextAction();
			std::cout << "AI {"<< ia->getName() << "} action time: " << ia->getActionTime() << "s.\n" << std::endl;
			//std::cout << "action [" << action.first << ", " << action.second << "]" << std::endl;
			this->doAction(ia, action.first, action.second);
			this->state = EStatus::WAITING;
		}
	}
}

void	GameController::enter()
{
	for (std::size_t i = 0; i < RuleManager::rules.size(); ++i)
	{
	//	std::cout << "-> "<< RuleManager::rules[i].first << " = " << RuleManager::rules[i].third << std::endl;
		this->referee.enable_rule(RuleManager::rules[i].second, RuleManager::rules[i].third);
	}
	//std::cout << "p1: " << RuleManager::p1 << " p2: " << RuleManager::p2 << std::endl;
	//std::cout << "A1: " << RuleManager::p1IAMethod << " A2: " << RuleManager::p2IAMethod << std::endl;
	if (RuleManager::p1 == true) {
		this->players[ETurn::BLACK] = new HumanPlayer(PlayerId::P1, "player1");
	}
	else {
		IAPlayer *tmp = new IAPlayer(PlayerId::P1, RuleManager::p1IAMethod, IAManager::getMethod(RuleManager::p1IAMethod));
		this->players[ETurn::BLACK] = tmp;
	}
	if (RuleManager::p2 == true) {
		this->players[ETurn::WHITE] = new HumanPlayer(PlayerId::P2, "player2");
	}
	else {
		IAPlayer *tmp = new IAPlayer(PlayerId::P2, RuleManager::p2IAMethod, IAManager::getMethod(RuleManager::p2IAMethod));
		this->players[ETurn::WHITE] = tmp;
	}
	this->haveToWait = false;
	this->state = EStatus::WAITING;
}

bool	GameController::reset()
{
	this->players[ETurn::WHITE]->reset();
	this->players[ETurn::BLACK]->reset();
	this->resetMap();
	this->players.clear();
	this->pawns.clear();
	this->referee.clear();
	this->whiteTurn = false;
	this->finished = false;
	return true;
}

bool	GameController::resetMap()
{
	if (this->state == EStatus::WAITING)
	{
		for (std::size_t y = 0; y < MAP_HEIGHT; ++y) {
			for (std::size_t x = 0; x < MAP_WIDTH; ++x) {
				this->gameMap(x, y).player_id = PlayerId::None;
			}
		}
		return true;
	}
	return false;
}

bool	GameController::undoAction()
{
	if (this->state == EStatus::WAITING)
	{
		if (this->current >= 0 && !this->finished) {
			this->referee.undo(this->history[this->current], this->gameMap);
			this->processTurn(this->history[this->current], false);
			--this->current;
			this->whiteTurn = !this->whiteTurn;
		}
		return true;
	}
	return false;
}

bool GameController::redoAction()
{
	if (this->state == EStatus::WAITING)
	{
		if (this->current < (int)this->history.size() - 1 && !this->finished) {
			++this->current;
			this->referee.redo(this->history[this->current], this->gameMap);
			this->processTurn(this->history[this->current], true);
			this->whiteTurn = !this->whiteTurn;
		}
		return true;
	}
	return false;
}

bool	GameController::newAction(int x, int y)
{
	if (this->state == EStatus::WAITING && !this->finished) {
		if (this->players.size() < 2) {
			throw Exception("Error", "this game requires at least 2 players", "GameController");
		}
		APlayer* player = this->players[this->getCurrentTurn()];
		if (player->getType() == PlayerType::HUMAN)
		{
			this->doAction(player, x, y);
			return true;
		}
	}
	return false;
}

void	GameController::doAction(APlayer *player, int x, int y)
{
	this->state = EStatus::RUNNING;
	if (this->referee.is_valid(x, y, player->getId(), this->gameMap)) {
		this->current++;
		this->history.resize(this->current);
		this->history.push_back(GameTurn());
		this->referee.play(x, y, player->getId(), this->gameMap, this->history[this->current]);
		this->processTurn(this->history[this->current], true);

		if (this->referee.get_winner() != PlayerId::None)
		{
			this->endOfTheGame();
		}
		this->whiteTurn = !this->whiteTurn;
	}
	this->state = EStatus::WAITING;
}

void GameController::endOfTheGame()
{
	PlayerId winner = this->referee.get_winner();

	this->finished = true;
	GenericTask task(ETask::ACTIVE_GUI_ELEM);
	task.addParameter("menuEndGame:true");
	this->notifyObserver(TaskFactory::createTask(ELocation::GAME_CONTROLLER, ELocation::GAME, task));
	GenericTask task2(ETask::GIVE_TASK);
	std::string v1 = "menuEndGame:ADD_TITLE:GamePlayerName1:black:";
	v1 += (RuleManager::p1 == true ? "Player Noir" : "IA Noir");
	task2.addParameter(v1);
	this->notifyObserver(TaskFactory::createTask(ELocation::GAME_CONTROLLER, ELocation::GAME, task2));
	GenericTask task3(ETask::GIVE_TASK);
	std::string v2 = "menuEndGame:ADD_TITLE:GamePlayerName2:black:";
	v2 += (RuleManager::p2 == true ? "Player Blanc" : "IA Blanc");
	task3.addParameter(v2);
	this->notifyObserver(TaskFactory::createTask(ELocation::GAME_CONTROLLER, ELocation::GAME, task3));

	GenericTask task4(ETask::GIVE_TASK);
	std::string v3 = "menuEndGame:ADD_TITLE:GamePlayerResult1:";
	v3 += (winner == PlayerId::P1 ? "green:Victory !" : "red:Defeat");
	task4.addParameter(v3);
	this->notifyObserver(TaskFactory::createTask(ELocation::GAME_CONTROLLER, ELocation::GAME, task4));
	GenericTask task5(ETask::GIVE_TASK);
	std::string v4 = "menuEndGame:ADD_TITLE:GamePlayerResult2:";
	v4 += (winner == PlayerId::P2 ? "green:Victory !" : "red:Defeat");
	task5.addParameter(v4);
	this->notifyObserver(TaskFactory::createTask(ELocation::GAME_CONTROLLER, ELocation::GAME, task5));
}

void						GameController::processTurn(GameTurn &turn, bool mode) {
	std::vector<GameAction>	tasks = std::get<1>(turn);

	GameActionType task = (mode == true ? GameActionType::ADD : GameActionType::DEL);
	for (std::size_t i = 0; i < tasks.size(); ++i)
	{
		if (std::get<0>(tasks[i]) == task) {
			this->addPawn(std::get<1>(tasks[i]), std::get<2>(tasks[i]));
		}
		else {
			this->deletePawn(std::get<1>(tasks[i]), std::get<2>(tasks[i]));
		}
	}
}

void	GameController::addPawn(int x, int y)
{
	this->pawns.push_back(Tuple<ETurn, int, int>(this->getCurrentTurn(), x, y));
}

void	GameController::deletePawn(int x, int y)
{
	for (std::size_t i = 0; i < this->pawns.size(); ++i) {
		if (this->pawns[i].second == x && this->pawns[i].third == y) {
			this->pawns.erase(this->pawns.begin() + i);
		}
	}
}

void GameController::setWaitingRequest(bool value)
{
	this->haveToWait = value;
}

ETurn	GameController::getCurrentTurn() const
{
	return (this->whiteTurn == true ? WHITE : BLACK);
}

std::vector<Tuple<ETurn, int, int> >	GameController::getPawns() const
{
	return this->pawns;
}

bool	GameController::isFinished() const
{
	return this->finished;
}

bool GameController::isCalculating() const
{
	return (this->state == EStatus::RUNNING ? true : false);
}

bool	GameController::currentIsHuman()
{
	return (this->players[this->getCurrentTurn()]->getType() == PlayerType::HUMAN);
}