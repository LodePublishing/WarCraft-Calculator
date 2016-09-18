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

// TODO: reorganize the CLASSes (private,protected,public entities...)

//CHANGED: 0 Check dazugefuegt fuer Buchstabenzaehler (division durch 0 wenn z.B. Q vorkommt!)
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "io.h"
#include "human.h"
//#include "ork.h"
//#include "elves.h"
//#include "undead.h"
#include "init.h"
#include "names.h"
#include "settings.h"

//#define gizmowidth 35

#define ALPHA_TIER 5 //in percent
#define ZELL_TEILUNG 5 
#define CROSSING_OVER 25

//96!?
// Here are some global variables (accessible by any class due to 'extern' declaration in 'main.h'
double Harvest_Speed;

unsigned char buildable[MAX_GOALS],Build_Av[MAX_GOALS],Build_Bv[MAX_GOALS],tgoal[MAX_GOALS],Variabel[MAX_GOALS]; 
unsigned char Max_Build_Types,race,colors;
unsigned short total_goals,currentMutation,currentMutationRate,Generations;//,Mut_Window;
unsigned char counter,who_crosses;//,Test;//,tcount;
long totalProteins[MAX_GOALS];
GOAL goal[MAX_GOALS]; // GOAL := what buildings should be there AT THE END
EXPANSION Expansion[MAX_EXPANSIONS];
RACE * player[MAX_PLAYER];
RACE * Save[RUNNINGS];
RACE * tempp;
		
unsigned char Basic[MAX_LENGTH][2],Basic_Length;
/*struct UNIT
{
	char text[162]; //or 161?
} unit[MAX_GOALS];*/


#define MAX_MUT_DISPLAY 3
struct boLog
{
	unsigned char count;
	unsigned char order;
} bolog[MAX_LENGTH],forcelog[MAX_GOALS];

struct mutLog
{
	unsigned char count,from,to;
}
mutlog[MAX_LENGTH][MAX_MUT_DISPLAY];


int compare(const void * a,const void * b)
{
	if(( (*(Player_Human*)a).pFitness<(*(Player_Human*)b).pFitness)||(((*(Player_Human*)a).pFitness==(*(Player_Human*)b).pFitness)&&((*(Player_Human*)a).sFitness<=(*(Player_Human*)b).sFitness)))
		return (1);
	else if(( (*(Player_Human*)a).pFitness>(*(Player_Human*)b).pFitness)|| ((*(Player_Human*)a).sFitness>(*(Player_Human*)b).sFitness))
		return (-1);
	else return(0);
}
				

