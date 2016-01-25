#include "Game\Player\APlayer.h"



APlayer::APlayer(PlayerId id, PlayerType type, std::string name) : id(id), type(type), name(name)
{
}

APlayer::~APlayer()
{
}

void	APlayer::reset()
{
}

// GETTERS

PlayerId	APlayer::getId() const
{
	return this->id;
}

PlayerType APlayer::getType() const
{
	return this->type;
}

std::pair<int, int>		APlayer::getNextAction()
{
	return std::make_pair(-1, -1);
}

std::string APlayer::getName() const
{
	return this->name;
}
