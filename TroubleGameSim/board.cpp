
#include "stdafx.h"
#include "board.h"
#include "settings.h"
#include "game.h"

using namespace troubleGameSim;

std::vector<Peg> board::pegs;
std::vector<BoardUnit> board::units;

void board::CreateNewBoard()
{
	// Create the starting positions (home area)
	std::vector<std::pair<int, int>> homeUnits;
	homeUnits.push_back({ 3,  0 });
	homeUnits.push_back({ 5,  0 });
	homeUnits.push_back({ 1,  1 });
	homeUnits.push_back({ 3,  1 });

	homeUnits.push_back({ 33,  0 });
	homeUnits.push_back({ 35,  0 });
	homeUnits.push_back({ 35,  1 });
	homeUnits.push_back({ 37,  1 });

	homeUnits.push_back({ 35, 13 });
	homeUnits.push_back({ 37, 13 });
	homeUnits.push_back({ 33, 14 });
	homeUnits.push_back({ 35, 14 });

	homeUnits.push_back({ 1, 13 });
	homeUnits.push_back({ 3, 13 });
	homeUnits.push_back({ 3, 14 });
	homeUnits.push_back({ 5, 14 });

	// Create the main circle (public area)
	std::vector<std::pair<int, int>> publicUnits;
	publicUnits.push_back({ 13, 0 });
	publicUnits.push_back({ 17, 0 });
	publicUnits.push_back({ 21, 0 });
	publicUnits.push_back({ 25, 0 });
	publicUnits.push_back({ 28, 1 });
	publicUnits.push_back({ 31, 2 });
	publicUnits.push_back({ 34, 3 });

	publicUnits.push_back({ 37, 4 });
	publicUnits.push_back({ 37, 6 });
	publicUnits.push_back({ 37, 8 });
	publicUnits.push_back({ 37, 10 });
	publicUnits.push_back({ 34, 11 });
	publicUnits.push_back({ 31, 12 });
	publicUnits.push_back({ 28, 13 });

	publicUnits.push_back({ 25, 14 });
	publicUnits.push_back({ 21, 14 });
	publicUnits.push_back({ 17, 14 });
	publicUnits.push_back({ 13, 14 });
	publicUnits.push_back({ 10, 13 });
	publicUnits.push_back({  7, 12 });
	publicUnits.push_back({  4, 11 });

	publicUnits.push_back({  1, 10 });
	publicUnits.push_back({  1,  8 });
	publicUnits.push_back({  1,  6 });
	publicUnits.push_back({  1,  4 });
	publicUnits.push_back({  4,  3 });
	publicUnits.push_back({  7,  2 });
	publicUnits.push_back({ 10,  1 });

	// Create the finish units (finish area)
	std::vector<std::pair<int, int>> finishUnits;
	finishUnits.push_back({  9,  3 });
	finishUnits.push_back({ 11,  4 });
	finishUnits.push_back({ 13,  5 });
	finishUnits.push_back({ 15,  6 });

	finishUnits.push_back({ 29,  3 });
	finishUnits.push_back({ 27,  4 });
	finishUnits.push_back({ 25,  5 });
	finishUnits.push_back({ 23,  6 });

	finishUnits.push_back({ 29, 11 });
	finishUnits.push_back({ 27, 10 });
	finishUnits.push_back({ 25,  9 });
	finishUnits.push_back({ 23,  8 });

	finishUnits.push_back({ 9,  11 });
	finishUnits.push_back({ 11, 10 });
	finishUnits.push_back({ 13,  9 });
	finishUnits.push_back({ 15,  8 });

	// Reserve some memory
	BoardUnit unit(0, 0, 0, 0, -1);

	// Flush the data into the final form
	// Adding home zone units
	int vectorIndex = 0;
	for (int player = 0; player < PLAYER_COUNT; player++)
	{
		for (int peg = 0; peg < PEGS_PER_PLAYER; peg++)
		{
			unit.Recycle(peg, homeUnits[vectorIndex].first, homeUnits[vectorIndex].second, AREA_HOME, player);
			units.push_back(unit);
			vectorIndex += 1;
		}
	}

	// Adding finish zone units
	vectorIndex = 0;
	for (int player = 0; player < PLAYER_COUNT; player++)
	{
		for (int peg = 0; peg < PEGS_PER_PLAYER; peg++)
		{
			unit.Recycle(peg, finishUnits[vectorIndex].first, finishUnits[vectorIndex].second, AREA_FINISH, player);
			units.push_back(unit);
			vectorIndex += 1;
		}
	}

	// Adding public zone units
	for (int i = 0; i < (int)publicUnits.size(); i++)
	{
		unit.Recycle(i, publicUnits[i].first, publicUnits[i].second, AREA_PUBLIC);
		units.push_back(unit);
	}
}

