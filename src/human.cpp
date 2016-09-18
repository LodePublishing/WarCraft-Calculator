#include "human.h"
#include "settings.h"

// MOVED all #defines for units/buildings/upgrades to main.h (because the stats thingy)

	void Player_Human::Set_Goals()
	{
		unsigned char i,j,k,tmp;
		long Need_Wood;

//-----General (put it in races.cpp later)----------
		for(j=0;j<6;j++)
		for(i=0;i<MAX_GOALS;i++)
			if(goal[i].what>0)
			{
				buildable[i]=1;

				for(k=0;k<3;k++)
					if((stats[HUMAN][i].prerequisite[k]>0)&&(goal[stats[HUMAN][i].prerequisite[k]].what==0))
						goal[stats[HUMAN][i].prerequisite[k]].what=1;
				if((stats[HUMAN][i].facility>0)&&(goal[stats[HUMAN][i].facility].what==0)&&(i!=TIER2)&&(i!=TIER3)&&(stats[HUMAN][i].facility!=SCOUT_TOWER))
				{
					Variabel[stats[HUMAN][i].facility]=1;
					goal[stats[HUMAN][i].facility].what=1;
				}
//-------------------------------------------------				
				
				//That should be it for 90%... now here the special items:	
				switch(i)
				{
					case GUARD_TOWER:
					case CANNON_TOWER:
					case ARCANE_TOWER:
						buildable[SCOUT_TOWER]=1;break;
						
					case WORKSHOP:
					case ARCANE_SANCTUM:
					case CASTLE:
						buildable[KEEP]=1;break;
					case MELEE_WEAPONS:
					case MELEE_PLATING:
					case RANGED_WEAPONS:
					case LEATHER_ARMOR:
						if(goal[i].what==2) buildable[KEEP]=1; else if((goal[i].what==3)&&(goal[FORTRESS].what==0)) goal[CASTLE].what=1;break;
					case SORCERESS_TRAINING:
					case PRIEST_TRAINING:
						if((goal[i].what==2)&&(goal[CASTLE].what==0)) goal[CASTLE].what=1;break;
					case LUMBER_HARVESTING:
						buildable[KEEP]=1;
						if((goal[LUMBER_HARVESTING].what==2)&&(goal[CASTLE].what==0))
							goal[CASTLE].what=1;break;
					case MASONRY:
						if(goal[MASONRY].what==2) buildable[KEEP]=1;
						if((goal[MASONRY].what==3)&&(goal[CASTLE].what==0)) goal[CASTLE].what=1;break;
					case PALADIN:
					case ARCHMAGE:
					case MOUNTAIN_KING:
					case BLOOD_MAGE:
						if(goal[i].what>1) goal[i].what=1;
						tmp=goal[PALADIN].what+goal[ARCHMAGE].what+goal[MOUNTAIN_KING].what+goal[BLOOD_MAGE].what;
						if((tmp==3)&&(goal[CASTLE].what==0)) goal[CASTLE].what=1;
						else if(tmp==2) buildable[KEEP]=1;break;
					default:break;
				}
			}
		if((goal[CASTLE].what==0)&&(buildable[KEEP]>0)&&(goal[KEEP].what==0)) goal[KEEP].what=1;

		buildable[PEASANT]=1;
		buildable[TOWN_HALL]=1;
		buildable[FARM]=1;
	
		for(i=0;i<MAX_GOALS;i++) Variabel[i]=0;
		Variabel[PEASANT]=1;
		Variabel[FARM]=1;
		Variabel[TOWN_HALL]=1;
if(ADDITIONAL_ORDERS==1)
{
                buildable[ADD_PEASANT_TO_BUILDING]=1;
	        goal[ADD_PEASANT_TO_BUILDING].what=0;
		Variabel[ADD_PEASANT_TO_BUILDING]=1;
		buildable[IF]=1;goal[IF].what=0;
		buildable[JMP]=1;goal[JMP].what=0;
		buildable[NOP]=1;goal[NOP].what=0;
		Variabel[IF]=1;Variabel[JMP]=1;Variabel[NOP]=1;
}	

 
 
		for(i=0;i<MAX_GOALS;i++)
			Need_Wood+=(goal[i].what*stats[HUMAN][i].res[WOOD]);
		//TODO: Fehler: Morphupgrades (mit nur 'buildable=...' werden ignoriert) Also die Schritte townhall->keep->castle nur castle
		if(Need_Wood>0)
		{
			buildable[ONE_WOOD_PEASANT_TO_MINE]=1;
			buildable[ONE_GOLD_PEASANT_TO_FOREST]=1;
			Variabel[ONE_WOOD_PEASANT_TO_MINE]=1;
			Variabel[ONE_GOLD_PEASANT_TO_FOREST]=1;
		}

//hier rein, dass benoetigte Gebaeude ebenfalls eine Zeit abbekommen!
// Dann aber erst noch einfuehren, dass es mehrere verschiedene goals geben kann!


	}
	
