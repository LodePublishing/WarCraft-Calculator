#include <stdlib.h>

#include "settings.h"
#include "race.h"

// TODO: recheck the speed of the units in zerg.cpp, protoss.cpp and terra.cpp
// TODO: Implement the locations of buildings (expansion, wallin, ...)

void RACE::CalculateFitness()
{
	unsigned char i;
	unsigned char bonus[MAX_GOALS]; // temporary data to check whether a bonus is already given (only applies if force > goal)
	pFitness=0;
	sFitness=0;
		
//	for(i=0;i<RESOURCES;i++)
//		sFitness+=(unsigned short)(harvested_res[i]+res[i]);
	sFitness=(unsigned short)harvested_res[GOLD]+(unsigned short)harvested_res[WOOD]/2;
	//Fehlt Modifikator! Mineral_Blocks, Mineral Mod, ...
//TODO: Bugfix
	if(ready==0)
        {
	         timer=setup.Max_Time;
		 for(i=0;i<MAX_GOALS;i++)
                 	if(goal[i].what>0)
	        	{
	                	if(goal[i].what>force[i])
				{
					if(ftime[i]>0) // ftime => when the last item is built 
					{
		//not all goals met and not below time
					if(goal[i].time>0)
					pFitness+=(stats[race][i].Worth*goal[i].time*force[i])/(goal[i].what*ftime[i]);
					else
					pFitness+=(stats[race][i].Worth*setup.Max_Time*force[i])/(goal[i].what*ftime[i]);	
					//else pFitness+=(stats[race][i].Worth*force[i])/goal[i].what;
					}
					else 
					{
						if(goal[i].time>0)
							pFitness+=(stats[race][i].Worth*goal[i].time*force[i])/(goal[i].what*setup.Max_Time);
			        		else pFitness+=(stats[race][i].Worth*force[i])/goal[i].what;
					}
				}
				else //force >= goal
				{
				if((goal[i].time>0)&&(ftime[i]>goal[i].time))
					pFitness+=(goal[i].time*stats[race][i].Worth/ftime[i]);
				else pFitness+=stats[race][i].Worth;
					
/*				if(goal[i].what<force[i])
					for(j=0;j<RESOURCES;j++)
						sFitness-=(force[i]-goal[i].what)*stats[race][i].res[j];*/
				}
		}
// TODO: Check for very small 'goal.time' values, probably in scc.cpp!!	 
	for(i=0;i<MAX_GOALS;i++)
		bonus[i]=goal[i].what-force[i];
	for(i=0;i<MAX_BUILDINGS;i++)
                if((building[i].RB>0)&&(goal[building[i].type].what>force[building[i].type])&&(bonus[building[i].type]>0))
		{
			if((goal[building[i].type].time>0)&&(force[building[i].type]==0))
	                	pFitness+=(building[i].RB*stats[race][building[i].type].Worth*goal[building[i].type].time*force[i])/(goal[building[i].type].what*stats[race][building[i].type].BT*setup.Max_Time);
			else 				   		
				pFitness+=((building[i].RB*stats[race][building[i].type].Worth)/(goal[building[i].type].what*stats[race][building[i].type].BT));
			bonus[building[i].type]--;
		}
	}
	else   // all goals fulfilled, fitness <- timer 
	{
		pFitness=setup.Max_Time-timer;
		for(i=0;i<MAX_GOALS;i++)
	               	if(goal[i].what>0)
	                	pFitness+=race[stats][i].Worth;
	}
}


