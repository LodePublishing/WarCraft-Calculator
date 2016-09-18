#include "undead.h"
#include "settings.h"

// MOVED all #defines for units/buildings/upgrades to main.h (because the stats thingy)


//TODO: UNSUMMON BUILDINGS!!! (50%)
// sinnvolle gebaeude:
// Haunted Gold Mine ? Explodiert die wenn zuende?
// Ziggurat
// Altar of Darkness
// Slaughterhouse
// Graveyard
// savrificial Pit
// boneyard
// Tomb of Relics
// Last building which was either used or needed <- 



	void Player_Undead::Set_Goals()
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
					if((stats[UNDEAD][i].prerequisite[k]>0)&&(goal[stats[UNDEAD][i].prerequisite[k]].what==0))
						goal[stats[UNDEAD][i].prerequisite[k]].what=1;
				if((stats[UNDEAD][i].facility>0)&&(goal[stats[UNDEAD][i].facility].what==0))
					goal[stats[UNDEAD][i].facility].what=1;
//-------------------------------------------------				
				
				//That should be it for 90%... now here the special items:	
				switch(i)
				{
					case SLAUGHTERHOUSE:
					case TEMPLE_OF_THE_DAMNED:
					case SACRIFICIAL_PIT:
					case WEB:
					case BURROW_UNDEAD:
							buildable[HALLS_OF_THE_DEAD]=1;break;
					case UNHOLY_STRENGTH:
					case UNHOLY_ARMOR:
					case CREATURE_ATTACK:
					case CREATURE_CARAPACE:
						if(goal[i].what==2) buildable[HALLS_OF_THE_DEAD]=1; else if((goal[i].what==3)&&(goal[BLACK_CITADEL].what==0)) goal[BLACK_CITADEL].what=1;break;

					case NECROMANCER_TRAINING:
					case BANSHEE_TRAINING:
						if((goal[i].what==2)&&(goal[BLACK_CITADEL].what==0)) goal[BLACK_CITADEL].what=1;break;
					default:break;
				}
			}
		if((goal[TIER3].what==0)&&(buildable[TIER2]>0)&&(goal[TIER2].what==0)) goal[TIER2].what=1; // ERROR: goal[stronghold]>1
		
		buildable[ACOLYTE]=1;
		buildable[NECROPOLIS]=1;
		buildable[ZIGGURAT]=1;
		buildable[HAUNTED_GOLD_MINE]=1;
if(ADDITIONAL_ORDERS==1)
{
		buildable[NOP]=1;
		goal[NOP].what=0;
		buildable[UNSUMMON_BUILDING]=1;
		goal[UNSUMMON_BUILDING].what=0;
		buildable[JMP]=1;
		buildable[IF]=1;
		goal[JMP].what=1;
		goal[IF].what=1;
}

		Need_Wood=0;
		for(i=0;i<MAX_GOALS;i++)
			Need_Wood+=(goal[i].what*stats[UNDEAD][i].res[WOOD]);
		//TODO: Fehler: Morphupgrades (mit nur 'buildable=...' werden ignoriert) Also die Schritte townhall->keep->castle nur castle

		if(Need_Wood>0)
		{
			buildable[GHOUL]=1;
			buildable[CRYPT]=1;
		}

		Max_Build_Types=0;
		for(i=0;i<MAX_GOALS;i++)
		if(buildable[i]==1)
		{
			Build_Av[Max_Build_Types]=i;
			Max_Build_Types++;
		}
//Redo here some wundead (ghouls!)
	}
	