/*	bool Player_Human::valid() // Just run a fast check for valid build order... ignore resources, workers and build time
	{
		
	}*/



// Do one run, go through one build order and record the results	
	void Player_Human::Calculate()
	{
		unsigned char tt,j,tSupply,tMax_Supply,i,passt;
		ready=0;
		timer=0;
		for(i=0;i<RESOURCES;i++)
			harvested_res[i]=0;
		
//		Vespene_Av=setup.Vespene_Geysirs;		
//		Vespene_Extractors=0;
		tt=0;
		wait_nop=0;
		
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
					passt=0;
					while((building[j].peons>1)&&(passt==0)) //Multibuild!
					{
						if(building[j].multi==0)
						{
							building[j].multi=building[j].RB;
							for(i=0;i<building[j].peons-1;i++)
								building[j].multi*=(1+(building[j].peons*0.15))/(0.85+(building[j].peons*0.15));
							building[j].multi/=(stats[HUMAN][building[j].type].BT*building[j].RB); //??
						}
						if( (res[GOLD]>building[j].multi*stats[HUMAN][building[j].type].res[GOLD]) && (res[WOOD]>=building[j].multi*stats[HUMAN][building[j].type].res[WOOD]) )
						{
							res[GOLD]-=building[j].multi*stats[HUMAN][building[j].type].res[GOLD];
							res[WOOD]-=building[j].multi*stats[HUMAN][building[j].type].res[WOOD];
							passt=1;		
						}
						else
						{
							building[j].multi=0;
							building[j].RB*=(building[j].peons+1)/(building[j].peons);
							building[j].peons--;
						}
					}

					if(building[j].RB>0) building[j].RB--;
						
					if(building[j].RB==0)
					{
						//TODO: COMPLETELY rewrite this part
/*						if((setup.Time_to_Enemy>0)&&(building[j].type<TOWN_HALL)&&(building[j].on_the_run==0)&&(building[j].type!=PEASANT))//Transporter!= rein
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

						if(stats[HUMAN][building[j].type].facility>0)
							availible[stats[HUMAN][building[j].type].facility]++;
						switch(building[j].type)
						{
							case BACKPACK:availible[building[j].facility]++;break;
							case PEASANT:PeonAt[GOLDMINE]++;availible[building[j].facility]++;break;
							case FARM:Supply+=6;Max_Supply+=6;break;
							case TOWN_HALL:expansions++;Supply+=12;Max_Supply+=12;break;
							case KEEP:force[TOWN_HALL]--;availible[TOWN_HALL]--;break;
							case CASTLE:force[KEEP]--;availible[KEEP]--;break;
//LUMBER_MILL evtl holz modifikator aendern lassen

							case ARCANE_TOWER:
							case CANNON_TOWER:
							case GUARD_TOWER:availible[SCOUT_TOWER]--;force[SCOUT_TOWER]--;break;
							default:break;
						}

// hier kein fehler						
						if(building[j].RB==0)
						{
							CheckReady(j);
							if(stats[HUMAN][building[j].type].type==BUILDING) 
							{
								PeonAt[GOLD]+=building[j].peons;
								PeonAt[BUILDING]-=building[j].peons;
								building[j].peons=0;
							}
						}
					}
				}
			}
  
   
//                       program[IP].need_Supply=tMax_Supply-tSupply;
//                       program[IP].have_Supply=tMax_Supply;
//                       program[IP].res[GOLD]=(unsigned short)res[GOLD];
//                       program[IP].res[WOOD]=(unsigned short)res[WOOD];
																						       
			ok=0;
                        if(wait_nop>0)
                        {
	                        wait_nop--;
	                        if(wait_nop==0)
	                        {
		                        program[IP].built=1;
		                        IP++;
				}
		                 
			}
			else
			if(Build_Av[program[IP].order]==NOP)
			{
				if(wait_nop==0) wait_nop=IP/10;
			}
			else if(Build_Av[program[IP].order]==ADD_PEASANT_TO_BUILDING)
			{
				if(PeonAt[GOLDMINE]+PeonAt[FOREST]>0)
				{
					if(BuildingRunning>0)
					{
						min=5000;
						n=0;
						for(i=0;i<MAX_BUILDINGS;i++)
							if(building[i].RB>0)
							{
								if((stats[HUMAN][building[i].type].type==BUILDING) && (stats[HUMAN][building[i].type].BT+REACH_BUILDING_SITE-building[i].RB<min))
								{
									min=stats[HUMAN][building[i].type].BT+REACH_BUILDING_SITE-building[i].RB;
									n=i;
								}
							}
						if((min<5000)&&(building[n].RB<stats[HUMAN][building[n].type].BT))
						{
							ok=1;
							program[IP].built=1;
							PeonAt[BUILDING]++;
							if(PeonAt[GOLDMINE]>0)
								PeonAt[GOLDMINE]--;
							else if(PeonAt[FOREST]>0)
								PeonAt[FOREST]--;
							// else...
							building[n].peons++;
							program[IP].res[GOLD]=(unsigned short)res[GOLD];
			                                program[IP].res[WOOD]=(unsigned short)res[WOOD];
				                        program[IP].need_Supply=tMax_Supply-tSupply;
				                        program[IP].have_Supply=tMax_Supply;
							program[IP].time=timer;
		
							building[n].RB=(building[n].RB*building[n].peons)/(building[n].peons+1);
							suc=OK;
						} else tt++;
					} else suc=BUILDING_AVAILIBLE;
				} else suc=WORKER_AVAILIBLE;
				if((tt>REACH_BUILDING_SITE)||(ok==1))
				{
					program[IP].success=suc;
					IP++;
					tt=0;
				}
			} else
			{	
			tt++;
			Build(Build_Av[program[IP].order]);
			if(suc>0) program[IP].success=suc;
			if((ok==1)||(tt>MAX_BUILD_TIME))
			{
				if(tt<=MAX_BUILD_TIME) 
					program[IP].time=timer;
				else 
				{
					program[IP].success=TIMEOUT;
					program[IP].time=20000;
				}
				program[IP].res[GOLD]=(unsigned short)res[GOLD];
				program[IP].res[WOOD]=(unsigned short)res[WOOD];
				program[IP].need_Supply=tMax_Supply-tSupply;
				program[IP].have_Supply=tMax_Supply;
				program[IP].temp=availible[BARRACKS]+force[BARRACKS];
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


void Player_Human::InitRaceSpecific()
{
	force[TOWN_HALL]=1;
	availible[TOWN_HALL]=1;
	force[PEASANT]=5;
// Supply -> how much supply is left
	Supply=7;
	Max_Supply=12;
	PeonAt[BUILDING]=0;
}

Player_Human::Player_Human()
{
}

Player_Human::~Player_Human()
{
}

void Player_Human::readjust_goals()
{
	unsigned i;
	for(i=0;i<MAX_GOALS;i++)
		if(goal[i].what>0)
		{
			switch(i)
			{
				case GUARD_TOWER:
				case CANNON_TOWER:
				case ARCANE_TOWER:if(goal[i].what<=goal[SCOUT_TOWER].what)
							  goal[SCOUT_TOWER].what-=goal[i].what;
						  else goal[SCOUT_TOWER].what=0;break;

				case TIER2:if(goal[TIER2].what<=goal[TIER1].what)
						   goal[TIER1].what-=goal[TIER2].what;
					   else goal[TIER1].what=0;break;
				case TIER3:if(goal[TIER3].what<=goal[TIER2].what)
						   goal[TIER2].what-=goal[TIER3].what;
					   else goal[TIER2].what=0;break;
				default:break;
			}
		}
}
