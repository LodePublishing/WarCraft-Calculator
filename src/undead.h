#include "race.h"

class Player_Undead: public RACE
{
public:
	virtual void Set_Goals();
	virtual void Build(unsigned char what);
	virtual void Calculate();
	virtual void InitRaceSpecific();
	virtual void readjust_goals();
	Player_Undead();
	virtual ~Player_Undead();
};
