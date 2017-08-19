
#include "stdafx.h"
#include "io.h"
#include "gfx.h"
#include "game.h"
#include "settings.h"
#include "board.h"

using namespace troubleGameSim;

void gfx::DisplayBoardState()
{
	/* Construct an empty board */
	char boardState[BOARD_WIDTH][BOARD_HEIGHT];
	for (int y = 0; y < BOARD_HEIGHT; y++)
	{
		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			boardState[x][y] = ' ';
		}
	}

	/* For each unit, mark a character */
	for (int i = 0; i < (int)board::units.size(); i++)
	{
		std::pair<int, int> unitPos = board::units[i].GetPosition();
		boardState[unitPos.first][unitPos.second] = '*';
	}

	/* For each Peg, mark another character */
	for (int i = 0; i < (int)board::pegs.size(); i++)
	{
		std::pair<int, int> unitPos = board::pegs[i].GetWorldPosition();
		boardState[unitPos.first][unitPos.second] = 49 + board::pegs[i].GetOwner();
	}
	
	/* Send the board to IO */
	io::ShowBoard(boardState);
}