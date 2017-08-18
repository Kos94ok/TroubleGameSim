
#include "stdafx.h"
#include "Player.h"
#include "game.h"

using namespace troubleGameSim;

int Player::GetPegStartingPosition()
{
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
	int val = GetPegStartingPosition() + 27;
	if (val >= 28)
		val -= 28;
	return val;
}

void Player::MarkAsFinished()
{
	// Add the trophy
	trophy = game::playersFinished;
	// Increment the finished player counter
	game::playersFinished += 1;
}