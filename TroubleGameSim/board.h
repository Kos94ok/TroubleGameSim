#pragma once

#include "stdafx.h"
#include "Peg.h"
#include "BoardUnit.h"

namespace troubleGameSim
{
	/* A namespace that contains all the board state information */
	namespace board
	{
		/* A list of all Pegs in the game */
		extern std::vector<Peg> pegs;
		/* A list of all board units in the game */
		extern std::vector<BoardUnit> units;

		/* Initialize a new board for the new game */
		void CreateNewBoard();
		/* Initialize a new set of Pegs for the new game */
		void CreateNewPegs();
		/* Check if the unit is occupied by some peg. If an owner is specified, only this player's Pegs are considered */
		bool IsUnitOccupied(int index, int area, int owner = -1);
		/* Check if the specified Peg can move that amount of spaces forward */
		bool CanPegMove(int player, int pegIndex, int amountOfSpaces);
		/* Check if the specified Peg can move that amount of spaces forward. Takes an internal vector index as parameter instead */
		bool CanPegMoveRaw(int pegIndexInArray, int amountOfSpaces);
		/* Send any Pegs on that position back to their home area */
		void SendPegToHome(int position, int area);
	}
}