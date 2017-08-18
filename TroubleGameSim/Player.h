#pragma once

class Player
{
	int index;
	bool hasStarted;
	int trophy;

public:
	bool hasPoppedThisTurn;

	Player(int index)
	{
		this->index = index;
		hasStarted = false;
		hasPoppedThisTurn = false;
		trophy = -1;
	}

	bool HasStartedPlaying() { return hasStarted; }
	void AllowIntoGame() { hasStarted = true; }
	bool HasFinished() { return trophy > -1; }
	int GetTrophy() { return trophy; }

	int GetPegStartingPosition();
	int GetPegFinishTurn();
	void MarkAsFinished();
};