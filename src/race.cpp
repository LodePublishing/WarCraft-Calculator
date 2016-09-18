#include "race.h"
#include "settings.h"
#include <stdlib.h>

// TODO: recheck the speed of the units in zerg.cpp, protoss.cpp and terra.cpp
// TODO: Implement the locations of buildings (expansion, wallin, ...)

void RACE::CalculateFitness()
{
	unsigned char i,j;
	unsigned char bonus[MAX_GOALS]; // temporary data to check whether a bonus is already given (only applies if force > goal)
	pFitness=0;
	sFitness=0;
		
	for(i=0;i<RESOURCES;i++)
		sFitness+=(unsigned short)(harvested_res[i]);
	//Fehlt Modifikator! Mineral_Blocks, Mineral Mod, ...
	if(ready==0)
        {
	         timer=setup.Max_Time;
		 for(i=0;i<building_types;i++)
                 	if(goal[i].what>0)
	        	{
	                	if(goal[i].what>force[i])
				{
					if(ftime[i]>0) // ftime => when the last item is built 
					{
			//not all goals met and not below time
						if(goal[i].time>0)
							pFitness+=(100*goal[i].time*force[i])/(goal[i].what*ftime[i]);
						else pFitness+=(100*force[i])/goal[i].what;
					}
					else 
					{
						if(goal[i].time>0)
							pFitness+=(100*goal[i].time*force[i])/(goal[i].what*setup.Max_Time);
			        		else pFitness+=(100*force[i])/goal[i].what;
					}
				}
				else //force >= goal
				{
				if((goal[i].time>0)&&(ftime[i]>goal[i].time))
					pFitness+=(goal[i].time*100/ftime[i]);
				else pFitness+=100;
					
				if(goal[i].what<force[i])
					for(j=0;j<RESOURCES;j++)
						sFitness-=(force[i]-goal[i].what)*stats[race][i].res[j];
				}
		}
// TODO: Check for very small 'goal.time' values, probably in scc.cpp!!	 
	for(i=0;i<MAX_GOALS;i++)
		bonus[i]=goal[i].what-force[i];
	for(i=0;i<MAX_BUILDINGS;i++)
                if((building[i].RB>0)&&(goal[building[i].type].what>force[building[i].type])&&(bonus[building[i].type]>0))
		{
			if((goal[building[i].type].time>0)&&(force[building[i].type]==0))
	                	pFitness+=(building[i].RB*100*goal[building[i].type].time*force[i])/(goal[building[i].type].what*stats[race][building[i].type].BT*setup.Max_Time);
			else 				   		
				pFitness+=((building[i].RB*100)/(goal[building[i].type].what*stats[race][building[i].type].BT));
			bonus[building[i].type]--;
		}
	}
	else   // all goals fulfilled, fitness <- timer 
	{
		pFitness=setup.Max_Time-timer;
		for(i=0;i<building_types;i++)
	               	if(goal[i].what>0)
	                	pFitness+=100;
	}
}


//Check whether all goals are reached and do some after-completion stuff 
void RACE::CheckReady(unsigned char j)
{
	unsigned char i;

	force[building[j].type]++;
	
	program[building[j].IP].built=1;
	if(((force[building[j].type]>=goal[building[j].type].what)&&(ftime[building[j].type]==0))||(goal[building[j].type].what==0))
		ftime[building[j].type]=timer; // Get time when the goal was fulfilled OR the time when the last item was build (if goal = 0)
	
	if(stats[race][building[j].type].type<3)
		availible[building[j].type]++;
	else
		availible[building[j].type]=1;
	ready=1;
	for(i=0;i<building_types;i++)
		ready&=((goal[i].what<=force[i])&&((goal[i].time>=ftime[i])||(goal[i].time==0)));
}



void RACE::Harvest_Resources()
{
	double i;
	if(PeonAt[GOLDMINE]>5*(expansions+1)) i=5*(expansions+1); else i=PeonAt[GOLDMINE]; //EXPANSIONS!

	if((Max_Supply-Supply)>80)
	{
		res[GOLD]+=0.8*i;
		harvested_res[GOLD]+=0.8*i;
	}
	if((Max_Supply-Supply)>50)	
	{
		res[GOLD]+=1.4*i;
		harvested_res[GOLD]+=1.4*i;
	}
	else
	{
		res[GOLD]+=2*i;
		harvested_res[GOLD]+=2*i;
	}

	res[WOOD]+=Harvest_Speed*PeonAt[FOREST]; //TODO!!! mehr :)
	harvested_res[WOOD]+=Harvest_Speed*PeonAt[FOREST];

/*	for(i=0;i<RESOURCES;i++)
		if(PeonAt[i+2]<MAX_PEONS)
		{
		//TODO: v.a. fuer Holzabbauen noch was rein, weg wird laenger!
			//auch abstand zu Saegewerk... letztes Saegewerk als Zeit hernehmen oder so			
			res[i]+=Harvest_Speed[i][PeonAt[i+2]];
			harvested_res[i]+=Harvest_Speed[i][PeonAt[i+2]];
		}
		else // In case there is a maximum where additional peons have no effect ~~ Change ... for wood pretty useless
		{
			res[i]+=Harvest_Speed[i][MAX_PEONS-1];
			harvested_res[i]+=Harvest_Speed[i][PeonAt[i+2]];
		}
	// Still, there is the location important... i.e. distance to minerals/wood or goldmine!*/
	
}

