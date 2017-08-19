
#include "stdafx.h"
#include "io.h"
#include "game.h"
#include "settings.h"

using namespace troubleGameSim;

std::string io::consoleBufferRaw = "";
short io::activeBuffer = 0;
char io::consoleBuffer[CONSOLE_BUFFER_COUNT][FRAME_WIDTH][FRAME_HEIGHT];

void io::ShowCurrentTurn()
{
	/* Turn number */
	io::Output("Turn " + std::to_string(game::currentTurn + 1) + ", player " + std::to_string(game::activePlayer + 1));
	/* If some value has already been rolled, display it as well */
	if (game::rolledValue != -1)
		io::Output("                  Popped value: " + std::to_string(game::rolledValue));
	/* Bottom separator */
	io::Output("\n=====================================================\n");
}

void io::ShowAvailableActions()
{
	/* For each available action, output a text representation */
	std::vector<game::Action> actions = game::GetAvailableActions(game::activePlayer);
	for (int i = 0; i < (int)actions.size(); i++)
	{
		std::string text = "";
		switch (actions[i])
		{
		case game::Action::rollNumber:
			text = "Pop a number";
			break;
		case game::Action::skipTurn:
			text = "Skip this turn";
			break;
		case game::Action::movePeg:
			text = "Move a peg";
			break;
		case game::Action::newPeg:
			text = "Add a new peg";
			break;
		default:
			text = "No localization!";
			break;
		}
		io::Output(std::to_string(i + 1) + ". " + text + "\n");
	}
}

void io::Output(std::string value)
{
	/* Append the new text to a buffer */
	io::consoleBufferRaw.append(value);
}

void io::ShowBoard(char arr[BOARD_WIDTH][BOARD_HEIGHT])
{
	/* Copy the provided board data into frame buffer */
	for (int y = 0; y < BOARD_HEIGHT; y++)
	{
		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			consoleBuffer[activeBuffer][x + BOARD_OFFSET_LEFT][y + HEADER_HEIGHT] = arr[x][y];
		}
	}
}

void io::ShowHeader()
{
	/* Just a predefined text */
	io::Output("=====================================================\n");
	io::Output("                Trouble Game Simulator!\n");
	io::Output("=====================================================\n");
	/* The last line doesn't fit to the header - will be shown under the game board */
	io::Output("=====================================================\n");
}

void io::SwapBuffers()
{
	/* Convert text buffer to frame data */
	short curX = 0, curY = 0;
	for (int i = 0; i < (int)consoleBufferRaw.length(); i++)
	{
		char curChar = consoleBufferRaw[i];
		/* A newline */
		if (curChar == '\n')
		{
			curX = 0;
			curY += 1;
		}
		/* Some other character */
		else
		{
			/* Output the character */
			consoleBuffer[activeBuffer][curX][curY] = curChar;
			/* Advance the cursor */
			curX += 1;
			if (curX >= FRAME_WIDTH)
			{
				curX = 0;
				curY += 1;
			}
		}
		/* Header limit reached - skip the game board */
		if (curY == HEADER_HEIGHT)
			curY += BOARD_HEIGHT;
		/* Height limit reached - cut off the remaining text */
		if (curY >= FRAME_HEIGHT)
			break;
	}
	/* Clear the text buffer */
	consoleBufferRaw.clear();
	/* Compare the frame buffers */
	int backBuffer = 1 - activeBuffer;
	for (int y = 0; y < FRAME_HEIGHT; y++)
	{
		for (int x = 0; x < FRAME_WIDTH; x++)
		{
			if (consoleBuffer[activeBuffer][x][y] != consoleBuffer[backBuffer][x][y])
			{
				/* A difference is found - output the new character */
				io::MoveCaretTo(x, y);
				std::cout << consoleBuffer[activeBuffer][x][y];
			}
		}
	}
	/* Swap the active buffer */
	activeBuffer = 1 - activeBuffer;
	/* Clear the back buffer */
	for (int y = 0; y < FRAME_HEIGHT; y++)
	{
		for (int x = 0; x < FRAME_WIDTH; x++)
		{
			consoleBuffer[activeBuffer][x][y] = ' ';
		}
	}
}

void io::ClearBuffers()
{
	for (int y = 0; y < FRAME_HEIGHT; y++)
	{
		for (int x = 0; x < FRAME_WIDTH; x++)
		{
			for (int i = 0; i < CONSOLE_BUFFER_COUNT; i++)
			{
				consoleBuffer[i][x][y] = ' ';
			}
		}
	}
}