int main(int argc, char* argv[])
{	
	unsigned short Mutation,MutationRate,run,unchangedRuns,bestPrimaryFitness,bestSecondaryFitness,basicFitness;
	unsigned char counter,gcount,dom,worst;
	char Input[11],Output[9],RaceName[7];
	char tmp[255];
	int race_size=0;
	unsigned short old_bestTime,old_bestPrimaryFitness,old_bestSecondaryFitness,orderTemp,old_Time,old_Food,s,t,u,v,generation,calc,gen_count[RUNNINGS],totalCrossOver,negativeCrossOver,temp_pFitness,temp_sFitness,negative_Crossing_Over,selection;
	
	struct MUTCOUNT
	{
		unsigned char on;
		unsigned char target;
	} mut_count[MAX_MUT_DISPLAY];
	RACE * Child1;
	RACE * Child2;
	long diversity,d2;
	unsigned char a;
//	char * gizmo;
	
	gcount=16;
	generation=0;
        calc=0;
	run=0;
        bestPrimaryFitness=0;
        unchangedRuns=0;
        bestSecondaryFitness=0;
	orderTemp=200;
        counter=1;
	old_bestPrimaryFitness=0;
	old_bestSecondaryFitness=0;
	for(s=0;s<MAX_GOALS;s++) Variabel[s]=0;
        for(s=0;s<MAX_LENGTH;s++) {bolog[s].count=0;for(t=0;t<4;t++) mutlog[s][t].count=0;};
		 
	srand(time(NULL));
//	clrscr();
	
	if(setup.InitSettings()==1)
	{
		print("Error during Setup. Repair / Reinstall the settings.txt file!\n");
	        return(1);
	}
	TranslateData(argc,argv);
	//TODO: input additional arguments (like 'using defaults', scouttime or everything in settings.txt
	//TODO: Improve the implementation of parameter checking... looks really confusing 
	//Especially the order of the parameters...
	if(setup.Verbose==1)
	print("Setting Race and initializing player models... ");
        
	Player_Human playerh[MAX_PLAYER],Saveh[RUNNINGS],Child1h,Child2h;
//	Player_Orc playero[MAX_PLAYER],Saveo[RUNNINGS],Child1o,Child2o;
  //      Player_Elves playere[MAX_PLAYER],Savee[RUNNINGS],Child1e,Child2e; 
//	Player_Undead playeru[MAX_PLAYER],Saveu[RUNNINGS],Child1u,Child2u;
								
	switch(race)
	{
		case HUMAN:
			{
				sprintf(Input,"goal_h.txt");
				sprintf(Output,"bo_h.txt");
				sprintf(RaceName,"Human");
				Harvest_Speed=0.8;
				for(s=0;s<MAX_PLAYER;s++) player[s]=&playerh[s];
				for(s=0;s<RUNNINGS;s++) Save[s]=&Saveh[s];
				Child1=&Child1h;Child2=&Child2h;
				race_size=sizeof(Player_Human);
			};break;
		case ORC:
			{
				sprintf(Input,"goal_o.txt");
				sprintf(Output,"bo_o.txt");
				sprintf(RaceName,"Orc");
				Harvest_Speed=0.8;
//				for(s=0;s<MAX_PLAYER;s++) player[s]=&playero[s];
//				for(s=0;s<RUNNINGS;s++) Save[s]=&Saveo[s];
//				Child1=&Child1o;Child2=&Child2o;
			};break;
		case ELVES:
			{
				sprintf(Input,"goal_e.txt");
				sprintf(Output,"bo_e.txt");
				sprintf(RaceName,"Elves");
				Harvest_Speed=0.62;
//				for(s=0;s<MAX_PLAYER;s++) player[s]=&playere[s];
//				for(s=0;s<RUNNINGS;s++) Save[s]=&Savee[s];
//				Child1=&Child1e;Child2=&Child2e;
			};break;
		case UNDEAD:
			{
				sprintf(Input,"goal_u.txt");
				sprintf(Output,"bo_u.txt");
				sprintf(RaceName,"Undead");
				Harvest_Speed=1.33;
//				for(s=0;s<MAX_PLAYER;s++) player[s]=&playeru[s];
//				for(s=0;s<RUNNINGS;s++) Save[s]=&Saveu[s];
//				Child1=&Child1u;Child2=&Child2u;
			};break;
		default:print("not enough arguments");return 0;break;
	}
	sprintf(tmp,"[%s]",RaceName);print(tmp);setColor(32);print(" ok\n");setColor(37);

//	if(Test==0)
//	{
		if(setup.InitGoal(Input)==1)
		{
			sprintf(tmp,"Error during Setup. Repair / Reinstall the %s file!\n",Input);
			print(tmp);
		        return(1);
		}
//	}
	
	for(s=0;s<MAX_PLAYER;s++)
	setup.AdjustMining();		 
/*	if(Test>0)
	{
		for(s=0;s<MAX_GOALS;s++)
		{
			goal[s].what=0;
			goal[s].time=0;
		}
		for(s=0;s<MAX_LENGTH;s++)
			if(bo[s].count>0)
				goal[bo[s].type].what+=bo[s].count;		
	}*/

	if(setup.Verbose==1) print("Generating valid basic solution...\n");
	
	// Sets additional goals, say the user enters "Guardien" Set_Goals will also set Hive, Greater Spire, Lair, Queens Nest, Extractor and Spawning Pool as a goal
	player[0]->Set_Goals(); 
	Init();
	
	// Maybe just do 4 different functions instead of a function for every member of the class as it affects only global variables
	
 	
//	if(Test<2)
//	{
		player[0]->GenerateBasicBuildOrder();
		for(s=0;s<MAX_PLAYER;s++)
			player[s]->Restart();
//	}
	//Test == 2 => "-T" Parameter, just run a single run to determine the time it needs
/*	else if(Test==2) 
	{
		counter=0;
		player[0]->Init();
		for(t=0;t<MAX_LENGTH;t++)
			if(bo[t-counter].count>0)
			{
				u=bo[t-counter].count; //Translate the build order say 1: "5 marines" in 1: Marine, 2: Marine, ..., 5: Marine
				while((t<MAX_LENGTH)&&(u>0))
				{
					player[0]->program[t].order=Build_Bv[bo[t-counter].type];
					u--;counter++;
					player[0]->program[t].time=20000;
					player[0]->program[t].built=0;
					t++;

					//~~~~
				}
				counter--;t--;
			}
				else 
				{
					player[0]->program[t].order=Build_Bv[NOP];
					player[0]->program[t].time=20000;
					player[0]->program[t].built=0;	
				}
		
		// "scc -b Drone" results in a goal[DRONE].what == 5
			for(s=0;s<MAX_GOALS;s++)
				if(player[0]->force[s]>0)
					goal[s].what+=player[0]->force[s];
			player[0]->readjust_goals(); // actually affects only zerg (and archon of the protoss)

			printf("Translated goals:\n");
			for(s=0;s<MAX_GOALS;s++)
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
				if((player[0]->program[s].built==1)&&(Build_Av[player[0]->program[s].order]!=NOP))
						//surpress NOP orders
			printf("%s [%.2i:%.2i] %s [%2i/%2i] [G: %i] [W: %i]\n",stats[race][Build_Av[player[0]->program[s].order]].name,player[0]->program[s].time/60,player[0]->program[s].time%60,error_m[player[0]->program[s].success],player[0]->program[s].need_Supply,player[0]->program[s].have_Supply,player[0]->program[s].res[GOLD],player[0]->program[s].res[WOOD]);
			//	else s=MAX_LENGTH;
				
			printf("Needed Time: ");	
			setColor(32);
			printf("[%.2i:%.2i] ",player[0]->timer/60,player[0]->timer%60);
			setColor(37);

	                 printf("Force at the end:\n");
			 for(s=0;s<MAX_GOALS;s++)
			 {
				 if((s==0)&&(race!=UNDEAD))
				 {
					 if(player[0]->force[s]>0)
						 printf("%s: %i [Mine: %2i] [Forest: %2i]\n",stats[race][s].name,player[0]->force[s],player[0]->PeonAt[GOLDMINE],player[0]->PeonAt[FOREST]);
				 }
				 else		 
				if(player[0]->force[s]>0)
					printf("%s: %i\n",stats[race][s].name,player[0]->force[s]);
			 }
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
					        setColor(32);
				       		printf("%s",stats[race][Build_Av[player[0]->program[s+1].order]].name);
					        setColor(37);
				                printf(" the following requirement failed : \n");
						setColor(31);
						printf("%80s\n",error_m[player[0]->program[s+1].success]);
						setColor(37);
						printf("You probably forgot entering the following goals or put them in the wrong order:\n");
						//TODO: wenn keine dann auch keine anzeigen!
						setColor(31);
	                                        for(t=0;t<MAX_GOALS;t++)
							if(player[0]->force[t]<goal[t].what)
								printf("%s [%i]\n",stats[race][t].name,goal[t].what-player[0]->force[t]);
					        setColor(37);
						printf("\nCheck your build order, reread the readme and/or contact ClawSoftware :)\n");
						s=5000;
					} else s++;
				if(s!=5000)
				{
					printf("Although all given orders were build without errors, not all goals were reached.\n");
					printf("You probably forgot entering the following goals:\n");
					setColor(31);
					for(s=0;s<MAX_GOALS;s++)
						if(player[0]->force[s]<goal[s].what)
							printf("%s [%i]\n",stats[race][s].name,goal[s].what-player[0]->force[s]);
					setColor(37);
					printf("\nCheck your build order, reread the readme and/or contact ClawSoftware :)\n");
				}
				}
			printf("\n");
			return(0);	
	}*/
        old_bestTime=setup.Max_Time;

	// Creating Unit text... (right bottom corner)
/*	for(s=0;s<60;s++)
sprintf(unit[s].text,"              Unit Name: %NAME_LENGTHs    Buildtime: %3i seconds    Minerals : %3i    Gas      : %3i    Supply   : %i    Type     : %i                     ",stats[race][s].name,stats[race][s].BT,stats[race][s].mins,stats[race][s].gas,stats[race][s].supply,stats[race][s].type);*/
                         

	
//some blabla
	if(setup.Verbose==1)
	{
		print("\n\n OK! System is ready to start. Press Enter to continue... \n");

		a=getchar();clrscr();
/*	
	print("Welcome to StarCraftCalculator v1.02 [April/07/2003]!\n-------------------------------------\n\n"
	sprint("- Check the ""%s"" file to change goals of the BO\n",Input);
	print("  You may change additional settings in the ""settings.txt"" file.\n");
	printf("- If you are new to this program, try to read the readme.txt\n");
	printf("- After the calculation is complete, a new file called %s will be created.\n",Output);
        printf("  It contains the build order and some additional informations.\n");
	printf("- Remember: SCC is based on a speed 5 game.\n");

	printf("\n\n");
        printf("Please note:\n");
	printf("            This may take a while.\n");
	printf("            If the 'generations' counter keep jumping back\n");
	printf("            you do not need to worry:\n");
	printf("That is exactly how it should be :)\n\n");
	printf("\nPress Enter to show the goals...\n");	
        a=getchar();*/clrscr();
	printf("\n");
//	if(translate==0)
//		printf("Goals (as stated in ""%s"")\n",Input);
//	else printf("Goals (as received from command line)\n");
	
/*	for(s=0;s<MAX_GOALS;s++)
		if(goal[s].what>0)
		{
			if(goal[s].time==0)
				printf("- %20s : %2i   (%s) \n",stats[race][s].name,goal[s].what,kurz[race][s].b);
			else printf("- %20s : %2i   (%s) [%.2i:%.2i] \n",stats[race][s].name,goal[s].what,kurz[race][s].b,goal[s].time/60,goal[s].time%60);
		}

	printf("\n\n");
	printf("Press ENTER to let the calculation start!\n");
	a=getchar();clrscr();*/

	// OK, lets start the main loop :)
	}
#ifdef WIN32
	SetConsoleActiveScreenBuffer(scr);
#endif
	for(s=0;s<MAX_MUT_DISPLAY;s++) 
	{
		mut_count[s].on=0;
		mut_count[s].target=0;
	}
	player[0]->Init();
	player[0]->Calculate();	
	basicFitness=0;
//	basicFitness=player[0]->pFitness;
	Mutation=setup.Mutations;
        MutationRate=setup.Mutation_Rate;
        Generations=setup.Max_Generations;
	totalCrossOver=1;
	negativeCrossOver=0;

	for(s=0;s<RUNNINGS;s++)
	{
		Save[s]->pFitness=0;
		Save[s]->sFitness=0;
	}
	
	while(run<RUNNINGS)
	{
		calc++;
		if(calc%10==0)
		{
			negative_Crossing_Over=(negativeCrossOver*100)/totalCrossOver;///(CROSSING_OVER*10);
			totalCrossOver=1;
			negativeCrossOver=0;
		}
		generation++;
                unchangedRuns++;
		currentMutation=Mutation*(unchangedRuns+Generations)*(unchangedRuns+Generations)/(Generations*Generations);
		currentMutationRate=Mutation*(Generations-unchangedRuns/2)*(Generations-unchangedRuns/2)/(Generations*Generations);
// Core of the Program
//Crossing over!
                old_bestTime=player[0]->timer;
		old_bestPrimaryFitness=player[0]->pFitness;
		old_bestSecondaryFitness=player[0]->sFitness;
		for(t=0;t<MAX_GOALS;t++) totalProteins[t]=0;
		for(s=0;s<MAX_PLAYER;s++) (*player[s]).Init();
                for(s=1;s<MAX_PLAYER;s++) (*player[s]).Mutate();
                for(s=0;s<MAX_PLAYER;s++) (*player[s]).Calculate();
		diversity=0;
		for(t=0;t<MAX_GOALS;t++)
			totalProteins[t]/=MAX_PLAYER;
		for(s=0;s<MAX_PLAYER;s++)
			for(t=0;t<MAX_GOALS;t++)
				diversity+=(totalProteins[t]-player[s]->protein[t])*(totalProteins[t]-player[s]->protein[t]);
		diversity/=MAX_PLAYER;
		
		

		qsort(*player,MAX_PLAYER,race_size,compare);
if(basicFitness==0) basicFitness=player[0]->pFitness;
		
		/*
		for(s=1;s<MAX_PLAYER;s++)
                if((player[s]->pFitness>player[0]->pFitness)||((player[s]->pFitness==player[0]->pFitness)&&(player[s]->sFitness>=player[0]->sFitness)))
                {
	                tempp=player[s];
	                player[s]=player[0];
	                player[0]=tempp;
	        }
		
		*/	
		
	        if(player[0]->pFitness>bestPrimaryFitness)
	        {
	 	       bestPrimaryFitness=player[0]->pFitness;
		       bestSecondaryFitness=player[0]->sFitness;
		       unchangedRuns=0;
		}
		else if(player[0]->sFitness>bestSecondaryFitness)
                {
	                bestSecondaryFitness=player[0]->sFitness;
	                unchangedRuns=0;
	        }
		selection=0;
		for(v=0;v<MAX_PLAYER*CROSSING_OVER/100;v++)
		{
			s=rand()%(MAX_PLAYER/2);
			t=rand()%(MAX_PLAYER/2);
			d2=0;
			for(u=0;u<MAX_GOALS;u++)
				d2+=(player[s]->protein[u]-player[t]->protein[u])*(player[s]->protein[u]-player[t]->protein[u]);

			if(d2*d2<100)
			{

			
			//TODO: s und t tauschen ...
			if((player[t]->pFitness<player[s]->pFitness)||((player[t]->pFitness==player[s]->pFitness)&&(player[t]->sFitness<player[s]->sFitness)))
			{u=s;s=t;t=u;};

			if((player[s]->pFitness<player[t]->pFitness)||((player[s]->pFitness==player[t]->pFitness)&&(player[s]->sFitness<player[t]->sFitness)))
			{
				selection++;
				who_crosses=0;
				counter=MAX_LENGTH;// => 1/MAX_LENGTH probability for a cut for any place
				temp_pFitness=player[s]->pFitness;
				temp_sFitness=player[s]->sFitness;
				for(u=0;u<MAX_LENGTH;u++)
				{
//					if(((who_crosses==0)&&(Build_Av[player[t]->program[u].order]==MARKER))||((who_crosses==1)&&(Build_Av[player[s]->program[u].order]==MARKER)))/						counter=2;
//					if(counter==0) counter=1;
					if(rand()%counter==0)
					{
						if(who_crosses==0) who_crosses=1; else who_crosses=0;
						counter=MAX_LENGTH;
					}
					if(who_crosses==0)
					{
						Child1->program[u][0].order=player[t]->program[u][0].order;
						Child1->program[u][1].order=player[s]->program[u][1].order;
						Child2->program[u][0].order=player[s]->program[u][0].order;
						Child2->program[u][1].order=player[t]->program[u][1].order;
					}
					else
					{
						Child1->program[u][0].order=player[s]->program[u][0].order;
                                                Child1->program[u][1].order=player[t]->program[u][1].order;
                                                Child2->program[u][0].order=player[t]->program[u][0].order;
                                                Child2->program[u][1].order=player[s]->program[u][1].order;
					}
				}
				Child1->length=MAX_LENGTH;Child2->length=MAX_LENGTH;
				Child1->Init();
				Child1->Mutate();
				Child1->Calculate();
				Child2->Init();
				Child2->Mutate();
				Child2->Calculate();
				
/*				if( 
	(
	 (Child1->pFitness>player[s]->pFitness)||
((Child1->pFitness==player[s]->pFitness)&&(Child1->sFitness>=player[s]->sFitness))

	)
						&&*/
				if(
				((Child1->pFitness>Child2->pFitness)||((Child1->pFitness==Child2->pFitness)&&(Child1->sFitness>=Child2->sFitness))
				 )
				)
				{
					for(u=0;u<MAX_LENGTH;u++)
					{
						player[MAX_PLAYER-selection]->program[u][0].order=Child1->program[u][0].order;
						player[MAX_PLAYER-selection]->program[u][1].order=Child1->program[u][1].order;
					}
					// mehr kopieren?
					player[MAX_PLAYER-selection]->pFitness=Child1->pFitness;
					player[MAX_PLAYER-selection]->sFitness=Child1->sFitness;
					totalCrossOver++;
				}
				else
//				if((Child2->pFitness>player[s]->pFitness)||((Child2->pFitness==player[s]->pFitness)&&(Child2->sFitness>=player[s]->sFitness)))
				{
					 for(u=0;u<MAX_LENGTH;u++)
				 	 {
	                                         player[MAX_PLAYER-selection]->program[u][0].order=Child2->program[u][0].order;
						 player[MAX_PLAYER-selection]->program[u][1].order=Child2->program[u][1].order;
					 }
					 player[MAX_PLAYER-selection]->pFitness=Child2->pFitness;
					 player[MAX_PLAYER-selection]->sFitness=Child2->sFitness;
					 totalCrossOver++;
				}
				if((temp_pFitness>player[MAX_PLAYER-selection]->pFitness)||((temp_pFitness==player[MAX_PLAYER-selection]->pFitness)&&(temp_sFitness>player[MAX_PLAYER-selection]->sFitness)))
					negativeCrossOver++;
			}
			
			}
		}


		
		for(v=0;v<MAX_PLAYER*ZELL_TEILUNG/100;v++)
		{
			t=rand()%(MAX_PLAYER/2);
			selection++;
			for(u=0;u<MAX_LENGTH;u++)
			{
				player[MAX_PLAYER-selection]->program[u][0].order=player[t]->program[u][0].order;
				player[MAX_PLAYER-selection]->program[u][1].order=player[t]->program[u][1].order;
			}
			player[MAX_PLAYER-selection]->pFitness=player[t]->pFitness;
			player[MAX_PLAYER-selection]->sFitness=player[t]->sFitness;
		}
		
                for(s=0;s<MAX_PLAYER*ALPHA_TIER/100;s++)
	                {
			selection++;	
                        t=MAX_PLAYER-selection;
			for(u=0;u<MAX_LENGTH;u++)
			{
        			player[t]->program[u][0].order=player[0]->program[u][0].order;
				player[t]->program[u][1].order=player[0]->program[u][1].order;
			}
				player[t]->pFitness=player[0]->pFitness;
		                player[t]->sFitness=player[0]->sFitness;
	                
			}
		
				
	// Save the program when 'Max_Generations' Generations were no change
	    if(unchangedRuns>=Generations)
		{
			unchangedRuns=0;
			gen_count[run]=generation;
			generation=0;
			//Problem bei timer == MaxTIme
			u=0;
			for(t=0;t<RUNNINGS;t++)
				if((Save[t]->pFitness<player[0]->pFitness)||((Save[t]->pFitness==player[0]->pFitness)&&(Save[t]->sFitness<player[0]->sFitness)))
				{
					for(u=RUNNINGS-1;u>t;u--)
						Save[u]=Save[u-1];
					u=t;
					t=RUNNINGS;
				}
			for(t=0;t<2;t++)
			for(s=0;s<MAX_LENGTH;s++)
			{
				Save[u]->program[s][t].order=player[0]->program[s][t].order;
				Save[u]->program[s][t].time=player[0]->program[s][t].time;
				Save[u]->program[s][t].need_Supply=player[0]->program[s][t].need_Supply;
				Save[u]->program[s][t].have_Supply=player[0]->program[s][t].have_Supply;
				Save[u]->program[s][t].success=player[0]->program[s][t].success;
				Save[u]->program[s][t].built=player[0]->program[s][t].built;
//				Save[u]->program[s][t].temp=player[0]->program[s][t].temp;
			}
			Save[u]->pFitness=player[0]->pFitness;
			Save[u]->timer=player[0]->timer;
			for(s=0;s<RESOURCES;s++)
			{
				Save[u]->res[s]=player[0]->res[s];
				Save[u]->harvested_res[s]=player[0]->harvested_res[s];
			}
			
			Save[u]->length=player[0]->length;

			for(s=0;s<MAX_GOALS;s++)
			{
				Save[u]->force[s]=player[0]->force[s];
				Save[u]->ftime[s]=player[0]->ftime[s];
			}

			switch(run)
			{
				case RUNNINGS-2:
					
			// Last run: Get the best run and retry to optimize it.
					Generations*=2;
					Mutation*=2;
					MutationRate/=2;
					Basic_Length=Save[0]->length;
					for(s=0;s<2;s++)
					for(t=0;t<Save[0]->length;t++)
						Basic[t][s]=Save[0]->program[t][s].order;
				default:
//			if(Test<2)
		        	for(s=0;s<MAX_PLAYER;s++)
			        	player[s]->Restart();
				//TODO: Mehr auf 0 setzen...
 /*        		else
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
			}*/
				break;
			}

			bestPrimaryFitness=0;
			bestSecondaryFitness=0;
			old_bestTime=setup.Max_Time; 
			old_bestPrimaryFitness=0;
			old_bestSecondaryFitness=0;
			run++;
			for(s=0;s<MAX_LENGTH;s++) {bolog[s].count=0;for(t=0;t<MAX_MUT_DISPLAY;t++) mutlog[s][t].count=0;};
		}
	    

		//Print the screen :)
		if(setup.Verbose==1)
		{
			gotoxy(0,0);

	   	print("Calculating ");

		if(setup.Gizmo==1)
		{
//			print("[");
//			setColor(32);
//			for(s=0;s<gizmowidth;s++)
//			{
//				sprintf(tmp,"%c",gizmo[(calc/2+s)%gizmolength]);
//				print(tmp);
//			}
//			setColor(37);
//			print("]");
		}
		print("  Status:");

		if(gcount<160) gcount++;
		if(player[0]->timer<setup.Max_Time)
		{
			if(old_bestTime>player[0]->timer) gcount=0;
			if(gcount<=16)
			print(" got faster solution! ");
				else
			print(" optimizing resources.");
		}
		else			
		{
			if((old_bestPrimaryFitness/100)<(player[0]->pFitness/100)) gcount=0;

			if(gcount<=16)
			print(" another goal complete");
			else
			print(" searching . . .      ");
		}
		setColor(37);
		print("diversity:");
		setColor(32);
		printf("%5i",diversity);
		print("    \n");

		gotoxy(1,2);sprintf(tmp,"%2i runs and %3i+ generations remaining. [Total %4i] [negative CO: %3i] ",RUNNINGS-run,Generations-unchangedRuns,generation,negative_Crossing_Over);
		print(tmp);
		gotoxy(0,4);
		if(player[0]->timer<setup.Max_Time)
			print("[resources] [time]");
		else print("[resources] [fitness]");
		gotoxy(0,5);
		print("------------------");
		gotoxy(2,6);sprintf(tmp,"  %5.4i",(int)(player[0]->harvested_res[GOLD]+player[0]->harvested_res[WOOD]));
		print(tmp);
		setAt(gcount);
		gotoxy(13,6);
		if(player[0]->timer<setup.Max_Time) 
		     {sprintf(tmp,"%.2i:%.2i",player[0]->timer/60,player[0]->timer%60);print(tmp);} 
		else {sprintf(tmp," %i ",player[0]->pFitness);print(tmp);}
		if(player[0]->pFitness>0)
		{
			sprintf(tmp," [%3i percent]",(100*basicFitness)/player[0]->pFitness);
			print(tmp);
		}
		
printf("C1 %i [%i] || C2 %i [%i]",Child1->pFitness,Child1->sFitness,Child2->pFitness,Child2->sFitness);
       /*		
	setColor(31);
if((calc%80==0)||(calc%80==1)) setColor(37); else setColor(31);
	gotoxy(35,3);print("   /   / __ __  ___    / ");
if((calc%80==2)||(calc%80==3)) setColor(37); else setColor(31);
	gotoxy(35,4);print("  / / / /  /   /  /   / /    ");
if((calc%80==4)||(calc%80==5)) setColor(37); else setColor(31);
	gotoxy(35,5);print(" / / / /  /   /  /   ----  ");
if((calc%80==6)||(calc%80==7)) setColor(37); else setColor(31);
	gotoxy(35,6);print("/_/_/ /_ /_  /__/.   /     ");
if((calc%80==8)||(calc%80==9)) setColor(37); else setColor(31);*/
		
		for(s=0;s<MAX_GOALS;s++) tgoal[s]=goal[s].what;
//bolog logs how long which build order stands there (you know, the colors ;-)
		//TODO: recognize moved blocks to stress real Mutations
		
		orderTemp=200;
		old_Time=0;
		old_Food=0;
		counter=1;
		t=0;
		setColor(37);
			
		if(setup.Detailed_Output==1)
		{
/*			for(s=0;s<5;s++)
                	{
		       		t=0;
		                while((t<HEIGHT)&&((player[0]->program[(s+1)*HEIGHT-t][0].built==0)||(player[0]->program[(s+1)*HEIGHT-t][1].built==1))) t++;
		               	gotoxy(WIDTH*s+2,25-setup.Console24Lines);//WIN32 1 <> LINUX 0
				if(t<HEIGHT)
				{
					if(player[0]->program[s*HEIGHT][0].built>0)
						sprintf(tmp,"[%.2i:%.2i]",player[0]->program[(s+1)*HEIGHT-t][0].time/60,player[0]->program[(s+1)*HEIGHT-t][0].time%60);
					else if(player[0]->program[s*HEIGHT][1].built>0)
						sprintf(tmp,"[%.2i:%.2i]",player[0]->program[(s+1)*HEIGHT-t][1].time/60,player[0]->program[(s+1)*HEIGHT-t][1].time%60);
					else sprintf(tmp,"       ");
					print(tmp);
				}
			}*/
			
			t=0;
			/*for(s=0;s<MAX_MUT_DISPLAY;s++)
		        {
		                mut_count[s].on=0;
		                mut_count[s].target=0;
		        }*/

/*			for(s=0;s<player[0]->length;s++)
			if(player[0]->program[s].mutate<MAX_LENGTH)
                                        {
                                                if(player[0]->program[s].mutate>s)
                                                {
                                                        for(v=0;v<MAX_MUT_DISPLAY;v++)
                                                                if(mut_count[v].on==0)
                                                                {
                                                                        for(u=s;u<player[0]->program[s].mutate+1;u++)
                                                                        {
                                                                                mutlog[u][v].count=80;
                                                                                mutlog[u][v].from=s;
                                                                                mutlog[u][v].to=player[0]->program[s].mutate;
                                                                        }
                                                                        mut_count[v].on=1;
                                                                        mut_count[v].target=player[0]->program[s].mutate;
                                                                        v=MAX_MUT_DISPLAY;
                                                                }
                                                }
                                                else
                                                {
                                                        for(v=0;v<MAX_MUT_DISPLAY;v++)
                                                                if((mut_count[v].on==1)&&(mut_count[v].target==s))
                                                                {
                                                                        mut_count[v].on=0;
                                                                        v=MAX_MUT_DISPLAY;
                                                                }
                                                }
                                        }
			
*/
			if(player[0]->length>0)
			for(s=0;s<4*HEIGHT;s++)
			{
/*				if(player[0]->program[s].newmut==1)
				{
					for(u=s;u<MAX_LENGTH-1;u++)
					{
						bolog[u].count=bolog[u+1].count;
						bolog[u].order=bolog[u+1].order;
					}
				}
				else if(player[0]->program[s].newmut==2)
				{
					for(u=MAX_LENGTH-1;u>s+1;u--)
					{
						bolog[u].count=bolog[u-1].count;
						bolog[u].order=bolog[u-1].count;
					}
				}*/
				gotoxy((t/HEIGHT)*WIDTH,9+t%HEIGHT-setup.Console24Lines);
				t++;
				setColor(37);
				if(player[0]->program[s][0].built==1) dom=0;
				else if(player[0]->program[s][1].built==1) dom=1;
				else dom=2;
				if(dom!=2)
				{
					if(bolog[s].order==player[0]->program[s][dom].order)
                                	{
				        	if(bolog[s].count<160)
							bolog[s].count++;
					} else
					{
						bolog[s].count=0;
						bolog[s].order=player[0]->program[s][dom].order;
					}
					
					setColor(35);
					sprintf(tmp,"%c",error_sm[player[0]->program[s][dom].success]);
					print(tmp);
					setAt(bolog[s].count);
					sprintf(tmp,"%s|%s",kurz[race][Build_Av[player[0]->program[s][0].order]].b,kurz[race][Build_Av[player[0]->program[s][1].order]].b);
					print(tmp);
					setColor(37);
//					if(player[0]->program[s][dom].need_Supply<100)
//						sprintf(tmp," %.2i",player[0]->program[s][dom].need_Supply);
//					else sprintf(tmp,"%3i",player[0]->program[s][dom].need_Supply);
//					print(tmp);
					

					/*if(player[0]->program[s].mutate<MAX_LENGTH)
					{
						if(player[0]->program[s].mutate>s)
						{
							for(v=0;v<MAX_MUT_DISPLAY;v++)
								if(mut_count[v].on==0)
								{
									for(u=s;u<player[0]->program[s].mutate+1;u++) 
									{
										mutlog[u][v].count=160;
										mutlog[u][v].from=s;
										mutlog[u][v].to=player[0]->program[s].mutate;
									}
									mut_count[v].on=1;
									mut_count[v].target=player[0]->program[s].mutate;
									v=MAX_MUT_DISPLAY;
								}
						}
	        				else 
						{
							for(v=0;v<MAX_MUT_DISPLAY;v++)
								if((mut_count[v].on==1)&&(mut_count[v].target==s))
								{
									mut_count[v].on=0;
									v=MAX_MUT_DISPLAY;
								}
						}
					}*/
					
					/*for(u=0;u<MAX_MUT_DISPLAY;u++) 
						if(mutlog[s][u].count>0)
						{
							setAt(80-mutlog[s][u].count);
							if(mutlog[s][u].from==s) print("*");
							else
							if(mutlog[s][u].to==s) print("/");
							else
							print("|");
							mutlog[s][u].count--;
						} else print(" ");*/
//					if((player[0]->program[s].mutate<MAX_LENGTH)&&(player[0]->program[s].mutate>s)&&(mut_count<MAX_MUT_DISPLAY)) mut_count++;
				}
   				else print("  ------  ");
			}
		}
		}
/*		else
		{
			for(s=0;(s<MAX_LENGTH)&&(t<3*HEIGHT+3);s++)
			{
				while((player[0]->program[s][dom].built==0)&&(s<MAX_LENGTH-1))
	                        	s++;
        	                if(orderTemp==Build_Av[player[0]->program[s][dom].order]) counter++;
				else if(orderTemp<200)
				{
					if(bolog[t].order==orderTemp)
	        	                {
						if(bolog[t].count<160)
						bolog[t].count++;
					}
                        	        else
					{
						bolog[t].count=0;
						bolog[t].order=orderTemp;
					}
				
					gotoxy((t/(HEIGHT+1))*17,9+t%(HEIGHT+1)-setup.Console24Lines);
					if(counter>1) { sprintf(tmp,"%2i",counter);setColor(35);print(tmp);} else print("  ");
						setAt(bolog[t].count);
					t++;
					sprintf(tmp,"%s",kurz[race][orderTemp].b);
					print(tmp);
					setColor(37);
				        sprintf(tmp," %.2i:%.2i ",old_Time/60,old_Time%60);
					print(tmp);
					setColor(35);
					if(old_Food<100) sprintf(tmp,"%.2i",old_Food); else sprintf(tmp,"%3i",old_Food);
					print(tmp);
					setColor(37);
					counter=1;
					orderTemp=Build_Av[player[0]->program[s][0].order];
					old_Time=player[0]->program[s][0].time;
					old_Food=player[0]->program[s][0].need_Supply;
				}
				else
				{
					orderTemp=Build_Av[player[0]->program[s][0].order];
					old_Time=player[0]->program[s][0].time;
					old_Food=player[0]->program[s][0].need_Supply;
				}
			}
			for(s=t;(s<=MAX_LENGTH)&&(s<3*(HEIGHT+1));s++)
			{
				gotoxy((s/(HEIGHT+1))*17,9+s%(HEIGHT+1)-setup.Console24Lines);
				print("  ------       x");
			}
		}*/

		setColor(37);

		t=4;
		gotoxy(66,3);print("Force:");
		for(s=0;s<MAX_GOALS;s++)
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
				if(t>23-setup.Console24Lines) s=MAX_GOALS;
				
				//Well... it can't print out more than ~20 goals :/ 
			}
		if(t<=23-setup.Console24Lines)
		{
			gotoxy(66,t);
			setColor(37);
			print("non-goals:");
			t++;
			for(s=0;s<MAX_GOALS;s++)
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
						if(t>23-setup.Console24Lines) s=MAX_GOALS;
				}
		for(s=0;s<23-t-setup.Console24Lines;s++)
		{
			gotoxy(70,t+s);
			print("         ");
//		}
		}
		
/*		if(setup.Gizmo==1)
		{
			setColor(37);
			gotoxy(54,25-setup.Console24Lines);
		 	print("[");
			setColor(33);
	     for(s=0;s<23;s++)
			{
				sprintf(tmp,"%c",unit[tunit].text[(calc/2+s)%(sizeof(unit[tunit].text)-1)]);
				//sizeof correct? mmmh...
				print(tmp);
			}	

			if((calc/2+1)%(sizeof(unit[tunit].text)-1)==0)
			{
				clrscr(); // <- hacked to reduce graphic errors... D:
				tunit=rand()%MAX_GOALS;
				while(player[0]->force[tunit]==0)
					tunit=rand()%MAX_GOALS;
			}
		
                setColor(37);
                print("]");
			}*/
		}

