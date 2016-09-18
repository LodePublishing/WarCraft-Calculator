#ifndef __INIT_H
#define __INIT_H

struct myBO
{
	unsigned char type,race,length,count;
	unsigned short code[26];
	unsigned short tmp;
};

extern myBO bo[];
extern void Init();
extern unsigned char TranslateData(int argc, char* argv[]);
#endif
		
