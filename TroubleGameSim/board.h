#pragma once

#include "Peg.h"
#include "BoardUnit.h"

namespace troubleGameSim
{
	namespace board
	{
		extern std::vector<Peg> pegs;
		extern std::vector<BoardUnit> units;

		void CreateNewBoard();
		void CreateNewPegs();
		bool IsUnitOccupied(int index, int area, int owner = -1);
		bool CanPegMove(int player, int pegIndex, int amountOfSpaces);
		bool CanPegMoveRaw(int pegIndexInArray, int amountOfSpaces);
		void SendPegToHome(int position, int area);
		char GetObjectSymbol(int x, int y);
	}
}