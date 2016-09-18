#include "race.h"

class Player_Elves: public RACE
{
public:
	virtual void Set_Goals();
	virtual void Calculate();
	virtual void InitRaceSpecific();
	virtual void readjust_goals();
	Player_Elves();
	virtual ~Player_Elves();
};
