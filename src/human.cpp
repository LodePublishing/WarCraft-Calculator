#include "human.h"
#include "settings.h"

// MOVED all #defines for units/buildings/upgrades to main.h (because the stats thingy)

#define BUILDING_TYPES_HUMAN 54

	void Player_Human::Set_Goals()
	{
		unsigned char i,j,k;
		long Need_Wood;
		building_types=BUILDING_TYPES_HUMAN;


//-----General (put it in races.cpp later)----------
		for(j=0;j<6;j++)
		for(i=0;i<BUILDING_TYPES_HUMAN;i++)
			if(goal[i].what>0)
			{
				Ziel[i]=1;

				for(k=0;k<3;k++)
					if((stats[HUMAN][i].prerequisite[k]>0)&&(goal[stats[HUMAN][i].prerequisite[k]].what==0))
						goal[stats[HUMAN][i].prerequisite[k]].what=1;
				if((stats[HUMAN][i].facility>0)&&(goal[stats[HUMAN][i].facility].what==0))
					goal[stats[HUMAN][i].facility].what=1;
//-------------------------------------------------				
				
				//That should be it for 90%... now here the special items:	
				switch(i)
				{
					case GUARD_TOWER:
					case CANNON_TOWER:
					case ARCANE_TOWER:
						Ziel[SCOUT_TOWER]=1;break;
						
					case WORKSHOP:
					case ARCANE_SANCTUM:
					case CASTLE:
						Ziel[KEEP]=1;break;
					case MELEE_WEAPONS:
					case MELEE_PLATING:
					case RANGED_WEAPONS:
					case LEATHER_ARMOR:
						if(goal[i].what==2) Ziel[KEEP]=1; else if((goal[i].what==3)&&(goal[FORTRESS].what==0)) goal[CASTLE].what=1;break;
					case SORCERESS_TRAINING:
					case PRIEST_TRAINING:
						if((goal[i].what==2)&&(goal[CASTLE].what==0)) goal[CASTLE].what=1;break;
					case LUMBER_HARVESTING:
						Ziel[KEEP]=1;
						if((goal[LUMBER_HARVESTING].what==2)&&(goal[CASTLE].what==0))
							goal[CASTLE].what=1;break;
					case MASONRY:
						if(goal[MASONRY].what==2) Ziel[KEEP]=1;
						if((goal[MASONRY].what==3)&&(goal[CASTLE].what==0)) goal[CASTLE].what=1;break;
				}
			}
		if((goal[CASTLE].what==0)&&(Ziel[KEEP]>0)) goal[KEEP].what=1;
		
		Ziel[PEASANT]=1;
		Ziel[TOWN_HALL]=1;
		Ziel[FARM]=1;

		Need_Wood=0;
		for(i=0;i<BUILDING_TYPES_HUMAN;i++)
			Need_Wood+=(goal[i].what*stats[HUMAN][i].res[WOOD]);
		//TODO: Fehler: Morphupgrades (mit nur 'Ziel=...' werden ignoriert) Also die Schritte townhall->keep->castle nur castle

		if(Need_Wood>0)
		{
			Ziel[ONE_WOOD_PEASANT_TO_MINE]=1;
			Ziel[ONE_GOLD_PEASANT_TO_FOREST]=1;
		}

		Max_Build_Types=0;
		for(i=0;i<BUILDING_TYPES_HUMAN;i++)
		if(Ziel[i]==1)
		{
			Build_Av[Max_Build_Types]=i;
			Max_Build_Types++;
		}
//Redo here some work (ghouls!)

		goal[ONE_GOLD_PEASANT_TO_FOREST].what=0; // Just to be sure :)
		goal[ONE_WOOD_PEASANT_TO_MINE].what=0;		
	}
	