// End of Verbose
		


			

	} // end while...
	
	//TODO: Ende des letzten Runs verkleinern... braucht ja net alles neu initialisiert werden...
	
	
//	delete [] gizmo;

	//start of the file output block...

// Run canceled before all 5 runs were calculated? => Save the present run
/*	if(run<RUNNINGS)
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

		for(s=0;s<MAX_GOALS;s++)
		{
			Save[run]->force[s]=player[0]->force[s];
			Save[run]->ftime[s]=player[0]->ftime[s];
		}
	}*/
	
//sorting the runs
//TODO: Recheck for equal solutions!
/*	for(s=0;s<run;s++)
		for(t=s+1;t<run;t++)
		{
			 if( ((Save[t]->pFitness>Save[s]->pFitness)&&(Save[t]->timer<setup.Max_Time))||
			     ((Save[t]->pFitness==Save[s]->pFitness)&&(Save[t]->sFitness>Save[s]->sFitness)&&(Save[t]->timer<setup.Max_Time)) )
			 {
				 tempp=Save[s];
				 Save[s]=Save[t];
				 Save[t]=tempp;
			 }
		}*/
	//TODO: gecancelten Run auffangen...
		
//	clrscr();
	
#ifdef WIN32
	CloseHandle(scr);
#endif
//	setColor(37);
	print("\n");
