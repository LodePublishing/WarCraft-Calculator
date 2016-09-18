// DONE: 60 -> MAX_GOALS
// DONE: 3 -> MAX_RACES
// IMPROVED countr <> Race determination

// StarCraft Calculator - Calculates and optimizes build orders
// Copyright (C) 2003 Clemens Lode
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

// See www.clawsoftware.de for updates/news/faq/tutorials etc.

// TODO: replace '60' with the max buildings constant
// TODO: reorganize the CLASSes (private,protected,public entities...)

//CHANGED: 0 Check dazugefuegt fuer Buchstabenzaehler (division durch 0 wenn z.B. Q vorkommt!)
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "human.h"
#include "ork.h"
#include "elves.h"
#include "undead.h"

#include "names.h"
#include "settings.h"
#define HEIGHT 16 // Number of entries (build order list)
#define WIDTH 11 // witdh of the entries
//#define gizmowidth 35

inline unsigned char UpperCase(char x) {if(x>91) return (x-32); else return(x);}

// Here are some global variables (accessible by any class due to 'extern' declaration in 'main.h'
double Harvest_Speed;

unsigned char Ziel[MAX_GOALS],Build_Av[MAX_GOALS],Build_Bv[MAX_GOALS],tgoal[MAX_GOALS]; 
unsigned char Vespene_Av,Max_Build_Types,race,building_types,availible_expansions;
unsigned short total_goals;
unsigned char num,Vespene_Extractors;
GOAL goal[MAX_GOALS]; // GOAL := what buildings should be there AT THE END

RACE * player[MAX_PLAYER];

struct UNIT
{
	char text[162]; //or 161?
} unit[MAX_GOALS];


struct boLog
{
	unsigned char count;
	unsigned char order;
} bolog[MAX_LENGTH],forcelog[MAX_GOALS];

// Ugly functions, have to change them later
void setAt(unsigned char cnt)
{
	if(cnt<4) setup.setColor(37);  //WHITE
	else if(cnt<8) setup.setColor(33); // GREEN
	else if(cnt<16) setup.setColor(32); // ORANGE
	else if(cnt<32) setup.setColor(36); // PURPLE
	else if(cnt<64) setup.setColor(31); // RED
	else setup.setColor(34); // BLUE
};

void setAt2(unsigned char cnt)
{
        if(cnt<=1) setup.setColor(37); //WHITE
        else if(cnt<=2) setup.setColor(33); //GREEN
        else if(cnt<=4) setup.setColor(32); //ORANGE
        else if(cnt<=8) setup.setColor(36); // PURPLE
        else if(cnt<=16) setup.setColor(31); //RED
        else setup.setColor(37); //WHITE
};

struct myBO
{
	unsigned char type,race,length,count;
	unsigned short code[26];
	unsigned short tmp;
} bo[MAX_LENGTH];

struct mySTATS
{
	unsigned short code[26];
        unsigned char length;	
} mystats[MAX_RACES][MAX_GOALS];