// Test whether the item can be build (minerals, wood, supply, buildings, ...)
	void Player_Human::Build(unsigned char what)
	{
		unsigned char m;
		suc=0;

	//	Das ganze zeug hier in die Race.cpp schreiben (ausser die Spezialfaelle und die peonverschiebeaktion (Undead, ghuls!)
			if(what==ONE_GOLD_PEASANT_TO_FOREST)
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
			if(what==ONE_WOOD_PEASANT_TO_MINE)
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
		
			if( (Supply<stats[HUMAN][what].supply) && (stats[HUMAN][what].supply>0)) suc=4;
			else 
				//TODO: Allgemein schreib0rn!
			if ( res[GOLD]<stats[HUMAN][what].res[GOLD]+(stats[race][what].type==4)*force[what]*stats[race][what].upres[GOLD]) suc=2;
			else
			if ( res[WOOD]<stats[HUMAN][what].res[WOOD]+(stats[race][what].type==4)*force[what]*stats[race][what].upres[WOOD]) suc=3;
			else if	(PeonAt[GOLD]+PeonAt[WOOD]<1*(stats[HUMAN][what].type==2)) suc=6;
			else //Check whether this is already researched/upgraded
				
			if(
			 (stats[HUMAN][what].type>=3)&&
			 ((stats[HUMAN][what].type!=4)||(force[what]>=3)||(availible[what]!=1))&&
			 ((stats[HUMAN][what].type!=3)||(force[what]!=0)||(availible[what]!=1))
			) suc=7;
			else
		       if( ((stats[HUMAN][what].prerequisite[0]==0)||(force[stats[HUMAN][what].prerequisite[0]]>0))&&
 			   ((stats[HUMAN][what].prerequisite[1]==0)||(force[stats[HUMAN][what].prerequisite[1]]>0))&&
			   ((stats[HUMAN][what].prerequisite[2]==0)||(force[stats[HUMAN][what].prerequisite[2]]>0))&&
			   ((stats[HUMAN][what].facility==0)||(availible[stats[HUMAN][what].facility]>0)) && (nr<255))
//TODO: 'suc' rein
		{
			switch(what) 
	// TODO: Maybe generalize the whole part... i.e. prequesite and availible building in the stats :-o
	// TODO: Maybe optimize the order of checks to improve speed
			{
				case BACKPACK:
				case PEASANT:if(availible[CASTLE]>0)
						{
						building[nr].facility=CASTLE;
						Produce(what);
						availible[CASTLE]--;
						}					     
					     else if(availible[KEEP]>0)
					     {
					building[nr].facility=CASTLE;
					      	     Produce(what);
						availible[KEEP]--;
					     }
					     else if(availible[TOWN_HALL]>0)
					     {
						building[nr].facility=TOWN_HALL;
						     Produce(what);
						     availible[TOWN_HALL]--;
					     };break;//~~
					     
				case ARCANE_SANCTUM:
				case WORKSHOP:if(force[KEEP]+force[CASTLE]>0)
							      Produce(what);break;
					
				case LUMBER_HARVESTING:if(((force[what]==0)&&(force[KEEP]+force[CASTLE]>0))||((force[what]==1)&&(force[CASTLE]>0)))
							       {
								       Produce(what);
								       availible[LUMBER_MILL]--;
							       };break;
								       
				case MASONRY:if((force[what]==0)||((force[what]==1)&&(force[KEEP]+force[CASTLE]>0))||((force[what]==2)&&(force[CASTLE]>0)))
						     {
							     Produce(what);
							     availible[LUMBER_MILL]--;
						     };break;
					     
				case MELEE_WEAPONS:
				case MELEE_PLATING:
				case RANGED_WEAPONS:
				case LEATHER_ARMOR:if((force[what]==0)||((force[what]==1)&&(force[KEEP]+force[CASTLE]>0))||((force[what]==2)&&(force[CASTLE]>0)))
							   {
								   Produce(what);
								   availible[BLACKSMITH]--;
							   };break;				
				case PRIEST_TRAINING:
				case SORCERESS_TRAINING:if((force[what]==0)||((force[what]==1)&&(force[CASTLE]>0)))
								{
									Produce(what);
									availible[ARCANE_SANCTUM]--; //~~
								};break;

				case KEEP:if(availible[TOWN_HALL]>0)
						  {
							Produce(what);
		      					availible[TOWN_HALL]--;
						  };break;
	    //well... if I write 'town_hall' in facility it gets a goal... TODO: Change this :)
				case CASTLE:if(availible[KEEP]>0)
						    {
							   Produce(what);
							   availible[KEEP]--;
						    };break;
			        default:Produce(what);if(stats[HUMAN][what].facility>0) availible[stats[HUMAN][what].facility]--;break;
				
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
	void Player_Human::Calculate()
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
							case PEASANT:PeonAt[GOLDMINE]++;
					availible[building[j].facility]++;break;
							case FARM:Supply+=6;Max_Supply+=6;break;
							case TOWN_HALL:if(availible_expansions>0) {availible_expansions--;expansions++;};								  Supply+=12;Max_Supply+=12;break;
							case KEEP:force[TOWN_HALL]--;break;
							case CASTLE:force[KEEP]--;break;
//LUMBER_MILL evtl holz modifikator aendern lassen

							case ARCANE_TOWER:
							case CANNON_TOWER:
							case GUARD_TOWER:availible[SCOUT_TOWER]--;force[SCOUT_TOWER]--;break;
							default:break;
						}
						
						if(building[j].RB==0)
						{
							CheckReady(j);
							if(stats[HUMAN][building[j].type].type==2) 
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
	//nothing to readjust here as Terra has no morphing units
}
