#pragma once

#include "stdafx.h"
#include <utility>

/* A class that represents a position on the game board. A unit is occupied when
 * there is some Peg having the same area and position. In case of AREA_HOME and
 * AREA_FINISH, the owner must also be the same.
 */
class BoardUnit
{
private:
	/* The unit index in the area it occupies. */
	int id;
	/* The area where the unit is located. */
	int area;
	/* The owning player for this unit.
	 * For AREA_PUBLIC, always set to -1
	 */
	int ownerPlayer;
	/* A pair of coordinates to represent the unit position on the game board. */
	std::pair<int, int> boardPos;

public:
	/* Basic constructor */
	BoardUnit(int index, int x, int y, int area, int ownerPlayer = -1)
	{
		this->id = index;
		this->boardPos = { x, y };
		this->area = area;
		this->ownerPlayer = ownerPlayer;
	}
	/* Recycle the unit. Helps to prevent the creation of multiple objects during initialization. */
	void Recycle(int index, int x, int y, int area, int ownerPlayer = -1)
	{
		this->id = index;
		this->boardPos = { x, y };
		this->area = area;
		this->ownerPlayer = ownerPlayer;
	}

	/* Public getter methods. Blocks modifications of those variables by outsiders. */
	int GetIndex() { return id; }
	int GetArea() { return area; }
	int GetOwner() { return ownerPlayer; }
	std::pair<int, int> GetPosition() { return boardPos; }
};