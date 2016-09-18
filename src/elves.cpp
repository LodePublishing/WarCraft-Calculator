#include "elves.h"
#include "settings.h"

// MOVED all #defines for units/buildings/upgrades to main.h (because the stats thingy)


//TODO: Moonwells, Detonate

	void Player_Elves::Set_Goals()
	{
		unsigned char i,j,k;
		long Need_Wood;

//-----General (put it in races.cpp later)----------
		for(j=0;j<6;j++)
		for(i=0;i<MAX_GOALS;i++)
			if(goal[i].what>0)
			{
				buildable[i]=1;

				for(k=0;k<3;k++)
					if((stats[ELVES][i].prerequisite[k]>0)&&(goal[stats[ELVES][i].prerequisite[k]].what==0))
						goal[stats[ELVES][i].prerequisite[k]].what=1;
				if((stats[ELVES][i].facility>0)&&(goal[stats[ELVES][i].facility].what==0)&&(i!=TIER2)&&(i!=TIER3))
					goal[stats[ELVES][i].facility].what=1;
//-------------------------------------------------				
				
				//That should be it for 90%... now here the special items:	
				switch(i)
				{
					case BALLISTA:
					case ANCIENT_OF_LORE:
					case ANCIENT_OF_WIND:
					case IMPROVED_BOWS:
					case SENTINEL:
					case IMPALING_BOLT:
					case NATURES_BLESSING:	
					case TREE_OF_ETERNITY:
						buildable[TREE_OF_AGES]=1;break;
					case ENCHANTED_BEARS:if(goal[DRUID_OF_CLAW_TRAINING].what<2) goal[DRUID_OF_CLAW_TRAINING].what=2;break;
					case ENCHANTED_CROWS:if(goal[DRUID_OF_THALON_TRAINING].what<2) goal[DRUID_OF_THALON_TRAINING].what=2;break;
					case STRENGTH_OF_THE_MOON:
					case MOON_ARMOR:
					case STRENGTH_OF_THE_WILD:
					case REINFORCED_HIDE:
							if(goal[i].what==2) buildable[TREE_OF_AGES]=1; else if((goal[i].what==3)&&(goal[TREE_OF_ETERNITY].what==0)) goal[TREE_OF_ETERNITY].what=1;break;
								     

					case DRUID_OF_CLAW_TRAINING:
					case DRUID_OF_THALON_TRAINING:if((goal[i].what==2)&&(goal[TREE_OF_ETERNITY].what==0)) goal[TREE_OF_ETERNITY].what=1;break;
					default:break;
				}
			}
		if((goal[TREE_OF_ETERNITY].what==0)&&(buildable[TREE_OF_AGES]>0)&&(goal[TREE_OF_AGES].what==0)) goal[TREE_OF_AGES].what=1; // ERROR: goal[stronghold]>1
		
		buildable[WISP]=1;
		buildable[TREE_OF_LIFE]=1;
		buildable[MOONWELL]=1;
if(ADDITIONAL_ORDERS==1)
{	
		buildable[CANCEL_BUILDING]=1;
		buildable[NOP]=1;
		buildable[JMP]=1;
		buildable[IF]=1;
		goal[NOP].what=0;
		goal[CANCEL_BUILDING].what=0;
		goal[IF].what=0;
		goal[JMP].what=0;
		
}

		Need_Wood=0;
		for(i=0;i<MAX_GOALS;i++)
			Need_Wood+=(goal[i].what*stats[ELVES][i].res[WOOD]);
		//TODO: Fehler: Morphupgrades (mit nur 'buildable=...' werden ignoriert) Also die Schritte townhall->keep->castle nur castle

		if(Need_Wood>0)
		{
			buildable[ONE_WOOD_WISP_TO_MINE]=1;
			buildable[ONE_GOLD_WISP_TO_FOREST]=1;
		}

		Max_Build_Types=0;
		for(i=0;i<MAX_GOALS;i++)
		if(buildable[i]==1)
		{
			Build_Av[Max_Build_Types]=i;
			Max_Build_Types++;
		}
//Redo here some welves (ghouls!)

		goal[ONE_GOLD_WISP_TO_FOREST].what=0; // Just to be sure :)
		goal[ONE_WOOD_WISP_TO_MINE].what=0;		
	}

