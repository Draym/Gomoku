#include <stdexcept>

#include "referee\History.h"

PlayerId operator~(const PlayerId& value)
{
	switch (value)
	{
	case PlayerId::P1:
		return PlayerId::P2;
		break;
	case PlayerId::P2:
		return PlayerId::P1;
		break;
	default:
		throw std::runtime_error("Impossible PlayerId inversion");
	}
}

GameActionType operator~(const GameActionType& value)
{
	switch (value)
	{
	case GameActionType::ADD:
		return GameActionType::DEL;
		break;
	case GameActionType::DEL:
		return GameActionType::ADD;
		break;
	default:
		throw std::runtime_error("Unknown GameActionType");
	}
}
