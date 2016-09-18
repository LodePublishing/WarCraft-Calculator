#ifndef __MAIN_H
#define __MAIN_H

#define ADDITIONAL_ORDERS 0 

#define MAX_BUILD_TIME 300 //TODO:Problem bei 152... wenn z.B. nur 1 Holzhacker da is...
#define MAX_LENGTH 96
#define RUNNINGS 5 
#define MAX_PLAYER 100
#define MAX_BUILDINGS 10 // How many buildings can you built simultaneously?
#define MAX_GOALS 63

#define MAX_CREEPS 10

//to generalize!
#define TIER1 22
#define TIER2 23
#define TIER3 24

#define MAX_RACES 4
#define HUMAN 0
#define ORC 1
#define ELVES 2
#define UNDEAD 3

#define RESOURCES 2

#define GOLD 0
#define WOOD 1

#define WORKPLACES 3

#define GOLDMINE 0
#define FOREST 1
#define BUILDING 2

#define MAX_PEONS 50


#define PEASANT 0
#define MILITIA 1
#define FOOTMAN 2
#define RIFLEMAN 3
#define KNIGHT 4
#define PRIEST 5
#define SORCERESS 6
#define SPELL_BREAKER 7

#define GYROCEPTOR 8
#define MORTAR_TEAM 9
#define STEAM_TANK 10
#define GRYPHON_RIDER 11
#define DRAGONHAWK_RIDER 12

#define WATER_ELEMENTAL_LVL1 13
#define WATER_ELEMENTAL_LVL2 14
#define WATER_ELEMENTAL_LVL3 15
#define PHOENIX 16

#define PALADIN 17
#define ARCHMAGE 18
#define MOUNTAIN_KING 19
#define BLOOD_MAGE 20

#define FARM 21
#define TOWN_HALL 22
#define KEEP 23
#define CASTLE 24
#define BACKPACK 25
#define BARRACKS 26
#define ALTAR_OF_KINGS 27
#define LUMBER_MILL 28
#define SCOUT_TOWER 29
#define BLACKSMITH 30
#define WORKSHOP 31
#define ARCANE_SANCTUM 32
#define GRYPHON_AVIARY 33
#define ARCANE_VAULT 34
#define GUARD_TOWER 35
#define CANNON_TOWER 36
#define ARCANE_TOWER 37

#define DEFEND 38
#define LONG_RIFLES 39
#define ANIMAL_WAR_TRAINING 40
#define GYROCEPTOR_BOMBS 41
#define WAR_ENGINE 42
#define FLARE 43
#define FRAGMENTATION_SHARDS 44
#define STORM_HAMMERS 45

#define LUMBER_HARVESTING 46
#define MASONRY 47
#define MELEE_WEAPONS 48
#define MELEE_PLATING 49
#define RANGED_WEAPONS 50
#define LEATHER_ARMOR 51
#define PRIEST_TRAINING 52
#define SORCERESS_TRAINING 53
#define CONTROL_MAGIC 54
#define MAGIC_SENTINEL 55

#define HUMAN_BUILDINGS 56

#define ADD_PEASANT_TO_BUILDING 56//!!
//#define NOP 57
#define ONE_WOOD_PEASANT_TO_MINE 58   //!!!
#define ONE_GOLD_PEASANT_TO_FOREST 59


#define PEON 0
#define GRUNT 1
#define HEADHUNTER 2
#define CATAPULT 3
#define RAIDER 4
#define TAUREN 5
#define SHAMAN 6
#define WITCH_DOCTOR 7
#define SPIRIT_WALKER 8
#define KODO_BEAST 9
#define WYVERN_RIDER 10
#define TROLL_BAT_RIDER 11
#define SPIRIT_WOLF_LVL1 12
#define DIRE_WOLF_LVL2 13
#define SHADOW_WOLF_LVL3 14
#define SERPENT_WARD 15

#define BLADEMASTER 16
#define FAR_SEER  17
#define TAUREN_CHIEFTAIN 18
#define SHADOW_HUNTER 19

#define BURROW 20
#define WARMILL 21
#define GREAT_HALL 22
#define STRONGHOLD 23
#define FORTRESS 24
//#define BACK_PACK 25
//#define BARRACKS 26 ! => humans
#define ALTAR_OF_STORMS 27
#define BESTIARY 28
#define SPIRIT_LODGE 29
#define TAUREN_TOTEM 30
#define VOODOO_LOUNGE 31
#define WATCH_TOWER 32

#define PILLAGE 33
#define BERSERKER_STRENGTH 34
#define TROLL_REGENERATION 35
#define BERSERKER 36
#define BURNING_OIL 37
#define REINFORCED_DEFENSE 38
#define ENSNARE 39
#define WAR_DRUMS 40
#define ENVENOMED_SPEARS 41
#define LIQUID_FIRE 42
#define PULVERIZE 43

#define MELEE_WEAPONS_ORC 44 //~~~
#define UNIT_ARMOR 45
#define RANGED_WEAPONS_ORC 46 //~~~
#define SPIKED_BARRICADES 47
#define SHAMAN_TRAINING 48
#define WITCH_DOCTOR_TRAINING 49
#define SPIRIT_WALKER_TRAINING 50

#define ORC_BUILDINGS 51

#define ONE_WOOD_PEON_TO_MINE 58
#define ONE_GOLD_PEON_TO_FOREST 59 //!! 



#define WISP 0
#define ARCHER 1
#define HUNTRESS 2
#define BALLISTA 3
#define DRYAD 4
#define DRUID_OF_CLAW 5
#define MOUNTAIN_GIANT 6
#define HIPPOGRYPH 7
#define DRUID_OF_THALON 8
#define FAERIE_DRAGON 9
#define CHIMAERA 10
#define TREANT 11
#define SPIRIT_OF_VENGEANCE 12
#define VENGEANCE 13

#define DEMON_HUNTER 14
#define KEEPER_OF_THE_GROVE 15
#define PRIESTESS_OF_THE_MOON 16
#define WARDEN 17

#define ANCIENT_OF_WAR 18
#define ANCIENT_OF_LORE 19
#define ANCIENT_OF_WIND 20
#define ANCIENT_PROTECTOR 21
#define TREE_OF_LIFE 22
#define TREE_OF_AGES 23
#define TREE_OF_ETERNITY 24

