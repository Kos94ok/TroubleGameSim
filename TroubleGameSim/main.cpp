
#include "stdafx.h"
#include "io.h"
#include "gfx.h"
#include "settings.h"
#include "game.h"
#include "board.h"

#include <fstream>

using namespace troubleGameSim;

int main()
{
	/* Initialize the frame buffers */
	io::ClearBuffers();
	/* Clear the console screen */
	io::ForceClear();
	/* Initialize the game and the board */
	game::StartNewGame();
	/* Start the main loop */
	int in = -1;
	while (in != KEYS_EXIT && !game::isCompleted)
	{
		/* Render the board */
		io::ShowHeader();
		gfx::DisplayBoardState();

		/* Show available actions */
		io::ShowCurrentTurn();
		io::ShowAvailableActions();

		/* Flush changes to screen */
		io::SwapBuffers();

		/* Wait for player input */
		in = io::getch();

		/* Perform selected action */
		bool nextTurn = game::PerformAction(game::GetPerformedAction(in, game::activePlayer), game::activePlayer);
		/* If the player's turn is over, move the turn */
		if (nextTurn)
		{
			/* Reset the variables */
			game::rolledValue = -1;
			game::players[game::activePlayer].hasPoppedThisTurn = false;

			/* Move the turn to next player until a not-yet-finished player found */
			int playersCycled = 0;
			while (playersCycled < PLAYER_COUNT)
			{
				game::activePlayer += 1;
				if (game::activePlayer >= PLAYER_COUNT)
				{
					game::activePlayer = 0;
					game::currentTurn += 1;
				}
				/* A player is found - break the loop */
				if (!game::players[game::activePlayer].HasFinished())
				{
					break;
				}
				/* Otherwise, increment a variable and continue */
				else
				{
					playersCycled += 1;
				}
			}
			/* If iterated on all players and no player still found, the game is completed. */
			if (playersCycled == PLAYER_COUNT)
			{
				game::isCompleted = true;
			}
		}
	}

	/* Clear the screen */
	io::ForceClear();

	/* If the game was completed */
	if (game::isCompleted)
	{
		/* Determine the players' finishing positions */
		int first, second, third, fourth;
		for (int i = 0; i < PLAYER_COUNT; i++)
		{
			switch (game::players[i].GetTrophy())
			{
			case 0:
				first = i;
				break;
			case 1:
				second = i;
				break;
			case 2:
				third = i;
				break;
			case 3:
				fourth = i;
				break;
			}
		}

		/* Show some statistics */
		std::cout << "=====================================================\n";
		std::cout << "                Game Over!\n";
		std::cout << "=====================================================\n";

		std::cout << " The winner is Player " + std::to_string(first + 1) << "\n";
		if (PLAYER_COUNT >= 2)
			std::cout << " Second place: Player " + std::to_string(second + 1) << "\n";
		if (PLAYER_COUNT >= 3)
			std::cout << " Third place: Player " + std::to_string(third + 1) << "\n";
		if (PLAYER_COUNT >= 4)
			std::cout << " Fourth place: Player " + std::to_string(fourth + 1) << "\n";
		std::cout << "\n The game took " + std::to_string(game::currentTurn - 1) + " turn(s) to complete.\n" << std::endl;
	}
	/* If the game was aborted */
	else
	{
		std::cout << "The game was aborted after " + std::to_string(game::currentTurn) + " turn(s).\n" << std::endl;
	}

	/* Show a message and wait for the user to press the escape key */
	std::cout << "Press escape to continue..." << std::endl;
	do
	{
		in = io::getch();
	} while (in != 27);

    return 0;
}
