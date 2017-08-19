
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
	/* Reference:
	 * https://stackoverflow.com/questions/2732292/setting-the-cursor-position-in-a-win32-console-application
	 */

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD caretPosition = { (short)x, (short)y };
	SetConsoleCursorPosition(consoleHandle, caretPosition);
}

void io::ForceClear()
{
	system("cls");
}