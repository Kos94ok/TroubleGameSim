
#include "stdafx.h"
#include "io.h"
#include "game.h"
#include "settings.h"

using namespace troubleGameSim;

/* Linux implementation of a getch() function */
int io::getch()
{
	/* Reference:
	 * https://stackoverflow.com/questions/7469139/what-is-equivalent-to-getch-getche-in-linux
	 */

    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    return (int)buf;
}

/* Reference:
 * https://stackoverflow.com/questions/26423537/how-to-position-the-input-text-cursor-in-c
 */
void io::MoveCaretTo(int x, int y)
{
	printf("\033[%d;%dH", (y + 1), (x + 1));
}

void io::ForceClear()
{
    printf("\033[H\033[J");
}
