#include "ork.h"
#include "settings.h"

// MOVED all #defines for units/buildings/upgrades to main.h (because the stats thingy)

#define BUILDING_TYPES_ORC 50

	void Player_Orc::Set_Goals()
	{
		unsigned char i,j,k;
		long Need_Wood;
		building_types=BUILDING_TYPES_ORC;


//-----General (put it in races.cpp later)----------
		for(j=0;j<6;j++)
		for(i=0;i<BUILDING_TYPES_ORC;i++)
			if(goal[i].what>0)
			{
				Ziel[i]=1;

				for(k=0;k<3;k++)
					if((stats[ORC][i].prerequisite[k]>0)&&(goal[stats[ORC][i].prerequisite[k]].what==0))
						goal[stats[ORC][i].prerequisite[k]].what=1;
				if((stats[ORC][i].facility>0)&&(goal[stats[ORC][i].facility].what==0))
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
						Ziel[STRONGHOLD]=1;break;

					case MELEE_WEAPONS_ORC:
					case UNIT_ARMOR:
					case RANGED_WEAPONS_ORC:
					case LEATHER_ARMOR:
						if(goal[i].what==2) Ziel[STRONGHOLD]=1; else if((goal[i].what==3)&&(goal[FORTRESS].what==0)) goal[FORTRESS].what=1;break;
					
					case SHAMAN_TRAINING:
					case WITCH_DOCTOR_TRAINING:
					case SPIRIT_WALKER_TRAINING:
						if((goal[i].what==2)&&(goal[FORTRESS].what==0)) goal[FORTRESS].what=1;break;
					default:break;
				}
			}
		if((goal[FORTRESS].what==0)&&(Ziel[STRONGHOLD]>0)) goal[STRONGHOLD].what=1; // ERROR: goal[stronghold]>1
		
		Ziel[PEON]=1;
		Ziel[GREAT_HALL]=1;
		Ziel[BURROW]=1;

		Need_Wood=0;
		for(i=0;i<BUILDING_TYPES_ORC;i++)
			Need_Wood+=(goal[i].what*stats[ORC][i].res[WOOD]);
		//TODO: Fehler: Morphupgrades (mit nur 'Ziel=...' werden ignoriert) Also die Schritte townhall->keep->castle nur castle

		if(Need_Wood>0)
		{
			Ziel[ONE_WOOD_PEON_TO_MINE]=1;
			Ziel[ONE_GOLD_PEON_TO_FOREST]=1;
		}

		Max_Build_Types=0;
		for(i=0;i<BUILDING_TYPES_ORC;i++)
		if(Ziel[i]==1)
		{
			Build_Av[Max_Build_Types]=i;
			Max_Build_Types++;
		}
//Redo here some work (ghouls!)

		goal[ONE_GOLD_PEON_TO_FOREST].what=0; // Just to be sure :)
		goal[ONE_WOOD_PEON_TO_MINE].what=0;		
	}
	
