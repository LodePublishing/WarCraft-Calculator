struct Names
{
	char b[6];
};

const char error_m[9][20]=
{
	"OK",
	"Building availible",
	"enough Gold",
	"enough Wood",
	"Supply satisfied",
	"Larva availible",
	"Worker availible",
	"researched",
	"Timeout"};

const char resource[RESOURCES][5]=
{
	"Gold",
	"Wood"
};

const char error_sm[9]=
{
	        'o','b','m','g','s','l','w','r','t'
};

const Names kurz[MAX_RACES][MAX_GOALS]=
{
	{
		{"Peasn"},{"Milit"},{"Footm"},{"Rifle"},{"Knigh"},{"Pries"},{"Sorcr"},{"SpllB"},{"Gyroc"},
		{"Morta"},{"Steam"},{"Gryph"},{"Drago"},{"Watr1"},{"Watr2"},{"Watr3"},{"Phoen"},{"Twnhl"},
		{" Keep"},{"Castl"},{"Barra"},{" Farm"},{"Altar"},{"LMill"},{"SctTw"},{"Smith"},{"WrkSh"},
		{"ArcSn"},{"GryAv"},{"ArcVl"},{"GrdTw"},{"CanTw"},{"ArcTw"},{"BckPk"},{"Defnd"},{"LngRf"},
		{"AnWar"},{"GyrBm"},{"WarEn"},{"Flare"},{"FrgSh"},{"StrmH"},{"LmbHa"},{"Mason"},{"MelWe"},
		{"MelPl"},{"RanWe"},{"LeaAr"},{"PriTr"},{"SrcTr"},{"CntrM"},{"MagSe"},{">>Gld"},{">>Wod"},
		{"NULL!"},{"NULL!"},{"NULL!"},{"NULL!"},{"NULL!"},{"NULL!"}
	},

	{
		{" Peon"},{"Grunt"},{"HeadH"},{"Catap"},{"Raidr"},{"Taurn"},{"Shamn"},{"WtchD"},{"SprtW"},
		{"KodoB"},{"WyvRi"},{"TrBRi"},{"SprWo"},{"DirWo"},{"ShdWo"},{"SerpW"},{"GrHal"},{"StrHo"},
		{"Fortr"},{"Altar"},{"Barra"},{"WarMi"},{"Besti"},{"SprtL"},{"TauTo"},{"VoodL"},{"Burro"},
		{"WtchT"},{"Pilla"},{"BackP"},{"BrsSt"},{"TrlRe"},{"Brskr"},{"BurnO"},{"ReDef"},{"Ensna"},
		{"WarDr"},{"EnvSp"},{"LiqFi"},{"Pulvr"},{"MelWe"},{"UnArm"},{"RanWe"},{"SpkBa"},{"ShamT"},
		{"WtchT"},{"SpWTr"},{">>Gld"},{">>Wod"},{"NULL!"},{"NULL!"},{"NULL!"},{"NULL!"},{"NULL!"},
		{"NULL!"},{"NULL!"},{"NULL!"},{"NULL!"},{"NULL!"},{"NULL!"}
	},

	{
		{" Wisp"},{"Archr"},{"Huntr"},{"Blsta"},{"Dryad"},{"DoClw"},{"MntGi"},{"Hippo"},{"DoTha"},
		{"FaeDr"},{"Chima"},{"Trean"},{"SpVen"},{"Venge"},{"TrLif"},{"TrAge"},{"TrEte"},{"AnWar"},
		{"AnLor"},{"AnWin"},{"AnPro"},{"AnWon"},{"MoonW"},{"AltEl"},{"HuntH"},{"ChRoo"},{"BackP"},
		{"ImpBo"},{"Markm"},{"Senti"},{"MoonG"},{"ImpBo"},{"UltrV"},{"WellS"},{"NatBl"},{"AboMg"},
		{"EnBea"},{"HrdSk"},{"ResSk"},{"HipTr"},{"EnCrw"},{"CorBr"},{"StrMo"},{"MoArm"},{"StrWl"},
		{"ReiHd"},{"DoCTr"},{"DoTTr"},{">>Gld"},{">>Wod"},{"NULL!"},{"NULL!"},{"NULL!"},{"NULL!"},
		{"NULL!"},{"NULL!"},{"NULL!"},{"NULL!"},{"NULL!"},{"NULL!"}
	},
		
	{
	{"Acoly"},{"Ghoul"},{"CryFi"},{"Gargo"},{"Abomi"},{"MeatW"},{"Necro"},{"Bansh"},{"FrstW"},
	{"Shade"},{"SkWar"},{"SkMag"},{"Infer"},{"CrBLA"},{"CrBLB"},{"CrBLC"},{"ObsSt"},{"HauGo"},
	{"Ncrpo"},{"HaotD"},{"BlaCi"},{"Crypt"},{"Ziggu"},{"AltDa"},{"Grave"},{"Slaug"},{"TmplD"},
	{"SacPi"},{"BoneY"},{"ToRel"},{"NerTw"},{"SpiTw"},{"BackP"},{"Cannb"},{"GhouF"},{"  Web"},
	{"Burrw"},{"StonF"},{"DisCl"},{"ExCor"},{"Destr"},{"SkLon"},{"SkMas"},{"FrzBr"},{"UnStr"},
	{"UnArm"},{"CrAtt"},{"CrCap"},{"NecTr"},{"BanTr"},{"NULL!"},{"NULL!"},{"NULL!"},{"NULL!"},
	{"NULL!"},{"NULL!"},{"NULL!"},{"NULL!"},{"NULL!"},{"NULL!"}
	}
};	

