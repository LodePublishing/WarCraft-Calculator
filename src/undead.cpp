#include "undead.h"
#include "settings.h"

// MOVED all #defines for units/buildings/upgrades to main.h (because the stats thingy)

#define BUILDING_TYPES_UNDEAD 50

	void Player_Undead::Set_Goals()
	{
		unsigned char i,j,k;
		long Need_Wood;
		building_types=BUILDING_TYPES_UNDEAD;


//-----General (put it in races.cpp later)----------
		for(j=0;j<6;j++)
		for(i=0;i<BUILDING_TYPES_UNDEAD;i++)
			if(goal[i].what>0)
			{
				Ziel[i]=1;

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
							Ziel[HALLS_OF_THE_DEAD]=1;break;
					case UNHOLY_STRENGTH:
					case UNHOLY_ARMOR:
					case CREATURE_ATTACK:
					case CREATURE_CARAPACE:
						if(goal[i].what==2) Ziel[HALLS_OF_THE_DEAD]=1; else if((goal[i].what==3)&&(goal[BLACK_CITADEL].what==0)) goal[BLACK_CITADEL].what=1;break;

					case NECROMANCER_TRAINING:
					case BANSHEE_TRAINING:
						if((goal[i].what==2)&&(goal[BLACK_CITADEL].what==0)) goal[BLACK_CITADEL].what=1;break;
					default:break;
				}
			}
		if((goal[BLACK_CITADEL].what==0)&&(Ziel[HALLS_OF_THE_DEAD]>0)) goal[HALLS_OF_THE_DEAD].what=1; // ERROR: goal[stronghold]>1
		
		Ziel[ACOLYTE]=1;
		Ziel[NECROPOLIS]=1;
		Ziel[ZIGGURAT]=1;
		Ziel[HAUNTED_GOLD_MINE]=1;

		Need_Wood=0;
		for(i=0;i<BUILDING_TYPES_UNDEAD;i++)
			Need_Wood+=(goal[i].what*stats[UNDEAD][i].res[WOOD]);
		//TODO: Fehler: Morphupgrades (mit nur 'Ziel=...' werden ignoriert) Also die Schritte townhall->keep->castle nur castle

		if(Need_Wood>0)
		{
			Ziel[GHOUL]=1;
			Ziel[CRYPT]=1;
		}

		Max_Build_Types=0;
		for(i=0;i<BUILDING_TYPES_UNDEAD;i++)
		if(Ziel[i]==1)
		{
			Build_Av[Max_Build_Types]=i;
			Max_Build_Types++;
		}
//Redo here some wundead (ghouls!)
	}
	
