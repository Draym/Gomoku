#include "Game\Player\IAPlayer.h"


IAPlayer::IAPlayer(PlayerId id, std::string name, IAI<Grid<Cell>>::Function func) : APlayer(id, PlayerType::IA, name), ia(id, func)
{
}

IAPlayer::~IAPlayer()
{
}

bool IAPlayer::isCreated() const
{
	return this->ia.has_played();
}

bool IAPlayer::isRunning() const
{
	return this->ia.is_playing();
}


void	IAPlayer::newAction(const Grid<Cell>& map, const Referee<Grid<Cell>>& referee)
{
	this->ia.play_async(referee, map);
}

double IAPlayer::getActionTime() const
{
	return this->ia.get_time_elapsed();
}

std::pair<int, int>	IAPlayer::getNextAction()
{
	CellCoordinate tmp = this->ia.get_result();

	return std::make_pair(tmp.at(0), tmp.at(1));
}

void	IAPlayer::setMethod(IAI<Grid<Cell>>::Function method)
{
	this->ia.change_mind(method);
}
