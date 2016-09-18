#ifndef __IO_H
#define __IO_H

#define HEIGHT 16 // Number of entries (build order list)
#define WIDTH 11 // witdh of the entries

inline unsigned char UpperCase(char x) {if(x>91) return (x-32); else return(x);}
extern void setColor(unsigned char c);
extern void setAt(unsigned char cnt);
//extern void setAt2(unsigned char cnt);

#ifdef WIN32
#include <windows.h>
HANDLE scr;
const unsigned char colorsWin32[7]= 
//Translate Linux ANSI Colors to SetConsoleTextAttribute Colors
{
	                FOREGROUND_RED,FOREGROUND_GREEN,FOREGROUND_RED|FOREGROUND_GREEN,FOREGROUND_BLUE,FOREGROUND_RED|FOREGROUND_BLUE,FOREGROUND_GREEN|FOREGROUND_BLUE,FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN
};
void print(const char * x) {DWORD num; WriteConsole(scr,x,strlen(x),&num,0); }
#define clrscr() system("clear");
#define gotoxy(x,y) {COORD pos={(x),(y)}; SetConsoleCursorPosition(scr,pos); }

#elif __linux__
#define clrscr() printf("\033[2J") // Bildschirm loeschen
#define gotoxy(x,y) printf("\033[%d;%dH",(y),(x))
#define print(x) printf((x))
#endif

#endif