// Test whether the item can be build (minerals, wood, supply, buildings, ...)
	void Player_Orc::Build(unsigned char what)
	{
		unsigned char m;
		suc=0;

	//	Das ganze zeug hier in die Race.cpp schreiben (ausser die Spezialfaelle und die peonverschiebeaktion (Undead, ghuls!)
			if(what==ONE_GOLD_PEON_TO_FOREST)
			{
				if(PeonAt[GOLDMINE]>0)
				{
					ok=1;
					PeonAt[GOLDMINE]--;
					PeonAt[FOREST]++;
					program[IP].built=1;
				} else suc=6;
			}
			else
			if(what==ONE_WOOD_PEON_TO_MINE)
			{
				if(PeonAt[FOREST]>0)
				{
					ok=1;
					PeonAt[FOREST]--;
					PeonAt[GOLDMINE]++;
					program[IP].built=1;
				} else suc=6;
			}
			else
			{
				nr=255;
				for(m=0;m<MAX_BUILDINGS;m++)
				if(building[m].RB==0)
				{
					nr=m;
					m=MAX_BUILDINGS;			
				}
		
			if( (Supply<stats[ORC][what].supply) && (stats[ORC][what].supply>0)) suc=4;
			else 
				//TODO: Allgemein schreib0rn!
			if ( res[GOLD]<stats[ORC][what].res[GOLD]+(stats[race][what].type==4)*force[what]*stats[race][what].upres[GOLD]) suc=2;
			else
			if ( res[WOOD]<stats[ORC][what].res[WOOD]+(stats[race][what].type==4)*force[what]*stats[race][what].upres[WOOD]) suc=3;
			else if	(PeonAt[GOLD]+PeonAt[WOOD]<1*(stats[ORC][what].type==2)) suc=6;
			else //Check whether this is already researched/upgraded
				
			if(
			 (stats[ORC][what].type>=3)&&
			 ((stats[ORC][what].type!=4)||(force[what]>=3)||(availible[what]!=1))&&
			 ((stats[ORC][what].type!=3)||(force[what]!=0)||(availible[what]!=1))
			) suc=7;
			else
		       if( ((stats[ORC][what].prerequisite[0]==0)||(force[stats[ORC][what].prerequisite[0]]>0))&&
 			   ((stats[ORC][what].prerequisite[1]==0)||(force[stats[ORC][what].prerequisite[1]]>0))&&
			   ((stats[ORC][what].prerequisite[2]==0)||(force[stats[ORC][what].prerequisite[2]]>0))&&
			   ((stats[ORC][what].facility==0)||(availible[stats[ORC][what].facility]>0)) && (nr<255))
//TODO: 'suc' rein
		{
			switch(what) 
	// TODO: Maybe generalize the whole part... i.e. prequesite and availible building in the stats :-o
	// TODO: Maybe optimize the order of checks to improve speed
			{
				case PILLAGE:
				case BACKPACK_ORC:
				case PEON:if(availible[FORTRESS]>0)
						{
						building[nr].facility=FORTRESS;
						Produce(what);
						availible[FORTRESS]--;
						}					     
					     else if(availible[STRONGHOLD]>0)
					     {
						building[nr].facility=STRONGHOLD;
					      	     Produce(what);
						availible[STRONGHOLD]--;
					     }
					     else if(availible[GREAT_HALL]>0)
					     {
						building[nr].facility=GREAT_HALL;
						     Produce(what);
						     availible[GREAT_HALL]--;
					     };break;//~~
				case TROLL_REGENERATION:
				case BERSERKER_STRENGTH:
					     if(force[STRONGHOLD]+force[FORTRESS]>0)
					     {
						     Produce(what);
						     availible[BARRACKS]--;
					     };break;
				case SPIRIT_LODGE:
				case BESTIARY:
					     if(force[STRONGHOLD]+force[FORTRESS]>0) Produce(what);break;
				case MELEE_WEAPONS_ORC:
				case UNIT_ARMOR:
				case RANGED_WEAPONS_ORC:
				case LEATHER_ARMOR:
					     if( (force[what]==0)|| ((force[what]==1)&&(force[STRONGHOLD]+force[FORTRESS]>0)) || ((force[what]==2)&&(force[FORTRESS]>0)))
					     {
						     Produce(what);
						     availible[WARMILL]--;
					     };break;
                                case SHAMAN_TRAINING:
				case WITCH_DOCTOR_TRAINING:
				case SPIRIT_WALKER_TRAINING:
					     if( (force[what]==0) || ((force[what]==1)&&(force[FORTRESS]>0)))
					     { 
						     Produce(what);
						     availible[SPIRIT_LODGE]--;
					     };break;
					
				case STRONGHOLD:if(availible[GREAT_HALL]>0)
						  {
							Produce(what);
		      					availible[GREAT_HALL]--;
						  };break;
	    //well... if I write 'town_hall' in facility it gets a goal... TODO: Change this :)
				case FORTRESS:if(availible[STRONGHOLD]>0)
						    {
							   Produce(what);
							   availible[STRONGHOLD]--;
						    };break;
			        default:Produce(what);if(stats[ORC][what].facility>0) availible[stats[ORC][what].facility]--;break;
				
			}
			if((ok==1)&&(stats[race][what].type==2))				        
			{
			building[nr].RB+=5; //5 in game seconds to reach the building site
			//TODO: Verallgemeinern!
			if(PeonAt[GOLD]>0)
				PeonAt[GOLD]--;
			else if(PeonAt[WOOD]>0)
				PeonAt[WOOD]--;

			//TODO: Insert check whether there are enough peons!!
			PeonAt[BUILDING]++;
	         }
		}
	}
			if((suc==0)&&(ok==0))
				suc=1;
	}

// Do one run, go through one build order and record the results	
	void Player_Orc::Calculate()
	{
		unsigned char tt,j,tSupply,tMax_Supply,i;
		ready=0;
		timer=0;
		for(i=0;i<RESOURCES;i++)
			harvested_res[i]=0;
		
		Vespene_Av=setup.Vespene_Geysirs;		
		Vespene_Extractors=0;
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
							case BACKPACK_ORC:availible[building[j].facility]++;break;
							case PEON:PeonAt[GOLDMINE]++;
								  availible[building[j].facility]++;break;
							case BURROW:Supply+=8;Max_Supply+=8;break;
							case GREAT_HALL:Supply+=10;Max_Supply+=10;break;
							case STRONGHOLD:force[GREAT_HALL]--;break; 
							case FORTRESS:force[STRONGHOLD]--;break;
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
			
			tt++;
			ok=0;
			Build(Build_Av[program[IP].order]);
			if(suc>0) program[IP].success=suc;
			if((ok==1)||(tt>267))
			{
				if(tt<=267) program[IP].time=timer;
				else 
				{
					program[IP].success=8;
					program[IP].time=20000;
				}
				program[IP].need_Supply=tMax_Supply-tSupply;
				program[IP].have_Supply=tMax_Supply;
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
	//nothing to readjust here as Terra has no morphing units
}
