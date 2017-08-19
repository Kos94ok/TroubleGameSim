#pragma once

/* A class that represents a player. */
class Player
{
	/* The player's number. Always in range [0; PLAYER_COUNT). */
	int index;
	/* Did the player already roll a first 6 to get into the game? */
	bool hasStarted;
	/* The position of the player who has completed the game. If still playing, set to -1. */
	int trophy;

public:
	/* Did the player roll a number this turn? */
	bool hasPoppedThisTurn;

	/* Basic constructor */
	Player(int index)
	{
		this->index = index;
		hasStarted = false;
		hasPoppedThisTurn = false;
		trophy = -1;
	}

	/* Public getter methods. Blocks modifications of those variables by outsiders. */
	bool HasStartedPlaying() { return hasStarted; }
	bool HasFinished() { return trophy > -1; }
	int GetTrophy() { return trophy; }

	/* Public setter methods. */
	void AllowIntoGame() { hasStarted = true; }

	/* Get the index of the unit where all the player's Pegs start. */
	int GetPegStartingPosition();
	/* Get index of the first AREA_PUBLIC unit which should be unreachable by all player's Pegs.
	 * When this index is reached, the Peg should instead turn to the finishing area.
	 */
	int GetPegFinishTurn();
	/* Mark the player as finished and hand out a trophy. */
	void MarkAsFinished();
};