#ifndef PRINTING_H
#define PRINTING_H

#define colprintxy(color,x,y) {setcolor(color);gotoxy(x,y);printf("%c%c",219,219);}
void gotoxy(int x, int y) {SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x*2+25,y+2});}

void setcolor(int color){
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}


void hidecursor()
{
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
#endif
