#ifndef MAIN_H
#define MAIN_H

#define MAX_LENGTH 96
#define RUNNINGS 5 
#define MAX_PLAYER 100
#define LARVA_MAX 200
#define MAX_BUILDINGS 12 // How many buildings can you built simultaneously?
#define MAX_GOALS 60
#define DATA_SET_SIZE 15

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

#define TOWN_HALL 17
#define KEEP 18
#define CASTLE 19
#define BARRACKS 20
#define FARM 21
#define ALTAR_OF_KINGS 22
#define LUMBER_MILL 23
#define SCOUT_TOWER 24
#define BLACKSMITH 25
#define WORKSHOP 26
#define ARCANE_SANCTUM 27
#define GRYPHON_AVIARY 28
#define ARCANE_VAULT 29
#define GUARD_TOWER 30
#define CANNON_TOWER 31
#define ARCANE_TOWER 32

#define BACKPACK 33
#define DEFEND 34
#define LONG_RIFLES 35
#define ANIMAL_WAR_TRAINING 36
#define GYROCEPTOR_BOMBS 37
#define WAR_ENGINE 38
#define FLARE 39
#define FRAGMENTATION_SHARDS 40
#define STORM_HAMMERS 41

#define LUMBER_HARVESTING 42
#define MASONRY 43
#define MELEE_WEAPONS 44
#define MELEE_PLATING 45
#define RANGED_WEAPONS 46
#define LEATHER_ARMOR 47
#define PRIEST_TRAINING 48
#define SORCERESS_TRAINING 49
#define CONTROL_MAGIC 50
#define MAGIC_SENTINEL 51
#define ONE_WOOD_PEASANT_TO_MINE 52
#define ONE_GOLD_PEASANT_TO_FOREST 53


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

#define GREAT_HALL 16
#define STRONGHOLD 17
#define FORTRESS 18
#define ALTAR_OF_STORMS 19
//#define #BARRACKS 20 !
#define WARMILL 21
#define BESTIARY 22
#define SPIRIT_LODGE 23
#define TAUREN_TOTEM 24
#define VOODOO_LOUNGE 25
#define BURROW 26
#define WATCH_TOWER 27

#define PILLAGE 28
#define BACKPACK_ORC 29 // ~~
#define BERSERKER_STRENGTH 30
#define TROLL_REGENERATION 31
#define BERSERKER 32
#define BURNING_OIL 33
#define REINFORCED_DEFENSE 34
#define ENSNARE 35
#define WAR_DRUMS 36
#define ENVENOMED_SPEARS 37
#define LIQUID_FIRE 38
#define PULVERIZE 39

#define MELEE_WEAPONS_ORC 40 //~~~
#define UNIT_ARMOR 41
#define RANGED_WEAPONS_ORC 42 //~~~
#define SPIKED_BARRICADES 43
#define SHAMAN_TRAINING 44
#define WITCH_DOCTOR_TRAINING 45
#define SPIRIT_WALKER_TRAINING 46

#define ONE_WOOD_PEON_TO_MINE 47
#define ONE_GOLD_PEON_TO_FOREST 48



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

#define TREE_OF_LIFE 14
#define TREE_OF_AGES 15
#define TREE_OF_ETERNITY 16
#define ANCIENT_OF_WAR 17
#define ANCIENT_OF_LORE 18
#define ANCIENT_OF_WIND 19
#define ANCIENT_PROTECTOR 20
#define ANCIENT_OF_WONDERS 21
#define MOONWELL 22
#define ALTAR_OF_ELDERS 23
#define HUNTERS_HALL 24
#define CHIMAERA_ROOST 25

#define BACKPACK_ELVES 26
#define IMPROVED_BOWS 27
#define MARKSMANSHIP 28
#define SENTINEL 29
#define MOON_GLAIVE 30
#define IMPALING_BOLT 31
#define ULTRAVISION 32
#define WELL_SPRING 33
#define NATURES_BLESSING 34
#define ABOLISH_MAGIC 35
#define ENCHANTED_BEARS 36
#define HARDENED_SKIN 37
#define RESISTANT_SKIN 38
#define HIPPOGRYPH_TRAINING 39
#define ENCHANTED_CROWS 40
#define CORROSIVE_BREATH 41
#define STRENGTH_OF_THE_MOON 42
#define MOON_ARMOR 43
#define STRENGTH_OF_THE_WILD 44
#define REINFORCED_HIDE 45
#define DRUID_OF_CLAW_TRAINING 46
#define DRUID_OF_THALON_TRAINING 47 
#define ONE_WOOD_WISP_TO_MINE 48
#define ONE_GOLD_WISP_TO_FOREST 49


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

