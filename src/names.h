#define ERROR_MESSAGES 13

struct Names
{
	char b[6];
};

const char error_m[ERROR_MESSAGES][21]=
{
	"OK",
	"Technology availible",
	"Building availible",
	"enough Gold",
	"enough Wood",
	"Supply satisfied",
	"Larva availible",
	"Worker availible",
	"researched",
	"Timeout",
	"Hero problem",
	"Too many buildings",
	"Expansion availible"};

const char resource[RESOURCES][5]=
{
	"Gold",
	"Wood"
};

const char error_sm[ERROR_MESSAGES]=
{
	        'o','t','b','m','g','s','l','w','r','T','h','y','E'
};

const Names kurz[MAX_RACES][MAX_GOALS+2]=
{
	{
		{"Peasn"},{"Milit"},{"Footm"},{"Rifle"},{"Knigh"},{"Pries"},{"Sorcr"},{"SpllB"},{"Gyroc"},
		{"Morta"},{"Steam"},{"Gryph"},{"Drago"},{"Watr1"},{"Watr2"},{"Watr3"},{"Phoen"},{"Palad"},
		{"ArchM"},{"MntKi"},{"BloMg"},{" Farm"},{"Twnhl"},{" Keep"},{"Castl"},{"BckPk"},{"Barra"},
		{"Altar"},{"LMill"},{"SctTw"},{"Smith"},{"WrkSh"},{"ArcSn"},{"GryAv"},{"ArcVl"},{"GrdTw"},
		{"CanTw"},{"ArcTw"},{"Defnd"},{"LngRf"},{"AnWar"},{"GyrBm"},{"WarEn"},{"Flare"},{"FrgSh"},
		{"StrmH"},{"LmbHa"},{"Mason"},{"MelWe"},{"MelPl"},{"RanWe"},{"LeaAr"},{"PriTr"},{"SrcTr"},
		{"CntrM"},{"MagSe"},{"AddPe"},{"N O P"},{">>Gld"},{">>Wod"},{" I F "},{" JMP "}
	},

	{
		{" Peon"},{"Grunt"},{"HeadH"},{"Catap"},{"Raidr"},{"Taurn"},{"Shamn"},{"WtchD"},{"SprtW"},
		{"KodoB"},{"WyvRi"},{"TrBRi"},{"SprWo"},{"DirWo"},{"ShdWo"},{"SerpW"},{"BldMa"},{"FarSe"},
		{"TauCh"},{"ShdwH"},{"Burro"},{"WarMl"},{"GrHal"},{"StrHo"},{"Fortr"},{"BckPk"},{"Altar"},
		{"Barra"},{"Besti"},{"SprtL"},{"TauTo"},{"VoodL"},{"WtchT"},{"Pilla"},{"BrsSt"},{"TrlRe"},
		{"Brskr"},{"BurnO"},{"ReDef"},{"Ensna"},{"WarDr"},{"EnvSp"},{"LiqFi"},{"Pulvr"},{"MelWe"},
		{"UnArm"},{"RanWe"},{"SpkBa"},{"ShamT"},{"WtchT"},{"SpWTr"},{"NULL!"},{"NULL!"},{"NULL!"},
		{"NULL!"},{"NULL!"},{"NULL!"},{"N O P"},{">>Gld"},{">>Wod"},{" I F "},{" JMP "}
	},

	{
		{" Wisp"},{"Archr"},{"Huntr"},{"Blsta"},{"Dryad"},{"DoClw"},{"MntGi"},{"Hippo"},{"DoTha"},
		{"FaeDr"},{"Chima"},{"Trean"},{"SpVen"},{"Venge"},{"DemHu"},{"KeepG"},{"PrieM"},{"Wardn"},
		{"AnWar"},{"AnLor"},{"AnWin"},{"AnPro"},{"TrLif"},{"TrAge"},{"TrEte"},{"BckPk"},{"AnWon"},
		{"MoonW"},{"AltEl"},{"HuntH"},{"ChRoo"},{"ImpBo"},{"Markm"},{"Senti"},{"MoonG"},{"ImpBo"},
		{"UltrV"},{"WellS"},{"NatBl"},{"AboMg"},{"EnBea"},{"HrdSk"},{"ResSk"},{"HipTr"},{"EnCrw"},
		{"CorBr"},{"StrMo"},{"MoArm"},{"StrWl"},{"ReiHd"},{"DoCTr"},{"DoTTr"},{"Cancl"},{"NULL!"},
		{"NULL!"},{"NULL!"},{"NULL!"},{"N O P"},{">>Gld"},{">>Wod"},{" I F "},{" JMP "}
	},
		
	{
		{"Acoly"},{"Ghoul"},{"CryFi"},{"Gargo"},{"Abomi"},{"MeatW"},{"Necro"},{"Bansh"},{"FrstW"},
		{"Shade"},{"SkWar"},{"SkMag"},{"Infer"},{"CrBLA"},{"CrBLB"},{"CrBLC"},{"ObsSt"},{"DthKn"},
		{"DrdLo"},{" Lich"},{"CrptL"},{"HauGo"},{"Ncrpo"},{"HaotD"},{"BlaCi"},{"BckPk"},{"Crypt"},
		{"Ziggu"},{"AltDa"},{"Grave"},{"Slaug"},{"TmplD"},{"SacPi"},{"BoneY"},{"ToRel"},{"NerTw"},
		{"SpiTw"},{"Cannb"},{"GhouF"},{"  Web"},{"Burrw"},{"StonF"},{"DisCl"},{"ExCor"},{"Destr"},
		{"SkLon"},{"SkMas"},{"FrzBr"},{"UnStr"},{"UnArm"},{"CrAtt"},{"CrCap"},{"NecTr"},{"BanTr"},
		{"Unsum"},{"NULL!"},{"NULL!"},{"N O P"},{"NULL!"},{"NULL!"},{" I F "},{" JMP "}
	}
};	

