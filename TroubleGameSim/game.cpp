
#include "stdafx.h"
#include "game.h"
#include "board.h"
#include <random>

using namespace troubleGameSim;

bool game::isCompleted = false;
int game::playersFinished = 0;
int game::currentTurn = 0;
int game::activePlayer = 0;
std::vector<Player> game::players;

int game::rolledValue = -1;
std::mt19937 randomEngine;

void game::StartNewGame()
{
	std::random_device rd;
	randomEngine = std::mt19937(rd());

	board::CreateNewBoard();
	board::CreateNewPegs();

	for (int i = 0; i < PLAYER_COUNT; i++)
	{
		players.push_back(Player(i));
	}
}

void game::PopNumber()
{
	std::uniform_int_distribution<int> dist(1, 6);

	rolledValue = dist(randomEngine);
	//rolledValue = 6;
}

bool game::ResetTurnIfApplicable(int player)
{
	if (game::rolledValue == 6)
	{
		game::rolledValue = -1;
		game::players[player].hasPoppedThisTurn = false;
		return false;
	}
	return true;
}

bool game::PerformAction(game::Action action, int player)
{
	// Roll a number
	if (action == game::Action::rollNumber)
	{
		game::PopNumber();
		game::players[player].hasPoppedThisTurn = true;
		if (game::rolledValue == 6)
			game::players[player].AllowIntoGame();
		return false;
	}
	// New peg
	else if (action == game::Action::newPeg)
	{
		// Find a peg
		for (int i = 0; i < (int)board::pegs.size(); i++)
		{
			if (board::pegs[i].GetOwner() == player && board::pegs[i].GetArea() == AREA_HOME)
			{
				board::pegs[i].MoveTo(game::players[game::activePlayer].GetPegStartingPosition(), AREA_PUBLIC);
				break;
			}
		}
		return ResetTurnIfApplicable(player);
	}
	// Move a peg
	else if (action == game::Action::movePeg)
	{
		// Find a peg
		for (int i = 0; i < (int)board::pegs.size(); i++)
		{
			if (board::pegs[i].GetOwner() == player && board::pegs[i].GetArea() != AREA_HOME && board::CanPegMoveRaw(i, game::rolledValue))
			{
				//board::pegs[i].MoveTo(game::players[game::activePlayer].GetPegStartingPosition(), AREA_PUBLIC);
				int targetArea = board::pegs[i].GetArea();
				int targetPosition = board::pegs[i].GetAreaPosition() + game::rolledValue;
				int finishTurn = game::players[player].GetPegFinishTurn();
				// Turn to finish
				if (targetArea == AREA_PUBLIC && board::pegs[i].GetAreaPosition() < finishTurn && targetPosition >= finishTurn)
				{
					targetPosition -= finishTurn;
					targetArea = AREA_FINISH;
				}
				// Adjust for board overflow
				else
				{
					if (targetPosition >= PUBLIC_AREA_LENGTH)
						targetPosition -= PUBLIC_AREA_LENGTH;
				}
				// Send enemy peg to home
				if (targetArea == AREA_PUBLIC && board::IsUnitOccupied(targetPosition, AREA_PUBLIC))
				{
					board::SendPegToHome(targetPosition, AREA_PUBLIC);
				}
				board::pegs[i].MoveTo(targetPosition, targetArea);
				// Check for game winning condition
				game::CheckForWin(player);
				break;
			}
		}
		return ResetTurnIfApplicable(player);
	}
	// Skip the turn
	else if (action == game::Action::skipTurn)
	{
		return true;
	}
	return false;
}

game::Action game::GetPerformedAction(int index, int player)
{
	index -= 49;
	std::vector<game::Action> availableActions = GetAvailableActions(player);
	if (index >= 0 && index < (int)availableActions.size())
	{
		return availableActions[index];
	}
	return game::Action::invalid;
}

std::vector<game::Action> game::GetAvailableActions(int player)
{
	std::vector<game::Action> returnVector;

	// Pre-calculate some values
	int pegsInHome = 0;
	for (int i = 0; i < (int)board::pegs.size(); i++)
	{
		if (board::pegs[i].GetArea() == AREA_HOME && board::pegs[i].GetOwner() == player)
		{
			pegsInHome += 1;
		}
	}
	int movablePegs = 0;
	for (int i = 0; i < PEGS_PER_PLAYER; i++)
	{
		if (board::CanPegMove(player, i, game::rolledValue))
		{
			movablePegs += 1;
		}
	}

	// Check for all the possible actions
	if (!game::players[player].hasPoppedThisTurn)
	{
		returnVector.push_back(game::Action::rollNumber);
	}
	if (pegsInHome > 0 && !board::IsUnitOccupied(game::players[player].GetPegStartingPosition(), AREA_PUBLIC) && game::rolledValue == 6)
	{
		returnVector.push_back(game::Action::newPeg);
	}
	if (game::players[player].HasStartedPlaying() && game::players[player].hasPoppedThisTurn && movablePegs > 0)
	{
		returnVector.push_back(game::Action::movePeg);
	}

	// If nothing else - skip the turn
	if (returnVector.size() == 0)
		returnVector.push_back(game::Action::skipTurn);

	return returnVector;
}

void game::CheckForWin(int player)
{
	// Calculate the pegs
	int pegsInPlace = 0;
	for (int i = 0; i < (int)board::pegs.size(); i++)
	{
		if (board::pegs[i].GetOwner() == player && board::pegs[i].GetArea() == AREA_FINISH)
		{
			pegsInPlace += 1;
		}
	}
	// If there are enough, declare the winner
	if (pegsInPlace == PEGS_PER_PLAYER)
	{
		game::players[player].MarkAsFinished();
	}
}