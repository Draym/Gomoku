#include "Game\Player\HumanPlayer.h"


HumanPlayer::HumanPlayer(PlayerId id, std::string name) : APlayer(id, PlayerType::HUMAN, name)
{
}


HumanPlayer::~HumanPlayer()
{
}
