#ifndef TSPIN_H
#define TSPIN_H

#include "position.h"
#include <stdio.h>

bool spun=false;

void tspin(Position* position){
    int truth=0;
    if(stage[position->y][position->x]>0)
        truth++;
    if(stage[position->y+2][position->x]>0)
        truth++;
    if(stage[position->y][position->x+2]>0)
        truth++;
    if(stage[position->y+2][position->x+2]>0)
        truth++;
    if(truth>=3){
        spun=true;
    }else{
        spun=false;
    }
}
#endif