//Check whether all goals are reached and do some after-completion stuff 
void RACE::CheckReady(unsigned char j)
{
	unsigned char i;

	force[building[j].type]++;
	
	program[building[j].IP][dominant].built=1;
	if(((force[building[j].type]>=goal[building[j].type].what)&&(ftime[building[j].type]==0))||(goal[building[j].type].what==0))
		ftime[building[j].type]=timer; // Get time when the goal was fulfilled OR the time when the last item was build (if goal = 0)
	if((stats[race][building[j].type].type==RESEARCH)||(stats[race][building[j].type].type==UPGRADE))
		availible[building[j].type]=1;
	else
		availible[building[j].type]++;
	ready=1;
	for(i=0;i<MAX_GOALS;i++)
//		ready&=((goal[i].what<=force[i])&&((goal[i].time>=ftime[i])||(goal[i].time==0)));
		ready&=(goal[i].what<=force[i]);	
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
	for(i=0;i<RESOURCES;i++) res[i]-=stats[race][what].res[i];
	building[nr].type=what;
	Supply-=stats[race][what].supply;
	building[nr].on_the_run=0;
	switch(stats[race][what].type)
	{
	case BUILDING:
			building[nr].RB+=REACH_BUILDING_SITE; //5 in game seconds to reach the building site
			if(race!=UNDEAD)
			{
				if(PeonAt[GOLDMINE]>0) PeonAt[GOLDMINE]--;
				else if(PeonAt[WOOD]>0) PeonAt[WOOD]--;
				if(race==ELVES) { force[WISP]--;Supply++;}
				else PeonAt[BUILDING]++;	
				if(race==HUMAN) building[nr].peons=1;
			};break;
		
		case RESEARCH:availible[what]=0;break;
		case UPGRADE:availible[what]=0;
	   	             building[nr].RB+=force[what]*16; //16 in WC, 32 in SC
                  		for(i=0;i<RESOURCES;i++)
		                 	res[i]-=stats[race][what].upres[i]*force[what];break;
		case HERO:if(heroes>0) {res[GOLD]-=425;res[WOOD]-=100;};heroes++;;break;
		default:break;
        };
	building[nr].IP=IP;
	building[nr].dominant=dominant;
	ok=1;
	nr=255;
        for(i=0;i<MAX_BUILDINGS;i++) if(building[i].RB==0)
        {
	        nr=i;
	        i=MAX_BUILDINGS;
        }
}

unsigned char sqrt(unsigned char a)
{
	unsigned char i,b;
	b=a/2;
	for(i=0;i<3;i++)
	{
		if(b==0) return 0;
		b=(b+a/b)/2;	
	}
	return b;
};

// some functions to modify the list of orders
// One of the Core functions
void RACE::Mutate()
{
	unsigned char ta,x,y,k;
//	unsigned char tb,tmp[MAX_LENGTH];
	//length=MAX_LENGTH;
	if(length==0) return;
	
	for(k=0;k<2;k++)
	for(x=0;x<MAX_LENGTH;x++)
	{
		//delete one variabel entry and move
		if(((setup.GenerateBuildorder==0)||(Variabel[Build_Bv[program[x][k].order]]==1))&&(rand()%MAX_LENGTH==0))
		{
			switch(rand()%3)
			{
				case 0://delete one variabel entry and move - Mehrere Schmieden/Kasernen etc. zulassen!
					for(y=x;y<MAX_LENGTH-1;y++)
						program[y][k].order=program[y+1][k].order;
					program[x][k].newmut=1;break;
				case 1://add one variabel entry
					for(y=MAX_LENGTH-1;y>x;y--)
						program[y][k].order=program[y-1][k].order;
					program[y][k].newmut=2;
					y=rand()%Max_Build_Types;
					if(setup.GenerateBuildorder==1)
						while(Variabel[y]==0) y=rand()%Max_Build_Types;
						program[x][k].order=y;break;
				case 2://change one entry
					y=rand()%Max_Build_Types;//Optimieren
					if(setup.GenerateBuildorder==1)
						while(Variabel[y]==0) y=rand()%Max_Build_Types;
						program[x][k].order=y;break;
			}
		}
		else 
		if(rand()%MAX_LENGTH==0)
		{
		//exchange two entries
			y=rand()%MAX_LENGTH; //TODO: Aendern in bevorzugtes Ziel => Naehe
			if(x!=y)
			{
				program[x][k].mutate=y;
				program[y][k].mutate=x;
				ta=program[x][k].order;
				program[x][k].order=program[y][k].order;
				program[y][k].order=ta;
			}
		}

/*        for(i=0;i<currentMutation;i++)
        {
                x=rand()%MAX_LENGTH;
                //delete one variabel entry and move
                if((rand()%(currentMutationRate)==0)&&(Variabel[Build_Bv[program[x].order]]==1))
                {
                        //Mehrere Schmieden/Kasernen etc. zulassen!
                        for(y=x;y<MAX_LENGTH-1;y++)
                                program[y].order=program[y+1].order;
                        program[x].newmut=1;
                } else

                //add one variabel entry
//              x=rand()%MAX_LENGTH;
                if((rand()%(currentMutationRate)==0)&&(Variabel[Build_Bv[program[x].order]]==1))
                {
                        for(y=MAX_LENGTH-1;y>x;y--)
                                program[y].order=program[y-1].order;
                        program[y].newmut=2;
                        y=rand()%Max_Build_Types;
                        while(Variabel[Build_Bv[program[y].order]]==0) y=rand()%Max_Build_Types;
                                program[x].order=y;
                } else

                //change one entry
//              x=rand()%MAX_LENGTH;
                if((rand()%(currentMutationRate)==0)&&(Variabel[Build_Bv[program[x].order]]==1))
                {
                        y=rand()%Max_Build_Types;//Optimieren
                        while(Variabel[y]==0) y=rand()%Max_Build_Types;
                        program[x].order=y;
                } else


                //exchange two entries
                if(rand()%(currentMutationRate)==0)
                {
                        y=sqrt(rand()%(length*length));
                        if(x!=y)
                        {
                        program[x].mutate=y;
                        program[y].mutate=x;

                        ta=program[x].order;
                        program[x].order=program[y].order;
                        program[y].order=ta;
                        }
                }
*/ 
		//rotate a list [ta, ta+1, ..., tb] -> [ta+1, ..., tb, ta]
/*		if(rand()%(currentMutationRate)==0)
		{
			ta=rand()%MAX_LENGTH;
			tb=rand()%MAX_LENGTH;
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
		if(rand()%(currentMutationRate)==0)
		{
			ta=rand()%MAX_LENGTH;
			tb=rand()%MAX_LENGTH;
			x=rand()%MAX_LENGTH;
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
		}*/
	}
		
}


