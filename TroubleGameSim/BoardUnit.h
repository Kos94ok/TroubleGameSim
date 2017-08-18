#pragma once

#include "stdafx.h"
#include <utility>

class BoardUnit
{
private:
	int id;
	int area;
	std::pair<int, int> boardPos;
	int ownerPlayer;

public:
	BoardUnit(int index, int x, int y, int area, int ownerPlayer = -1)
	{
		this->id = index;
		this->boardPos = { x, y };
		this->area = area;
		this->ownerPlayer = ownerPlayer;
	}

	void Recycle(int index, int x, int y, int area, int ownerPlayer = -1)
	{
		this->id = index;
		this->boardPos = { x, y };
		this->area = area;
		this->ownerPlayer = ownerPlayer;
	}

	int GetIndex() { return id; }
	int GetArea() { return area; }
	int GetOwner() { return ownerPlayer; }
	std::pair<int, int> GetPosition() { return boardPos; }
};