// Do one run, go through one build order and record the results	
	void Player_Undead::Calculate()
	{
		unsigned char tt,j,tSupply,tMax_Supply,i,BuildingRunning;
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
			
			for(i=0;i<3;i++)
				if(unsummon_count[i]>0)
				{
					unsummon_count[i]--;
					res[GOLD]+=stats[UNDEAD][unsummon_type[i]].res[GOLD]*25/stats[UNDEAD][unsummon_type[i]].hp;
					res[WOOD]+=stats[UNDEAD][unsummon_type[i]].res[WOOD]*25/stats[UNDEAD][unsummon_type[i]].hp;
					if(unsummon_count[i]==0)
					{
						force[unsummon_type[i]]--;
						//ZIGGURATS! FOOD!
						unsummon_type[i]=0;
					}
				}
			
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
//gebaeude hoert auf zu produzieren wenn weggeschickt, gebaute sachen werden gecancelt
						// mmmh... halt nen resourcencounter reinhaun (jedes mal wenn bt-- is halt mit rein von 0 auf x erhoehen
						
						//TODO:Problem: If a haunted Gold mine is canceled the expansion is reserved but not freed!!!
						//
						if(stats[UNDEAD][building[j].type].facility>0)
						{
							last_used=stats[UNDEAD][building[j].type].facility;
							availible[stats[UNDEAD][building[j].type].facility]++;
						}
						
							
		//Merken was als letztes benutzt wurde! fuer unsummon
						switch(building[j].type)
						{
							case HAUNTED_GOLD_MINE:expansions++;break;
							case BACKPACK:availible[building[j].facility]++;break;
							case ACOLYTE:PeonAt[GOLDMINE]++;availible[building[j].facility]++;break; // dont unsummon this... 
							case GHOUL:PeonAt[FOREST]++;break;
							case ZIGGURAT:Supply+=10;Max_Supply+=10;break;
							case SPIRIT_TOWER:
							case NERUBIAN_TOWER:force[ZIGGURAT]--;availible[ZIGGURAT]--;break;
							case NECROPOLIS:Supply+=10;Max_Supply+=10;break;
							case HALLS_OF_THE_DEAD:force[NECROPOLIS]--;availible[NECROPOLIS]--;break; 
							case BLACK_CITADEL:force[HALLS_OF_THE_DEAD]--;availible[HALLS_OF_THE_DEAD]--;break;
							default:break;
						}
						unsummon=stats[UNDEAD][building[j].type].facility;//Unsummon is for '-t' only (backtracing goals)
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
			if(Build_Av[program[IP].order]==UNSUMMON_BUILDING)
			{
				if(last_used>0)
				{
					if(availible[last_used]>0)
					{
						for(i=0;i<3;i++)
						{
							if(unsummon_count[i]==0)
							{
								unsummon_count[i]=stats[UNDEAD][last_used].hp/50;
								unsummon_type[i]=last_used;
								availible[last_used]--;
								last_used=0;
								program[IP].built=1;
								ok=1;
								i=4;
							}
						}
						if(i==4) suc=TOO_MANY_BUILDINGS;
						else suc=OK;
					} else suc=BUILDING_AVAILIBLE;
				}
				else suc=TOO_MANY_BUILDINGS;
			} else
			{
			tt++;
			Build(Build_Av[program[IP].order]);
			if(suc>0) program[IP].success=suc;
			if((ok==1)||(tt>MAX_BUILD_TIME))
			{
				if(tt<=MAX_BUILD_TIME) program[IP].time=timer;
				else 
				{
					program[IP].success=TIMEOUT;
					program[IP].time=20000;
				}
				program[IP].need_Supply=tMax_Supply-tSupply;
				program[IP].have_Supply=tMax_Supply;
				tt=0;
				IP++;
			}
			}
		//Scoutpeon
			//TODO: Allgemein!
		if((setup.Scout_Time>0)&&(timer==setup.Scout_Time)&&(PeonAt[GOLD]>0))
			PeonAt[GOLD]--;
		
		timer++;
	}

	length=IP;
	CalculateFitness();
}


void Player_Undead::InitRaceSpecific()
{
	unsigned char i;
	for(i=0;i<3;i++)
	{
		unsummon_count[i]=0;
		unsummon_type[i]=0;
	}
	last_used=0;
	force[NECROPOLIS]=1;
	availible[NECROPOLIS]=1;
	force[ACOLYTE]=4;
	force[GHOUL]=1;
	force[HAUNTED_GOLD_MINE]=1;
// Supply -> how much supply is left
	Supply=4;
	Max_Supply=10;
	PeonAt[BUILDING]=0;
	PeonAt[GOLDMINE]=4;
	PeonAt[FOREST]=1; //Ghoul!
}

Player_Undead::Player_Undead()
{
}

Player_Undead::~Player_Undead()
{
}

void Player_Undead::readjust_goals() //ONLY for -t
{
	unsigned char i,j;
	for(i=0;i<MAX_GOALS;i++)
		if(goal[i].what>0)
		{
			switch(i)
			{
				case NERUBIAN_TOWER:
				case SPIRIT_TOWER:
					if(goal[i].what<=goal[ZIGGURAT].what)
						goal[ZIGGURAT].what--;
					else goal[ZIGGURAT].what=0;break;
				case HALLS_OF_THE_DEAD:
					if(goal[TIER2].what<=goal[TIER1].what)
						goal[TIER1].what-=goal[TIER2].what;
					else goal[TIER1].what=0;break;
				case BLACK_CITADEL:
					if(goal[TIER3].what<=goal[TIER2].what)
						goal[TIER2].what-=goal[TIER3].what;
					else goal[TIER2].what=0;break;
				default:break;
			}
		}
	i=MAX_LENGTH-1;
	while(i>0)
	{
		if(Build_Av[program[i].order]==UNSUMMON_BUILDING)
		{
			j=i;
			while(j>0)
			{
				if(stats[UNDEAD][Build_Av[program[j].order]].unsummon==1)
					goal[Build_Av[program[j].order]].what--;
				j--;
			}
		}
		i--;
	}
}
			
				
