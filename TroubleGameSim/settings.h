#pragma once

namespace troubleGameSim
{
	/* A key code to close the game. Default: 27 [Escape] */
	const short KEYS_EXIT = 27;

	/* Frame buffer count. Default: 2 */
	const short CONSOLE_BUFFER_COUNT = 2;
	/* The height of the game frame in console characters. Default: 64 */
	const short FRAME_HEIGHT = 64;
	/* The width of the game frame in console characters. Default: 64 */
	const short FRAME_WIDTH = 64;
	/* The height of the game board. Default: 16 */
	const short BOARD_HEIGHT = 16;
	/* The width of the game board. Default: 40 */
	const short BOARD_WIDTH = 40;
	/* The game board offset from the top border of the screen. Default: 3 */
	const short HEADER_HEIGHT = 3;
	/* The game board offset from the left border of the screen. Default: 7 */
	const short BOARD_OFFSET_LEFT = 7;

	/* The coded values for areas. Can have any values, but should never match. */
	const short AREA_HOME = 0;
	const short AREA_PUBLIC = 1;
	const short AREA_FINISH = 2;

	/* The amount of players in the game. Affects the game board. Accepts any value in range [1; 4]. Default: 4 */
	const short PLAYER_COUNT = 4;
	/* The amount of Pegs created per player. Affects the game board. Accepts any value in range [1; 4]. Default: 4 */
	const short PEGS_PER_PLAYER = 4;
	/* The amount of units in the public area. Incorrect value will break the game. Default: 28 */
	const short PUBLIC_AREA_LENGTH = 28;
}