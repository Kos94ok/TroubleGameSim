#pragma once

#include "Player.h"

namespace troubleGameSim
{
	namespace game
	{
		enum Action
		{
			accept,
			skipTurn,
			rollNumber,
			movePeg,
			newPeg,
			invalid,
		};

		extern bool isCompleted;
		extern int playersFinished;
		extern int currentTurn;
		extern int activePlayer;
		extern std::vector<Player> players;

		extern int rolledValue;

		void StartNewGame();
		void PopNumber();
		bool ResetTurnIfApplicable(int player);
		bool PerformAction(game::Action action, int player);
		game::Action GetPerformedAction(int index, int player);
		std::vector<Action> GetAvailableActions(int player);
		void CheckForWin(int player);
	}
}