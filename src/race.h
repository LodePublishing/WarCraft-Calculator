#ifndef __RACE_H
#define __RACE_H

#include "main.h"

class RACE
{
public:
	unsigned char expansions,heroes;
	unsigned char force[MAX_GOALS];
	unsigned short ftime[MAX_GOALS]; //when the goal is reached / when the last item is produced
	unsigned char availible[MAX_GOALS];
	
	float res[RESOURCES];
		
	unsigned short min,n,unsummon,wait_nop;
	
	unsigned short PeonAt[WORKPLACES]; // 0: Nothing, 1: building, 2+ :resources 
	unsigned short length,BuildingRunning;
	short Supply,Max_Supply;
	unsigned char suc,IP;

	unsigned char ready;
	struct Program
	{
		unsigned char order,location,need_Supply,have_Supply,success,built;
		unsigned short time,temp,res[RESOURCES];
	} program[MAX_LENGTH];
	struct Building
	{
		unsigned short RB; // Remaining Buildtime
		unsigned short type; // Type of Building
		unsigned char on_the_run; //unit that is running towards the enemy
//		unsigned char location; 
		float multi;
		unsigned char peons; //ONLY for humans
		unsigned char facility; //in what building is it produced (currently only for peons...)
		unsigned char IP;
		// Main, Front, Enemy Front, Enemy Main, Drop(?), Expansion(?)
	} building[MAX_BUILDINGS];

	unsigned char ok,nr;
	float harvested_res[RESOURCES];
	unsigned short pFitness,sFitness,timer; // DELETED: minsready, gasready

	// => human.h, ork.h, elves.h, undead.h
	virtual void Set_Goals() {};
	virtual void Calculate() {}; 
	virtual void InitRaceSpecific() {};
	virtual void readjust_goals() {};

	void CheckReady(unsigned char j);
	void CalculateFitness();
	void Mutate();
	void Restart();
	void Build(unsigned char what);
	void Produce(unsigned char who);
	void Harvest_Resources();
	void Init();
	void GenerateBasicBuildOrder();
	RACE();

};

#endif //__RACE_H
