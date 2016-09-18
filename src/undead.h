#include "race.h"

class Player_Undead: public RACE
{
	unsigned char last_used; //only for unsummon: the last required / used building
	unsigned char unsummon_count[3];
	unsigned char unsummon_type[3];
public:
	virtual void Set_Goals();
	virtual void Calculate();
	virtual void InitRaceSpecific();
	virtual void readjust_goals();
	Player_Undead();
	virtual ~Player_Undead();
};