// Test whether the item can be build (minerals, wood, supply, buildings, ...)
	void Player_Undead::Build(unsigned char what)
	{
		unsigned char m;
		suc=0;

		//TODO: Ghoul management!
		nr=255;
		for(m=0;m<MAX_BUILDINGS;m++)
		if(building[m].RB==0)
		{
			nr=m;
			m=MAX_BUILDINGS;			
		}
		
			if( (Supply<stats[UNDEAD][what].supply) && (stats[UNDEAD][what].supply>0)) suc=4;
			else 
				//TODO: Allgemein schreib0rn!
			if ( res[GOLD]<stats[UNDEAD][what].res[GOLD]+(stats[race][what].type==4)*force[what]*stats[race][what].upres[GOLD]) suc=2;
			else
			if ( res[WOOD]<stats[UNDEAD][what].res[WOOD]+(stats[race][what].type==4)*force[what]*stats[race][what].upres[WOOD]) suc=3;
			else if	(PeonAt[GOLD]+PeonAt[WOOD]<1*(stats[UNDEAD][what].type==2)) suc=6;
			else //Check whether this is already researched/upgraded
				
			if(
			 (stats[UNDEAD][what].type>=3)&&
			 ((stats[UNDEAD][what].type!=4)||(force[what]>=3)||(availible[what]!=1))&&
			 ((stats[UNDEAD][what].type!=3)||(force[what]!=0)||(availible[what]!=1))
			) suc=7;
			else
		       if( ((stats[UNDEAD][what].prerequisite[0]==0)||(force[stats[UNDEAD][what].prerequisite[0]]>0))&&
 			   ((stats[UNDEAD][what].prerequisite[1]==0)||(force[stats[UNDEAD][what].prerequisite[1]]>0))&&
			   ((stats[UNDEAD][what].prerequisite[2]==0)||(force[stats[UNDEAD][what].prerequisite[2]]>0))&&
			   ((stats[UNDEAD][what].facility==0)||(availible[stats[UNDEAD][what].facility]>0)) && (nr<255))
//TODO: 'suc' rein
		{
			switch(what) 
	// TODO: Maybe optimize the order of checks to improve speed
			{
				case HAUNTED_GOLD_MINE:if(availible_expansions>0)
							       {
								       Produce(what);
								       availible_expansions--;
							       };break;
				case BACKPACK_UNDEAD:
				case ACOLYTE:if(availible[BLACK_CITADEL]>0)
						{
						building[nr].facility=BLACK_CITADEL;
						Produce(what);
						availible[BLACK_CITADEL]--;
						}					     
					     else if(availible[HALLS_OF_THE_DEAD]>0)
					     {
						building[nr].facility=HALLS_OF_THE_DEAD;
					      	     Produce(what);
						availible[HALLS_OF_THE_DEAD]--;
					     }
					     else if(availible[NECROPOLIS]>0)
					     {
						building[nr].facility=NECROPOLIS;
						     Produce(what);
						     availible[NECROPOLIS]--;
					     };break;
				case SLAUGHTERHOUSE:
				case TEMPLE_OF_THE_DAMNED:
				case SACRIFICIAL_PIT:
					if(force[HALLS_OF_THE_DEAD]+force[BLACK_CITADEL]>0) Produce(what);break;
				
				case WEB:
				case BURROW_UNDEAD:
					if(force[HALLS_OF_THE_DEAD]+force[BLACK_CITADEL]>0)
					{
						Produce(what);
						availible[CRYPT]--;
					};break;
				
				case UNHOLY_STRENGTH:
				case UNHOLY_ARMOR:
				case CREATURE_ATTACK:
				case CREATURE_CARAPACE:
					if( (force[what]==0) || ((force[what]==1)&&(force[HALLS_OF_THE_DEAD]+force[BLACK_CITADEL]>0)) || ((force[what]==2)&&(force[BLACK_CITADEL]>0)))
					{
						Produce(what);
						availible[GRAVEYARD]--;
					};break;
				case NECROMANCER_TRAINING:
				case BANSHEE_TRAINING:
					if( (force[what]==0) || ((force[what]==1)&&(force[BLACK_CITADEL]>0)))
					{
						Produce(what);
						availible[TEMPLE_OF_THE_DAMNED]--;
					};break;
				case NERUBIAN_TOWER:
				case SPIRIT_TOWER:if(availible[ZIGGURAT]>0)
							  {
								  Produce(what);
								  availible[ZIGGURAT]--;
							  };break;
							  
					
				case HALLS_OF_THE_DEAD:if(availible[NECROPOLIS]>0)
						  {
							Produce(what);
		      					availible[NECROPOLIS]--;
						  };break;
				case BLACK_CITADEL:if(availible[HALLS_OF_THE_DEAD]>0)
						    {
							   Produce(what);
							   availible[HALLS_OF_THE_DEAD]--;
						    };break;
			        default:Produce(what);if(stats[UNDEAD][what].facility>0) availible[stats[UNDEAD][what].facility]--;break;
				
			}
//			if((ok==1)&&(stats[race][what].type==2))				        
//			{
//			building[nr].RB+=5; //5 in game seconds to reach the building site
//			//TODO: Verallgemeinern!
//			if(PeonAt[GOLD]>0)
//				PeonAt[GOLD]--;

			//TODO: Insert check whether there are enough peons!!
//			PeonAt[BUILDING]++;
//	         }
	}
			if((suc==0)&&(ok==0))
				suc=1;
	}

// Do one run, go through one build order and record the results	
	void Player_Undead::Calculate()
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

						if(stats[UNDEAD][building[j].type].facility>0)
							availible[stats[UNDEAD][building[j].type].facility]++;
						switch(building[j].type)
						{
							case HAUNTED_GOLD_MINE:expansions++;break;
							case BACKPACK_UNDEAD:availible[building[j].facility]++;break;
							case ACOLYTE:PeonAt[GOLDMINE]++;availible[building[j].facility]++;break;
							case GHOUL:PeonAt[FOREST]++;break;
							case ZIGGURAT:Supply+=10;Max_Supply+=10;break;
							case SPIRIT_TOWER:
							case NERUBIAN_TOWER:force[ZIGGURAT]--;break;
							case NECROPOLIS:Supply+=10;Max_Supply+=10;break;
							case HALLS_OF_THE_DEAD:force[NECROPOLIS]--;break; 
							case BLACK_CITADEL:force[HALLS_OF_THE_DEAD]--;break;
							default:break;
						}
						
						if(building[j].RB==0)
							CheckReady(j);
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
		if((setup.Scout_Time>0)&&(timer==setup.Scout_Time)&&(PeonAt[GOLD]>0))
			PeonAt[GOLD]--;
		
		timer++;
	}

	length=IP;
	CalculateFitness();
}


void Player_Undead::InitRaceSpecific()
{
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

void Player_Undead::readjust_goals()
{
	//nothing to readjust here as Terra has no morphing units
}