void RACE::Build(unsigned char what)
{
	unsigned char k,l;
	unsigned short life_creeps,life_troups;
	const Stats * stat;
	stat=&stats[race][what];
	suc=0;
	ok=0;
/*	if((ADDITIONAL_ORDERS==1)&&(what==IF))
	{
		if((IP<MAX_LENGTH-1)&&(force[Build_Av[program[IP+1].order]]>0))
		{
			ok=1;
			program[IP].built=1;
			program[IP+1].built=1; //Obacht wegen CancelBuildign bei NE
			IP++;
		}
				
	}
	else
	if((ADDITIONAL_ORDERS==1)&&(what==JMP))
	{
		if(IP<MAX_LENGTH-10)
		{
			ok=1;
			program[IP].built=1;
			IP+=2;			
		}
	} else*/
	if(what==ONE_GOLD_PEASANT_TO_FOREST)
	{
		if(PeonAt[GOLDMINE]>0)
		{
			ok=1;
			PeonAt[GOLDMINE]--;
			PeonAt[FOREST]++;
			program[IP][dominant].built=1;
		} else suc=WORKER_AVAILIBLE;
	}
	else
        if(what==ONE_WOOD_PEASANT_TO_MINE)
	{
		if(PeonAt[FOREST]>0)
		{
			ok=1;
			PeonAt[FOREST]--;
			PeonAt[GOLDMINE]++;
			program[IP][dominant].built=1;
		} else suc=WORKER_AVAILIBLE;
	}
/*	else 
	if((race==UNDEAD)&&(what==UNSUMMON_BUILDING))
	{
	//TODO ?!	
	}*/
	else 
//TODO: Array und testen wo der comp am meisten haengenbleibt und abbricht... moeglichst dann nach oben bringen!			
		if(((stat->prerequisite[0]>0)&&(force[stat->prerequisite[0]]==0))||((stat->prerequisite[1]>0)&&(force[stat->prerequisite[1]]==0))||((stat->prerequisite[2]>0)&&(force[stat->prerequisite[2]]==0))||((stat->special==1)&&(((stat->type==UPGRADE)&&(  ((force[what]==0)&&(force[TIER3]+force[TIER2]==0))||((force[what]==1)&&(force[TIER3]==0))))|| ((stat->type!=UPGRADE)&&(force[TIER3]+force[TIER2]==0))))) suc=TECHNOLOGY_AVAILIBLE;
		//Undead/ork hier rein! merken was als letztes benoetigt wurde!
		else
		if((stat->facility>0)&&(availible[stat->facility]==0)) suc=BUILDING_AVAILIBLE;
                else
                if ((unsigned short)res[GOLD]<(stat->res[GOLD]+(stat->type==UPGRADE)*force[what]*stat->upres[GOLD])) suc=ENOUGH_GOLD;
                else
                if ((unsigned short)res[WOOD]<(stat->res[WOOD]+(stat->type==UPGRADE)*force[what]*stat->upres[WOOD])) 
		suc=ENOUGH_WOOD;
                else
		if( (Supply<stat->supply) && (stat->supply>0)) suc=SUPPLY_SATISFIED;
		else
		if((stat->type==UPGRADE)&&(((force[what]==2)&&(force[TIER3]==0))||((force[what]==1)&&(force[TIER3]+force[TIER2]==0)))) suc=TECHNOLOGY_AVAILIBLE;
		else
		if((stat->type==HERO)&&((force[what]>0)||(heroes>=3)||((heroes==2)&&(force[CASTLE]==0))||((heroes==1)&&(force[CASTLE]+force[KEEP]==0))||((heroes>0)&&((res[GOLD]<425)||(res[WOOD]<100))))) suc=HERO_PROBLEM;
		else
		if((((stat->type==RESEARCH))&&((force[what]>0)||(availible[what]==0)))||(((stat->type==UPGRADE))&&((force[what]>3)||(availible[what]==0)))) suc=RESEARCHED;
		else       		
		if (PeonAt[GOLDMINE]+PeonAt[WOOD]*(race!=UNDEAD)<1*(stat->type==BUILDING)) suc=WORKER_AVAILIBLE;
		else
		if(nr==255) suc=TOO_MANY_BUILDINGS;
		else
//TODO: bei Fehlern trotzdem Auftrag ausfuehren, aber Strafpunkte verteilen!
		if((race==ELVES)&&(what==ENCHANTED_BEARS))
		{
			if(force[DRUID_OF_CLAW_TRAINING]==2)
			{
				Produce(what);
				availible[ANCIENT_OF_LORE]--;
			}
		}
		else if((race==ELVES)&&(what==ENCHANTED_CROWS))
		{
			if(force[DRUID_OF_THALON_TRAINING]==2)
			{
				Produce(what);
				availible[ANCIENT_OF_WIND]--;
			}
		}
		else if((race==ELVES)&&(what==NATURES_BLESSING))
		{
			if(availible[TIER3]>0) {building[nr].facility=TIER3;Produce(what);availible[TIER3]--;}
  			else if(availible[TIER2]>0) {building[nr].facility=TIER2;Produce(what);availible[TIER2]--;}
			else suc=BUILDING_AVAILIBLE;
		}

		//!! On the Run fuer building noch rein, um die exe ueberhaupt zu erreichen!
		else if(((race==UNDEAD)&&(what==HAUNTED_GOLD_MINE))||((race!=UNDEAD)&&(what==TIER1)))
		{
			for(k=0;k<MAX_EXPANSIONS;k++)
				if(Expansion[k].status==1)
				{
					life_troups=0;
					life_creeps=0;
//					for(l=0;l<MAX_CREEPS;l++)
//						life_creeps+=Expansion[k].creeps[l];
					for(l=0;l<MAX_GOALS;l++)
						if(stats[race][l].type==UNIT) life_troups+=stats[race][l].hp*force[l];
					if(life_creeps<=life_troups) { Expansion[k].status=0;}
				}
				for(k=0;k<MAX_EXPANSIONS;k++)
					if(Expansion[k].status==0)
					{
// was ueberlegen hier... v.a. undead unsummon Code umschreiben
//						building[nr].facility=k+1;
						Produce(what);
						Expansion[k].status=2;
						k=MAX_EXPANSIONS;
					}
			if(k<MAX_EXPANSIONS) suc=EXPANSIONS_AVAILIBLE;
		}
		else if( ((race==ORC)&&(what==PILLAGE))||(what==BACKPACK)||(what==PEASANT) )
		{
			if(availible[TIER3]>0) { building[nr].facility=TIER3;Produce(what);availible[TIER3]--;}
        		else if(availible[TIER2]>0) { building[nr].facility=TIER2;Produce(what);availible[TIER2]--;}
	                else if(availible[TIER1]>0) { building[nr].facility=TIER1;Produce(what);availible[TIER1]--;}
	                else suc=BUILDING_AVAILIBLE;
		}
		else if( (race==UNDEAD)&&((what==NERUBIAN_TOWER)||(what==SPIRIT_TOWER)) )
		{
			if(availible[ZIGGURAT]>0) { availible[ZIGGURAT]--;Produce(what);}
			else suc=BUILDING_AVAILIBLE;
		}
		else
		{
	               	Produce(what);
			if(stat->facility>0) availible[stat->facility]--;
		}
	                
	
        if((suc==OK)&&(ok==0))
	        suc=TECHNOLOGY_AVAILIBLE;
	if(suc==OK)
	{
		protein[what]++;
		totalProteins[what]++;
	}
}



