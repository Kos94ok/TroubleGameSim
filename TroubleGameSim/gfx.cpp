
#include "stdafx.h"
#include "io.h"
#include "gfx.h"
#include "game.h"
#include "settings.h"
#include "board.h"

using namespace troubleGameSim;

void gfx::DisplayBoardState()
{
	// Construct a board
	char boardState[BOARD_WIDTH][BOARD_HEIGHT];
	for (int y = 0; y < BOARD_HEIGHT; y++)
	{
		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			boardState[x][y] = ' ';
		}
	}
	for (int i = 0; i < (int)board::units.size(); i++)
	{
		std::pair<int, int> unitPos = board::units[i].GetPosition();
		boardState[unitPos.first][unitPos.second] = '*';
	}

	for (int i = 0; i < (int)board::pegs.size(); i++)
	{
		std::pair<int, int> unitPos = board::pegs[i].GetWorldPosition();
		boardState[unitPos.first][unitPos.second] = 49 + board::pegs[i].GetOwner();
	}

	io::ShowBoard(boardState);

	//io::Output("Turn " + std::to_string(game::currentTurn));
}