char board::GetObjectSymbol(int x, int y)
{
	// Look for pegs first
	for (int i = 0; i < (int)pegs.size(); i++)
	{
		std::pair<int, int> pegPos = pegs[i].GetWorldPosition();
		if (pegPos.first == x && pegPos.second == y)
		{
			return '0' + pegs[i].GetOwner();
		}
	}
	// If no pegs found, check the units
	for (int i = 0; i < (int)units.size(); i++)
	{
		std::pair<int, int> unitPos = units[i].GetPosition();
		if (units[i].GetArea() != AREA_HOME && unitPos.first == x && unitPos.second == y)
		{
			return 35;
		}
	}
	// No object found - return a space
	return ' ';
}

void board::CreateNewPegs()
{
	Peg pegHandle(0, 0);
	for (int player = 0; player < PLAYER_COUNT; player++)
	{
		for (int peg = 0; peg < PEGS_PER_PLAYER; peg++)
		{
			pegHandle.Recycle(peg, player);
			board::pegs.push_back(pegHandle);
		}
	}
}

bool board::IsUnitOccupied(int index, int area, int owner)
{
	for (int i = 0; i < (int)pegs.size(); i++)
	{
		if (pegs[i].GetArea() == area && pegs[i].GetAreaPosition() == index
			&& (owner == -1 || pegs[i].GetOwner() == owner))
		{
			return true;
		}
	}
	return false;
}

bool board::CanPegMove(int player, int pegIndex, int amountOfSpaces)
{
	int pegsFound = 0;
	for (int i = 0; i < (int)pegs.size(); i++)
	{
		if (pegs[i].GetOwner() == player)
		{
			if (pegIndex == pegsFound)
			{
				return CanPegMoveRaw(i, amountOfSpaces);
			}
			pegsFound += 1;
		}
	}
	return false;
}

bool board::CanPegMoveRaw(int pegIndexInArray, int amountOfSpaces)
{
	int area = pegs[pegIndexInArray].GetArea();
	int pos = pegs[pegIndexInArray].GetAreaPosition();
	int owner = pegs[pegIndexInArray].GetOwner();
	int finishPos = game::players[owner].GetPegFinishTurn();

	if (area == AREA_HOME
		|| (area == AREA_FINISH && pos + amountOfSpaces >= PEGS_PER_PLAYER)
		|| (area == AREA_PUBLIC && pos < finishPos && pos + amountOfSpaces - finishPos >= PEGS_PER_PLAYER)
		|| (area == AREA_FINISH && board::IsUnitOccupied(pos + amountOfSpaces, AREA_FINISH, owner))
		|| (area == AREA_PUBLIC && pos < finishPos && pos + amountOfSpaces >= finishPos && board::IsUnitOccupied(pos + amountOfSpaces - finishPos, AREA_FINISH, owner)))
	{
		return false;
	}

	return true;
}

void board::SendPegToHome(int position, int area)
{
	int targetPeg = -1;
	// Find our target peg
	for (int i = 0; i < (int)pegs.size(); i++)
	{
		if (pegs[i].GetArea() == area && pegs[i].GetAreaPosition() == position)
		{
			targetPeg = i;
			break;
		}
	}

	if (targetPeg == -1)
		return;

	// Find a suitable place for said peg
	for (int i = 0; i < (int)units.size(); i++)
	{
		if (units[i].GetArea() == AREA_HOME && units[i].GetOwner() == pegs[targetPeg].GetOwner()
			&& !IsUnitOccupied(units[i].GetIndex(), AREA_HOME))
		{
			pegs[targetPeg].MoveTo(units[i].GetIndex(), AREA_HOME);
		}
	}
}