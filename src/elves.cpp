#include "elves.h"
#include "settings.h"

// MOVED all #defines for units/buildings/upgrades to main.h (because the stats thingy)

#define BUILDING_TYPES_ELVES 50

	void Player_Elves::Set_Goals()
	{
		unsigned char i,j,k;
		long Need_Wood;
		building_types=BUILDING_TYPES_ELVES;


//-----General (put it in races.cpp later)----------
		for(j=0;j<6;j++)
		for(i=0;i<BUILDING_TYPES_ELVES;i++)
			if(goal[i].what>0)
			{
				Ziel[i]=1;

				for(k=0;k<3;k++)
					if((stats[ELVES][i].prerequisite[k]>0)&&(goal[stats[ELVES][i].prerequisite[k]].what==0))
						goal[stats[ELVES][i].prerequisite[k]].what=1;
				if((stats[ELVES][i].facility>0)&&(goal[stats[ELVES][i].facility].what==0))
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
						Ziel[TREE_OF_AGES]=1;break;
					case ENCHANTED_BEARS:if(goal[DRUID_OF_CLAW_TRAINING].what<2) goal[DRUID_OF_CLAW_TRAINING].what=2;break;
					case ENCHANTED_CROWS:if(goal[DRUID_OF_THALON_TRAINING].what<2) goal[DRUID_OF_THALON_TRAINING].what=2;break;
					case STRENGTH_OF_THE_MOON:
					case MOON_ARMOR:
					case STRENGTH_OF_THE_WILD:
					case REINFORCED_HIDE:
							if(goal[i].what==2) Ziel[TREE_OF_AGES]=1; else if((goal[i].what==3)&&(goal[TREE_OF_ETERNITY].what==0)) goal[TREE_OF_ETERNITY].what=1;break;
								     

					case DRUID_OF_CLAW_TRAINING:
					case DRUID_OF_THALON_TRAINING:if((goal[i].what==2)&&(goal[TREE_OF_ETERNITY].what==0)) goal[TREE_OF_ETERNITY].what=1;break;
					default:break;
				}
			}
		if((goal[TREE_OF_ETERNITY].what==0)&&(Ziel[TREE_OF_AGES]>0)) goal[TREE_OF_AGES].what=1; // ERROR: goal[stronghold]>1
		
		Ziel[WISP]=1;
		Ziel[TREE_OF_LIFE]=1;
		Ziel[MOONWELL]=1;

		Need_Wood=0;
		for(i=0;i<BUILDING_TYPES_ELVES;i++)
			Need_Wood+=(goal[i].what*stats[ELVES][i].res[WOOD]);
		//TODO: Fehler: Morphupgrades (mit nur 'Ziel=...' werden ignoriert) Also die Schritte townhall->keep->castle nur castle

		if(Need_Wood>0)
		{
			Ziel[ONE_WOOD_WISP_TO_MINE]=1;
			Ziel[ONE_GOLD_WISP_TO_FOREST]=1;
		}

		Max_Build_Types=0;
		for(i=0;i<BUILDING_TYPES_ELVES;i++)
		if(Ziel[i]==1)
		{
			Build_Av[Max_Build_Types]=i;
			Max_Build_Types++;
		}
//Redo here some welves (ghouls!)

		goal[ONE_GOLD_WISP_TO_FOREST].what=0; // Just to be sure :)
		goal[ONE_WOOD_WISP_TO_MINE].what=0;		
	}
	
