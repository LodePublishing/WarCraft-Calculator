#include "race.h"

class Player_Orc: public RACE
{
public:
	virtual void Set_Goals();
	virtual void Build(unsigned char what);
	virtual void Calculate();
	virtual void InitRaceSpecific();
	virtual void readjust_goals();
	Player_Orc();
	virtual ~Player_Orc();
};
