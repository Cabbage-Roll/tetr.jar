#ifndef HELP_H
#define HELP_H

#define ON 1
#define OFF 0

#define UNISTI 0
#define POSTAVI 1

#include "position.h"
#include "printing.h"

int help = OFF;

void updateHelp(Position* position,int mode)
{
    int y = position->y;
    while(!isCollide(position->x, y + 1, position->block_size))
    {
        y += 1;
    }
    setcolor(15);
    for(int i = 0; i < position->block_size; i += 1)
    {
        for(int j = 0; j < position->block_size; j += 1)
        {
            if(block[i][j] > 0)
            {
                gotoxy(j+position->x,i+y);
                printf("%c%c",(mode == UNISTI) ? ' ' : 219,(mode == UNISTI) ? ' ' : 219);
            }
        }
    }
}

#endif