// Do one run, go through one build order and record the results	
	void Player_Elves::Calculate()
	{
		unsigned char tt,j,tSupply,tMax_Supply,i;
		ready=0;
		timer=0;
		for(i=0;i<RESOURCES;i++)
			harvested_res[i]=0;
		
//		Vespene_Av=setup.Vespene_Geysirs;		
//		Vespene_Extractors=0;
		tt=0;

		while((timer<setup.Max_Time) && (ready==0) && (IP<MAX_LENGTH))
		{
			tSupply=Supply;// for the log file
			tMax_Supply=Max_Supply;
			BuildingRunning=0;

			Harvest_Resources();
			
			for(j=0;j<MAX_BUILDINGS;j++)
			{
				if(building[j].RB>0)
				{
					BuildingRunning=1;
					building[j].RB--;
					if(building[j].RB==0)
					{
						//TODO: COMPLETELY rewrite this part
/*						if((setup.Time_to_Enemy>0)&&(building[j].type<TOWN_HALL)&&(building[j].on_the_run==0)&&(building[j].type!=PEON))//Transporter!= rein
						{
							building[j].on_the_run=1;
							if(building[j].type==VULTURE)
							{
								if(force[ION_THRUSTERS]>0)
									building[j].RB+=(unsigned short)(setup.Time_to_Enemy*0.75);
								else
									building[j].RB+=setup.Time_to_Enemy;
							}
							else if((building[j].type==MARINE)||(building[j].type==FIREBAT))
							{
								if((force[STIM_PACKS]>0)&&(force[MARINE]<4*force[MEDIC]))
									building[j].RB+=(unsigned short)(setup.Time_to_Enemy*0.75);
								else
									building[j].RB+=setup.Time_to_Enemy;
							}
							else if(building[j].type==WRAITH)
								building[j].RB+=(unsigned short)(setup.Time_to_Enemy*0.75);
							else if((building[j].type<SIEGE_TANK)||(building[j].type==MEDIC)||(building[j].type==SCV)||(building[j].type==GOLIATH)||(building[j].type==GHOST)||(building[j].type==VALKYRIE)||(building[j].type==SCIENCE_VESSEL))
								building[j].RB+=setup.Time_to_Enemy;
							else if(building[j].type==BATTLE_CRUISER)
								building[j].RB+=(unsigned short)(setup.Time_to_Enemy*1.25);
						}*/

						if(stats[ELVES][building[j].type].facility>0)
							availible[stats[ELVES][building[j].type].facility]++;
						switch(building[j].type)
						{
							case BACKPACK:availible[building[j].facility]++;break;
							case WISP:PeonAt[GOLDMINE]++;
								  availible[building[j].facility]++;break;
							case MOONWELL:Supply+=8;Max_Supply+=8;break;
							case TREE_OF_LIFE:expansions++;Supply+=10;Max_Supply+=10;break;
							case TREE_OF_AGES:force[TREE_OF_LIFE]--;availible[TREE_OF_LIFE]--;break; 
							case TREE_OF_ETERNITY:force[TREE_OF_AGES]--;availible[TREE_OF_AGES]--;break;
							default:break;
						}
						
						if(building[j].RB==0)
							CheckReady(j);
					}
				}
			}
			ok=0;
			if(wait_nop>0)
			{
				wait_nop--;
				if(wait_nop==0)
				{
			             program[IP].built=1;
                                     program[IP].need_Supply=tMax_Supply-tSupply;
                                     program[IP].have_Supply=tMax_Supply;
			             program[IP].res[GOLD]=(unsigned short)res[GOLD];
			             program[IP].res[WOOD]=(unsigned short)res[WOOD];
				     IP++;
				}
			}
			
			if(Build_Av[program[IP].order]==NOP)
			{
				if(wait_nop==0) wait_nop=WAIT_NOP_TIME;
			}
			else
                        if(Build_Av[program[IP].order]==CANCEL_BUILDING)
		        {
				if(BuildingRunning>0)
				{
				        min=5000;
				        n=0;
				        for(i=0;i<MAX_BUILDINGS;i++)
					        if(building[i].RB>0)
					        {
						        if((stats[ELVES][building[i].type].type==BUILDING) && (stats[ELVES][building[i].type].BT-building[i].RB<min))
       	                                         // type == 2 because this makes only sense with buildings
							{
								min=stats[ELVES][building[i].type].BT-building[i].RB;
								n=i;
							}
						}
					if(min<5000)
					{
						ok=1;
						PeonAt[FOREST]++;
						res[GOLD]+=stats[ELVES][building[n].type].res[GOLD]*0.5; //?
						res[WOOD]+=stats[ELVES][building[n].type].res[WOOD]*0.5; //?
						Supply--; //another wisp
						force[WISP]++;
						if(building[n].type==TIER1)
						{
							for(j=0;j<MAX_EXPANSIONS;j++)
								if(Expansion[j].status==2)
								{
									j=MAX_EXPANSIONS;
									Expansion[j].status=0;
								
							}
						}
						building[n].type=NOP;//!!!
						building[n].RB=0;
						program[IP].built=1;
						program[building[n].IP].built=1;
						suc=OK;
					} else suc=BUILDING_AVAILIBLE;
				} else suc=BUILDING_AVAILIBLE;
			} else
			{
			Build(Build_Av[program[IP].order]);
			tt++;
//			printf("%s suc: %i\n",stats[ELVES][Build_Av[program[IP].order]].name,suc);
			if(suc>0) program[IP].success=suc; //?
			if((ok==1)||(tt>MAX_BUILD_TIME))
			{
				if(tt<=MAX_BUILD_TIME) program[IP].time=timer;
				else 
				{
					program[IP].success=TIMEOUT; //~
					program[IP].time=20000;
				}
				program[IP].need_Supply=tMax_Supply-tSupply;
				program[IP].have_Supply=tMax_Supply;
				program[IP].res[GOLD]=(unsigned short)res[GOLD];
				program[IP].res[WOOD]=(unsigned short)res[WOOD];
				tt=0;
				IP++;
			} 
			}
		//Scoutpeon
			//TODO: Allgemein!
		if((setup.Scout_Time>0)&&(timer==setup.Scout_Time)&&((PeonAt[GOLD]>0)||(PeonAt[WOOD]>0)))
		{
			if(PeonAt[GOLD]>0)
				PeonAt[GOLD]--;
			else PeonAt[WOOD]--;
		}
		
		timer++;
	}

	length=IP;
	CalculateFitness();
}