//#define BACK_PACK 25 !!

#define ANCIENT_OF_WONDERS 26
#define MOONWELL 27
#define ALTAR_OF_ELDERS 28
#define HUNTERS_HALL 29
#define CHIMAERA_ROOST 30

#define IMPROVED_BOWS 31
#define MARKSMANSHIP 32
#define SENTINEL 33
#define MOON_GLAIVE 34
#define IMPALING_BOLT 35
#define ULTRAVISION 36
#define WELL_SPRING 37
#define NATURES_BLESSING 38
#define ABOLISH_MAGIC 39
#define ENCHANTED_BEARS 40
#define HARDENED_SKIN 41
#define RESISTANT_SKIN 42
#define HIPPOGRYPH_TRAINING 43
#define ENCHANTED_CROWS 44
#define CORROSIVE_BREATH 45
#define STRENGTH_OF_THE_MOON 46
#define MOON_ARMOR 47
#define STRENGTH_OF_THE_WILD 48
#define REINFORCED_HIDE 49
#define DRUID_OF_CLAW_TRAINING 50
#define DRUID_OF_THALON_TRAINING 51 

#define ELVES_BUILDINGS 52

#define CANCEL_BUILDING 52

#define ONE_WOOD_WISP_TO_MINE 58
#define ONE_GOLD_WISP_TO_FOREST 59


#define ACOLYTE 0
#define GHOUL 1
#define CRYPT_FIEND 2
#define GARGOYLE 3
#define ABOMINATION 4
#define MEAT_WEAGON 5
#define NECROMANCER 6
#define BANSHEE 7
#define FROST_WYRM 8
#define SHADE 9
#define SKELETON_WARRIOR 10
#define SKELETAL_MAGE 11
#define INFERNAL 12
#define CARRION_BEETLE_LVL1 13
#define CARRION_BEETLE_LVL2 14
#define CARRION_BEETLE_LVL3 15
#define OBSIDIAN_STATUE 16

#define DEATH_KNIGHT 17
#define DREAD_LORD 18
#define LICH 19
#define CRYPT_LORD 20

#define HAUNTED_GOLD_MINE 21
#define NECROPOLIS 22
#define HALLS_OF_THE_DEAD 23
#define BLACK_CITADEL 24
//#define BACKPACK 25 !!

#define CRYPT 26
#define ZIGGURAT 27
#define ALTAR_OF_DARKNESS 28
#define GRAVEYARD 29
#define SLAUGHTERHOUSE 30
#define TEMPLE_OF_THE_DAMNED 31
#define SACRIFICIAL_PIT 32
#define BONEYARD 33
#define TOMB_OF_RELICS 34
#define NERUBIAN_TOWER 35
#define SPIRIT_TOWER 36

#define CANNIBALIZE 37
#define GHOUL_FRENZY 38
#define WEB 39
#define BURROW_UNDEAD 40
#define STONE_FORM 41
#define DIESEASE_CLOUR 42
#define EXHUME_CORPSES 43
#define DESTROYER 44
#define SKELETAL_LONGEVITY 45
#define SKELETAL_MASTERY 46
#define FREEZING_BREATH 47

#define UNHOLY_STRENGTH 48
#define UNHOLY_ARMOR 49
#define CREATURE_ATTACK 50
#define CREATURE_CARAPACE 51
#define NECROMANCER_TRAINING 52
#define BANSHEE_TRAINING 53

#define UNDEAD_BUILDINGS 54

#define UNSUMMON_BUILDING 54


#define IF 60
#define JMP 61
#define MARKER 62

#define NOP 57
#define WAIT_NOP_TIME 10

#define MAX_EXPANSIONS 20

#define REACH_BUILDING_SITE 5
struct EXPANSION
{
	unsigned char status; // 0: free, 1: Creeps, 2: Exe
	unsigned char distance; //in seconds for basic melee
	unsigned char creeps[MAX_CREEPS]; //type of creeps
};


#define MUTATION_WINDOW 0

struct GOAL
{
	unsigned short time,what;
};

//some global variables

extern unsigned char buildable[MAX_GOALS],Build_Av[MAX_GOALS],Build_Bv[MAX_GOALS],Variabel[MAX_GOALS]; //Variabel -> Add/remove peasants as much as you want
extern unsigned char Max_Build_Types,race,colors;//,Test;
extern unsigned short total_goals,currentMutationRate,currentMutation,Generations;
extern GOAL goal[MAX_GOALS];
extern double Harvest_Speed; //~~~
extern long totalProteins[MAX_GOALS];
extern EXPANSION Expansion[MAX_EXPANSIONS];
extern unsigned char Basic[MAX_LENGTH][2],Basic_Length; //Basic: Basic valid build order
//extern unsigned short Mut_Window;
/*const double HARVEST_SPEED_RACE[MAX_RACES][RESOURCES][MAX_PEONS]=
{
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	},
	{
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
        },
	{
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	},
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	}
};*/

#define NAME_LENGTH 24

struct Stats
{
	char name[NAME_LENGTH];
	unsigned short hp;
	unsigned short BT;
	unsigned short res[RESOURCES];
	unsigned char supply;
	unsigned short type; // 0: nothing, 1: unit, 2: building (primarily for differentation between normal buildings and building upgrades), 3: Research, 4: Upgrade, 5: Hero
	unsigned short xp; 
	unsigned char unsummon; //Unsummonable building? i.e. raiders (pillage), wisps (break up building) or acolytes
	unsigned char upres[RESOURCES]; //additional costs for upgrades
        unsigned short Worth;
	unsigned char special; // normal units: keep or castle is needed, upgrades: it's a two-level upgrade only!
	unsigned char prerequisite[3]; // what prerequisit buildings are needed (BESIDES the production building itself)| 0 => ignore
	unsigned char facility; // where the unit is trained (<=> availible!) | 0 => ignore
};

#define NOTHING 0
#define UNIT 1
#define BUILDING 2
#define RESEARCH 3
#define UPGRADE 4
#define HERO 5


