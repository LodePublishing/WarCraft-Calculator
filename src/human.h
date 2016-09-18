#include "race.h"

class Player_Human: public RACE
{
public:
	virtual void Set_Goals();
	virtual void Calculate();
	virtual void InitRaceSpecific();
	virtual void readjust_goals();
	Player_Human();
	virtual ~Player_Human();
};