int main(int argc, char* argv[])
{	
// TODO: make some significant variables...	
	unsigned short run,rfit,afit,sfit;
	unsigned char counter,gcount;
	char I[11],O[9],R[7];
	char tmp[255];
	unsigned short old_time,old_fit,old,old_t,old_sup,s,t,u,generation,calc;

	//TODO: Check unsigned char <> unsigned short counting variables (especially s,t,u)
	
	unsigned char a,Test,z,tunit,translate,zahl;
	char * buffer;
	char * IOp;
//	char * gizmo;
	unsigned short size;
	int i,j,k,f,countr[MAX_RACES];

	Vespene_Extractors=0;
// TODO: maybe put them to settings	
	race=5;
	Test=0;
	gcount=16;
	tunit=0;
	generation=0;
        run=0;
        afit=0;
        rfit=0;
        sfit=0;
	old=200;
        counter=1;
	old_fit=0;
	translate=0;
	
	
	srand(time(NULL));
	clrscr();
	
	if(setup.InitSettings()==1)
	{
		printf("Error during Setup. Repair / Reinstall the settings.txt file!\n");
	        return(1);
	}
	 
	if(argc<=1)
	{
		printf("HINT: You may directly start wcc also with h, o, e or z as parameter.\n");
		printf("Press ENTER to continue\n");
		a=getchar();
	//	printf("%s",helper);
	//	delete helper;
	}
	else
	{
		if(UpperCase(argv[1][0])=='H')
			race=HUMAN;
		else if(UpperCase(argv[1][0])=='O')
			race=ORC;
		else if(UpperCase(argv[1][0])=='E')
			race=ELVES;
               else if(UpperCase(argv[1][0])=='U')
	                race=UNDEAD;
		else if((argc>2)&&(argv[1][0]=='-'))
		{
			if(UpperCase(argv[1][1])=='I')
			{
				translate=1; // We need a translation of the data later
				IOp = new char [sizeof(argv[2])]; 
				IOp=argv[2];
				FILE * pFile2;
				pFile2 = fopen(IOp,"rb");
				if(pFile2==NULL)
				{
					printf("FATAL ERROR: Build Order File %s not found.\n",IOp);
					printf("Exiting...\n");
					return(1);
				}
				printf("Checking build order input file [%s]...\n",IOp);
				printf("File found. Opening...\n");
				printf("File opened... reading...\n");
			        fseek (pFile2, 0, SEEK_END);
				size = ftell (pFile2);
				buffer = new char [size];
				fseek (pFile2, 0, SEEK_SET);
				fread(buffer,1,size,pFile2);
				fclose(pFile2);
				printf("File closed, data saved [%i Bytes].\n",size);
			} else  // not 'I'
	// B? User called 'scc' with a goal / build order list as parameter
			if(UpperCase(argv[1][1])=='B')
			{
				translate=1; // we need a translation of the data later
				size=0;
				for(t=2;t<argc;t++)
					size+=sizeof(argv[t])+100;
			//TODO: Find a better formula for size (segmentation faults!)	
				buffer = new char [size];
				for(t=0;t<size;t++)
					buffer[t]=0;
				s=0;
// Analyze the parameters and copy them into a buffer
				for(t=2;t<argc;t++)
				{
					u=0;
					if((argv[t][0]>47)&&(argv[t][0]<58))
					{
						while((argv[t][u]>47)&&(argv[t][u]<58))
						{
							buffer[s+u]=argv[t][u];
							u++;
						}
						s+=u;
						t++;
						u=0;
					}
					if(t<argc)
					{
						while(argv[t][u]>64)
						{
							buffer[s]=argv[t][u];
							u++;s++;
						}
					}
					buffer[s]=10;
					s++;
				}
			} else //not 'B', not 'I'
			{
//				printf("%s",helper);
//			        delete helper;
				return(1);
			}
	         } else //not '-'
		 {
//                 	printf("%s",helper);
//			delete helper;
			return(1);
		 }			 
	} // end of 'not argc<=1'
				
//TODO!! inform the user about the abort...			
	if(translate==1)
	{
		printf("Translating data...");
		
		for(t=0;t<MAX_LENGTH;t++)
		{
			for(s=0;s<26;s++) bo[t].code[s]=0;
			bo[t].type=0;
			bo[t].race=5;
			bo[t].length=0;
		}
		s=0;t=0;
		zahl=0;	
		 
		while(s<size)
		{		
			//TODO: DOS / LINUX compability, next line 1310 <=> 10 !?
					
			//translate the parameter arguments buffer to actual goals	
			if(buffer[s]==10)
			{
				if(zahl==0)
					t++;
				else 				
					bo[t].count=0;
				zahl=0;
			}
			else if((buffer[s]>47)&&(buffer[s]<58))
			{
				if((s<size-2)&&(buffer[s+2]>47)&&(buffer[s+2]<58))
				{
					setup.setColor(31);
					printf("FATAL ERROR: Count too high! Do not use larger numbers than 99!\n");
					setup.setColor(37);
					printf("Exiting...\n");
					return(1);
				}
				if((s<size-1)&&(buffer[s+1]>47)&&(buffer[s+1]<58))
				{
					zahl=(buffer[s]-48)*10+(buffer[s+1]-48);
					s++;
				}
				else zahl=buffer[s]-48;
			}
			else if(buffer[s]>64)
			{
				bo[t].code[(int)(UpperCase(buffer[s])-65)]++;
				bo[t].length++;
				if(zahl>0)
					bo[t].count=zahl;
				else if(bo[t].count==0)
					bo[t].count=1;
				zahl=0;
			}
			s++;
		} // end of buffer checking

		//calculate the relative frequency of letters
		for(t=0;t<MAX_LENGTH;t++)
       	        	if(bo[t].length>0)
				for(s=0;s<26;s++)
				{
					bo[t].code[s]*=100;
					bo[t].code[s]=bo[t].code[s]/bo[t].length;
				}
		delete buffer;

		//Create lists with numbers of chars of the names in stats 	
		for(i=0;i<MAX_RACES;i++)
			for(j=0;j<MAX_GOALS;j++)
			{
				mystats[i][j].length=0;
				for(t=0;t<26;t++)
					mystats[i][j].code[t]=0;
				
				for(t=0;t<NAME_LENGTH;t++)
					if(stats[i][j].name[t]>64)
					{
						mystats[i][j].length++;
						mystats[i][j].code[(int)(UpperCase(stats[i][j].name[t])-65)]++;
					}
				for(t=0;t<26;t++)
				if(mystats[i][j].length>0)
				{
					mystats[i][j].code[t]*=100;
					mystats[i][j].code[t]=mystats[i][j].code[t]/mystats[i][j].length;
				}
				else  mystats[i][j].code[t]=0;
			} // End of creating relative frequencies out of stats names
			
		// Calculate the distance between the parameter and the stats names
		int Distance;
		for(k=0;k<MAX_LENGTH;k++)
			if(bo[k].count>0)
			{
				f=60000;
				for(i=0;i<MAX_RACES;i++)
					for(j=0;j<60;j++)
					{
						Distance=0;
						for(t=0;t<26;t++)
							Distance+=bo[k].code[t]*bo[k].code[t]+mystats[i][j].code[t]*mystats[i][j].code[t]-2*bo[k].code[t]*mystats[i][j].code[t];
						if(f>Distance)
						{
							f=Distance;
							bo[k].race=i;
							bo[k].type=j;
							bo[k].tmp=f;
						}
					}
			} // end of calculating distance
		for(i=0;i<MAX_RACES;i++)
			countr[i]=0;
// Counter to determine the race on basis of the frequency of races in the accumulated bo-data...
		for(i=0;i<MAX_LENGTH;i++)
			if(bo[i].race<MAX_RACES)
				countr[bo[i].race]++;
		race=0;
		for(i=0;i<MAX_RACES;i++)
			if(countr[i]>countr[race]) race=i;

	
//... and recheck the whole data on basis of the new information ( so that all bo's are in the same race...

		for(i=0;i<MAX_LENGTH;i++)
			if((bo[i].race!=race)&&(bo[i].race<MAX_RACES))
			{
				f=60000;
				for(j=0;j<60;j++)
				{
					Distance=0;
					for(t=0;t<26;t++)
					Distance+=(mystats[race][j].code[t]-bo[i].code[t])*(mystats[race][j].code[t]-bo[i].code[t]);
					if(f>Distance)
					{
						f=Distance;
						bo[i].race=race;
						bo[i].type=j;
						bo[i].tmp=f;
					}
				}
			}
		//end of race-recheck
				
		if((argc>3)&&(argv[argc-1][0]=='-')&&(UpperCase(argv[argc-1][1])=='T'))
			Test=2;
		else Test=1;

		setup.setColor(32);
		printf(" ok\n");
		setup.setColor(37);
	
	}
			 
	//TODO: input additional arguments (like 'using defaults', scouttime or everything in settings.txt
	//TODO: Improve the implementation of parameter checking... looks really confusing 
	//Especially the order of the parameters...
	
	if(race==5)
	{
		printf("Press '1' for Human, '2' for Orc, '3' for Elves or '4' for Undead.\n");
		while(race==5)
		{
			a=getchar();	
			if(((a-49)>=0)&&((a-49)<MAX_RACES)) race=a-49;
		}
	}

	printf("Setting Race ... ");
	
	switch(race)
	{
		case HUMAN:sprintf(I,"goal_h.txt");sprintf(O,"bo_h.txt");sprintf(R,"Human");break;
		case ORC:sprintf(I,"goal_o.txt");sprintf(O,"bo_o.txt");sprintf(R,"Orc");break;
		case ELVES:sprintf(I,"goal_e.txt");sprintf(O,"bo_e.txt");sprintf(R,"Elves");break;
		case UNDEAD:sprintf(I,"goal_u.txt");sprintf(O,"bo_u.txt");sprintf(R,"Undead");break;
		default:printf("not enough arguments");return 0;break;
	}
	printf("[%s]",R);
	setup.setColor(32);
	printf(" ok\n");
	setup.setColor(37);

	if(Test==0)
	{
		if(setup.InitGoal(I)==1)
		{
			printf("Error during Setup. Repair / Reinstall the %s file!\n",I);
		        return(1);
		}
	}
	
	printf("Initializing player models...\n");
	Player_Human playerh[MAX_PLAYER];
	Player_Human Saveh[RUNNINGS];
	Player_Orc playero[MAX_PLAYER];
	Player_Orc Saveo[RUNNINGS];
	Player_Elves playere[MAX_PLAYER];
	Player_Elves Savee[RUNNINGS];
        Player_Undead playeru[MAX_PLAYER];
        Player_Undead Saveu[RUNNINGS];

	
	RACE * Save[RUNNINGS];
	RACE * tempp; 	
// TODO: Looks pretty hacked... maybe implement a better method later to allow the virtual construction in RACE
	if(race==HUMAN)
	{
		Harvest_Speed=0.8;
		for(s=0;s<MAX_PLAYER;s++)
			player[s]=&playerh[s];
		for(s=0;s<RUNNINGS;s++)
			Save[s]=&Saveh[s];
	}
	else if(race==ORC)
	{
		Harvest_Speed=0.8;
		for(s=0;s<MAX_PLAYER;s++)
			player[s]=&playero[s];
		for(s=0;s<RUNNINGS;s++)
			Save[s]=&Saveo[s];
	}
	else if(race==ELVES)
	{
		Harvest_Speed=0.62;
		for(s=0;s<MAX_PLAYER;s++)
			player[s]=&playere[s];
		for(s=0;s<RUNNINGS;s++)
			Save[s]=&Savee[s];
	} else if(race==UNDEAD)
	{
		Harvest_Speed=1.33;
		for(s=0;s<MAX_PLAYER;s++)
			player[s]=&playeru[s];
		for(s=0;s<RUNNINGS;s++)
			Save[s]=&Saveu[s];
	}
		 
	Max_Build_Types=0;

	if(Test>0)
	{
		for(s=0;s<MAX_GOALS;s++)
		{
			goal[s].what=0;
			goal[s].time=0;
		}
		for(s=0;s<MAX_LENGTH;s++)
			if(bo[s].count>0)
				goal[bo[s].type].what+=bo[s].count;		
	}

	// Sets additional goals, say the user enters "Guardien" Set_Goals will also set Hive, Greater Spire, Lair, Queens Nest, Extractor and Spawning Pool as a goal
	player[0]->Set_Goals(); 
		 
	// Maybe just do 4 different functions instead of a function for every member of the class as it affects only global variables
	
	//Translate from [0..Max_Build_Types] to [0..building_types]
	//Max_Build_Types is goal specific, building_types only depends on the race
	for(s=0;s<Max_Build_Types;s++)
		Build_Bv[Build_Av[s]]=s; 

	setup.AdjustMining();
			 
	if(Test<2)
		for(s=0;s<MAX_PLAYER;s++)
			player[s]->Restart();
	//Test == 2 => "-T" Parameter, just run a single run to determine the time it needs
	else if(Test==2) 
	{
		z=0;
		player[0]->Init();
		for(t=0;t<MAX_LENGTH;t++)
			if(bo[t-z].count>0)
			{
				u=bo[t-z].count; //Translate the build order say 1: "5 marines" in 1: Marine, 2: Marine, ..., 5: Marine
				while((t<MAX_LENGTH)&&(u>0))
				{
					player[0]->program[t].order=Build_Bv[bo[t-z].type];
					u--;z++;
					player[0]->program[t].time=20000;
					player[0]->program[t].built=0;
					t++;

					//~~~~
				}
				z--;t--;
			}
				else 
				{
					player[0]->program[t].order=255;
					player[0]->program[t].time=20000;
					player[0]->program[t].built=0;	
				}
		
		// "scc -b Drone" results in a goal[DRONE].what == 5
			for(s=0;s<building_types;s++)
				if(player[0]->force[s]>0)
					goal[s].what+=player[0]->force[s];
			player[0]->readjust_goals(); // actually affects only zerg (and archon of the protoss)

			printf("Translated goals:\n");
			for(s=0;s<building_types;s++)
				if(goal[s].what>0)
					printf("%s : %i\n",stats[race][s].name,goal[s].what); 
			printf("\nPress Enter to show time\n");

			a=getchar();
			player[0]->timer=setup.Max_Time;
			player[0]->IP=0;

			player[0]->Calculate();

		//print out all orders that are executed without problems
			printf("Successful build order:           [Requirement fulfilled]\n");
			for(s=0;s<MAX_LENGTH;s++)
				if(player[0]->program[s].built==1)
			printf("    %s [%.2i:%.2i] %s\n",stats[race][Build_Av[player[0]->program[s].order]].name,player[0]->program[s].time/60,player[0]->program[s].time%60,error_m[player[0]->program[s].success]);
				else s=MAX_LENGTH;
				
			printf("Needed Time: ");	
			setup.setColor(32);
			printf("[%.2i:%.2i] ",player[0]->timer/60,player[0]->timer%60);
			setup.setColor(37);
	
		// no solution? probably forgot a tech building or supply
			if(player[0]->timer==setup.Max_Time)
			{
				printf("\n => invalid build order, goals not reached.\n");	
				s=0;
			//determine the order which could not be executed
				while(s<MAX_LENGTH)
					if((s+1<MAX_LENGTH)&&(player[0]->program[s+1].built==0))
					{
						printf("When trying to build ");
					        setup.setColor(32);
				       		printf("%s",stats[race][Build_Av[player[0]->program[s].order]].name);
					        setup.setColor(37);
				                printf(" the following requirement failed : \n");
						setup.setColor(31);
						printf("%80s\n",error_m[player[0]->program[s].success]);
					        setup.setColor(37);
						printf("\nCheck your build order, reread the readme and/or contact ClawSoftware :)\n");
						s=MAX_LENGTH;
					} else s++;
				}
			printf("\n");
			return(0);	
	}
        old_time=setup.Max_Time;

	// Creating Unit text... (right bottom corner)
/*	for(s=0;s<60;s++)
sprintf(unit[s].text,"              Unit Name: %NAME_LENGTHs    Buildtime: %3i seconds    Minerals : %3i    Gas      : %3i    Supply   : %i    Type     : %i                     ",stats[race][s].name,stats[race][s].BT,stats[race][s].mins,stats[race][s].gas,stats[race][s].supply,stats[race][s].type);*/
                         
			for(s=0;s<MAX_LENGTH;s++)
                                bolog[s].count=0;

	
//some blabla
printf("\n\n OK! System is ready to start. Press Enter to continue... \n");

	a=getchar();



	
	clrscr();
	gotoxy(0,0);

	printf("Welcome to StarCraftCalculator v1.02 [April/07/2003]!\n");
	printf("-------------------------------------\n\n");
	printf("- Check the ""%s"" file to change goals of the BO\n",I);
	printf("  You may change additional settings in the ""settings.txt"" file.\n");
	printf("- If you are new to this program, try to read the readme.txt\n");
	printf("- After the calculation is complete, a new file called %s will be created.\n",O);
        printf("  It contains the build order and some additional informations.\n");
	printf("- Remember: SCC is based on a speed 5 game.\n");

	printf("\n\n");
        printf("Please note:\n");
	printf("            This may take a while.\n");
	printf("            If the 'generations' counter keep jumping back\n");
	printf("            you do not need to worry:\n");
	printf("That is exactly how it should be :)\n\n");
	printf("\nPress Enter to show the goals...\n");	
        a=getchar();
	clrscr();
	gotoxy(0,0);
	printf("\n");
	if(translate==0)
		printf("Goals (as stated in ""%s"")\n",I);
	else printf("Goals (as received from command line)\n");
	
	for(s=0;s<building_types;s++)
		if(goal[s].what>0)
		{
			if(goal[s].time==0)
				printf("- %20s : %2i   (%s) \n",stats[race][s].name,goal[s].what,kurz[race][s].b);
			else printf("- %20s : %2i   (%s) [%.2i:%.2i] \n",stats[race][s].name,goal[s].what,kurz[race][s].b,goal[s].time/60,goal[s].time%60);
		}

	calc=0;
	printf("\n\n");
	printf("Press ENTER to let the calculation start!\n");
	
	a=getchar();
	clrscr();

// OK, lets start the main loop :)
#ifdef WIN32
	SetConsoleActiveScreenBuffer(scr);
#endif

	while(run<RUNNINGS)
	{
		gotoxy(0,0);
	
	  	generation++;
                rfit++;
	        calc++;
		
//TODO: player[0] is not yet initialized as the best build order ... (in the very first run)
// probably the best thing to do is to move the block to the end 
		old_time=player[0]->timer;
		old_fit=player[0]->pFitness; 

		for(s=0;s<MAX_PLAYER;s++)
			(*player[s]).Init();
		for(s=1;s<MAX_PLAYER;s++)
			(*player[s]).Mutate();
		
		for(s=0;s<MAX_PLAYER;s++)
			(*player[s]).Calculate();

// Determine the best build order depending on the primary fitness (needed time and completed goals) and the secondary fitness (gathered resources)		
		for(s=1;s<MAX_PLAYER-1;s++)
			if((player[s]->pFitness>player[0]->pFitness)||((player[s]->pFitness==player[0]->pFitness)&&(player[s]->sFitness>player[0]->sFitness)))
			{
				tempp=player[s];
				player[s]=player[0];
				player[0]=tempp;
			}
		// bigger than afit or sfit? good! We completed another goal or at least a part of it
		// Maybe implement another parameter to deactivate sFitness... will (maybe!) cause faster calculation but worse build orders (in terms of resources)
		if(player[0]->pFitness>afit)
		{
			afit=player[0]->pFitness;
			sfit=player[0]->sFitness;
			rfit=0;
		}
		else if(player[0]->sFitness>sfit)
		{
			sfit=player[0]->sFitness;
			rfit=0;
		}
		
		//Print the screen :)
		if(setup.Verbose==1)
		{
			gotoxy(0,0);

	   	print("Calculating ");

		if(setup.Gizmo==1)
		{
//			print("[");
//			setup.setColor(32);
//			for(s=0;s<gizmowidth;s++)
//			{
//				sprintf(tmp,"%c",gizmo[(calc/2+s)%gizmolength]);
//				print(tmp);
//			}
//			setup.setColor(37);
//			print("]");
		}
		print("  Status:");

		if(gcount<160) gcount++;
		if(player[0]->timer<setup.Max_Time)
		{
			if(old_time>player[0]->timer) gcount=0;
			if(gcount<=16)
			print(" got faster solution! ");
				else
			print(" optimizing resources.");
		}
		else			
		{
			if((old_fit/100)<(player[0]->pFitness/100)) gcount=0;

			if(gcount<=16)
			print(" another goal complete");
			else
			print(" searching . . .      ");
		}
		
		setup.setColor(37);
		gotoxy(1,2);sprintf(tmp,"%i runs and %i+ generations remaining. [Total %i generations]      ",RUNNINGS-run,setup.Max_Generations-rfit,generation);
		print(tmp);
		gotoxy(0,4);
		print("[resources] [time]");
		gotoxy(0,5);
		print("------------------");
		gotoxy(2,6);sprintf(tmp,"  %5.4i",(int)(player[0]->harvested_res[GOLD]+player[0]->harvested_res[WOOD]));
		print(tmp);
		setAt(gcount);
		gotoxy(13,6);if(player[0]->timer<setup.Max_Time) { sprintf(tmp,"%.2i:%.2i",player[0]->timer/60,player[0]->timer%60);print(tmp);} else print(" ---- ");
		
         
	setup.setColor(31);
if((calc%80==0)||(calc%80==1)) setup.setColor(37); else setup.setColor(31);
	gotoxy(20,3);print("     /   / __ __  ___  _");
if((calc%80==2)||(calc%80==3)) setup.setColor(37); else setup.setColor(31);
	gotoxy(20,4);print("    / / / /  /   /  /  /");
if((calc%80==4)||(calc%80==5)) setup.setColor(37); else setup.setColor(31);
	gotoxy(20,5);print("   / / / /  /   /  /  /");
if((calc%80==6)||(calc%80==7)) setup.setColor(37); else setup.setColor(31);
	gotoxy(20,6);print("  /_/_/ /_ /_  /__/. /");
if((calc%80==8)||(calc%80==9)) setup.setColor(37); else setup.setColor(31);
		
		for(s=0;s<MAX_GOALS;s++)
			tgoal[s]=goal[s].what;
//bolog logs how long which build order stands there (you know, the colors ;-)
		//TODO: recognize moved blocks to stress real Mutations
		
		old=200;
		old_t=0;
		old_sup=0;
		counter=1;
		t=0;
		setup.setColor(37);
			
		if(setup.Detailed_Output==1)
		{
			for(s=0;s<5;s++)
                	{
		       			t=0;
		                while((t<HEIGHT)&&(player[0]->program[(s+1)*HEIGHT-t].built==0)) t++;
		               	gotoxy(WIDTH*s+2,25-setup.Console24Lines);//WIN32 1 <> LINUX 0
				if((t<HEIGHT)||(player[0]->program[s*HEIGHT].built>0))
				{
					sprintf(tmp,"[%.2i:%.2i]",player[0]->program[(s+1)*HEIGHT-t].time/60,player[0]->program[(s+1)*HEIGHT-t].time%60);
					print(tmp);
				}
				else print("       ");
			}
			
			t=0;
			for(s=0;s<MAX_LENGTH;s++)
			{
				gotoxy((t/HEIGHT)*WIDTH,9+t%HEIGHT-setup.Console24Lines);
				t++;
				setup.setColor(37);
				if(player[0]->program[s].built==1)
				{
					if(bolog[s].order==player[0]->program[s].order)
                                	{
				        	if(bolog[s].count<160)
							bolog[s].count++;
					} else
					{
						bolog[s].count=0;
						bolog[s].order=player[0]->program[s].order;
					}
					
					setup.setColor(34);
					if(tgoal[Build_Av[player[0]->program[s].order]]>0)
					{
						print("@");
						tgoal[Build_Av[player[0]->program[s].order]]--;
					} else print(" ");
					setup.setColor(35);
					sprintf(tmp,"%c",error_sm[player[0]->program[s].success]);
					print(tmp);
					setAt(bolog[s].count);
					sprintf(tmp,"%s",kurz[race][Build_Av[player[0]->program[s].order]].b);
					print(tmp);
					setup.setColor(37);
					if(player[0]->program[s].need_Supply<100)
						sprintf(tmp," %.2i",player[0]->program[s].need_Supply);
					else sprintf(tmp,"%3i",player[0]->program[s].need_Supply);
					print(tmp);
				}
				else print(" ------    "); 
			}
		}
		else
		{
		for(s=0;(s<MAX_LENGTH)&&(t<3*HEIGHT+3);s++)
		{
			while((player[0]->program[s].built==0)&&(s<MAX_LENGTH-1))
                        	s++;
                        if(old==Build_Av[player[0]->program[s].order]) counter++;
			else if(old<200)
			{
				if(bolog[t].order==old)
	                        {
					if(bolog[t].count<160)
					bolog[t].count++;
				}
                                else
				{
					bolog[t].count=0;
					bolog[t].order=old;
				}
				
				gotoxy((t/(HEIGHT+1))*17,9+t%(HEIGHT+1)-setup.Console24Lines);
				if(counter>1) { sprintf(tmp,"%2i",counter);setup.setColor(35);print(tmp);} else print("  ");
					setAt(bolog[t].count);
				t++;
				sprintf(tmp,"%s",kurz[race][old].b);
				print(tmp);
				setup.setColor(37);
			    sprintf(tmp," %.2i:%.2i ",old_t/60,old_t%60);
				print(tmp);
				setup.setColor(35);
				if(old_sup<100) sprintf(tmp,"%.2i",old_sup); else sprintf(tmp,"%3i",old_sup);
				print(tmp);
				setup.setColor(37);
				counter=1;
				old=Build_Av[player[0]->program[s].order];
				old_t=player[0]->program[s].time;
				old_sup=player[0]->program[s].need_Supply;
			}
			else
			{
				old=Build_Av[player[0]->program[s].order];
				old_t=player[0]->program[s].time;
				old_sup=player[0]->program[s].need_Supply;
			}
		}
		for(s=t;(s<=MAX_LENGTH)&&(s<3*(HEIGHT+1));s++)
		{
			gotoxy((s/(HEIGHT+1))*17,9+s%(HEIGHT+1)-setup.Console24Lines);
			print("  ------       x");
		}
		}

		setup.setColor(37);

		t=4;
		gotoxy(66,3);print("Force:");
		for(s=0;s<building_types;s++)
			if(goal[s].what>0)
			{
				if(forcelog[s].order==player[0]->force[s])
                        	{
		                      if(forcelog[s].count<160)
								forcelog[s].count++;
			        }
                        	else
			        {
				 	forcelog[s].count=0;
				        forcelog[s].order=player[0]->force[s];
				}
				
				setAt(forcelog[s].count);
				gotoxy(70,t);				
				sprintf(tmp,"%s:%2i ",kurz[race][s].b,player[0]->force[s]);
				print(tmp);
				t++;
				if(t>23-setup.Console24Lines) s=building_types;
				
				//Well... it can't print out more than ~20 goals :/ 
			}
		if(t<=23-setup.Console24Lines)
		{
			gotoxy(66,t);
			setup.setColor(37);
			print("non-goals:");
			t++;
			for(s=0;s<building_types;s++)
				if((goal[s].what==0)&&(player[0]->force[s]))
				{
					if(forcelog[s].order==player[0]->force[s])
					{
						if(forcelog[s].count<160)
							forcelog[s].count++;
					}
					else
					{
						forcelog[s].count=0;
						forcelog[s].order=player[0]->force[s];
					}
						setAt(forcelog[s].count);
						gotoxy(70,t);
						sprintf(tmp,"%s:%2i ",kurz[race][s].b,player[0]->force[s]);
						print(tmp);
						t++;
						if(t>23-setup.Console24Lines) s=building_types;
				}
		for(s=0;s<23-t-setup.Console24Lines;s++)
		{
			gotoxy(70,t+s);
			print("         ");
		}
		}
		
/*		if(setup.Gizmo==1)
		{
			setup.setColor(37);
			gotoxy(54,25-setup.Console24Lines);
		 	print("[");
			setup.setColor(33);
	     for(s=0;s<23;s++)
			{
				sprintf(tmp,"%c",unit[tunit].text[(calc/2+s)%(sizeof(unit[tunit].text)-1)]);
				//sizeof correct? mmmh...
				print(tmp);
			}	

			if((calc/2+1)%(sizeof(unit[tunit].text)-1)==0)
			{
				clrscr(); // <- hacked to reduce graphic errors... D:
				tunit=rand()%building_types;
				while(player[0]->force[tunit]==0)
					tunit=rand()%building_types;
			}
		
                setup.setColor(37);
                print("]");
			}*/
		}

// End of Verbose
		
// Core of the Program
// It *works*... though there is probably a better algorithm (exchange of parts of the program instead of just overwriting other build orders that are worse)
		// It's just a hill climbing algorithm... If the Fitness of one program is higher than the other, it is overwritten.
		// Secondary fitness just comes in when primary fitness is equal
// TODO: Test and implement better algorithms for reproduction		
		for(s=1;s<10;s++)
		{
			t=rand()%(MAX_PLAYER-1)+1;
			for(u=0;u<MAX_LENGTH;u++)
			player[t]->program[u].order=player[0]->program[u].order;
			player[t]->pFitness=player[0]->pFitness;
			player[t]->sFitness=player[0]->sFitness;
		}
		for(s=1;s<MAX_PLAYER;s++)
		{
			t=rand()%MAX_PLAYER;
			if((player[s]->pFitness<player[t]->pFitness)||((player[s]->pFitness==player[t]->pFitness)&&(player[s]->sFitness<player[t]->sFitness)))
			{
			for(u=0;u<MAX_LENGTH;u++)
			player[s]->program[u].order=player[t]->program[u].order;
			
			player[s]->pFitness=player[t]->pFitness;
			player[s]->sFitness=player[t]->sFitness;
			}
			
		}
	// Save the program when 'Max_Generations' Generations were no change
	    if(rfit>=setup.Max_Generations)
		{
			rfit=0;
			generation=0;
			for(s=0;s<MAX_LENGTH;s++)
			{
				Save[run]->program[s].order=player[0]->program[s].order;
				Save[run]->program[s].time=player[0]->program[s].time;
				Save[run]->program[s].need_Supply=player[0]->program[s].need_Supply;
				Save[run]->program[s].have_Supply=player[0]->program[s].have_Supply;
				Save[run]->program[s].success=player[0]->program[s].success;
				Save[run]->program[s].built=player[0]->program[s].built;
			}

			Save[run]->pFitness=player[0]->pFitness;
			Save[run]->timer=player[0]->timer;
			for(s=0;s<RESOURCES;s++)
			{
				Save[run]->res[s]=player[0]->res[s];
				Save[run]->harvested_res[s]=player[0]->harvested_res[s];
			}
			
			Save[run]->length=player[0]->length;

			for(s=0;s<building_types;s++)
			{
				Save[run]->force[s]=player[0]->force[s];
				Save[run]->ftime[s]=player[0]->ftime[s];
			}

			if(Test<2)
		        	for(s=0;s<MAX_PLAYER;s++)
			        	player[s]->Restart();
         		else
		        {
				for(s=0;s<MAX_PLAYER;s++)
				{
					for(t=0;t<MAX_LENGTH;t++)
					{
						player[s]->program[t].order=bo[t].type;
						player[s]->program[t].time=20000;
					}
				player[s]->timer=setup.Max_Time;
				player[s]->IP=0;
				player[s]->length=MAX_LENGTH;
				}
			}
			
			afit=0;
			sfit=0;
			old_time=setup.Max_Time; 
			old_fit=0;
			run++;
			for(s=0;s<MAX_LENGTH;s++)
				bolog[s].count=0;
		}
	    if(player[0]->force[13]==255)
		    a=getchar();
	    
	} // end while...

//	delete gizmo;

	//start of the file output block...

// Run canceled before all 5 runs were calculated? => Save the present run
	if(run<RUNNINGS)
	{
		for(s=0;s<MAX_LENGTH;s++)
		{
			Save[run]->program[s].order=player[0]->program[s].order;
			Save[run]->program[s].time=player[0]->program[s].time;
			Save[run]->program[s].have_Supply=player[0]->program[s].have_Supply;
			Save[run]->program[s].need_Supply=player[0]->program[s].need_Supply;
			Save[run]->program[s].success=player[0]->program[s].success;
			Save[run]->program[s].built=player[0]->program[s].built;
		}	
		Save[run]->pFitness=player[0]->pFitness;
		Save[run]->timer=player[0]->timer;
		for(s=0;s<RESOURCES;s++)
		{
			Save[run]->harvested_res[s]=player[0]->harvested_res[s];
			Save[run]->res[s]=player[0]->res[s];
		}
			
		Save[run]->length=player[0]->length;

		for(s=0;s<building_types;s++)
		{
			Save[run]->force[s]=player[0]->force[s];
			Save[run]->ftime[s]=player[0]->ftime[s];
		}
	}
	
	t=0;
//Determine the best run
	if(run>0)
	{
		afit=0;
		sfit=0;
		for(s=0;s<RUNNINGS;s++)
		{
			if((Save[s]->pFitness>afit)&&(Save[s]->timer<setup.Max_Time))
			{
				afit=Save[s]->pFitness;
				t=s;
			}
			else if((Save[s]->pFitness==afit)&&(Save[s]->timer<setup.Max_Time)&&(Save[s]->sFitness>sfit))
			{
				sfit=Save[s]->sFitness;
				t=s;
			}
		}
	}
	clrscr();
	
#ifdef WIN32
	CloseHandle(scr);
#endif

// Even best run did not find a solution?
	if(Save[t]->timer>=setup.Max_Time)
	{
		printf("NO Solution found. This should not happen.\n");
		printf("Please try the following:\n");
		printf(" - Reread all WARNINGS carefully.\n");
	        printf(" - Reduce the amount of goals in %s",I);
		printf(" - Increase Max Time and/or adjust other settings depending on your task\n");
		printf(" - Contact scc@clawsoftware.de. Please include all .txt files and a short description of the problem.\n");
		printf(" - You might also want to check www.clawsoftware.de for updates or read the Forum/SCC page.\n");
		printf(" Press ENTER to quit...\n");
		a=getchar();
		return(1);
	}

// Start saving the data	
	FILE * pFile;
	pFile = fopen(O,"w");
	fprintf(pFile,"---------------------------------------------------\n");
	fprintf(pFile,"---StarCraftCalculator by ClawSoftware.de [v1.02]--\n");
	fprintf(pFile,"---------------------------------------------------\n\n");
	fprintf(pFile,"[----Best solution---]\n\n");
	
	
	fprintf(pFile,"     Time used: %.2i:%.2i minutes\n",Save[t]->timer/60,Save[t]->timer%60);	
	if(race!=2) fprintf(pFile,"     Scouting unit after %.2i:%.2i minutes\n",setup.Scout_Time/60,setup.Scout_Time%60);
	if(setup.Time_to_Enemy>0) fprintf(pFile,"     Time to Enemy: %i seconds\n\n",setup.Time_to_Enemy);
	
	printf("\nHeader saved...");
	
	old=200;
	counter=1;
	for(s=0;s<=Save[t]->length;s++)
	{
		if(setup.Detailed_Output==0)
		{
			while(((Save[t]->program[s].time>=Save[t]->timer)||(Build_Av[Save[t]->program[s].order]>=building_types))&&(s<MAX_LENGTH-1))
				s++;
			if(old==Build_Av[Save[t]->program[s].order]) counter++;
			else if(old<200)
			{
				fprintf(pFile,"     %.2i x %s\n",counter,stats[race][old].name);
				counter=1;
				old=Build_Av[Save[t]->program[s].order];
			}
			else
				old=Build_Av[Save[t]->program[s].order];
		}
		else
			if(Save[t]->program[s].built==1)
				fprintf(pFile,"     [%.2i:%.2i] [%.2i/%.2i] %s [%s]\n",(Save[t]->program[s].time+0)/60,(Save[t]->program[s].time+0)%60,Save[t]->program[s].need_Supply,Save[t]->program[s].have_Supply,stats[race][Build_Av[Save[t]->program[s].order]].name,error_m[Save[t]->program[s].success]);
	}

	printf("Build Order saved...\n");
	
        fprintf(pFile,"\n     ---Force at the end---\n");
		 
	for(s=0;s<building_types;s++)
		if(Save[t]->force[s]>0)
			fprintf(pFile,"     %NAME_LENGTHs : %2i [Last one: %.2i:%.2i]\n",stats[race][s].name,Save[t]->force[s],Save[t]->ftime[s]/60,Save[t]->ftime[s]%60);
	for(s=0;s<RESOURCES;s++)
		fprintf(pFile,"\n     Harvested %s : %i\n",resource[s],(short)(Save[t]->harvested_res[s]));
	for(s=0;s<RESOURCES;s++)
		fprintf(pFile,"     %s at the end: %i\n",resource[s],(short)(Save[t]->res[s]));
	
	fprintf(pFile,"[---------end--------]\n\n");
	printf("First solution [%.2i:%.2i] succesfully saved...\n",Save[t]->timer/60,Save[t]->timer%60);
	printf("Checking for other solutions:\n");
	
/*	unsigned char otherfound=0;
	unsigned char newone=0;
	//~~~~ alles in eine schleife!
	// print out other runs
	if(run>0)
	for(u=0;u<run;u++)
	{
		newone=1;
		for(s=0;s<u;s++)
		{
			newone=newone&&(((short)Save[u]->harvested_mins!=(short)Save[s]->harvested_mins)||
				        ((short)Save[u]->harvested_gas!=(short)Save[s]->harvested_gas)||
				        ((short)Save[u]->timer!=(short)Save[s]->timer)||
				        ((short)Save[u]->mins!=(short)Save[s]->mins)||
				        ((short)Save[u]->gas!=(short)Save[s]->gas));
		}
			
		if((Save[u]->timer<setup.Max_Time)&&(t!=u)&&(newone==1))			
		{
			otherfound=1;
			fprintf(pFile,"[-----%2i. solution---]\n\n",u+1);
			fprintf(pFile,"     Time used: %.2i:%.2i minutes\n",Save[t]->timer/60,Save[u]->timer%60);
			if(race!=2) fprintf(pFile,"     Scouting unit after %.2i:%.2i minutes\n",setup.Scout_Time/60,setup.Scout_Time%60);
			if(setup.Time_to_Enemy>0) fprintf(pFile,"     Time to Enemy: %i seconds\n\n",setup.Time_to_Enemy);
			printf("Header saved... ");
			old=200;
			counter=1;
			for(s=0;s<=Save[u]->length;s++)
			{
				if(setup.Detailed_Output==0)
				{
					while(((Save[u]->program[s].time>=Save[u]->timer)||(Build_Av[Save[u]->program[s].order]>=building_types))&&(s<MAX_LENGTH-1))
						s++;
			if(old==Build_Av[Save[u]->program[s].order]) counter++;
			else if(old<200)
			{
				fprintf(pFile,"     %.2i x %s\n",counter,stats[race][old].name);
				counter=1;
				old=Build_Av[Save[u]->program[s].order];
			}
			else
				old=Build_Av[Save[u]->program[s].order];
		}
		else
		if((Save[u]->program[s].time<Save[u]->timer)&&(Build_Av[Save[u]->program[s].order]<building_types)&&((s==0)||(Save[u]->program[s].time>0)))
			
		fprintf(pFile,"     [%.2i:%.2i] [%.2i/%.2i] %s [%s]\n",(Save[u]->program[s].time+0)/60,(Save[u]->program[s].time+0)%60,Save[u]->program[s].need_Supply,Save[u]->program[s].have_Supply,stats[race][Build_Av[Save[u]->program[s].order]].name,error_m[Save[u]->program[s].success]);
	}

	printf("Build Order saved...\n");

	fprintf(pFile,"\n     ---Force at the end---\n");
	for(s=0;s<building_types;s++)
		if(Save[u]->force[s]>0)
			fprintf(pFile,"     %21s : %3i [Last one: %.2i:%.2i]\n",stats[race][s].name,Save[u]->force[s],Save[u]->ftime[s]/60,Save[u]->ftime[s]%60);

	fprintf(pFile,"\n     Harvested Minerals : %i\n",(short)(Save[u]->harvested_mins));
	fprintf(pFile,"     Harvested Gas      : %i\n",(short)(Save[u]->harvested_gas));
	fprintf(pFile,"     Minerals at the end: %i\n",(short)(Save[u]->mins));
	fprintf(pFile,"     Gas at the end     : %i\n",(short)(Save[u]->gas));
	fprintf(pFile,"[---------end--------]\n\n");
	printf("%i. solution [%.2i:%.2i] succesfully saved...\n",u+1,Save[u]->timer/60,Save[u]->timer%60);
		}
	}
	if(otherfound==0)
	{
		fprintf(pFile,"None found\n");
		printf("None found!\n");
	}*/
       
	fclose (pFile);
	printf("%s closed. All Data were saved.\n\n Thank you for using StarCalc!\n",O);
	printf("Have a nice day and visit www.clawsoftware.de!\n");

	// Have a nice day
	
	//TODO: Recheck the code whether REALLY all pointers / data are deleted/freed...
	
	for(s=0;s<MAX_PLAYER;s++)
		player[s]=NULL;
	for(s=0;s<RUNNINGS;s++)
		Save[s]=NULL;
	return 0;
};