#define OK 0
#define TECHNOLOGY_AVAILIBLE 1
#define BUILDING_AVAILIBLE 2
#define ENOUGH_GOLD 3
#define ENOUGH_WOOD 4
#define SUPPLY_SATISFIED 5
#define LARVA_AVAILIBE 6 //<-!
#define WORKER_AVAILIBLE 7
#define RESEARCHED 8				            
#define TIMEOUT 9
#define HERO_PROBLEM 10
#define TOO_MANY_BUILDINGS 11
#define EXPANSIONS_AVAILIBLE 12

const unsigned short Hero_XP[10]={100,125,150,175,200,225,250,275,300,325};
const unsigned short Creep_XP[10]={20,30,40,60,80,120,160,240,320,480};

//Gegnerische bringen 25% mehr! mmmh... ueberlegen...

//zu ueberlegen ob alles abbrechbar ist... mmmh... ob des was bringt? sozusagen deaktivierte Genabschnitte... 

//IGNORE BEFEHL!!!

//Human masonry: 1/5 LE / Level + 1 Armor
//Human Priest/Sorc: 75 LE
//Animal War Training +150 LE Gryphon/Knight


// MinAT, MaxAT, RS, Cooldown, 

const Stats stats[MAX_RACES][MAX_GOALS]=
{
	{
		{"                Peasant", 220, 15,{ 75,  0},1,1, 25,0,{  0,  0},100, 0, {0, 0, 0}, 0}, //no facility as there is special code in human.cpp
		{"                Militia", 220,  0,{  0,  0},1,1, 37,0,{  0,  0},100, 0, {0, 0, 0}, 0}, //~~~
		{"                Footman", 420, 20,{135,  0},2,1, 37,0,{  0,  0},100, 0, {0, 0, 0}, BARRACKS},
		{"               Rifleman", 520, 26,{205, 30},3,1, 50,0,{  0,  0},100, 0, {BLACKSMITH, 0, 0}, BARRACKS},
		{"                 Knight", 800, 45,{245, 60},4,1, 75,0,{  0,  0},100, 0, {BLACKSMITH, CASTLE, 0}, BARRACKS},
		{"                 Priest", 220, 28,{135, 10},2,1, 37,0,{  0,  0},100, 0, {0, 0, 0}, ARCANE_SANCTUM},
		{"              Sorceress", 250, 30,{155, 20},2,1, 37,0,{  0,  0},100, 0, {0, 0, 0}, ARCANE_SANCTUM},
		{"          Spell Breaker", 250, 28,{215, 30},3,1, 37,0,{  0,  0},100, 0, {ARCANE_VAULT, 0, 0}, ARCANE_SANCTUM}, //? 155/20/2 ? CASTLE? 37?
		{"             Gyroceptor", 350, 25,{ 90, 30},1,1, 37,0,{  0,  0},100, 0, {0, 0, 0}, WORKSHOP},
		{"            Mortar Team", 360, 40,{180, 70},3,1, 50,0,{  0,  0},100, 0, {0, 0, 0}, WORKSHOP},
		{"             Steam Tank", 700, 55,{195, 60},3,1, 50,0,{  0,  0},100, 0, {CASTLE, 0, 0}, WORKSHOP},
		{"          Gryphon Rider", 750, 45,{280, 70},4,1,100,0,{  0,  0},100, 0, {0, 0, 0}, GRYPHON_AVIARY},
		{"       Dragonhawk Rider", 750, 45,{235, 40},3,1,100,0,{  0,  0},100, 0, {ARCANE_VAULT, 0, 0}, GRYPHON_AVIARY}, //100 xp?
		{"   Water Elemental LvlA", 450,  0,{  0,  0},0,1, 50,0,{  0,  0},100, 0, {0, 0, 0}, 0},
	        {"   Water Elemental LvlB", 675,  0,{  0,  0},0,1, 75,0,{  0,  0},100, 0, {0, 0, 0}, 0},
	        {"   Water Elemental LvlC", 900,  0,{  0,  0},0,1,100,0,{  0,  0},100, 0, {0, 0, 0}, 0},
  		{"                Phoenix", 500,  0,{  0,  0},0,1,100,0,{  0,  0},100, 0, {0, 0, 0}, 0}, //100 xp?
       	 	{"                Paladin", 500, 55,{  0,  0},5,5,  0,0,{  0,  0},100, 0, {0, 0, 0}, ALTAR_OF_KINGS},
       		{"               Archmage", 500, 55,{  0,  0},5,5,  0,0,{  0,  0},100, 0, {0, 0, 0}, ALTAR_OF_KINGS},
		{"          Mountain King", 500, 55,{  0,  0},5,5,  0,0,{  0,  0},100, 0, {0, 0, 0}, ALTAR_OF_KINGS},
		{"             Blood Mage", 500, 55,{  0,  0},5,5,  0,0,{  0,  0},100, 0, {0, 0, 0}, ALTAR_OF_KINGS},
                {"                   Farm", 500, 35,{ 80, 20},0,2,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
		{"              Town Hall",1500,180,{385,185},0,2,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
		{"                   Keep",2000,120,{320,210},0,0,  0,0,{  0,  0},150, 0, {0, 0, 0}, TOWN_HALL},
		{"                 Castle",2500,120,{380,230},0,0,  0,0,{  0,  0},200, 0, {ALTAR_OF_KINGS, 0, 0}, KEEP},
                {"               Backpack",   0, 20,{ 50, 25},0,3,  0,0,{  0,  0},100, 0, {ARCANE_VAULT, 0, 0}, 0},
		{"               Barracks",1500, 60,{160, 60},0,2,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
		{"         Altar of Kings", 900, 60,{180, 50},0,2,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
		{"            Lumber Mill", 900, 60,{145,  0},0,2,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
		{"            Scout Tower", 500, 25,{ 30, 20},0,2,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
		{"             Blacksmith",1200, 70,{140, 60},0,2,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
		{"               Workshop",1200, 70,{140,140},0,2,  0,0,{  0,  0},100, 1, {BLACKSMITH, 0, 0}, 0},
		{"         Arcane Sanctum",1050, 80,{150,140},0,2,  0,0,{  0,  0},100, 1, {0, 0, 0}, 0},
		{"         Gryphon Aviary",1200, 75,{120,240},0,2,  0,0,{  0,  0},100, 0, {CASTLE, LUMBER_MILL, 0}, 0},
		{"           Arcane Vault", 500, 75,{130, 30},0,2,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
		{"            Guard Tower", 500, 70,{ 80, 60},0,0, 25,0,{  0,  0},100, 0, {LUMBER_MILL, 0, 0}, SCOUT_TOWER},
		{"           Cannon Tower", 600, 80,{170,100},0,0, 25,0,{  0,  0},100, 0, {WORKSHOP, 0, 0}, SCOUT_TOWER}, // Castle?
		{"           Arcane Tower", 500, 70,{ 80, 60},0,0, 25,0,{  0,  0},100, 0, {ARCANE_VAULT, 0, 0}, SCOUT_TOWER}, //Castle? 25xp?
		{"                 Defend",   0, 45,{150,100},0,3,  0,0,{  0,  0},100, 0, {0, 0, 0}, BARRACKS},
		{"             Long Rifle",   0, 30,{ 75,125},0,3,  0,0,{  0,  0},100, 0, {WORKSHOP, 0, 0}, BARRACKS},
		{"    Animal War Training",   0, 40,{150,250},0,3,  0,0,{  0,  0},100, 0, {CASTLE, LUMBER_MILL, BLACKSMITH}, BARRACKS},
		{"       Gyroceptor Bombs",   0, 35,{150,100},0,3,  0,0,{  0,  0},100, 0, {CASTLE, 0, 0}, WORKSHOP},
		{"             War Engine",   0, 40,{ 50,150},0,3,  0,0,{  0,  0},100, 0, {CASTLE, 0, 0}, WORKSHOP},
		{"                  Flare",   0, 30,{ 50, 50},0,3,  0,0,{  0,  0},100, 0, {0, 0, 0}, WORKSHOP},
		{"   Fragmentation Shards",   0, 40,{ 50,100},0,3,  0,0,{  0,  0},100, 0, {CASTLE, 0, 0}, WORKSHOP},
		{"          Storm Hammers",   0, 45,{125,225},0,3,  0,0,{  0,  0},100, 0, {0, 0, 0}, GRYPHON_AVIARY},
       		{"      Lumber Harvesting",   0, 60,{100,  0},0,4,  0,0,{100,  0},100, 1, {0, 0, 0}, LUMBER_MILL},
		{"                Masonry",   0, 60,{100,100},0,4,  0,0,{ 50, 50},100, 0, {0, 0, 0}, LUMBER_MILL},
		{"          Melee Weapons",   0, 60,{100, 50},0,4,  0,0,{150, 50},100, 0, {0, 0, 0}, BLACKSMITH},
		{"          Melee Plating",   0, 60,{125, 75},0,4,  0,0,{ 75, 50},100, 0, {0, 0, 0}, BLACKSMITH},
		{"         Ranged Weapons",   0, 60,{100, 50},0,4,  0,0,{150, 50},100, 0, {0, 0, 0}, BLACKSMITH},
		{"          Leather Armor",   0, 60,{100,100},0,4,  0,0,{ 50, 50},100, 0, {0, 0, 0}, BLACKSMITH},
		{"        Priest Training",   0, 60,{100,  0},0,4,  0,0,{100, 50},100, 1, {0, 0, 0}, ARCANE_SANCTUM},
	        {"     Sorceress Training",   0, 60,{100,  0},0,4,  0,0,{100, 50},100, 1, {0, 0, 0}, ARCANE_SANCTUM},
		{"          Control Magic",   0, 45,{ 75, 75},0,3,  0,0,{  0,  0},100, 0, {ARCANE_VAULT, 0, 0}, ARCANE_SANCTUM},
		{"         Magic Sentinel",   0, 30,{ 50, 50},0,3,  0,0,{  0,  0},100, 0, {0, 0, 0}, ARCANE_SANCTUM},
		{"Add Peasant to Building",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
		{"                    NOP",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
		{"   Wood Peasant to Mine",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
		{" Gold Peasant to Forest",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"                     IF",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"                    JMP",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"                 Marker",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0}
		
	},
//Berserker Strength => +100 le grunt	
        {                        
	        {"                   Peon", 250, 15,{ 75,  0},1,1, 25,0,{  0,  0},100, 0, {0, 0, 0}, 0},
	        {"                  Grunt", 680, 30,{200,  0},3,1, 50,0,{  0,  0},100, 0, {0, 0, 0}, BARRACKS},
	        {"             Headhunter", 280, 22,{135, 20},2,1, 37,0,{  0,  0},100, 0, {WARMILL, 0, 0}, BARRACKS},
	        {"               Catapult", 425, 45,{220, 50},4,1, 75,0,{  0,  0},100, 1, {WARMILL, 0, 0}, BARRACKS},
	        {"                 Raider", 610, 28,{180, 40},3,1, 50,0,{  0,  0},100, 0, {0, 0, 0}, BESTIARY},
	        {"                 Tauren",1300, 50,{280, 80},5,1,100,0,{  0,  0},100, 0, {0, 0, 0}, TAUREN_TOTEM},
	        {"                 Shaman", 260, 30,{130, 20},2,1, 37,0,{  0,  0},100, 0, {0, 0, 0}, SPIRIT_LODGE},
	        {"           Witch Doctor", 240, 30,{145, 25},2,1, 37,0,{  0,  0},100, 0, {0, 0, 0}, SPIRIT_LODGE},
	        {"          Spirit Walker", 250, 42,{195, 35},3,1,  0,0,{  0,  0},100, 0, {VOODOO_LOUNGE, 0, 0}, SPIRIT_LODGE}, //xp?
	        {"             Kodo Beast", 790, 30,{255, 60},4,1, 75,0,{  0,  0},100, 0, {WARMILL, 0, 0}, BESTIARY},
	        {"           Wyvern Rider", 500, 35,{265, 40},4,1, 75,0,{  0,  0},100, 0, {FORTRESS, 0, 0}, BESTIARY},
	        {"        Troll Bat Rider", 500, 25,{160, 40},2,1,  0,0,{  0,  0},100, 0, {FORTRESS, VOODOO_LOUNGE, 0}, BESTIARY}, //xp?
	        {"            Spirit Wolf", 200,  0,{  0,  0},0,1, 25,0,{  0,  0},100, 0, {0, 0, 0}, 0},
	        {"              Dire Wolf", 300,  0,{  0,  0},0,1, 37,0,{  0,  0},100, 0, {0, 0, 0}, 0},
	        {"            Shadow Wolf", 400,  0,{  0,  0},0,1, 50,0,{  0,  0},100, 0, {0, 0, 0}, 0},
	        {"           Serpent Ward",   0,  0,{  0,  0},0,1,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
		{"            Blademaster", 500, 55,{  0,  0},5,5,  0,0,{  0,  0},100, 0, {0, 0, 0}, ALTAR_OF_STORMS},
		{"               Far Seer", 500, 55,{  0,  0},5,5,  0,0,{  0,  0},100, 0, {0, 0, 0}, ALTAR_OF_STORMS},
		{"       Tauren Chieftain", 500, 55,{  0,  0},5,5,  0,0,{  0,  0},100, 0, {0, 0, 0}, ALTAR_OF_STORMS},
		{"          Shadow Hunter", 500, 55,{  0,  0},5,5,  0,0,{  0,  0},100, 0, {0, 0, 0}, ALTAR_OF_STORMS},
                {"                 Burrow", 600, 70,{160, 40},0,2,  0,1,{  0,  0},100, 0, {0, 0, 0}, 0},
 		{"               War Mill",1000, 70,{205,  0},0,2,  0,1,{  0,  0},100, 0, {0, 0, 0}, 0},
		{"             Great Hall",1500,150,{385,185},0,2,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
	        {"             Stronghold",2000,120,{315, 90},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, GREAT_HALL},
	        {"               Fortress",2500,120,{345,210},0,0,  0,0,{  0,  0},100, 0, {ALTAR_OF_STORMS, 0, 0}, STRONGHOLD},
                {"               Backpack",   0, 20,{ 50, 25},0,3,  0,0,{  0,  0},100, 0, {VOODOO_LOUNGE, 0, 0}, 0},
		{"        Altar of Storms", 900, 60,{180, 50},0,2,  0,1,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"               Barracks",1200, 60,{180, 50},0,2,  0,1,{  0,  0},100, 0, {0, 0, 0}, 0},
       	 	{"               Bestiary",1100, 70,{145,140},0,2,  0,1,{  0,  0},100, 1, {0, 0, 0}, 0},
        	{"           Spirit Lodge", 800, 70,{150,150},0,2,  0,1,{  0,  0},100, 1, {0, 0, 0}, 0},
        	{"           Tauren Totem",1200, 70,{ 90,200},0,2,  0,1,{  0,  0},100, 0, {WARMILL, FORTRESS, 0}, 0},
        	{"          Voodoo Lounge", 500, 60,{130, 30},0,2,  0,1,{  0,  0},100, 0, {0, 0, 0}, 0},
        	{"            Watch Tower", 500, 80,{110, 80},0,2,  0,1,{  0,  0},100, 0, {WARMILL, 0, 0}, 0},
        	{"                Pillage",   0, 45,{ 75, 25},0,3,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
		{"     Berserker Strength",   0, 40,{ 50,150},0,3,  0,0,{  0,  0},100, 1, {0, 0, 0}, BARRACKS},
	        {"     Troll Regeneration",   0, 35,{100,100},0,3,  0,0,{  0,  0},100, 1, {WARMILL, 0, 0}, BARRACKS},
	        {"              Berserker",   0, 40,{ 75,175},0,3,  0,0,{  0,  0},100, 1, {FORTRESS, WARMILL, 0}, BARRACKS}, 
	        {"            Burning Oil",   0, 30,{ 50,150},0,3,  0,0,{  0,  0},100, 0, {FORTRESS, 0, 0}, BARRACKS},
	        {"     Reinforced Defense",   0, 60,{ 50,200},0,3,  0,0,{  0,  0},100, 0, {FORTRESS, 0, 0}, WARMILL},
	        {"                Ensnare",   0, 40,{ 50, 75},0,3,  0,0,{  0,  0},100, 0, {0, 0, 0}, BESTIARY},
	        {"              War Drums",   0, 40,{100,150},0,3,  0,0,{  0,  0},100, 0, {FORTRESS, WARMILL, 0}, BESTIARY},
	        {"       Envenomed Spears",   0, 40,{100,150},0,3,  0,0,{  0,  0},100, 0, {FORTRESS, 0, 0}, BESTIARY},
	        {"            Liquid Fire",   0, 75,{ 75,125},0,3,  0,0,{  0,  0},100, 0, {FORTRESS, VOODOO_LOUNGE, 0}, BESTIARY},
	        {"              Pulverize",   0, 40,{100,250},0,3,  0,0,{  0,  0},100, 0, {0, 0, 0}, TAUREN_TOTEM},
	        {"          Melee Weapons",   0, 60,{100, 75},0,4,  0,0,{100, 50},100, 0, {0, 0, 0}, WARMILL},
	        {"             Unit Armor",   0, 60,{150, 75},0,4,  0,0,{150, 75},100, 0, {0, 0, 0}, WARMILL},
	        {"         Ranged Weapons",   0, 60,{ 75, 75},0,4,  0,0,{ 75, 75},100, 0, {0, 0, 0}, WARMILL},
	        {"      Spiked Barrikades",   0, 60,{ 25, 75},0,4,  0,0,{ 25,100},100, 0, {0, 0, 0}, WARMILL}, // !!! Spiked Lvl 3 : 150 Gold!
	        {"        Shaman Training",   0, 60,{100,  0},0,4,  0,0,{100, 50},100, 1, {0, 0, 0}, SPIRIT_LODGE},
	        {"   WitchDoctor Training",   0, 60,{100,  0},0,4,  0,0,{100, 50},100, 1, {0, 0, 0}, SPIRIT_LODGE},
	        {"   Spirit Walker Traini",   0, 60,{100,  0},0,4,  0,0,{100, 50},100, 1, {0, 0, 0}, SPIRIT_LODGE},
	        {"                   NULL",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
		{"                   NULL",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
	        {"                   NULL",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
	        {"                   NULL",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
	        {"                   NULL",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"                   NULL",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
		{"                    NOP",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"      Wood Peon to Mine",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"    Gold Peon to Forest",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"                     IF",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"                    JMP",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"                 Marker",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0}

	},
	{
                {"                   Wisp", 120, 14,{ 60,  0},1,1, 25,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"                 Archer", 250, 20,{130, 10},2,1, 37,0,{  0,  0},100, 0, {0, 0, 0}, ANCIENT_OF_WAR},
		{"               Huntress", 550, 30,{195, 20},3,1, 50,0,{  0,  0},100, 0, {HUNTERS_HALL, 0, 0}, ANCIENT_OF_WAR},
		{"               Ballista", 380, 48,{210, 65},4,1, 75,0,{  0,  0},100, 1, {HUNTERS_HALL, 0, 0}, ANCIENT_OF_WAR},
		{"                  Dryad", 380, 30,{145, 60},3,1, 37,0,{  0,  0},100, 0, {0, 0, 0}, ANCIENT_OF_LORE},
		{"      Druid of the Claw", 430, 30,{255, 80},4,1, 75,0,{  0,  0},100, 0, {0, 0, 0}, ANCIENT_OF_LORE},
		{"         Mountain Giant",1000, 45,{425,100},7,1,  0,0,{  0,  0},100, 0, {ANCIENT_OF_WONDERS, 0, 0}, ANCIENT_OF_LORE}, //xp?
		{"             Hippogryph", 500, 40,{160, 20},2,1, 37,0,{  0,  0},100, 0, {0, 0, 0}, ANCIENT_OF_WIND},
		{"        Druid of Thalon", 225, 22,{135, 20},2,1, 37,0,{  0,  0},100, 0, {0, 0, 0}, ANCIENT_OF_WIND}, //fehlt: hippogryp reiterin
		{"          Faerie Dragon", 200, 25,{155, 25},2,1,  0,0,{  0,  0},100, 0, {ANCIENT_OF_WONDERS, 0, 0}, ANCIENT_OF_WIND}, //xp?
		{"               Chimaera", 900, 65,{330, 70},5,1,100,0,{  0,  0},100, 0, {TREE_OF_ETERNITY, ANCIENT_OF_WIND, 0}, CHIMAERA_ROOST},
		{"                 Treant",  300, 0,{  0,  0},0,1, 25,0,{  0,  0},100, 0, {0, 0, 0}, 0}, //xp?
		{"    Spirit of Vengeance", 500,  0,{  0,  0},0,1,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0}, //xp?
		{"              Vengeance", 500,  0,{  0,  0},0,1,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"           Demon Hunter", 500, 55,{  0,  0},5,5,  0,0,{  0,  0},100, 0, {0, 0, 0}, ALTAR_OF_ELDERS},
                {"    Keeper of the Grove", 500, 55,{  0,  0},5,5,  0,0,{  0,  0},100, 0, {0, 0, 0}, ALTAR_OF_ELDERS},
                {"  Priestess of the Moon", 500, 55,{  0,  0},5,5,  0,0,{  0,  0},100, 0, {0, 0, 0}, ALTAR_OF_ELDERS},
                {"                 Warden", 500, 55,{  0,  0},5,5,  0,0,{  0,  0},100, 0, {0, 0, 0}, ALTAR_OF_ELDERS},
                {"         Ancient of War",1000, 60,{150, 60},0,2, 25,1,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"        Ancient of Lore", 900, 80,{155,145},0,2, 25,0,{  0,  0},100, 1, {0, 0, 0}, 0},
                {"        Ancient of Wind", 900, 70,{150,140},0,2, 25,0,{  0,  0},100, 1, {0, 0, 0}, 0},
                {"      Ancient Protector", 550, 80,{135, 80},0,2, 50,1,{  0,  0},100, 0, {0, 0, 0}, 0},
		{"           Tree of Life",1300,110,{340,185},0,2, 25,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"           Tree of Ages",1700,120,{320, 80},0,0, 25,0,{  0,  0},100, 0, {0, 0, 0}, TREE_OF_LIFE},
                {"       Tree of Eternity",2000,120,{350,220},0,0, 25,0,{  0,  0},100, 0, {ALTAR_OF_ELDERS, 0, 0}, TREE_OF_AGES},
                {"               Backpack",   0, 20,{ 50, 25},0,3,  0,0,{  0,  0},100, 0, {ANCIENT_OF_WONDERS, 0, 0}, 0},
		{"     Ancient of Wonders", 200, 60,{ 90, 30},0,2,  0,1,{  0,  0},100, 0, {0, 0, 0}, 0},
		{"              Moon Well", 600, 50,{180, 40},0,2,  0,1,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"        Altar of Elders", 900, 60,{180, 50},0,2,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"           Hunters Hall",1100, 60,{210,100},0,2,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"         Chimaera Roots",1200, 80,{100,230},0,2,  0,0,{  0,  0},100, 0, {TREE_OF_ETERNITY, ANCIENT_OF_WIND, 0}, 0},
                {"          Improved Bows",   0, 35,{ 50,100},0,3,  0,0,{  0,  0},100, 1, {0, 0, 0}, ANCIENT_OF_WAR},
                {"           Marksmanship",   0, 40,{100,175},0,3,  0,0,{  0,  0},100, 0, {TREE_OF_ETERNITY, HUNTERS_HALL, 0}, ANCIENT_OF_WAR},
                {"               Sentinel",   0, 20,{100,100},0,3,  0,0,{  0,  0},100, 1, {HUNTERS_HALL, 0, 0}, ANCIENT_OF_WAR},
                {"            Moon Glaive",   0, 35,{100,150},0,3,  0,0,{  0,  0},100, 0, {TREE_OF_ETERNITY, HUNTERS_HALL, 0}, ANCIENT_OF_WAR},
                {"          Impaling Bolt",   0, 60,{125,100},0,3,  0,0,{  0,  0},100, 1, {HUNTERS_HALL, 0, 0}, ANCIENT_OF_WAR},
                {"            Ultravision",   0, 45,{ 50, 50},0,3,  0,0,{  0,  0},100, 0, {0, 0, 0}, HUNTERS_HALL},
                {"            Well Spring",   0, 30,{ 75,150},0,3,  0,0,{  0,  0},100, 0, {TREE_OF_ETERNITY, 0, 0}, HUNTERS_HALL},
                {"      Nature's Blessing",   0, 60,{200,150},0,3,  0,0,{  0,  0},100, 1, {0, 0, 0}, 0},
                {"          Abolish Magic",   0, 45,{ 50, 50},0,3,  0,0,{  0,  0},100, 0, {0, 0, 0}, ANCIENT_OF_LORE},
                {"        Enchanted Bears",   0, 20,{ 25,100},0,3,  0,0,{  0,  0},100, 0, {TREE_OF_ETERNITY, DRUID_OF_CLAW_TRAINING, 0}, ANCIENT_OF_LORE}, //Druid of Claw Master!!
                {"          Hardened Skin",   0, 40,{100,250},0,3,  0,0,{  0,  0},100, 0, {ANCIENT_OF_WONDERS, TREE_OF_ETERNITY, 0}, ANCIENT_OF_LORE},
                {"         Resistant Skin",   0, 75,{ 50,100},0,3,  0,0,{  0,  0},100, 0, {ANCIENT_OF_WONDERS, TREE_OF_ETERNITY, 0}, ANCIENT_OF_LORE},
                {"    Hippogryph Training",   0, 30,{ 75, 75},0,3,  0,0,{  0,  0},100, 0, {0, 0, 0}, ANCIENT_OF_WIND},
                {"        Enchanted Crows",   0, 20,{ 25,100},0,3,  0,0,{  0,  0},100, 0, {TREE_OF_ETERNITY, DRUID_OF_THALON_TRAINING, 0}, ANCIENT_OF_WIND}, // !! special, thalon!
                {"       Corrosive Breath",   0, 40,{125,225},0,3,  0,0,{  0,  0},100, 0, {0, 0, 0}, CHIMAERA_ROOST},
                {"   Strength of the Moon",   0, 60,{125, 75},0,4,  0,0,{125, 25},100, 0, {0, 0, 0}, HUNTERS_HALL},
                {"             Moon Armor",   0, 60,{150, 75},0,4,  0,0,{100, 25},100, 0, {0, 0, 0}, HUNTERS_HALL},
                {"   Strength of the Wild",   0, 60,{100, 50},0,4,  0,0,{150, 50},100, 0, {0, 0, 0}, HUNTERS_HALL},
                {"        Reinforced Hide",   0, 60,{150, 50},0,4,  0,0,{100, 50},100, 0, {0, 0, 0}, HUNTERS_HALL},
                {" Druid of Claw Training",   0, 60,{100,  0},0,4,  0,0,{100, 50},100, 1, {0, 0, 0}, ANCIENT_OF_LORE},
		{"Druid of Thalon Traning",   0, 60,{100,  0},0,4,  0,0,{100, 50},100, 1, {0, 0, 0}, ANCIENT_OF_WIND},
                {"        Cancel Building",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
//		das naechste in der Liste!
                {"                   NULL",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"                   NULL",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"                   NULL",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
		{"                   NULL",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
		{"                    NOP",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
		{"      Wood Wisp to Mine",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
		{"    Gold Wisp to Forest",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"                     IF",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"                    JMP",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"                 Marker",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0}

	},
{
                {"                Acolyte", 180, 15,{ 75,  0},1,1, 25,0,{  0,  0},100, 0, {0, 0, 0}, 0}, //no facility => special code in undead.cpp
                {"                  Ghoul", 330, 18,{120,  0},2,1, 37,0,{  0,  0},100, 0, {0, 0, 0}, CRYPT},
                {"            Crypt Fiend", 550, 30,{215, 40},3,1, 50,0,{  0,  0},100, 0, {GRAVEYARD, 0, 0}, CRYPT},
                {"               Gargoyle", 400, 35,{185, 30},2,1, 37,0,{  0,  0},100, 0, {BLACK_CITADEL, GRAVEYARD, 0}, CRYPT},
		{"            Abomination",1080, 45,{240, 70},4,1, 75,0,{  0,  0},100, 0, {BLACK_CITADEL, 0, 0}, SLAUGHTERHOUSE},
                {"             Meat Wagon", 380, 45,{230, 50},4,1, 75,0,{  0,  0},100, 0, {0, 0, 0}, SLAUGHTERHOUSE},
                {"            Necromancer", 230, 30,{145, 20},2,1, 37,0,{  0,  0},100, 0, {0, 0, 0}, TEMPLE_OF_THE_DAMNED},
                {"                Banshee", 210, 35,{155, 30},2,1, 50,0,{  0,  0},100, 0, {0, 0, 0}, TEMPLE_OF_THE_DAMNED},
                {"            Frost Wyrms",1100, 60,{385,120},7,1,150,0,{  0,  0},100, 0, {0, 0, 0}, BONEYARD},
                {"                  Shade", 250, 15,{  0,  0},1,1, 25,0,{  0,  0},100, 0, {0, 0, 0}, SACRIFICIAL_PIT},
                {"       Skeleton Warrior", 180,  0,{  0,  0},0,1, 25,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"          Skeletal Mage", 180,  0,{  0,  0},0,1, 25,0,{  0,  0},100, 0, {0, 0, 0}, 0}, //25xp?
                {"               Infernal",1500,  0,{  0,  0},0,1,300,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"    Carrion Beetle LvlA", 500,  0,{  0,  0},0,1,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0}, //?
                {"    Carrion Beetle LvlB", 500,  0,{  0,  0},0,1,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"    Carrion Beetle LvlC", 500,  0,{  0,  0},0,1,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"        Obsidian Statue", 500, 45,{200, 35},3,1,  0,0,{  0,  0},100, 0, {0, 0, 0}, SLAUGHTERHOUSE},
		{"           Death Knight", 500, 55,{  0,  0},5,5,  0,0,{  0,  0},100, 0, {0, 0, 0}, ALTAR_OF_DARKNESS},
                {"             Dread Lord", 500, 55,{  0,  0},5,5,  0,0,{  0,  0},100, 0, {0, 0, 0}, ALTAR_OF_DARKNESS},
 	        {"                   Lich", 500, 55,{  0,  0},5,5,  0,0,{  0,  0},100, 0, {0, 0, 0}, ALTAR_OF_DARKNESS},
                {"             Crypt Lord", 500, 55,{  0,  0},5,5,  0,0,{  0,  0},100, 0, {0, 0, 0}, ALTAR_OF_DARKNESS},
                {"      Haunted Gold Mine", 950,110,{340,185},0,2,  0,1,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"             Necropolis",1500,120,{320, 80},0,2,  0,1,{  0,  0},100, 0, {0, 0, 0}, 0}, 
                {"      Halls of the Dead",2000,120,{350,220},0,0, 25,0,{  0,  0},100, 0, {0, 0, 0}, NECROPOLIS},
                {"          Black Citadel",2300, 60,{150, 60},0,0, 25,0,{  0,  0},100, 0, {ALTAR_OF_DARKNESS, 0, 0}, HALLS_OF_THE_DEAD},
                {"               Backpack",   0, 20,{ 50, 25},0,3,  0,0,{  0,  0},100, 0, {TOMB_OF_RELICS, 0, 0}, 0}, //special
		{"                  Crypt",1300, 80,{155,145},0,2,  0,1,{  0,  0},100, 0, {0, 0, 0}, 0}, 
                {"               Ziggurat", 550, 70,{150,140},0,2,  0,1,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"      Altar of Darkness", 900, 80,{135, 80},0,2,  0,1,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"              Graveyard", 900, 60,{ 90, 30},0,2,  0,1,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"         Slaughterhouse",1200, 50,{180, 40},0,2,  0,1,{  0,  0},100, 1, {GRAVEYARD, 0, 0}, 0},
                {"   Temple of the Damned",1100, 60,{180, 50},0,2,  0,1,{  0,  0},100, 1, {GRAVEYARD, 0, 0}, 0},
                {"        Sacrificial Pit", 900, 60,{210,100},0,2,  0,1,{  0,  0},100, 1, {0, 0, 0}, 0},
                {"               Boneyard",1500, 80,{100,230},0,2,  0,1,{  0,  0},100, 0, {BLACK_CITADEL, SACRIFICIAL_PIT, 0}, 0},
                {"         Tomb of Relics", 500, 80,{100,230},0,2,  0,1,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"         Nerubian Tower", 200, 80,{100,230},0,2, 25,1,{  0,  0},100, 0, {TOMB_OF_RELICS, 0, 0}, ZIGGURAT}, //25 xp?
                {"           Spirit Tower", 550, 80,{100,230},0,2, 25,0,{  0,  0},100, 0, {GRAVEYARD, 0, 0}, ZIGGURAT},
                {"            Cannibalize",   0, 30,{ 75,  0},0,3,  0,0,{  0,  0},100, 0, {0, 0, 0}, CRYPT},
                {"           Ghoul Frenzy",   0, 45,{100,150},0,3,  0,0,{  0,  0},100, 0, {0, 0, 0}, CRYPT},
                {"                    Web",   0, 30,{ 75, 75},0,3,  0,0,{  0,  0},100, 1, {GRAVEYARD, 0, 0}, CRYPT},
                {"                 Burrow",   0, 45,{ 75, 75},0,3,  0,0,{  0,  0},100, 1, {GRAVEYARD, 0, 0}, CRYPT},
                {"             Stone Form",   0, 40,{ 75,150},0,3,  0,0,{  0,  0},100, 0, {BLACK_CITADEL, GRAVEYARD, 0}, CRYPT},
                {"          Disease Cloud",   0, 45,{100,200},0,3,  0,0,{  0,  0},100, 0, {BLACK_CITADEL, 0, 0}, SLAUGHTERHOUSE},
                {"         Exhume Corpses",   0, 20,{125,100},0,3,  0,0,{  0,  0},100, 0, {BLACK_CITADEL, 0, 0}, SLAUGHTERHOUSE},
                {"              Destroyer",   0, 60,{ 75,150},0,3,  0,0,{  0,  0},100, 0, {BLACK_CITADEL, TOMB_OF_RELICS, 0}, SLAUGHTERHOUSE}, 
                {"     Skeletal Longevity",   0, 60,{100, 75},0,3,  0,0,{  0,  0},100, 0, {0, 0, 0}, TEMPLE_OF_THE_DAMNED},
                {"       Skeletal Mastery",   0, 45,{125,150},0,3,  0,0,{  0,  0},100, 0, {BLACK_CITADEL, 0, 0}, TEMPLE_OF_THE_DAMNED},
                {"        Freezing Breath",   0, 60,{150,275},0,3,  0,0,{  0,  0},100, 0, {0, 0, 0}, BONEYARD},
                {"        Unholy Strength",   0, 60,{125, 50},0,4,  0,0,{125, 50},100, 0, {0, 0, 0}, GRAVEYARD},
                {"           Unholy Armor",   0, 60,{125, 50},0,4,  0,0,{125, 50},100, 0, {0, 0, 0}, GRAVEYARD},
                {"        Creature Attack",   0, 60,{150, 50},0,4,  0,0,{ 75, 50},100, 0, {0, 0, 0}, GRAVEYARD},
                {"      Creature Carapace",   0, 60,{150, 75},0,4,  0,0,{100, 75},100, 0, {0, 0, 0}, GRAVEYARD},
                {"   Necromancer Training",   0, 60,{100,  0},0,4,  0,0,{100, 50},100, 1, {0, 0, 0}, TEMPLE_OF_THE_DAMNED},
                {"       Banshee Training",   0, 60,{100,  0},0,4,  0,0,{100, 50},100, 1, {0, 0, 0}, TEMPLE_OF_THE_DAMNED},
		{"      Unsummon Building",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"                   NULL",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"                   NULL",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"                    NOP",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"                   NULL",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"                   NULL",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"                     IF",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"                    JMP",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0},
                {"                 Marker",   0,  0,{  0,  0},0,0,  0,0,{  0,  0},100, 0, {0, 0, 0}, 0}

		 
		}
};








#endif


