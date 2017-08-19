#pragma once

#include "stdafx.h"
#include "settings.h"

namespace troubleGameSim
{
	/* A namespace that contains console input/output-related data and functions */
	namespace io
	{
		/* Buffer for text output */
		extern std::string consoleBufferRaw;
		/* Selected frame buffer */
		extern short activeBuffer;
		/* Frame buffers. Front/back buffer pair is used to compare an old image with a new one and only output the changed characters. */
		extern char consoleBuffer[CONSOLE_BUFFER_COUNT][FRAME_WIDTH][FRAME_HEIGHT];

		/* Display the current turn on the screen */
		void ShowCurrentTurn();
		/* Display the list of available actions */
		void ShowAvailableActions();

		/* Get a single character from the console input without echo and confirmation button */
		int getch();
		/* Move a console caret to specified coordinates */
		void MoveCaretTo(int x, int y);

		/* Output some text. Not shown on the screen until the next buffer swap. */
		void Output(std::string value);
		/* Show a pre-defined header */
		void ShowHeader();
		/* Copy a board representation to the back buffer */
		void ShowBoard(char arr[BOARD_WIDTH][BOARD_HEIGHT]);
		/* Swap the front and back buffers and output all buffered information to the screen */
		void SwapBuffers();
		/* Initialize the frame buffers into whitespaces */
		void ClearBuffers();
		/* Force clear the screen */
		void ForceClear();
	}
}