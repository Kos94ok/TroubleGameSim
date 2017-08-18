
#include "stdafx.h"
#include "io.h"
#include "game.h"
#include "settings.h"

using namespace troubleGameSim;

int io::getch()
{
	return _getch();
}

void io::MoveCaretTo(int x, int y)
{
	HANDLE hCon;
	COORD cPos;

	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	cPos.X = x;
	cPos.Y = y;
	SetConsoleCursorPosition(hCon, cPos);
}