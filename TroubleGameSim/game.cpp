
#include "stdafx.h"
#include "game.h"
#include "board.h"

using namespace troubleGameSim;

bool game::isCompleted = false;
int game::playersFinished = 0;
int game::currentTurn = 0;
int game::activePlayer = 0;
std::vector<Player> game::players;

int game::rolledValue = -1;
std::mt19937 game::randomEngine;

void game::StartNewGame()
{
	/* Initialize a random engine */
	std::random_device rd;
	randomEngine = std::mt19937(rd());

	/* Create a new board and a set of Pegs */
	board::CreateNewBoard();
	board::CreateNewPegs();

	/* Create the players */
	for (int i = 0; i < PLAYER_COUNT; i++)
	{
		players.push_back(Player(i));
	}
}

void game::PopNumber()
{
	/* Define the value range */
	std::uniform_int_distribution<int> dist(1, 6);
	/* Roll some value */
	rolledValue = dist(randomEngine);
}

bool game::ResetTurnIfApplicable(int player)
{
	/* If a player rolled 6, reset the turn */
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
	/* Roll a number */
	if (action == game::Action::rollNumber)
	{
		game::PopNumber();
		game::players[player].hasPoppedThisTurn = true;
		if (game::rolledValue == 6)
			game::players[player].AllowIntoGame();
		return false;
	}
	/* New Peg on the board */
	else if (action == game::Action::newPeg)
	{
		/* Find a suitable Peg */
		for (int i = 0; i < (int)board::pegs.size(); i++)
		{
			if (board::pegs[i].GetOwner() == player && board::pegs[i].GetArea() == AREA_HOME)
			{
				/* Move that Peg to a starting position */
				board::pegs[i].MoveTo(game::players[game::activePlayer].GetPegStartingPosition(), AREA_PUBLIC);
				break;
			}
		}
		/* Check if the turn is over or will continue */
		return ResetTurnIfApplicable(player);
	}
	/* Move a Peg */
	else if (action == game::Action::movePeg)
	{
		/* Select a peg index to move. For simplicity, set to constant value. */
		int movedPegIndex = 0;
		/* Find a Peg to move */
		int pegsFound = 0;
		/* Iterate through all the Pegs until the suitable one is found */
		for (int i = 0; i < (int)board::pegs.size(); i++)
		{
			if (board::pegs[i].GetOwner() == player && board::pegs[i].GetArea() != AREA_HOME && board::CanPegMoveRaw(i, game::rolledValue))
			{
				/* Peg found */
				if (movedPegIndex == pegsFound)
				{
					/* Get some data */
					int targetArea = board::pegs[i].GetArea();
					int targetPosition = board::pegs[i].GetAreaPosition() + game::rolledValue;
					int finishTurn = game::players[player].GetPegFinishTurn();
					/* If the move will put the Peg over one whole lap, turn it to finish area instead */
					if (targetArea == AREA_PUBLIC && board::pegs[i].GetAreaPosition() < finishTurn && targetPosition >= finishTurn)
					{
						targetPosition -= finishTurn;
						targetArea = AREA_FINISH;
					}
					/* Prevent the position value from going over maximum */
					else
					{
						if (targetPosition >= PUBLIC_AREA_LENGTH)
							targetPosition -= PUBLIC_AREA_LENGTH;
					}
					/* If the target position is occupied, move other Peg home */
					if (targetArea == AREA_PUBLIC && board::IsUnitOccupied(targetPosition, AREA_PUBLIC))
					{
						board::SendPegToHome(targetPosition, AREA_PUBLIC);
					}
					/* Perform the move */
					board::pegs[i].MoveTo(targetPosition, targetArea);
					/* Check for game winning condition */
					game::CheckForWin(player);
					break;
				}
				/* Wrong index, keep searching */
				else
				{
					pegsFound += 1;
				}
			}
		}
		/* Check if the turn is over or will continue */
		return ResetTurnIfApplicable(player);
	}
	/* Skip the turn */
	else if (action == game::Action::skipTurn)
	{
		return true;
	}
	return false;
}

game::Action game::GetPerformedAction(int index, int player)
{
	/* Convert key code into an action number */
	index -= 49;
	/* Return the selected action */
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

	/* Get the amount of Pegs in player's home area */
	int pegsInHome = 0;
	for (int i = 0; i < (int)board::pegs.size(); i++)
	{
		if (board::pegs[i].GetArea() == AREA_HOME && board::pegs[i].GetOwner() == player)
		{
			pegsInHome += 1;
		}
	}
	/* Get the amount of Pegs that player can move */
	int movablePegs = 0;
	for (int i = 0; i < PEGS_PER_PLAYER; i++)
	{
		if (board::CanPegMove(player, i, game::rolledValue))
		{
			movablePegs += 1;
		}
	}

	/* If a player hasn't popped a number, allow them to pop */
	if (!game::players[player].hasPoppedThisTurn)
	{
		returnVector.push_back(game::Action::rollNumber);
	}
	/* If player has popped a 6, there are Pegs in home area and the starting position is not occupied, allow them to move a Peg into the public area */
	if (pegsInHome > 0 && !board::IsUnitOccupied(game::players[player].GetPegStartingPosition(), AREA_PUBLIC) && game::rolledValue == 6)
	{
		returnVector.push_back(game::Action::newPeg);
	}
	/* If a player has popped some number and has some Peg that can move this amount of spaces, allow them to move */
	if (game::players[player].HasStartedPlaying() && game::players[player].hasPoppedThisTurn && movablePegs > 0)
	{
		returnVector.push_back(game::Action::movePeg);
	}

	/* If a player can't do anything, allow them to skip a turn */
	if (returnVector.size() == 0)
		returnVector.push_back(game::Action::skipTurn);

	return returnVector;
}

void game::CheckForWin(int player)
{
	/* Check the amount of Pegs in finish area */
	int pegsInPlace = 0;
	for (int i = 0; i < (int)board::pegs.size(); i++)
	{
		if (board::pegs[i].GetOwner() == player && board::pegs[i].GetArea() == AREA_FINISH)
		{
			pegsInPlace += 1;
		}
	}
	/* If all the Pegs are in finish area, the player has finished the game */
	if (pegsInPlace == PEGS_PER_PLAYER)
	{
		game::players[player].MarkAsFinished();
	}
}