#define HAUNTED_GOLD_MINE 17
#define NECROPOLIS 18
#define HALLS_OF_THE_DEAD 19
#define BLACK_CITADEL 20
#define CRYPT 21
#define ZIGGURAT 22
#define ALTAR_OF_DARKNESS 23
#define GRAVEYARD 24
#define SLAUGHTERHOUSE 25
#define TEMPLE_OF_THE_DAMNED 26
#define SACRIFICIAL_PIT 27
#define BONEYARD 28
#define TOMB_OF_RELICS 29
#define NERUBIAN_TOWER 30
#define SPIRIT_TOWER 31

#define BACKPACK_UNDEAD 32
#define CANNIBALIZE 33
#define GHOUL_FRENZY 34
#define WEB 35
#define BURROW_UNDEAD 36
#define STONE_FORM 37
#define DIESEASE_CLOUR 38
#define EXHUME_CORPSES 39
#define DESTROYER 40
#define SKELETAL_LONGEVITY 41
#define SKELETAL_MASTERY 42
#define FREEZING_BREATH 43

#define UNHOLY_STRENGTH 44
#define UNHOLY_ARMOR 45
#define CREATURE_ATTACK 46
#define CREATURE_CARAPACE 47
#define NECROMANCER_TRAINING 48
#define BANSHEE_TRAINING 49

#define MAX_EXPANSIONS 2

/*struct Expansion
{
	unsigned char status; // 0: free, 1: Creeps, 2: Exe
	unsigned char distance; 
}


struct MAP
{
	Expansion Exe[MAX_EXPANSIONS];
} map;*/





struct GOAL
{
	unsigned short time,what;
};

//some global variables

extern unsigned char Ziel[60],Build_Av[60],Build_Bv[60]; 
extern unsigned char Vespene_Av,Max_Build_Types,race,building_types;
extern unsigned short total_goals;
extern unsigned char num,Vespene_Extractors,availible_expansions;
extern GOAL goal[MAX_GOALS];
extern double Harvest_Speed; //~~~

const double HARVEST_SPEED_RACE[MAX_RACES][RESOURCES][MAX_PEONS]=
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
};

struct Stats
{
	char name[21];
	unsigned short BT;
	unsigned short res[RESOURCES];
	unsigned char supply;
	unsigned short type; // 0: nothing, 1: unit, 2: building (primarily for differentation between normal buildings and building upgrades), 3: Research, 4: Upgrade
	unsigned char upres[RESOURCES]; //additional costs for upgrades
	unsigned char prerequisite[3]; // what prerequisit buildings are needed (BESIDES the production building itself)| 0 => ignore 
	unsigned char facility; // where the unit is trained (<=> availible!) | 0 => ignore
};