// Reset all ongoing data (between two runs)
void RACE::Init()
{
	unsigned char i,j,k;
	heroes=0;
	for(i=0;i<MAX_GOALS;i++)
        {
               force[i]=0;
	       ftime[i]=0;
               if((stats[race][i].type==RESEARCH)||(stats[race][i].type==UPGRADE))
	               availible[i]=1;
	       else
	               availible[i]=0;//Researches that can be researched only once at a time
	}
	for(i=0;i<MAX_BUILDINGS;i++)
	{
	      	building[i].RB=0;
	       	building[i].type=255;
	       	building[i].IP=0;
		building[i].peons=0;	       
		building[i].on_the_run=0;
		building[i].multi=0;
		building[i].peons=0;
		building[i].facility=0;
		building[i].IP=0;
		
	}

	for(k=0;k<2;k++)
	for(i=0;i<MAX_LENGTH;i++)
	{
		program[i][k].mutate=MAX_LENGTH;
		program[i][k].built=0;
		program[i][k].success=0;
		program[i][k].have_Supply=0;
		program[i][k].need_Supply=0;
		program[i][k].time=0;
		for(j=0;j<RESOURCES;j++)
			program[i][k].res[j]=0;
		program[i][k].temp=0;
		program[i][k].newmut=0;
	}
        pFitness=0;
	sFitness=0;
	res[GOLD]=450; //TFT settings... for classic: 800/200
	res[WOOD]=200;
	expansions=0;
	for(i=0;i<MAX_GOALS;i++)
		protein[i]=0;
	for(i=0;i<MAX_EXPANSIONS;i++)
	{
		for(j=0;j<MAX_CREEPS;j++)
			Expansion[i].creeps[j]=rand()%200;
		Expansion[i].status=0; //CREEPS!
		Expansion[i].distance=0;
	}
	PeonAt[GOLDMINE]=5; //Undead!?
	PeonAt[FOREST]=0;
	IP=0;ok=0;nr=0;
	min=0;n=0;unsummon=0;wait_nop=0;suc=0;ready=0;
	harvested_res[GOLD]=0;
	harvested_res[WOOD]=0;
	timer=0;

	
	InitRaceSpecific();
}
//TODO KEEP 255!?
	
