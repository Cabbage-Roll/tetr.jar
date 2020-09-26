#ifndef MOVEBLOCK_H
#define MOVEBLOCK_H
void moveBlock(int x, int y,Position* position)
{
    for (int i = 0; i < position->block_size; i+=1)
    {
        for (int j = 0; j < position->block_size; j+=1)
        {
            if(block[i][j] > 0)
            {
                gotoxy(j + position->x,i + position->y);
                printf("  ");
            }
        }
    }

    if(help == ON)
        updateHelp(position,UNISTI);

    position->x = x;
    position->y = y;

    for (int i = 0; i < position->block_size; i++)
    {
        for (int j = 0; j < position->block_size; j++)
        {
            if(block[i][j] > 0)
            {
                colprintxy(block[i][j],position->x + j,position->y + i);
            }
        }
    }
    if(help == ON)
        updateHelp(position,POSTAVI);
}
#endif
