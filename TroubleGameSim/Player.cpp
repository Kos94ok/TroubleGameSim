
#include "stdafx.h"
#include "Player.h"
#include "game.h"

using namespace troubleGameSim;

int Player::GetPegStartingPosition()
{
	/* (index * 7) - 1, with overflow */
	switch (index)
	{
	case 0:
		return 27;
	case 1:
		return 6;
	case 2:
		return 13;
	case 3:
		return 20;
	}
	return 0;
}

int Player::GetPegFinishTurn()
{
	/* The first unreachable unit is always the starting unit. */
	return GetPegStartingPosition();
}

void Player::MarkAsFinished()
{
	/* Add the trophy */
	trophy = game::playersFinished;
	/* Increment the finished player counter */
	game::playersFinished += 1;
}