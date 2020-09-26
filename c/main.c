#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32
#define ESC 27
#define ENTER 13


#include "blocklist.h"
#include "bags.h"
#include "rotate.h"
#include "printing.h"
#include "help.h"
#include "position.h"
#include "tspin.h"
#include "kicktable.h"

int lines=0;
int next_blocks=5;
int gameover = 0;
int score = 0, counter = 0;
int block_hold = -1;
bool held=false;




void updateScore()
{
    held=false;
    gotoxy(-10,17);
    if(spun){
        setcolor(13);
        printf("T SPIN");
        PlaySound("tada.wav", NULL, SND_ASYNC);
        score+=lines*1000;
    }else if(lines==4){
        setcolor(3);
        PlaySound("Windows Unlock.wav", NULL, SND_ASYNC);
        printf("FOUR");
    }else{
        printf("      ");
    }

    spun=false;
    gotoxy(-10,15);
    setcolor(7);
    printf("Score: ");
    setcolor(14);
    printf("%6d",score);
}




int title()
{
    system("cls");
    printf("\tControls\n");
    printf("\tRotate CCW: Y/Z\n");
    printf("\tRotate CW: X\n");
    printf("\tRotate 180: UP\n");
    printf("\tHold: C\n");
    printf("\tHard drop: SPACE\n");
    printf("\tSoft drop: DOWN\n");
    printf("\tMove left: LEFT\n");
    printf("\tMove right: RIGHT\n");
    printf("\tPress 1 to start\n");
    printf("\tL to die\n");
    printf("\n\n\tNEXT BLOCKS: %i\n", next_blocks);
    printf("\t2 to decrease\n");
    printf("\t3 to increase\n");
    int input;
    do{
        input = getch();
    }while(input!= '1' && input != '2' && input !='3');

    if(input == '2'){
        if(next_blocks>0){
            next_blocks--;
        }
        title();
    }

     if(input == '3'){
        if(next_blocks<7){
            next_blocks++;
        }
        title();
    }
    return input;
}

void makenextblock(Position* position)
{
    position->x = 4;
    position->y = 0;
    position->rotation = 0;
    ///the first block
    block_current = bag1[0];
    if(bag1[0] == -1){
        shiftbag1();
    }

    shiftbag1();


    ///show next block
    for(int k=0;k<next_blocks;k++){
        for(int i = 0; i < 4; i += 1)
        {
            for(int j = 0; j < 4; j += 1)
            {
                if(block_list[bag1[k]][i][j] == 0)
                {
                    gotoxy(13 + j, 0 + i + k*4);
                    printf("  ");
                }
                else
                {
                    colprintxy(block_list[bag1[k]][i][j],j + 13, i + 0 + k*4);
                }
            }
        }
    }

    ///i or o
    ///iojstzl
    if(block_current == 2 || block_current == 4)
        position->block_size = 4;
    else
        position->block_size = 3;
    ///spawn block
    for(int i = 0; i <= position->block_size; i += 1)
    {
        for(int j = 0; j < position->block_size; j += 1)
        {
            block[i][j] = block_list[block_current][i][j];
        }
    }
    ///block out
    for(int i = 0; i < position->block_size; i += 1)
    {
        for(int j = 0; j < position->block_size; j += 1)
        {
            if(stage[i][j + position->x] > 0 && block[i][j] > 0)
            {
                gameover = true;
                return;
            }
            else if(block[i][j] > 0)
            {
                colprintxy(block[i][j],j + position->x,i);
            }
        }
    }
    if(help == ON)
        updateHelp(position,POSTAVI);
}

void initGame(Position* position)
{
    system("cls");
    for(int y = 0; y < 21; y += 1)
    {
        for(int x = 0; x < 12; x += 1)
        {
            if(x == 0 || x == 11 || y == 20)
            {
                stage[y][x] = 1;
                colprintxy(7,x,y);
            }
            else
            {
                stage[y][x] = 0;
                gotoxy(x,y);
                printf("  ");
            }
        }
    }
    score = 0;
    held=false;
    gameover = 0;
    bag1[0] = -1;
    block_hold = -1;
    generatebag2();
    for(int i=0;i<7;i++){
        bag1[i]=bag2[i];
    }
    generatebag2();
    updateScore();
    makenextblock(position);
}


void dropBlock(Position* position)
{
    int lines = 0;
    while(!isCollide(position->x, position->y + 1, position->block_size))
    {
        lines += 1;
        moveBlock(position->x, position->y + 1, position);
    }
    score += lines;
    updateScore();
    counter = 100;
}