void Player_Elves::InitRaceSpecific()
{
	force[TREE_OF_LIFE]=1;
	availible[TREE_OF_LIFE]=1;
	force[WISP]=5;
// Supply -> how much supply is left
	Supply=7;
	Max_Supply=12;
	PeonAt[BUILDING]=0;
	wait_nop=0;
}

Player_Elves::Player_Elves()
{
}

Player_Elves::~Player_Elves()
{
}

void Player_Elves::readjust_goals()
{
	unsigned char i,j;
	goal[WISP].what++; //because the beginning Tree of Life needs one Wisp
	for(i=0;i<MAX_GOALS;i++)
		if(goal[i].what>0)
		{
			if((stats[ELVES][i].type==BUILDING)&&(i!=TREE_OF_ETERNITY)&&(i!=TREE_OF_AGES))
			{
				if(goal[i].what<=goal[WISP].what)
					goal[WISP].what-=goal[i].what;
				else goal[WISP].what=0;
			}
			else if(i==TREE_OF_ETERNITY)
			{
				if(goal[TREE_OF_ETERNITY].what<=goal[TREE_OF_AGES].what)
					goal[TREE_OF_AGES].what-=goal[TREE_OF_ETERNITY].what;
				else goal[TREE_OF_AGES].what=0;
			}
			else if(i==TREE_OF_AGES)
			{
				if(goal[TREE_OF_AGES].what<=goal[TREE_OF_LIFE].what)
					goal[TREE_OF_LIFE].what-=goal[i].what;
				else goal[TREE_OF_LIFE].what=0;
			}
		}
	
	i=MAX_LENGTH-1;
	while(i>0)
	{
		if(Build_Av[program[i].order]==CANCEL_BUILDING)
		{
			j=i;
			while(j>0)
			{
				if(stats[ELVES][Build_Av[program[j].order]].unsummon==1)
					goal[Build_Av[program[j].order]].what--;
				j--;
			}
		}
		i--;
	}

	//Hippogryp rider etc. noch rein!!
}