const Stats stats[MAX_RACES][MAX_GOALS]=
{
	{					//       v
	{"             Peasant", 15, 75,  0,1,1,  0,  0, 0, 0, 0, 0}, //no facility as there is special code in human.cpp
	{"             Militia",  0,  0,  0,1,1,  0,  0, 0, 0, 0, 0}, //~~~
	{"             Footman", 20,135,  0,2,1,  0,  0, 0, 0, 0, BARRACKS},
	{"            Rifleman", 26,205, 30,3,1,  0,  0, BLACKSMITH, 0, 0, BARRACKS},
	{"              Knight", 45,245, 60,4,1,  0,  0, BLACKSMITH, CASTLE, 0, BARRACKS},
	{"              Priest", 28,135, 10,2,1,  0,  0, 0, 0, 0, ARCANE_SANCTUM},
	{"           Sorceress", 30,155, 20,2,1,  0,  0, 0, 0, 0, ARCANE_SANCTUM},
	{"       Spell Breaker", 28,215, 30,3,1,  0,  0, ARCANE_VAULT, 0, 0, ARCANE_SANCTUM}, //? 155/20/2 ? CASTLE?
	{"          Gyroceptor", 25, 90, 30,1,1,  0,  0, 0, 0, 0, WORKSHOP},
	{"         Mortar Team", 40,180, 70,3,1,  0,  0, 0, 0, 0, WORKSHOP},
	{"          Steam Tank", 55,195, 60,3,1,  0,  0, CASTLE, 0, 0, WORKSHOP},
	{"       Gryphon Rider", 45,280, 70,4,1,  0,  0, 0, 0, 0, GRYPHON_AVIARY},
	{"    Dragonhawk Rider", 45,235, 40,3,1,  0,  0, ARCANE_VAULT, 0, 0, GRYPHON_AVIARY},
	{"Water Elemental LvlA",  0,  0,  0,0,1,  0,  0, 0, 0, 0, 0},
        {"Water Elemental LvlB",  0,  0,  0,0,1,  0,  0, 0, 0, 0, 0},
        {"Water Elemental LvlC",  0,  0,  0,0,1,  0,  0, 0, 0, 0, 0},
  	{"             Phoenix",  0,  0,  0,0,1,  0,  0, 0, 0, 0, 0},

	{"           Town Hall",180,385,185,0,2,  0,  0, 0, 0, 0, 0},
	{"                Keep",120,320,210,0,0,  0,  0, 0, 0, 0, 0},// no townhall, see castle
	{"              Castle",120,380,230,0,0,  0,  0, ALTAR_OF_KINGS, 0, 0, 0}, // no 'keep' as facility, problems with goals...
	{"            Barracks", 60,160, 60,0,2,  0,  0, 0, 0, 0, 0},
	{"                Farm", 35, 80, 20,0,2,  0,  0, 0, 0, 0, 0},
	{"      Altar of Kings", 60,180, 50,0,2,  0,  0, 0, 0, 0, 0},
	{"         Lumber Mill", 60,145,  0,0,2,  0,  0, 0, 0, 0, 0},
	{"         Scout Tower", 25, 30, 20,0,2,  0,  0, 0, 0, 0, 0},
	{"          Blacksmith", 70,140, 60,0,2,  0,  0, 0, 0, 0, 0},
	{"            Workshop", 70,140,140,0,2,  0,  0, BLACKSMITH, 0, 0, 0}, // !!!Keep <> CASTLE!!!!=> SPECIAL
	{"      Arcane Sanctum", 80,150,140,0,2,  0,  0, 0, 0, 0, 0}, //Keep!!
	{"      Gryphon Aviary", 75,120,240,0,2,  0,  0, CASTLE, LUMBER_MILL, 0, 0},
	{"        Arcane Vault", 75,130, 30,0,2,  0,  0, 0, 0, 0, 0},
	{"         Guard Tower", 70, 80, 60,0,0,  0,  0, LUMBER_MILL, 0, 0, SCOUT_TOWER}, //~~
	{"        Cannon Tower", 80,170,100,0,0,  0,  0, WORKSHOP, 0, 0, SCOUT_TOWER}, // Castle?
	//guard/cannon/arcane tower have type 0 because they are no real buildings but upgrades... i.e. no peon is needed!
	{"        Arcane Tower", 70, 80, 60,0,0,  0,  0, ARCANE_VAULT, 0, 0, SCOUT_TOWER}, //Castle?
	
	{"            Backpack", 20, 50, 25,0,3,  0,  0, ARCANE_VAULT, 0, 0, TOWN_HALL}, //~~
	{"              Defend", 45,150,100,0,3,  0,  0, 0, 0, 0, BARRACKS},
	{"          Long Rifle", 30, 75,125,0,3,  0,  0, WORKSHOP, 0, 0, BARRACKS},
	{" Animal War Training", 40,150,250,0,3,  0,  0, CASTLE, LUMBER_MILL, BLACKSMITH, BARRACKS},

	{"    Gyroceptor Bombs", 35,150,100,0,3,  0,  0, CASTLE, 0, 0, WORKSHOP},
	{"          War Engine", 40, 50,150,0,3,  0,  0, CASTLE, 0, 0, WORKSHOP},
	{"               Flare", 30, 50, 50,0,3,  0,  0, 0, 0, 0, WORKSHOP},
	{"Fragmentation Shards", 40, 50,100,0,3,  0,  0, CASTLE, 0, 0, WORKSHOP},
	{"       Storm Hammers", 45,125,225,0,3,  0,  0, 0, 0, 0, GRYPHON_AVIARY},

        {"   Lumber Harvesting", 60,100,  0,0,4,100,  0, 0, 0, 0, LUMBER_MILL},
	{"             Masonry", 60,100,100,0,4, 50, 50, 0, 0, 0, LUMBER_MILL},
	{"       Melee Weapons", 60,100, 50,0,4,150, 50, 0, 0, 0, BLACKSMITH},
        {"       Melee Plating", 60,125, 75,0,4, 75, 50, 0, 0, 0, BLACKSMITH},
        {"      Ranged Weapons", 60,100, 50,0,4,150, 50, 0, 0, 0, BLACKSMITH},
        {"       Leather Armor", 60,100,100,0,4, 50, 50, 0, 0, 0, BLACKSMITH},
        {"     Priest Training", 60,100,  0,0,4,100, 50, 0, 0, 0, ARCANE_SANCTUM},
        {"  Sorceress Training", 60,100,  0,0,4,100, 50, 0, 0, 0, ARCANE_SANCTUM},
	
	{"       Control Magic", 45, 75, 75,0,3,  0,  0, ARCANE_VAULT, 0, 0, ARCANE_SANCTUM},
	{"	Magic Sentinel", 30, 50, 50,0,3,  0,  0, 0, 0, 0, ARCANE_SANCTUM},
		
	{"   Wood Peon to Mine",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
	{"   Mine Peon to Wood",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},

	{"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
        {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
        {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
        {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
        {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
        {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0}

	},



        {                                       //       v
	        {"                Peon", 15, 75,  0,1,1,  0,  0, 0, 0, 0, 0}, //no facility as there is special code in ork.cpp
	        {"               Grunt", 30,200,  0,3,1,  0,  0, 0, 0, 0, BARRACKS},
	        {"          Headhunter", 22,135, 20,2,1,  0,  0, WARMILL, 0, 0, BARRACKS},
	        {"            Catapult", 45,220, 50,4,1,  0,  0, WARMILL, 0, 0, BARRACKS}, //stronghold!
	        {"              Raider", 28,180, 40,3,1,  0,  0, 0, 0, 0, BESTIARY},
	        {"              Tauren", 50,280, 80,5,1,  0,  0, 0, 0, 0, TAUREN_TOTEM},
	        {"              Shaman", 30,130, 20,2,1,  0,  0, 0, 0, 0, SPIRIT_LODGE},
	        {"        Witch Doctor", 30,145, 25,2,1,  0,  0, 0, 0, 0, SPIRIT_LODGE},
	        {"       Spirit Walker", 42,195, 35,3,1,  0,  0, VOODOO_LOUNGE, 0, 0, SPIRIT_LODGE},
	        {"          Kodo Beast", 30,255, 60,4,1,  0,  0, WARMILL, 0, 0, BESTIARY},
	        {"        Wyvern Rider", 35,265, 40,4,1,  0,  0, FORTRESS, 0, 0, BESTIARY},
	        {"     Troll Bat Rider", 25,160, 40,2,1,  0,  0, FORTRESS, VOODOO_LOUNGE, 0, BESTIARY},
	        {"         Spirit Wolf",  0,  0,  0,0,1,  0,  0, 0, 0, 0, 0},
	        {"           Dire Wolf",  0,  0,  0,0,1,  0,  0, 0, 0, 0, 0},
	        {"         Shadow Wolf",  0,  0,  0,0,1,  0,  0, 0, 0, 0, 0},
	        {"        Serpent Ward",  0,  0,  0,0,1,  0,  0, 0, 0, 0, 0},

	        {"          Great Hall",150,385,185,0,2,  0,  0, 0, 0, 0, 0},
	        {"          Stronghold",120,315, 90,0,0,  0,  0, 0, 0, 0, 0},// no townhall, see castle
	        {"            Fortress",120,345,210,0,0,  0,  0, ALTAR_OF_STORMS, 0, 0, 0}, // no 'keep' as facility, problems with goals...
		{"     Altar of Storms", 60,180, 50,0,2,  0,  0, 0, 0, 0, 0},
                {"            Barracks", 60,180, 50,0,2,  0,  0, 0, 0, 0, 0},
		{"            War Mill", 70,205,  0,0,2,  0,  0, 0, 0, 0, 0},
       	 	{"            Bestiary", 70,145,140,0,2,  0,  0, 0, 0, 0, 0}, //keep -> special
        	{"        Spirit Lodge", 70,150,150,0,2,  0,  0, 0, 0, 0, 0}, //keep -> special
        	{"        Tauren Totem", 70, 90,200,0,2,  0,  0, WARMILL, FORTRESS, 0, 0},
        	{"       Voodoo Lounge", 60,130, 30,0,2,  0,  0, 0, 0, 0, 0},
        	{"              Burrow", 70,160, 40,0,2,  0,  0, 0, 0, 0, 0}, 
        	{"         Watch Tower", 80,110, 80,0,2,  0,  0, WARMILL, 0, 0, 0},
		
        	{"             Pillage", 45, 75, 25,0,3,  0,  0, 0, 0, 0, 0}, // halls...
        	{"            Backpack", 20, 50, 25,0,3,  0,  0, VOODOO_LOUNGE, 0, 0, 0}, // halls...
		{"  Berserker Strength", 40, 50,150,0,3,  0,  0, 0, 0, 0, BARRACKS}, // Stronghold!
	        {"  Troll Regeneration", 35,100,100,0,3,  0,  0, WARMILL, 0, 0, BARRACKS}, //Stronghold!
	        {"           Berserker", 40, 75,175,0,3,  0,  0, FORTRESS, WARMILL, 0, BARRACKS}, 
	        {"         Burning Oil", 30, 50,150,0,3,  0,  0, FORTRESS, 0, 0, BARRACKS},
	        {"  Reinforced Defense", 60, 50,200,0,3,  0,  0, FORTRESS, 0, 0, WARMILL},
	        {"             Ensnare", 40, 50, 75,0,3,  0,  0, 0, 0, 0, BESTIARY},
	        {"           War Drums", 40,100,150,0,3,  0,  0, FORTRESS, WARMILL, 0, BESTIARY},
	        {"    Envenomed Spears", 40,100,150,0,3,  0,  0, FORTRESS, 0, 0, BESTIARY},
	        {"         Liquid Fire", 75, 75,125,0,3,  0,  0, FORTRESS, VOODOO_LOUNGE, 0, BESTIARY},
	        {"           Pulverize", 40,100,250,0,3,  0,  0, 0, 0, 0, TAUREN_TOTEM},
	        {"       Melee Weapons", 60,100, 75,0,4,100, 50, 0, 0, 0, WARMILL},
	        {"          Unit Armor", 60,150, 75,0,4,150, 75, 0, 0, 0, WARMILL},
	        {"      Ranged Weapons", 60, 75, 75,0,4, 75, 75, 0, 0, 0, WARMILL},
	        {"   Spiked Barrikades", 60, 25, 75,0,4, 25,100, 0, 0, 0, WARMILL}, // !!! Spiked Lvl 3 : 150 Gold!
	        {"     Shaman Training", 60,100,  0,0,4,100, 50, 0, 0, 0, SPIRIT_LODGE},
	        {"WitchDoctor Training", 60,100,  0,0,4,100, 50, 0, 0, 0, SPIRIT_LODGE},
	        {"Spirit Walker Traini", 60,100,  0,0,4,100, 50, 0, 0, 0, SPIRIT_LODGE},
	        {"   Wood Peon to Mine",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
	        {"   Mine Peon to Wood",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
	        {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
	        {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
	        {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
	        {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
	        {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
                {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
                {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
                {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
                {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
                {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0}
	},



	
        {                                       //       v
                {"                Wisp", 14, 60,  0,1,1,  0,  0, 0, 0, 0, 0}, //no facility as there is special code in ork.cpp
                {"              Archer", 20,130, 10,2,1,  0,  0, 0, 0, 0, ANCIENT_OF_WAR},
		{"            Huntress", 30,195, 20,3,1,  0,  0, HUNTERS_HALL, 0, 0, ANCIENT_OF_WAR},
		{"            Ballista", 48,210, 65,4,1,  0,  0, HUNTERS_HALL, 0, 0, ANCIENT_OF_WAR}, // Tree of Ages!
		{"               Dryad", 30,145, 60,3,1,  0,  0, 0, 0, 0, ANCIENT_OF_LORE},
		{"   Druid of the Claw", 30,255, 80,4,1,  0,  0, 0, 0, 0, ANCIENT_OF_LORE},
		{"      Mountain Giant", 45,425,100,7,1,  0,  0, ANCIENT_OF_WONDERS, 0, 0, ANCIENT_OF_LORE},
		{"          Hippogryph", 40,160, 20,2,1,  0,  0, 0, 0, 0, ANCIENT_OF_WIND},
		{"     Druid of Thalon", 22,135, 20,2,1,  0,  0, 0, 0, 0, ANCIENT_OF_WIND},
		{"       Faerie Dragon", 25,155, 25,2,1,  0,  0, ANCIENT_OF_WONDERS, 0, 0, ANCIENT_OF_WIND},
		{"            Chimaera", 65,330, 70,5,1,  0,  0, TREE_OF_ETERNITY, ANCIENT_OF_WIND, 0, CHIMAERA_ROOST},
		{"              Treant",  0,  0,  0,0,1,  0,  0, 0, 0, 0, 0},
		{" Spirit of Vengeance",  0,  0,  0,0,1,  0,  0, 0, 0, 0, 0},
		{"           Vengeance",  0,  0,  0,0,1,  0,  0, 0, 0, 0, 0},
		
                {"        Tree of Life",110,340,185,0,2,  0,  0, 0, 0, 0, 0},
                {"        Tree of Ages",120,320, 80,0,0,  0,  0, 0, 0, 0, 0}, // No Tree of Life
                {"    Tree of Eternity",120,350,220,0,0,  0,  0, ALTAR_OF_ELDERS, 0, 0, 0}, // no 'Tree of ages' as f
                {"      Ancient of War", 60,150, 60,0,2,  0,  0, 0, 0, 0, 0},
                {"     Ancient of Lore", 80,155,145,0,2,  0,  0, 0, 0, 0, 0}, //Tree of Ages!
                {"     Ancient of Wind", 70,150,140,0,2,  0,  0, 0, 0, 0, 0}, //Tree of Ages!
                {"   Ancient Protector", 80,135, 80,0,2,  0,  0, 0, 0, 0, 0},
                {"  Ancient of Wonders", 60, 90, 30,0,2,  0,  0, 0, 0, 0, 0},
		{"           Moon Well", 50,180, 40,0,2,  0,  0, 0, 0, 0, 0},
                {"     Altar of Elders", 60,180, 50,0,2,  0,  0, 0, 0, 0, 0},
                {"        Hunters Hall", 60,210,100,0,2,  0,  0, 0, 0, 0, 0},
                {"      Chimaera Roots", 80,100,230,0,2,  0,  0, TREE_OF_ETERNITY, ANCIENT_OF_WIND, 0, 0},
		
                {"            Backpack", 20, 50, 25,0,3,  0,  0, ANCIENT_OF_WONDERS, 0, 0, 0}, // TOA!
                {"       Improved Bows", 35, 50,100,0,3,  0,  0, 0, 0, 0, ANCIENT_OF_WAR}, // TOA!
                {"        Marksmanship", 40,100,175,0,3,  0,  0, TREE_OF_ETERNITY, HUNTERS_HALL, 0, ANCIENT_OF_WAR},
                {"            Sentinel", 20,100,100,0,3,  0,  0, HUNTERS_HALL, 0, 0, ANCIENT_OF_WAR}, //TOA!
                {"         Moon Glaive", 35,100,150,0,3,  0,  0, TREE_OF_ETERNITY, HUNTERS_HALL, 0, ANCIENT_OF_WAR},
                {"       Impaling Bolt", 60,125,100,0,3,  0,  0, HUNTERS_HALL, 0, 0, ANCIENT_OF_WAR}, //TOA!
                {"         Ultravision", 45, 50, 50,0,3,  0,  0, 0, 0, 0, HUNTERS_HALL},
                {"         Well Spring", 30, 75,150,0,3,  0,  0, TREE_OF_ETERNITY, 0, 0, HUNTERS_HALL},
                {"   Nature's Blessing", 60,200,150,0,3,  0,  0, 0, 0, 0, 0}, // Tree of Ages...
                {"       Abolish Magic", 45, 50, 50,0,3,  0,  0, 0, 0, 0, ANCIENT_OF_LORE},
                {"     Enchanted Bears", 20, 25,100,0,3,  0,  0, TREE_OF_ETERNITY, DRUID_OF_CLAW_TRAINING, 0, ANCIENT_OF_LORE}, //Druid of Claw Master!!
                {"       Hardened Skin", 40,100,250,0,3,  0,  0, ANCIENT_OF_WONDERS, TREE_OF_ETERNITY, 0, ANCIENT_OF_LORE},
                {"      Resistant Skin", 75, 50,100,0,3,  0,  0, ANCIENT_OF_WONDERS, TREE_OF_ETERNITY, 0, ANCIENT_OF_LORE},
	 
                {" Hippogryph Training", 30, 75, 75,0,3,  0,  0, 0, 0, 0, ANCIENT_OF_WIND},
                {"     Enchanted Crows", 20, 25,100,0,3,  0,  0, TREE_OF_ETERNITY, DRUID_OF_THALON_TRAINING, 0, ANCIENT_OF_WIND}, // !! special, thalon!
                {"    Corrosive Breath", 40,125,225,0,3,  0,  0, 0, 0, 0, CHIMAERA_ROOST},
                {"Strength of the Moon", 60,125, 75,0,4,125, 25, 0, 0, 0, HUNTERS_HALL},
                {"          Moon Armor", 60,150, 75,0,4,100, 25, 0, 0, 0, HUNTERS_HALL},
                {"Strength of the Wild", 60,100, 50,0,4,150, 50, 0, 0, 0, HUNTERS_HALL},
                {"     Reinforced Hide", 60,150, 50,0,4,100, 50, 0, 0, 0, HUNTERS_HALL},
                {"Druid of Claw Traing", 60,100,  0,0,4,100, 50, 0, 0, 0, ANCIENT_OF_LORE},
		{"Druid of Thalon Trng", 60,100,  0,0,4,100, 50, 0, 0, 0, ANCIENT_OF_WIND},
		{"   Wood Wisp to Mine",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
		{" Gold Wisp to Forest",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
	        {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
                {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
                {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
                {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
                {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
                {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0}
	},

	{
                {"             Acolyte", 15, 75,  0,1,1,  0,  0, 0, 0, 0, 0}, //no facility => special code in undead.cpp
                {"               Ghoul", 18,120,  0,2,1,  0,  0, 0, 0, 0, CRYPT},
                {"         Crypt Fiend", 30,215, 40,3,1,  0,  0, GRAVEYARD, 0, 0, CRYPT},
                {"            Gargoyle", 35,185, 30,2,1,  0,  0, BLACK_CITADEL, GRAVEYARD, 0, CRYPT},
		{"         Abomination", 45,240, 70,4,1,  0,  0, BLACK_CITADEL, 0, 0, SLAUGHTERHOUSE},
                {"          Meat Wagon", 45,230, 50,4,1,  0,  0, 0, 0, 0, SLAUGHTERHOUSE},
                {"         Necromancer", 30,145, 20,2,1,  0,  0, 0, 0, 0, TEMPLE_OF_THE_DAMNED},
                {"             Banshee", 35,155, 30,2,1,  0,  0, 0, 0, 0, TEMPLE_OF_THE_DAMNED},
                {"         Frost Wyrms", 60,385,120,7,1,  0,  0, 0, 0, 0, BONEYARD},
                {"               Shade", 15,  0,  0,1,1,  0,  0, 0, 0, 0, SACRIFICIAL_PIT},
                {"    Skeleton Warrior",  0,  0,  0,0,1,  0,  0, 0, 0, 0, 0},
                {"       Skeletal Mage",  0,  0,  0,0,1,  0,  0, 0, 0, 0, 0},
                {"            Infernal",  0,  0,  0,0,1,  0,  0, 0, 0, 0, 0},
                {" Carrion Beetle LvlA",  0,  0,  0,0,1,  0,  0, 0, 0, 0, 0},
                {" Carrion Beetle LvlB",  0,  0,  0,0,1,  0,  0, 0, 0, 0, 0},
 	        {" Carrion Beetle LvlC",  0,  0,  0,0,1,  0,  0, 0, 0, 0, 0},
                {"     Obsidian Statue", 45,200, 35,3,1,  0,  0, 0, 0, 0, SLAUGHTERHOUSE},
// Destroyer?
	       

                {"   Haunted Gold Mine",110,340,185,0,2,  0,  0, 0, 0, 0, 0},
                {"          Necropolis",120,320, 80,0,2,  0,  0, 0, 0, 0, 0}, 
                {"   Halls of the Dead",120,350,220,0,0,  0,  0, 0, 0, 0, 0}, //no necropolis
                {"       Black Citadel", 60,150, 60,0,0,  0,  0, ALTAR_OF_DARKNESS, 0, 0, 0}, //no HOD
                {"               Crypt", 80,155,145,0,2,  0,  0, 0, 0, 0, 0}, 
                {"            Ziggurat", 70,150,140,0,2,  0,  0, 0, 0, 0, 0},
                {"   Altar of Darkness", 80,135, 80,0,2,  0,  0, 0, 0, 0, 0},
                {"           Graveyard", 60, 90, 30,0,2,  0,  0, 0, 0, 0, 0},
                {"      Slaughterhouse", 50,180, 40,0,2,  0,  0, GRAVEYARD, 0, 0, 0}, //HOD!
                {"Temple of the Damned", 60,180, 50,0,2,  0,  0, GRAVEYARD, 0, 0, 0}, //HOD!
                {"     Sacrificial Pit", 60,210,100,0,2,  0,  0, 0, 0, 0, 0}, //HOD!
                {"            Boneyard", 80,100,230,0,2,  0,  0, BLACK_CITADEL, SACRIFICIAL_PIT, 0, 0},
                {"      Tomb of Relics", 80,100,230,0,2,  0,  0, 0, 0, 0, 0},
                {"      Nerubian Tower", 80,100,230,0,2,  0,  0, TOMB_OF_RELICS, 0, 0, 0}, //?
                {"        Spirit Tower", 80,100,230,0,2,  0,  0, GRAVEYARD, 0, 0, 0}, //ZIGGURAT!

                {"            Backpack", 20, 50, 25,0,3,  0,  0, TOMB_OF_RELICS, 0, 0, 0}, //special
                {"         Cannibalize", 30, 75,  0,0,3,  0,  0, 0, 0, 0, CRYPT},
                {"        Ghoul Frenzy", 45,100,150,0,3,  0,  0, 0, 0, 0, CRYPT},
                {"                 Web", 30, 75, 75,0,3,  0,  0, GRAVEYARD, 0, 0, CRYPT}, //HOD!
                {"              Burrow", 45, 75, 75,0,3,  0,  0, GRAVEYARD, 0, 0, CRYPT}, //HOD!
                {"          Stone Form", 40, 75,150,0,3,  0,  0, BLACK_CITADEL, GRAVEYARD, 0, CRYPT},
                {"       Disease Cloud", 45,100,200,0,3,  0,  0, BLACK_CITADEL, 0, 0, SLAUGHTERHOUSE},
                {"      Exhume Corpses", 20,125,100,0,3,  0,  0, BLACK_CITADEL, 0, 0, SLAUGHTERHOUSE},
                {"           Destroyer", 60, 75,150,0,3,  0,  0, BLACK_CITADEL, TOMB_OF_RELICS, 0, SLAUGHTERHOUSE}, 
                {"  Skeletal Longevity", 60,100, 75,0,3,  0,  0, 0, 0, 0, TEMPLE_OF_THE_DAMNED},
                {"    Skeletal Mastery", 45,125,150,0,3,  0,  0, BLACK_CITADEL, 0, 0, TEMPLE_OF_THE_DAMNED},
                {"     Freezing Breath", 60,150,275,0,3,  0,  0, 0, 0, 0, BONEYARD},
                {"     Unholy Strength", 60,125, 50,0,4,125, 50, 0, 0, 0, GRAVEYARD},
                {"        Unholy Armor", 60,125, 50,0,4,125, 50, 0, 0, 0, GRAVEYARD},
                {"     Creature Attack", 60,150, 50,0,4, 75, 50, 0, 0, 0, GRAVEYARD},
                {"   Creature Carapace", 60,150, 75,0,4,100, 75, 0, 0, 0, GRAVEYARD},
                {"Necromancer Training", 60,100,  0,0,4,100, 50, 0, 0, 0, TEMPLE_OF_THE_DAMNED},
                {"    Banshee Training", 60,100,  0,0,4,100, 50, 0, 0, 0, TEMPLE_OF_THE_DAMNED},
                
		{"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
                {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
                {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
                {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
                {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0},
                {"                NULL",  0,  0,  0,0,0,  0,  0, 0, 0, 0, 0}
	}
		


};








#endif


