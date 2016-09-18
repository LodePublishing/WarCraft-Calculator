#define UNARMORED 0
#define LIGHT 1
#define MEDIUM 2
#define HEAVY 3
#define FORT 4

#define NORMAL 0
#define PIERCE 1
#define MAGIC 2
#define SIEGE 3
#define SIEGE_PIERCE 4 //Gyroceptor ground//air
#define NORMAL_SIEGE 5 // Mountain Giant
#define MAGIC_SIEGE 6 // Chimaera, after Corrosive Breath
#define PIERCE_NORMAL 7 //~~
#define CHAOS 8 

//#define NORMAL 0
#define INSTANT 1 //?
#define MISSILE 2
#define MSPLASH 3
#define MLINE 4 //Multiple targets: 2 Times vs Ground
#define ARTILLERY 5
#define MISSILE_INSTANT 6
#define MSPLASH_MISSILE 7 
#define MBOUNCE 8 // Huntress
#define ALINE 9 // Multiple Targets Ballistae
#define MISSILE_NORMAL 10 //

#define MELEE 0
#define NONE 0

struct UNIT
{
unsigned short Hit_Points;
unsigned short Hit_Points_Upgrade;
unsigned char Armor_Type;
unsigned char Armor,Armor_Upgrade;
unsigned short Speed;
unsigned char Attack_Type;
unsigned char Weapon_type; //??
unsigned char Gound_Attack[2]; // min/max
unsigned char Air_Attack[2];// min/max
unsigned char Upgrade_Ground_Attack;
unsigned char Upgrade_Air_Attack;
double CoolDown;
unsigned char Range;
unsigned char Range_Upgrade;
unsigned char spells[3];
} units[RACES][20]; //~~


units

int type[];
// Nahkaempfer, Fernkaempfer, Magier1, Magier2, Magier3, Held1, Held2, Held3 //~
int count; // Wahrscheinlichkeit dazu, dass tot (i.e. Spieler nicht schnell genug reagiert oder so) aber irgendwie noch so ein automatisch retreat oder so rein (also 10% der le noch da -> noch am fighten), dafuer 10% weniger Kampfkraft sobald mehr als 10% der units ihre le komplett verloren haetten
float cd_counter; //
int hitpoints; //Total
int position; //Entfernung vom Metzelnmittelpunkt



jeder Einheitentrupp hat nen cooldown-timer (fuer ranges)

	
if( (int)(cd_counter+units[race].









Unit     Hit Points  Armor Type  Armor  Sight  Speed  Build Time Attack Type Weapon Type Ground Attack Air Attack Cooldown Range   Peasant  75 0  1  220  Medium  0  80/60  190 15 Normal Normal 5.5 None 2 Melee   Militia  None None  1  220  Heavy  4/10  140/80  270 N/A Normal Normal 12.5/17 None 1.2 Melee   Footman  135 0  2  420  Heavy  2/8  140/80  270 20 Normal Normal 12.5/17 None 1.35 Melee   Rifleman  205 30  3  520  Medium  0/6  140/80  270 26 Pierce Instant 21/28.5 21/28.5 1.5 40/60   Knight  245 60  4  800/950  Heavy  5/11  140/80  350 45 Normal Normal 25/34 None 1.36 Melee   Priest  135 10  2  290/370  Unarmored  0  140/80  270 28 Magic Missile 8.5 8.5 2 60   Sorceress  155 20  2  325/405  Unarmored  0  140/80  270 30 Magic Missile 9 9 1.75 60   Spell Breaker  215 30  3  650  Heavy  3/9  140/80  300 28 Normal Normal 14/20 None 1.9 25   Gyrocopter  90 30  1  175  Heavy  2/8  180/110  400 25 Siege/Pierce Missile/Instant 7.5/12 6.5/18 2.5/2 Melee/50   Mortar Team  180 70  3  360  Heavy  0/6  140/120  270 40 Siege Artillery 58/99 None 3.5 25 min/115 max   Steam Tank/War Engine  195 60  3  700  Fort  2/8  140/80  220 55 Siege Instant 50/68 None 2.1 19   Gryphon Rider  280 70  4  825/975  Light  0/6  160/90  270 45 Magic Mline 50/68 50/68 2.2/2.4 45   Dragonhawk Rider  235 40  3  700/850  Light  1/7  140/80  350 45 Pierce Missile 16.5/21 16.5/21 1.7 30   Water Elemental 1  None None  None  450  Heavy  0  120/80  220 N/A Pierce Missile 25 25 1.5 30   Water Elemental 2  None None  None  675  Heavy  1  120/80  220 N/A Pierce Missile 35 35 1.5 30   Water Elemental 3  None None  None  900  Heavy  2  120/80  220 N/A Pierce Missile 45 45 1.5 30  Phoenix  None None  None  1250  Light  1  160/60  320 N/A Magic Msplash 68 68 1.4 60