void RACE::GenerateBasicBuildOrder()
{
	//problem wieder mit keep/castle
	unsigned char i,j,k,pre[MAX_GOALS],build_max,sup;
	build_max=0;
	for(j=0;j<2;j++)
	for(i=0;i<MAX_LENGTH;i++)
		Basic[i][j]=0;
	Basic_Length=0;

	if(race!=UNDEAD)
	{
		Basic[0][0]=Build_Bv[ONE_GOLD_PEASANT_TO_FOREST];
		Basic[1][0]=Build_Bv[ONE_GOLD_PEASANT_TO_FOREST];
		Basic[2][0]=Build_Bv[WISP];
		Basic[3][0]=Build_Bv[WISP];
		i=3;
		sup=3;
	}
	else
	{
		Basic[0][0]=Build_Bv[ACOLYTE];
		Basic[1][0]=Build_Bv[ACOLYTE];
		i=1;
		sup=2;
	}
	switch(race)
	{
		case UNDEAD:build_max=UNDEAD_BUILDINGS;break;
		case ORC:build_max=ORC_BUILDINGS;break;
		case ELVES:build_max=ELVES_BUILDINGS;break;
		case HUMAN:build_max=HUMAN_BUILDINGS;break;
		default:break;
	};
	
	for(j=0;j<MAX_GOALS;j++)
		if(force[j]>0) pre[j]=force[j]; else pre[j]=0;	
//TODO: Problem bei KEEPs
	if(setup.GenerateBuildorder==1)
	{
	for(k=0;k<MAX_LENGTH;k++)
	{
		j=0;
		while((j<build_max)&&(i<MAX_LENGTH-20))
		{
			if(((pre[j]<goal[j].what)&&(goal[j].what>0))||((buildable[j]>0)&&(force[j]==0)&&(pre[j]<buildable[j])))
			{
				if((stats[race][j].facility>0)&&(pre[stats[race][j].facility]==0))
					j=stats[race][j].facility;
                	        else if((stats[race][j].prerequisite[0]>0)&&(pre[stats[race][j].prerequisite[0]]==0))
	                                j=stats[race][j].prerequisite[0];
        	                else if((stats[race][j].prerequisite[1]>0)&&(pre[stats[race][j].prerequisite[1]]==0))
                	                j=stats[race][j].prerequisite[1];
				else if((stats[race][j].prerequisite[2]>0)&&(pre[stats[race][j].prerequisite[2]]==0))
					j=stats[race][j].prerequisite[2];
				else if((stats[race][j].type==UPGRADE)&&(stats[race][j].special>0)&&(pre[TIER3]==0))
					j=TIER3;
				else if((stats[race][j].special>0)&&(pre[TIER2]==0))
					j=TIER2;
				else if((stats[race][j].special>0)&&(pre[TIER3]==0))
					j=TIER3;
				else
				{
					//building!
					if((stats[race][j].type==BUILDING)&&(race==ELVES))
					{
						i++;
						Basic[i][0]=Build_Bv[WISP];
					}
					
					if(((stats[race][j].type==UNIT)||(stats[race][j].type==HERO))&&(stats[race][j].supply>sup))
					{
						i++;
						switch(race)
						{
							case HUMAN:Basic[i][0]=Build_Bv[FARM];pre[FARM]++;sup+=6;break;
							case ORC:Basic[i][0]=Build_Bv[BURROW];pre[BURROW]++;sup+=8;break;
							case ELVES:Basic[i][0]=Build_Bv[MOONWELL];pre[MOONWELL]++;sup+=9;break;
							case UNDEAD:Basic[i][0]=Build_Bv[ZIGGURAT];pre[ZIGGURAT]++;sup+=10;break;
							default:break;
						};
					};
					i++;
					if((stats[race][j].type==UNIT)&&(stats[race][j].supply>0)) sup-=stats[race][j].supply;
					Basic[i][0]=Build_Bv[j];
					pre[j]++;
					j++;
				}
			} else j++;
		}
	}
	}
	Basic_Length=i+1;
	for(j=0;j<MAX_LENGTH;j++)
		Basic[j][1]=Basic[j][0];
}

void RACE::Restart()
{
	unsigned char i,k;
	length=Basic_Length;

	for(k=0;k<2;k++)
	for(i=0;i<length;i++)
	{		
		program[i][k].order=Basic[i][k];
		program[i][k].built=0;
		program[i][k].success=0;
		program[i][k].time=20000;
		program[i][k].temp=0;
	}
	timer=setup.Max_Time;
	IP=0;
}

RACE::RACE()
{
	int i;
	for(i=0;i<MAX_GOALS;i++)
		buildable[i]=0;
}

