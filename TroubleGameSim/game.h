#pragma once

#include "stdafx.h"
#include "Player.h"

namespace troubleGameSim
{
	/* A namespace that contains all the players and game-related information */
	namespace game
	{
		/* A list of all possible actions that a player can perform on their turn */
		enum Action
		{
			skipTurn,
			rollNumber,
			movePeg,
			newPeg,
			invalid,
		};

		/* Is the game already completed? */
		extern bool isCompleted;
		/* How many players have already finished the game */
		extern int playersFinished;
		/* The current turn of the game. A single turn contains the moves of all players */
		extern int currentTurn;
		/* Current player performing their moves */
		extern int activePlayer;
		/* A list of all players in the game */
		extern std::vector<Player> players;

		/* Last popped random value */
		extern int rolledValue;
		/* A randomizer for the value */
		extern std::mt19937 randomEngine;

		/* Initialize the board and Pegs for a new game */
		void StartNewGame();
		/* Roll a random number. Stored in game::rolledValue */
		void PopNumber();
		/* If player has rolled a 6, reset his turn and let them roll another value */
		bool ResetTurnIfApplicable(int player);
		/* Perform an action for the player. It is assumed that the action is valid */
		bool PerformAction(game::Action action, int player);
		/* Convert the pressed button into the selected action */
		game::Action GetPerformedAction(int index, int player);
		/* Get a full list of all currently available actions */
		std::vector<Action> GetAvailableActions(int player);
		/* Check if the player has completed the game and, if necessary, mark him as a winner */
		void CheckForWin(int player);
	}
}