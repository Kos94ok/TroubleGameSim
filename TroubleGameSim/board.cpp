
#include "stdafx.h"
#include "board.h"
#include "settings.h"
#include "game.h"

using namespace troubleGameSim;

std::vector<Peg> board::pegs;
std::vector<BoardUnit> board::units;

void board::CreateNewBoard()
{
	/* Initialize the temporary data vectors with unit positions first. The order of those data points is important. */

	/* Create the starting positions (home area) */
	std::vector<std::pair<int, int>> homeUnits;
	/* Player 0 */
	homeUnits.push_back({ 3,  0 });
	if (PEGS_PER_PLAYER > 1) { homeUnits.push_back({ 5,  0 }); }
	if (PEGS_PER_PLAYER > 2) { homeUnits.push_back({ 1,  1 }); }
	if (PEGS_PER_PLAYER > 3) { homeUnits.push_back({ 3,  1 }); }

	/* Player 1 */
	homeUnits.push_back({ 33,  0 });
	if (PEGS_PER_PLAYER > 1) { homeUnits.push_back({ 35,  0 }); }
	if (PEGS_PER_PLAYER > 2) { homeUnits.push_back({ 35,  1 }); }
	if (PEGS_PER_PLAYER > 3) { homeUnits.push_back({ 37,  1 }); }

	/* Player 2 */
	homeUnits.push_back({ 35, 13 });
	if (PEGS_PER_PLAYER > 1) { homeUnits.push_back({ 37, 13 }); }
	if (PEGS_PER_PLAYER > 2) { homeUnits.push_back({ 33, 14 }); }
	if (PEGS_PER_PLAYER > 3) { homeUnits.push_back({ 35, 14 }); }

	/* Player 3 */
	homeUnits.push_back({ 1, 13 });
	if (PEGS_PER_PLAYER > 1) { homeUnits.push_back({ 3, 13 }); }
	if (PEGS_PER_PLAYER > 2) { homeUnits.push_back({ 3, 14 }); }
	if (PEGS_PER_PLAYER > 3) { homeUnits.push_back({ 5, 14 }); }

	/* Create the main circle (public area) */
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

	/* Create the finish units (finish area) */
	std::vector<std::pair<int, int>> finishUnits;

	/* Player 0 */
	finishUnits.push_back({  9,  3 });
	if (PEGS_PER_PLAYER > 1) { finishUnits.push_back({ 11,  4 }); }
	if (PEGS_PER_PLAYER > 2) { finishUnits.push_back({ 13,  5 }); }
	if (PEGS_PER_PLAYER > 3) { finishUnits.push_back({ 15,  6 }); }

	/* Player 1 */
	finishUnits.push_back({ 29,  3 });
	if (PEGS_PER_PLAYER > 1) { finishUnits.push_back({ 27,  4 }); }
	if (PEGS_PER_PLAYER > 2) { finishUnits.push_back({ 25,  5 }); }
	if (PEGS_PER_PLAYER > 3) { finishUnits.push_back({ 23,  6 }); }

	/* Player 2 */
	finishUnits.push_back({ 29, 11 });
	if (PEGS_PER_PLAYER > 1) { finishUnits.push_back({ 27, 10 }); }
	if (PEGS_PER_PLAYER > 2) { finishUnits.push_back({ 25,  9 }); }
	if (PEGS_PER_PLAYER > 3) { finishUnits.push_back({ 23,  8 }); }

	/* Player 3 */
	finishUnits.push_back({ 9,  11 });
	if (PEGS_PER_PLAYER > 1) { finishUnits.push_back({ 11, 10 }); }
	if (PEGS_PER_PLAYER > 2) { finishUnits.push_back({ 13,  9 }); }
	if (PEGS_PER_PLAYER > 3) { finishUnits.push_back({ 15,  8 }); }

	// Reserve some memory
	BoardUnit unit(0, 0, 0, 0, -1);

	/* Transform the temporary data points into BoardUnit objects. */
	/* Home units */
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

	/* Finish units */
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

	/* Public units */
	for (int i = 0; i < (int)publicUnits.size(); i++)
	{
		unit.Recycle(i, publicUnits[i].first, publicUnits[i].second, AREA_PUBLIC);
		units.push_back(unit);
	}
}

void board::CreateNewPegs()
{
	/* Create PEGS_PER_PLAYER Pegs for each of PLAYER_COUNT players. The pegHandle object is recycled multiple times. */
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
	/* Iterate through all the Pegs and check if their position, area and owner match the parameters.
	 * If owner == -1, ignore ownership of the Pegs.
	 */
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
	/* The following snippet relies on the fact that in current implementation the data structures are initialized
	 * on startup and left unmodified afterwards. In case this changes, this function must be re-evaluated.
	 *
	 * Iterate through all the Pegs and check for the owner. The Pegs are located in memory in fixed order, thus
	 * their position can be used as index.
	 */
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

	/* A Peg is unable to move if any of the following is true:
	 *	It is located in home area
	 *	A Peg is in finish area and there are not enough units in front of it
	 *	A Peg is close to the finish area and there are not enough units in front of it
	 *	A Peg is in finish area and the target unit is occupied by other Peg
	 *	A Peg is in public area and the target unit is occupied by the Peg with the same owner
	 *	A Peg is close to the finish area and the target unit is occupied by other Peg
	 */
	if (area == AREA_HOME
		|| (area == AREA_FINISH && pos + amountOfSpaces >= PEGS_PER_PLAYER)
		|| (area == AREA_PUBLIC && pos < finishPos && pos + amountOfSpaces - finishPos >= PEGS_PER_PLAYER)
		|| (area == AREA_FINISH && board::IsUnitOccupied(pos + amountOfSpaces, AREA_FINISH, owner))
		|| (area == AREA_PUBLIC && pos + amountOfSpaces < finishPos && board::IsUnitOccupied(pos + amountOfSpaces, AREA_PUBLIC, owner))
		|| (area == AREA_PUBLIC && pos < finishPos && pos + amountOfSpaces >= finishPos && board::IsUnitOccupied(pos + amountOfSpaces - finishPos, AREA_FINISH, owner)))
	{
		return false;
	}

	return true;
}

void board::SendPegToHome(int position, int area)
{
	/* Find the Peg to teleport */
	int targetPeg = -1;
	for (int i = 0; i < (int)pegs.size(); i++)
	{
		if (pegs[i].GetArea() == area && pegs[i].GetAreaPosition() == position)
		{
			targetPeg = i;
			break;
		}
	}

	/* No Peg found - stop the execution */
	if (targetPeg == -1)
		return;

	/* Look for a place in the home area and, if found, teleport there */
	for (int i = 0; i < (int)units.size(); i++)
	{
		if (units[i].GetArea() == AREA_HOME && units[i].GetOwner() == pegs[targetPeg].GetOwner()
			&& !IsUnitOccupied(units[i].GetIndex(), AREA_HOME))
		{
			pegs[targetPeg].MoveTo(units[i].GetIndex(), AREA_HOME);
		}
	}
}