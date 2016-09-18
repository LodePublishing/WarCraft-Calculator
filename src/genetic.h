#ifndef __GENETIC_H
#define __GENETIC_H

#include "main.h"

// The center of the storm!

struct Program
        {
                unsigned char order,location,need_Supply,have_Supply,success,built;
                unsigned short time,temp,res[RESOURCES];
                unsigned char mutate; //from where did it came
                unsigned char newmut;
        };

class GENETIC
{
	public:
		void Mutate();
		Program program[MAX_LENGTH][2];
		unsigned char IP;
		unsigned char protein[MAX_GOALS];	
		unsigned char length;

}


#endif
