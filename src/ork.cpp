#include "ork.h"
#include "settings.h"

// MOVED all #defines for units/buildings/upgrades to main.h (because the stats thingy)

	void Player_Orc::Set_Goals()
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
					if((stats[ORC][i].prerequisite[k]>0)&&(goal[stats[ORC][i].prerequisite[k]].what==0))
						goal[stats[ORC][i].prerequisite[k]].what=1;
				if((stats[ORC][i].facility>0)&&(goal[stats[ORC][i].facility].what==0)&&(i!=TIER2)&&(i!=TIER3))
					goal[stats[ORC][i].facility].what=1;
//-------------------------------------------------				
				
				//That should be it for 90%... now here the special items:	
				switch(i)
				{
					
					case TROLL_REGENERATION:
					case BERSERKER_STRENGTH: 
					case SPIRIT_LODGE:
					case BESTIARY:
					case FORTRESS:
						buildable[STRONGHOLD]=1;break;

					case MELEE_WEAPONS_ORC:
					case UNIT_ARMOR:
					case RANGED_WEAPONS_ORC:
					case LEATHER_ARMOR:
						if(goal[i].what==2) buildable[STRONGHOLD]=1; else if((goal[i].what==3)&&(goal[FORTRESS].what==0)) goal[FORTRESS].what=1;break;
					
					case SHAMAN_TRAINING:
					case WITCH_DOCTOR_TRAINING:
					case SPIRIT_WALKER_TRAINING:
						if((goal[i].what==2)&&(goal[FORTRESS].what==0)) goal[FORTRESS].what=1;break;
					default:break;
				}
			}
		if((goal[TIER3].what==0)&&(buildable[TIER2]>0)&&(goal[TIER2].what==0)) goal[TIER2].what=1;
		
		buildable[PEON]=1;
		buildable[GREAT_HALL]=1;
		buildable[BURROW]=1;
if(ADDITIONAL_ORDERS==1)
{
		buildable[NOP]=1;
		goal[NOP].what=0;			
		buildable[IF]=1;
		buildable[JMP]=1;
		goal[IF].what=1;
		goal[JMP].what=1;
}

		Need_Wood=0;
		for(i=0;i<MAX_GOALS;i++)
			Need_Wood+=(goal[i].what*stats[ORC][i].res[WOOD]);
		//TODO: Fehler: Morphupgrades (mit nur 'buildable=...' werden ignoriert) Also die Schritte townhall->keep->castle nur castle

		if(Need_Wood>0)
		{
			buildable[ONE_WOOD_PEON_TO_MINE]=1;
			buildable[ONE_GOLD_PEON_TO_FOREST]=1;
		}

		Max_Build_Types=0;
		for(i=0;i<MAX_GOALS;i++)
		if(buildable[i]==1)
		{
			Build_Av[Max_Build_Types]=i;
			Max_Build_Types++;
		}
//Redo here some work (ghouls!)

		goal[ONE_GOLD_PEON_TO_FOREST].what=0; // Just to be sure :)
		goal[ONE_WOOD_PEON_TO_MINE].what=0;		
	}
	
// Do one run, go through one build order and record the results	
	void Player_Orc::Calculate()
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

						if(stats[ORC][building[j].type].facility>0)
							availible[stats[ORC][building[j].type].facility]++;
						switch(building[j].type)
						{
							case PILLAGE:
							case BACKPACK:availible[building[j].facility]++;break;
							case PEON:PeonAt[GOLDMINE]++;
								  availible[building[j].facility]++;break;
							case BURROW:Supply+=8;Max_Supply+=8;break;
							case GREAT_HALL:expansions++;Supply+=10;Max_Supply+=10;break;
							case STRONGHOLD:force[GREAT_HALL]--;availible[GREAT_HALL]--;break; 
							case FORTRESS:force[STRONGHOLD]--;availible[STRONGHOLD]--;break;
							default:break;
						}
						
						if(building[j].RB==0)
						{
							CheckReady(j);
							if(stats[ORC][building[j].type].type==2) 
							{
								PeonAt[GOLD]++;
								PeonAt[BUILDING]--;
							}
						}
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
//				program[IP].
				tt=0;
				IP++;
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


void Player_Orc::InitRaceSpecific()
{
	force[GREAT_HALL]=1;
	availible[GREAT_HALL]=1;
	force[PEON]=5;
// Supply -> how much supply is left
	Supply=7;
	Max_Supply=12;
	PeonAt[BUILDING]=0;
}

Player_Orc::Player_Orc()
{
}

Player_Orc::~Player_Orc()
{
}

void Player_Orc::readjust_goals()
{
	//TODO: schoener schreiben
	unsigned char i;
	for(i=0;i<MAX_GOALS;i++)
		if(goal[i].what>0)
		{
			if(i==FORTRESS)
			{
				if(goal[FORTRESS].what<=goal[STRONGHOLD].what)
					goal[STRONGHOLD].what-=goal[FORTRESS].what;
				else goal[STRONGHOLD].what=0;
			}
			else if(i==STRONGHOLD)
			{
				if(goal[STRONGHOLD].what<=goal[GREAT_HALL].what)
					goal[GREAT_HALL].what-=goal[STRONGHOLD].what;
				else goal[GREAT_HALL].what=0;
			}
		}
}
