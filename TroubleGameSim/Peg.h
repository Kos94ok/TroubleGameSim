#pragma once

#include "stdafx.h"
#include "settings.h"

/* A class that represents some player's peg. */
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

	/* Peg current location.
	 * 0: Home area, not in play yet
	 * 1: Public area
	 * 2: Finish area
	 */
	int area;

	/* A player who owns this peg.*/
	int owner;

public:
	/* Basic constructor */
	Peg(int pos, int owner)
	{
		this->pos = pos;
		this->owner = owner;
		this->area = troubleGameSim::AREA_HOME;
	}
	/* Recycle the Peg. Helps to prevent the creation of multiple objects during initialization. */
	void Recycle(int pos, int owner)
	{
		this->pos = pos;
		this->owner = owner;
		this->area = troubleGameSim::AREA_HOME;
	}

	/* Calculates and returns the world position of the Peg, based on current area, position and owner. */
	std::pair<int, int> GetWorldPosition();

	/* Public getter methods. Blocks modifications of those variables by outsiders. */
	int GetOwner() { return owner; }
	int GetArea() { return area; }
	int GetAreaPosition() { return pos; }

	/* Move this peg to some position in some area.
	 * In case of AREA_HOME and AREA_FINISH, the target position also depends on the owner.
	 */
	void MoveTo(int pos, int area);
};