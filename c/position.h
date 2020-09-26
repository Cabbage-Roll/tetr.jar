#ifndef POSITION_H
#define POSITION_H
int stage[21][12];
int block[4][4];

int block_current=-1;

typedef struct{
    int x,y,block_size,rotation;
}Position;

bool isCollide(int x,int y,int block_size)
{
    for(int i = 0; i < block_size; i += 1)
    {
        for(int j = 0; j < block_size; j += 1)
        {
            if(stage[y + i][x + j] > 0 && block[i][j] > 0)
                return true;
        }
    }
    return false;
}

#endif
