#ifndef __RACE_H
#define __RACE_H

#include "main.h"

class RACE
{
public:
	unsigned char expansions;
	unsigned char force[MAX_GOALS];
	unsigned short ftime[MAX_GOALS]; //when the goal is reached / when the last item is produced
	unsigned char availible[MAX_GOALS];
	
	double res[RESOURCES];
		
	unsigned short min,n;
	
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
//		unsigned char location; /
		unsigned char facility; //in what building is it produced (currently only for peons...)
		unsigned char IP;
		// Main, Front, Enemy Front, Enemy Main, Drop(?), Expansion(?)
	} building[MAX_BUILDINGS];

	unsigned char nr,ok;

	double harvested_res[RESOURCES];
	unsigned short pFitness,sFitness,timer; // DELETED: minsready, gasready

	// => zerg.h, terra.h, protoss.h
	virtual void Set_Goals() {};
	virtual void Build(unsigned char what) {};
	virtual void Calculate() {}; 
	virtual void InitRaceSpecific() {};
	virtual void readjust_goals() {};

	void CheckReady(unsigned char j);
	void CalculateFitness();
	void Mutate();
	void Restart();
	void Produce(unsigned char who);
	
	void Harvest_Resources();
	void Init();
	RACE();

};

#endif //__RACE_H
