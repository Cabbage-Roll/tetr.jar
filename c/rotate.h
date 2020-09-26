#ifndef ROTATE_H
#define ROTATE_H

#include "help.h"
#include "printing.h"
#include "position.h"
#include "tspin.h"
#include "kicktable.h"
#include "moveblock.h"

#define CCW 0
#define CW 1
#define R180 2

void rotateBlock(Position* position, int d){
    int piece_type=position->block_size-3;
    int special;
    int tries=0;
    int oldrotation=position->rotation;

    int temp[position->block_size][position->block_size];

    if(help == ON)
        updateHelp(position,UNISTI);

    for(int i = 0; i < position->block_size; i += 1)
        for(int j = 0; j < position->block_size; j += 1)
            temp[i][j] = block[i][j];

    if(position->rotation==0 && d==CW)
        special=0;
    else if(position->rotation==1 && d==CCW)
        special=1;
    else if(position->rotation==1 && d==CW)
        special=2;
    else if(position->rotation==2 && d==CCW)
        special=3;
    else if(position->rotation==2 && d==CW)
        special=4;
    else if(position->rotation==3 && d==CCW)
        special=5;
    else if(position->rotation==3 && d==CW)
        special=6;
    else if(position->rotation==0 && d==CCW)
        special=7;


    switch(d){
    case CCW:
        for(int i = 0; i < position->block_size; i += 1){
            for(int j = 0; j < position->block_size; j += 1){
                block[i][j] = temp[j][position->block_size - 1 - i];
            }
        }

        position->rotation--;
        if(position->rotation==-1){
            position->rotation=3;
        }

        break;
    case CW:
        for(int i = 0; i < position->block_size; i += 1){
            for(int j = 0; j < position->block_size; j += 1){
                block[i][j] = temp[position->block_size - 1 - j][i];
            }
        }

        position->rotation++;
        if(position->rotation==4){
            position->rotation=0;
        }

        break;
    case R180:
        for(int i = 0; i < position->block_size; i += 1){
            for(int j = 0; j < position->block_size; j += 1){
                block[i][j] = temp[position->block_size-1-i][position->block_size-1-j];
            }
        }
        position->rotation+=2;
        break;
    }

    for(tries=0;tries<5;tries++){
        if(!(isCollide(position->x+kicks[piece_type][0][special][tries],position->y-kicks[piece_type][1][special][tries],position->block_size))){
            break;
        }

        if(tries==4){
            for (int i = 0; i < position->block_size; i+=1)
            {
                for (int j = 0; j < position->block_size; j+=1)
                {
                    block[i][j] = temp[i][j];
                }
            }
            position->rotation=oldrotation;
            if(help == ON)
                updateHelp(position,POSTAVI);
            return;
        }
    }

    moveBlock(position->x+kicks[piece_type][0][special][tries],position->y-kicks[piece_type][1][special][tries],position);

    ///if it succeeds show it
    for (int i = 0; i < position->block_size; i+=1)
    {
        for (int j = 0; j < position->block_size; j+=1)
        {
            if(stage[position->y + i][position->x + j] == 0 && block[i][j] == 0)
            {
                gotoxy(position->x + j,position->y + i);
                printf("  ");
            }
            else if(block[i][j] > 0)
            {
                colprintxy(block[i][j],position->x + j,position->y + i);
            }
        }
    }


    if(help == ON)
        updateHelp(position,POSTAVI);

    if(block_current==6){
        tspin(position);
    }
}

#endif