// Account the costs of a production
void RACE::Produce(unsigned char what)
{
	unsigned char i;
	building[nr].RB=stats[race][what].BT;
	for(i=0;i<RESOURCES;i++)
		res[i]-=stats[race][what].res[i];
	building[nr].type=what;
	Supply-=stats[race][what].supply;
	building[nr].on_the_run=0;
	if(stats[race][what].type>2) // Researches, Upgrades
		availible[what]=0; //Temporaliy/permanently shut down possibility to re-research the item while it is currently in research
	if(stats[race][what].type==4) // Upgrade!
	{
		building[nr].RB+=force[what]*16; //16 in WC, 32 in SC
		for(i=0;i<RESOURCES;i++)
			res[i]-=stats[race][what].upres[i]*force[what];
        }
	building[nr].IP=IP;
	ok=1;
}


// some functions to modify the list of orders
// One of the Core functions
void RACE::Mutate()
{
	unsigned char ta,tb,i,x,y,tmp[MAX_LENGTH];
	length=MAX_LENGTH;
	if(length==0) return;
	
	for(i=0;i<setup.Mutations;i++)
	{
		//delete one entry
		if(rand()%setup.Mutation_Rate==0)
		{
			x=rand()%length; //MAX_LENGTH
			for(y=x;y<length-1;y++)
			program[y].order=program[y+1].order;
		}
	
		//add one entry
		if(rand()%setup.Mutation_Rate==0)
		{
			x=rand()%length;
			for(y=length-1;y>x;y--)
				program[y].order=program[y-1].order;
			program[x].order=rand()%Max_Build_Types;
		}

		//change one entry
		if(rand()%setup.Mutation_Rate==0)
		{
			x=rand()%length;
			program[x].order=rand()%Max_Build_Types;
		}
		
		//exchange two entries
		if(rand()%setup.Mutation_Rate==0)
		{
			x=rand()%length;
			y=rand()%length;
			ta=program[x].order;
			program[x].order=program[y].order;
			program[y].order=ta;
		}

		//rotate a list [ta, ta+1, ..., tb] -> [ta+1, ..., tb, ta]
		if(rand()%(setup.Mutation_Rate)==0)
		{
			ta=rand()%length;
			tb=rand()%length;
			if(ta<tb)
			{
				x=program[ta].order;
				for(i=ta;i<tb;i++)
					program[i].order=program[i+1].order;
				program[tb].order=x;
			}
		}

		//move a block of orders  [a..b..ta..tb..c..d] -> [a..ta..tb..b..c..d]
		//TODO switch ta and tb if tb<ta
		if(rand()%(setup.Mutation_Rate)==0)
		{
			ta=rand()%length;
			tb=rand()%length;
			x=rand()%length; //move it here
			if((ta<tb)&&(x>tb))
			{
				for(i=0;i<x-tb;i++)
					tmp[i]=program[i+tb].order;
				for(i=ta;i<tb;i++)
					program[i+x-tb].order=program[i].order;
				for(i=0;i<x-tb;i++)
					program[ta+i].order=tmp[i];
		        } else
			if((ta<tb)&&(x<ta))
			{
				for(i=0;i<ta-x;i++)
					tmp[i]=program[i+x].order;
				for(i=ta;i<tb;i++)
					program[x+i-ta].order=program[i].order;
				for(i=0;i<ta-x;i++)
					program[tb-x].order=tmp[i];		
			}
		}
	}
		
}

// Reset all ongoing data (between two runs)
void RACE::Init()
{
	unsigned char i,j;
	for(i=0;i<building_types;i++)
        {
               force[i]=0;
	       ftime[i]=0;
               if(stats[race][i].type<3)
	               availible[i]=0;
	       else
	               availible[i]=1;//Researches that can be researched only once
	}
	for(i=0;i<MAX_BUILDINGS;i++)
	{
	       building[i].RB=0;
	       building[i].type=255;
	       building[i].IP=0;	
	}
	for(i=0;i<MAX_LENGTH;i++)
	{
		program[i].built=0;
		program[i].success=0;
		program[i].have_Supply=0;
		program[i].need_Supply=0;
		program[i].time=0;
		for(j=0;j<RESOURCES;j++)
			program[i].res[j]=0;
//		program[i].temp=0;
	}
        pFitness=0;
	sFitness=0;
	res[GOLD]=450; //TFT settings... for classic: 800/200
	res[WOOD]=200;
	expansions=0;
	availible_expansions=MAX_EXPANSIONS;
	PeonAt[GOLDMINE]=5;
	PeonAt[FOREST]=0;
	IP=0;
	InitRaceSpecific();
}
	

//Reinitialize programs with random orders
void RACE::Restart()
{
	unsigned char i;
	for(i=0;i<MAX_LENGTH;i++)
	{
		program[i].order=rand()%Max_Build_Types;
		program[i].built=0;
		program[i].success=0;
	// TODO: Maybe later implement a whole function to create a start list
	// ... mmmh... maybe just something with Set_Goals...
	// would decrease the time until the program can start time-optimization
	// but maybe we loose a possible solution... well...
		program[i].time=20000;
//		program[i].temp=0;
	// TODO: Maybe implement later researches / updates / certain buildings only one time per build order... Trying to research things more than once is senseless...
	}
	timer=setup.Max_Time;
	IP=0;
	length=MAX_LENGTH;
}

RACE::RACE()
{
}