// Even best run did not find a solution?
	if(Save[0]->timer>=setup.Max_Time)
	{
	/*	print("NO Solution found. This should not happen.\n");
		print("Please try the following:\n");
		print(" - Reread all WARNINGS carefully.\n");
	        print(" - Reduce the amount of goals in %s",Input);
		print(" - Increase Max Time and/or adjust other settings depending on your task\n");
		print(" - Contact scc@clawsoftware.de. Please include all .txt files and a short description of the problem.\n");
		 print(" - You might also want to check www.clawsoftware.de for updates or read the Forum/SCC page.\n");*/
		print(" Press ENTER to quit...\n");
		a=getchar();
		return(1);
	}
	
// Start saving the data	
	print("Writing data...\n");
	FILE * pFile;
	pFile = fopen(Output,"a");
	fprintf(pFile,"---------------------------------------------------\n");
	fprintf(pFile,"---StarCraftCalculator by ClawSoftware.de [v1.02]--\n");
	fprintf(pFile,"---------------------------------------------------\n\n");
	
	for(t=0;t<RUNNINGS;t++)
		if(Save[t]->timer<setup.Max_Time)
		{
//			fprintf(pFile,"[%.2i:%.2i] [%4i gen.] [%3i mut./%3i fac] [A:%2i/Z:%2i/C:%2i] [%3i CODE] [%6i MAX]\n",Save[t]->timer/60,Save[t]->timer%60,gen_count[t],setup.Mutations,setup.Mutation_Rate,ALPHA_TIER,ZELL_TEILUNG,CROSSING_OVER,ADDITIONAL_ORDERS,MAX_PLAYER*setup.Max_Generations);
			
			fprintf(pFile,"[----#%i solution----]\n\n",t+1);
			fprintf(pFile,"     Time used: %.2i:%.2i minutes\n",Save[t]->timer/60,Save[t]->timer%60);	
			fprintf(pFile,"     Scouting unit after %.2i:%.2i minutes\n",setup.Scout_Time/60,setup.Scout_Time%60);
			if(setup.Time_to_Enemy>0) fprintf(pFile,"     Time to Enemy: %i seconds\n\n",setup.Time_to_Enemy);
			fprintf(pFile,"[%4i generations] [%3i mutations] [%3i mutation factor]\n",gen_count[t],setup.Mutations/2,setup.Mutation_Rate*2);
//			old=200;
			counter=1;
//			for(s=0;s<=Save[t]->length;s++)
//			{
/*				if(setup.Detailed_Output==0)
				{
					while(((Save[t]->program[s].time>=Save[t]->timer)||(Build_Av[Save[t]->program[s].order]>=MAX_GOALS))&&(s<MAX_LENGTH-1)) s++;
					if(old==Build_Av[Save[t]->program[s].order]) counter++;
					else 
					if(old<200)
					{
						fprintf(pFile,"     %.2i x %s\n",counter,stats[race][old].name);
						counter=1;
						old=Build_Av[Save[t]->program[s].order];
					}
					else
						old=Build_Av[Save[t]->program[s].order];
				}
				else*/
/*				if(Save[t]->program[s].built==1)
					fprintf(pFile,"     [%.2i:%.2i] [%.2i/%.2i] %s [%s]\n",(Save[t]->program[s].time+0)/60,(Save[t]->program[s].time+0)%60,Save[t]->program[s].need_Supply,Save[t]->program[s].have_Supply,stats[race][Build_Av[Save[t]->program[s].order]].name,error_m[Save[t]->program[s].success]);
					
			}
		        fprintf(pFile,"\n     ---Force at the end---\n");
			for(s=0;s<MAX_GOALS;s++)
				if(Save[t]->force[s]>0)
					fprintf(pFile,"   %24s : %2i [Last one: %.2i:%.2i]\n",stats[race][s].name,Save[t]->force[s],Save[t]->ftime[s]/60,Save[t]->ftime[s]%60);
			for(s=0;s<RESOURCES;s++)
				fprintf(pFile,"\n     Harvested %s : %i\n",resource[s],(short)(Save[t]->harvested_res[s]));
			for(s=0;s<RESOURCES;s++)
				fprintf(pFile,"     %s at the end: %i\n",resource[s],(short)(Save[t]->res[s]));
			fprintf(pFile,"[----#%i solution end--------]\n\n",t+1);
			sprintf(tmp,"#%i solution [%.2i:%.2i] succesfully saved... [%4i generations]\n",t+1,Save[t]->timer/60,Save[t]->timer%60,gen_count[t]);
			print(tmp);*/
		}
	
	fclose (pFile);
	sprintf(tmp,"%s closed. All Data were saved.\n\n Thank you for using StarCalc!\n",Output);
	print(tmp);
	sprintf(tmp,"Have a nice day and visit www.clawsoftware.de!\n");
	print(tmp);

	//TODO: Recheck the code whether REALLY all pointers / data are deleted/freed...
	for(s=0;s<MAX_PLAYER;s++)
		player[s]=NULL;
	for(s=0;s<RUNNINGS;s++)
		Save[s]=NULL;
	tempp=NULL;
	return 0;
}