void holdBlock(Position* position){
    int temp;

    if(held==false){

        for(int i = 0; i < 4; i += 1)
        {
            for(int j = 0; j < 4; j += 1)
            {
                if(block_list[block_current][i][j] == 0)
                {
                    gotoxy(-7 + j, 3 + i);
                    printf("  ");
                }
                else
                {
                    colprintxy(block_list[block_current][i][j],j - 7, i + 3);
                }
            }
        }

        for (int i = 0; i < 4; i+=1)
        {
            for (int j = 0; j < 4; j+=1)
            {
                if(block[i][j] > 0)
                {
                    gotoxy(j + position->x,i + position->y);
                    printf("  ");
                }
            }
        }

        if(block_hold == -1)
        {
            block_hold=block_current;
            makenextblock(position);
        }
        else
        {
            temp=block_current;
            block_current=block_hold;
            block_hold=temp;
            position->x = 4;
            position->y = 0;
            position->rotation=0;
            if(block_current == 2 || block_current == 4)
                position->block_size = 4;
            else
                position->block_size = 3;
            for(int i = 0; i < position->block_size; i += 1){
                for(int j = 0; j < position->block_size; j += 1){
                    block[i][j] = block_list[block_current][i][j];
                }
            }
        }
    }else{

    PlaySound("bruh.wav", NULL, SND_ASYNC);
    }
    held=true;
}

void userInput(Position* position)
{
    int input = getch();

    if(input == 224)
        input = getch();

    switch (input)
    {
    case RIGHT:
        if (!isCollide(position->x + 1, position->y,position->block_size))
        {
            moveBlock(position->x + 1, position->y,position);
        }
        break;
    case LEFT:
        if (!isCollide(position->x - 1, position->y,position->block_size))
        {
            moveBlock(position->x - 1, position->y,position);
        }
        break;
    case DOWN:
        if (!isCollide(position->x, position->y + 1,position->block_size))
        {
            moveBlock(position->x, position->y + 1,position);
        }
        break;
    case 'y':
    case 'Y':
    case 'z':
    case 'Z':
        rotateBlock(position,CCW);
        break;
    case 'x':
    case 'X':
        rotateBlock(position,CW);
        break;
    case SPACE:
        dropBlock(position);
        break;
    case UP:
        rotateBlock(position,R180);
        break;
    case 'j':
    case 'J':
        help = (help == ON) ? OFF : ON;
        updateHelp(position,(help == ON) ? POSTAVI : UNISTI);
        break;
    case 'c':
    case 'C':
        holdBlock(position);
        break;
    case 'l':
    case 'L':
        gameover=1;
        break;
    }
}

void checkPlaced(Position* position)
{
    bool lineclean;
    lines = 0;
    for(int i = position->y; i < 20 && i < (position -> y + position -> block_size); i += 1)
    {
        lineclean = true;
        for(int j = 1; j < 11; j += 1)
        {
            if(stage[i][j] == 0)
            {
                lineclean = false;
                break;
            }
        }
        if(lineclean)
        {
            for(int j=1;j<11;j++){
                stage[0][j] = 0;
                gotoxy(j,0);
                printf("  ");
            }
            lines += 1;
            for(int k = i; k > 0; k -= 1)
            {
                for(int j = 1; j < 11; j += 1)
                {
                    stage[k][j] = stage[k - 1][j];
                    if(stage[k][j] > 0)
                    {
                        colprintxy(stage[k][j],j,k);
                    }
                    else
                    {
                        gotoxy(j,k);
                        printf("  ");
                    }
                }
            }

        }
    }
    switch(lines)
    {
    case 1:
        score += 40;
        break;
    case 2:
        score += 100;
        break;
    case 3:
        score += 300;
        break;
    case 4:
        score += 1200;
        break;
    }
    updateScore();
    }

void gameOver()
{
    system("cls");

    printf("\n\nYour score was:");
    setcolor(14);
    printf(" %6d",score);
    setcolor(7);
    printf("\n\nPress ");
    setcolor(10);
    printf("ENTER ");
    setcolor(7);
    printf("to restart game...\n");
    printf("\nPress ");
    setcolor(2);
    printf("ESC");
    setcolor(7);
    printf(" to quit...\n\n");
}


void placeBlock(Position* position)
{
    int q = 0;
    for(int i = 0; i < position->block_size; i += 1)
    {
        for(int j = 0; j < position->block_size; j += 1)
        {
            if(block[i][j] > 0)
            {
                if(q == 0)
                {
                    q = 1;
                    setcolor(block[i][j]);
                }
                gotoxy(j+position->x,i+position->y);
                printf("%c%c",219,219);
                stage[i + position->y][j + position->x] = block[i][j];
            }
        }
    }
}



int main()
{
    srand(time(NULL));
    if(title()=='0')
    {
        system("cls");
        printf("\n\n");
        return 0;
    }
    int input;
    hidecursor();
    Position position;
    do{
        initGame(&position);
        while(!gameover)
        {
            if(kbhit())
            {
                userInput(&position);
            }
            if(counter == 100)
            {
                if(!isCollide(position.x, position.y + 1, position.block_size))
                {
                    moveBlock(position.x, position.y + 1, &position);
                }
                else
                {
                    placeBlock(&position);
                    checkPlaced(&position);
                    makenextblock(&position);
                }
                counter=0;
            }
            else
               ///0G counter++;
            Sleep(10);
        }
        gameOver();
        do{
            input = getch();
        }while(input != ENTER && input != ESC);
    }while(input == ENTER);
}