// Test whether the item can be build (minerals, wood, supply, buildings, ...)
	void Player_Elves::Build(unsigned char what)
	{
		unsigned char m;
		suc=0;

			if(what==ONE_GOLD_WISP_TO_FOREST)
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
			if(what==ONE_WOOD_WISP_TO_MINE)
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
		
			if( (Supply<stats[ELVES][what].supply) && (stats[ELVES][what].supply>0)) suc=4;
			else 
				//TODO: Allgemein schreib0rn!
			if ( res[GOLD]<stats[ELVES][what].res[GOLD]+(stats[race][what].type==4)*force[what]*stats[race][what].upres[GOLD]) suc=2;
			else
			if ( res[WOOD]<stats[ELVES][what].res[WOOD]+(stats[race][what].type==4)*force[what]*stats[race][what].upres[WOOD]) suc=3;
			else if	(PeonAt[GOLD]+PeonAt[WOOD]<1*(stats[ELVES][what].type==2)) suc=6;
			else //Check whether this is already researched/upgraded
				
			if(
			 (stats[ELVES][what].type>=3)&&
			 ((stats[ELVES][what].type!=4)||(force[what]>=3)||(availible[what]!=1))&&
			 ((stats[ELVES][what].type!=3)||(force[what]!=0)||(availible[what]!=1))
			) suc=7;
			else
		       if( ((stats[ELVES][what].prerequisite[0]==0)||(force[stats[ELVES][what].prerequisite[0]]>0))&&
 			   ((stats[ELVES][what].prerequisite[1]==0)||(force[stats[ELVES][what].prerequisite[1]]>0))&&
			   ((stats[ELVES][what].prerequisite[2]==0)||(force[stats[ELVES][what].prerequisite[2]]>0))&&
			   ((stats[ELVES][what].facility==0)||(availible[stats[ELVES][what].facility]>0)) && (nr<255))
//TODO: 'suc' rein
		{
			switch(what) 
	// TODO: Maybe generalize the whole part... i.e. prequesite and availible building in the stats :-o
	// TODO: Maybe optimize the order of checks to improve speed
			{

				//SUC!!
				case NATURES_BLESSING:
					if(availible[TREE_OF_ETERNITY]>0)
					{
						building[nr].facility=TREE_OF_ETERNITY;
						Produce(what);
						availible[TREE_OF_ETERNITY]--;
					}
					else if(availible[TREE_OF_AGES]>0)
					{
						building[nr].facility=TREE_OF_AGES;
						Produce(what);
						availible[TREE_OF_AGES]--;
					};break;
				case BACKPACK_ELVES:
				case WISP:if(availible[TREE_OF_ETERNITY]>0)
						{
						building[nr].facility=TREE_OF_ETERNITY;
						Produce(what);
						availible[TREE_OF_ETERNITY]--;
						}					     
					     else if(availible[TREE_OF_AGES]>0)
					     {
						building[nr].facility=TREE_OF_AGES;
					      	     Produce(what);
						availible[TREE_OF_AGES]--;
					     }
					     else if(availible[TREE_OF_LIFE]>0)
					     {
						building[nr].facility=TREE_OF_LIFE;
						     Produce(what);
						     availible[TREE_OF_LIFE]--;
					     };break;
	
				case BALLISTA:
					     if(force[TREE_OF_AGES]+force[TREE_OF_ETERNITY]>0)
					     {
						     Produce(what);
						     availible[ANCIENT_OF_WAR]--;
					     };break;
				case ANCIENT_OF_LORE:
				case ANCIENT_OF_WIND:
					     if(force[TREE_OF_AGES]+force[TREE_OF_ETERNITY]>0)
						     Produce(what);break;
				case IMPROVED_BOWS:
				case SENTINEL:
				case IMPALING_BOLT:
					     if(force[TREE_OF_AGES]+force[TREE_OF_ETERNITY]>0)
					     {
						    Produce(what);
						    availible[ANCIENT_OF_WIND]--;
					     };break;
				case ENCHANTED_BEARS:if(force[DRUID_OF_CLAW_TRAINING]==2)
							     {
								     Produce(what);
								     availible[ANCIENT_OF_LORE]--;
							     };break;
				case ENCHANTED_CROWS:
						     if(force[DRUID_OF_THALON_TRAINING]==2)
						     {
							     Produce(what);
							     availible[ANCIENT_OF_WIND]--;
						     };break;
				case STRENGTH_OF_THE_MOON:
				case MOON_ARMOR:
				case STRENGTH_OF_THE_WILD:
				case REINFORCED_HIDE:
					if( (force[what]==0) || ((force[what]==1)&&(force[TREE_OF_AGES]+force[TREE_OF_ETERNITY]>0)) || ((force[what]==2)&&(force[TREE_OF_ETERNITY]>0)))
					{
						Produce(what);
						availible[HUNTERS_HALL]--;
					};break;

				case DRUID_OF_CLAW_TRAINING:
					if( (force[what]==0) || ((force[what]==1)&&(force[TREE_OF_ETERNITY]>0)))
					{
						Produce(what);
						availible[ANCIENT_OF_LORE]--;
					};break;
				case DRUID_OF_THALON_TRAINING:
					if( (force[what]==0) || ((force[what]==1)&&(force[TREE_OF_ETERNITY]>0)))
					{
						Produce(what);
						availible[ANCIENT_OF_WIND]--;
					};break;
				case TREE_OF_AGES:if(availible[TREE_OF_LIFE]>0)
						  {
							  Produce(what);
							  availible[TREE_OF_LIFE]--;
						  };break;
				case TREE_OF_ETERNITY:if(availible[TREE_OF_AGES]>0)
						      {
							      Produce(what);
							      availible[TREE_OF_AGES]--;
						      };break;
			        default:Produce(what);if(stats[ELVES][what].facility>0) availible[stats[ELVES][what].facility]--;break;
				
			}
			if((ok==1)&&(stats[race][what].type==2))				        
			{
			building[nr].RB+=5; //5 in game seconds to reach the building site
			if(PeonAt[GOLD]>0)
				PeonAt[GOLD]--;
			else if(PeonAt[WOOD]>0)
				PeonAt[WOOD]--;

			//TODO: Insert check whether there are enough peons!!
	         }
		}
	}
			if((suc==0)&&(ok==0))
				suc=1;
	}

// Do one run, go through one build order and record the results	
	void Player_Elves::Calculate()
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

						if(stats[ELVES][building[j].type].facility>0)
							availible[stats[ELVES][building[j].type].facility]++;
						switch(building[j].type)
						{
							case BACKPACK_ELVES:availible[building[j].facility]++;break;
							case WISP:PeonAt[GOLDMINE]++;
								  availible[building[j].facility]++;break;
							case MOONWELL:Supply+=8;Max_Supply+=8;break;
							case TREE_OF_LIFE:Supply+=10;Max_Supply+=10;break;
							case TREE_OF_AGES:force[TREE_OF_LIFE]--;break; 
							case TREE_OF_ETERNITY:force[TREE_OF_AGES]--;break;
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
}

Player_Elves::Player_Elves()
{
}

Player_Elves::~Player_Elves()
{
}

void Player_Elves::readjust_goals()
{
	//nothing to readjust here as Terra has no morphing units
}
