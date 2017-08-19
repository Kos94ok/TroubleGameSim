
#include "stdafx.h"
#include "Peg.h"
#include "settings.h"
#include "board.h"

using namespace troubleGameSim;

std::pair<int, int> Peg::GetWorldPosition()
{
	/* Iterate through all the units until the one with matching parameters is found. */
	for (int i = 0; i < (int)board::units.size(); i++)
	{
		if (board::units[i].GetIndex() == pos
			&& board::units[i].GetArea() == area
			&& (area == AREA_PUBLIC || board::units[i].GetOwner() == owner))
		{
			return board::units[i].GetPosition();
		}
	}
	return { -1, -1 };
}

void Peg::MoveTo(int pos, int area)
{
	this->pos = pos;
	this->area = area;
}