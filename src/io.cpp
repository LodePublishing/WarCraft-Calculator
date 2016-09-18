#include <stdio.h>
#include "io.h"
#include "main.h"

void setColor(unsigned char c)
{
        if(colors==1)
	{
		#ifdef WIN32
		SetConsoleTextAttribute(scr,colorsWin32[c-31]);
		#elif __linux__
		printf("\033[0;%d;40m",c);
		#endif
	}
};

void setAt(unsigned char cnt)
{
        if(cnt<4) setColor(37);  //WHITE
        else if(cnt<8) setColor(33); // GREEN
        else if(cnt<16) setColor(32); // ORANGE
        else if(cnt<32) setColor(36); // PURPLE
        else if(cnt<64) setColor(31); // RED
        else setColor(34); // BLUE
};

/*void setAt2(unsigned char cnt)
{
        if(cnt<=1) setColor(37); //WHITE
        else if(cnt<=2) setColor(33); //GREEN
        else if(cnt<=4) setColor(32); //ORANGE
        else if(cnt<=8) setColor(36); // PURPLE
        else if(cnt<=16) setColor(31); //RED
        else setColor(37); //WHITE
};*/

#ifdef WIN32
HANDLE scr;
void print(const char * x) {DWORD num; WriteConsole(scr,x,strlen(x),&num,0); }
#endif