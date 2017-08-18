#pragma once

#include "stdafx.h"
#include "settings.h"

class Peg
{
private:
	/* Peg position. Meaning depends on the context (area).
	 * When in home area:
	 * - Range [0; 3]
	 * When in public area:
	 * - Range [0; 27]
	 * When in finish area:
	 * - Range [0; 3]
	 */
	int pos;
	std::pair<int, int> worldPosition;

	/* Peg current location.
	 * 0: Home area, not in play yet
	 * 1: Public area
	 * 2: Finish area
	 */
	int area;

	/* A player who owns this peg.*/
	int owner;

public:
	Peg(int pos, int owner)
	{
		this->pos = pos;
		this->owner = owner;
		this->area = troubleGameSim::AREA_HOME;
		worldPosition = { -1, -1 };
	}
	void Recycle(int pos, int owner)
	{
		this->pos = pos;
		this->owner = owner;
		this->area = troubleGameSim::AREA_HOME;
		worldPosition = { -1, -1 };
	}

	std::pair<int, int> GetWorldPosition();

	int GetOwner() { return owner; }
	int GetArea() { return area; }
	int GetAreaPosition() { return pos; }

	void MoveTo(int pos, int area);
};