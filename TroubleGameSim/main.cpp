
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
	int in = -1;
	io::ClearBuffers();
	game::StartNewGame();
	while (in != KEYS_EXIT && !game::isCompleted)
	{
		// Display
		io::ShowHeader();
		gfx::DisplayBoardState();

		// Perform the pre-logic
		io::ShowCurrentTurn();
		io::ShowAvailableActions();

		// Flush the buffer
		io::SwapBuffers();

		// Wait for input
		in = io::getch();
		//io::Output(std::to_string(in));

		// Perform the logic
		bool nextTurn = game::PerformAction(game::GetPerformedAction(in, game::activePlayer), game::activePlayer);
		if (nextTurn)
		{
			game::rolledValue = -1;
			game::players[game::activePlayer].hasPoppedThisTurn = false;

			int playersCycled = 0;
			while (playersCycled < PLAYER_COUNT)
			{
				// Increment the variable
				game::activePlayer += 1;
				if (game::activePlayer >= PLAYER_COUNT)
				{
					game::activePlayer = 0;
					game::currentTurn += 1;
				}
				// If a player has not finished the game, break the loop
				if (!game::players[game::activePlayer].HasFinished())
				{
					break;
				}
				// Otherwise, increment a variable and continue
				else
				{
					playersCycled += 1;
				}
			}
			// Mark the game as completed
			if (playersCycled == PLAYER_COUNT)
			{
				game::isCompleted = true;
			}
		}
	}

	// Clear the screen
	io::ForceClear();

	// Determine the players' finishing positions
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

	// Output some finishing text
	std::cout << "=====================================================\n";
	std::cout << "                Game Over!\n";
	std::cout << "=====================================================\n";

	std::cout << " The winner is Player " + std::to_string(first + 1) << std::endl;
	if (PLAYER_COUNT >= 2)
		std::cout << " Second place: Player " + std::to_string(second + 1) << std::endl;
	if (PLAYER_COUNT >= 3)
		std::cout << " Third place: Player " + std::to_string(third + 1) << std::endl;
	if (PLAYER_COUNT >= 4)
		std::cout << " Fourth place: Player " + std::to_string(fourth + 1) << std::endl << std::endl;
	std::cout << " The game took " + std::to_string(game::currentTurn - 1) + " turn(s) to complete." << std::endl << std::endl;

	std::cout << "Press escape to continue..." << std::endl;
	in = -1;
	while (in != 27)
	{
		in = io::getch();
	}

    return 0;
}

