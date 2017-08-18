#pragma once

#include "stdafx.h"
#include "settings.h"

namespace troubleGameSim
{
	namespace io
	{
		extern std::string consoleBufferRaw;
		extern short activeBuffer;
		extern char consoleBuffer[2][64][64];

		void ShowCurrentTurn();
		void ShowAvailableActions();

		int getch();
		void MoveCaretTo(int x, int y);

		void Output(std::string value);
		void ShowHeader();
		void ShowBoard(char arr[BOARD_WIDTH][BOARD_HEIGHT]);
		void SwapBuffers();
		void ClearBuffers();
		void ForceClear();
	}
}