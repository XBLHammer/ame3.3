#include "Design.h"
#include "Network.h"

#define ADMIN
//#define BETA
//#define CLIENT

#pragma region GTA_V OFFSETS
	DWORD keys2[] = {0x831AC1C0, 0x835212A8, 0x835211D0, 0x835118E8, 0x8320210, 0x83212E8, 0x8252ED62};
#pragma endregion
namespace ENFORCER_MENU {

	namespace INTERNAL {

		void menuTimeoutFix_Loop()
		{
			if (ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()) && submenu != Closed)
			{
				lastSubmenu[submenuLevel] = submenu;
				lastOption[submenuLevel] = currentOption;
				submenu = Closed;
			}
			if (submenu != Closed)
			{
				menuTimeout++;
				if (menuTimeout > 30000 || !PLAYER::IS_PLAYER_PLAYING(PLAYER::PLAYER_ID()))
				{
					lastSubmenu[submenuLevel] = submenu;
					lastOption[submenuLevel] = currentOption;
					submenu = Closed;
				}
			}
			if (submenu == Closed)
			{
				hasBeenUsed = false;
				menuTimeout = 0;
			}
			if (hasBeenUsed == true)
			{
				hasBeenUsed = false;
				menuTimeout = 0;
			}
		}
	}
}
#pragma region Infinite Loop
using namespace ENFORCER_MENU;
void otherLoop()
{
	if (keyboardActive)
	{
		if (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 1)
		{
			keyboardActive = false;
			switch (keyboardAction)
			{
			case 0: *keyboardVar = StoI(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()); break; //addIntOption
			}
		}
		else if (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 2 || GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 3)
		{
			keyboardActive = false;
		}
	}
}
#pragma endregion



static void TriggerScriptEvent(int* Args, int ArgCount, Player BitsetPlayer)
{
	int Bitset = 0;
	GAMEPLAY::SET_BIT(&Bitset, BitsetPlayer);
	if (Bitset != 0) {
		SCRIPT::TRIGGER_SCRIPT_EVENT2(1, Args, ArgCount, Bitset);
	}
}
int subr = 0;
int subb = 0;
int subg = 0;
int suba = 200;
////////////////////////////
float CheckBoolZ = 0.055;
float CheckBoolX = 0.86;
float CheckBoolY = 0.23;
////////////////////////////
float Cunt = 0.675f;
float Cunt2 = 0.225;
float SubFont = 0;
float ScrollX = 0.78;
float menuXCoord = 0.845f;
float textXCoord = 0.76f;
float BackGPos1 = 0.032f;//AddCheckBool
float TextX = 0.32f;
float TextY = 0.40f;//30
float TitleY = 0.05f;
float TitleX = 0.70f;
float TitleY2 = 0.99f;
float DrawTittleY = 0.08f;
float DrawTittleY2 = 0.09f;
float SubTitleY = 0.20f;
float SubTitleX = 0.40f;
float SubTitleY2 = 0.32f;
float DrawSubTittleY = 0.14f;
float DrawSubTittleY2 = 0.034f;
float BackgroundH = 0.158f;
float BackgroundW = 0.27f;//0.28f
float BackGWidht = 0.216f;//0.28f
float DrawTittleX = 0.27f;//0.28f
float DrawSubTittleX = 0.27f;//0.28f
float DrawScaleX = 0.27f;
float ScrollerPosX = 0.23f;
float BackGPos2 = 0.12f;
float titlebox3 = 0.928f;
int maxOptions = 15;//23 
					////////////////////////////
float Globecord = 0.980f;
float GlobeCoordSX = 1.0f;
float GlobeCoordX = 0.50f;
float GlobeCoordY = 0.510f;
float MyTextXCoord = 0.83f;
float DirtLevelC = 0;
float FxSize = 1.0f;

//////////////////////////// Spawer Ped
int SpawnedPeds[20];
char* PedsNameArray[20];
int SpawnedPeds_;
int SelectedPeds;
char* PedsNameSpawned;

//////////////////////////// Spawer Object
int SpawnedObject[20];
char* ObjectNameArray[20];
int SpawnedObjects_;
int SelectedObject;
char* ObjectsNameSpawned;

//////////////////////////// Char Stuff
char* Name;
char * FXLoad; char * FXIDLoad; char* WalkTypeLoad;
char * Animation; char * AnimationID;
////////////////////////////

bool ProtectionTest9 = false;
bool ProtectionTest4 = false;
bool ProtectionTest7 = false;
bool ProtectionTest3 = false;
bool ProtectionTest6 = false;
bool ProtectionTest1 = false;

DWORD SaveVMPassed[100];
DWORD VMPassed[100];
DWORD VMReturned[5];
DWORD *VMArgs[3] = { VMReturned, 0, VMPassed };
XOVERLAPPED Overlapped2;
WCHAR Username2[15];
BOOL bInitialized = FALSE;
XINPUT_STATE InputState;
INT vm_tick;
#pragma endregion


#pragma region Internals
#pragma region Hook & Execution
void Reset()
{
	bInitialized = FALSE;
}
#pragma endregion
#pragma region Text
int snprintf(char *buffer, size_t len, const char *fmt, ...)
{
	va_list args;
	int i;

	va_start(args, fmt);
	i = vsnprintf(buffer, len, fmt, args);
	va_end(args);
	return i;
}

int TunablesAddress;
int FindTunablesPointer()
{
	return TunablesAddress = (*(int*)0x83DDD934) + 4;
}

void SetTunable(int index, int value)
{
	FindTunablesPointer();
	if (TunablesAddress != 4)
	{
		//NotifyAboveMap("~p~Zenyle Menu Tunables Really M8");
		int temp = TunablesAddress;
		temp += (index * 4);
		*(int*)temp = value;
	}
}


//SetTunable(4713, 1);


int XMASCONTENT(int yes)
{
	SetTunable(6880, false); // DISABLE_SNOWBALLS
	SetTunable(6881, true); // DISABLE_CHRISTMAS_TREE_PERISHING_SQUARE_SNOW
	SetTunable(6882, true); // DISABLE_CHRISTMAS_TREE_PERISHING_SQUARE
	SetTunable(6883, true); // DISABLE_CHRISTMAS_TREE_APARTMENT
	SetTunable(6884, yes); // DISABLE_CHRISTMAS_CLOTHING
	SetTunable(6885, yes); // DISABLE_CHRISTMAS_MASKS
	SetTunable(6886, yes); // DISABLE_CHRISTMAS_VEHICLES
	SetTunable(4724, yes); // TOGGLE_XMAS_CONTENT
	SetTunable(6889, yes); // VEHICLE_XMAS14_DINKA_JESTER_RACECAR
	SetTunable(6890, yes); // VEHICLE_XMAS14_DEWBAUCHEE_MASSACRO_RACECAR
	SetTunable(6891, yes); // VEHICLE_XMAS14_RAT_TRUCK
	SetTunable(6892, yes); // VEHICLE_XMAS14_SLAMVAN
	SetTunable(6893, yes); // VEHICLE_XMAS14_BRAVADO_SPRUNK_BUFFALO
	SetTunable(6894, yes); // VEHICLE_XMAS14_DEWBAUCHEE_MASSACRO_RACECAR
	SetTunable(6895, yes); // VEHICLE_XMAS14_VAPID_PISSWASSER_DOMINATOR
	SetTunable(6896, yes); // VEHICLE_XMAS14_BRAVADO_REDWOOD_GAUNTLET
	SetTunable(6897, yes); // VEHICLE_XMAS14_DECLASSE_BURGER_SHOT_STALLION
	SetTunable(6898, yes); // WEAPONS_XMAS14_HOMING_LAUNCHER
	SetTunable(6899, yes); // WEAPONS_XMAS14_HOMING_LAUNCHER_AMMO
	SetTunable(6900, yes); // WEAPONS_XMAS14_PROXIMITY_MINE
	SetTunable(6901, yes); // WEAPONS_XMAS14_BLACK_COMBAT_CHUTE_BAG
	SetTunable(6902, yes); // WEAPONS_XMAS14_GRAY_COMBAT_CHUTE_BAG
	SetTunable(6903, yes); // WEAPONS_XMAS14_CHARCOAL_COMBAT_CHUTE_BAG
	SetTunable(6904, yes); // WEAPONS_XMAS14_TAN_COMBAT_CHUTE_BAG
	SetTunable(6905, yes); // WEAPONS_XMAS14_FOREST_COMBAT_CHUTE_BAG
	SetTunable(6887, 10); // MAX_NUMBER_OF_SNOWBALLS
	SetTunable(6888, 3); // PICK_UP_NUMBER_OF_SNOWBALLS
	return 0;
}

int ANTIIDLEKICK(int yes)
{
	SetTunable(73, yes); // IDLEKICK_WARNING1
	SetTunable(74, yes); // IDLEKICK_WARNING2
	SetTunable(75, yes); // IDLEKICK_WARNING3
	return 0;
}

int IndependenceDayContent(int yes)
{
	SetTunable(6016, yes); // Toggle_activate_Western_sovereign
	SetTunable(6017, yes); // Toggle_activate_Monster_truck
	SetTunable(6011, yes); // INDEPENDENCE_DAY_DEACTIVATE_FIREWORKS_LAUNCHER
	SetTunable(6003, yes); // TOGGLE_ACTIVATE_INDEPENDENCE_PACK
	return 0;
}

int TOGGLESNOW(int yes)
{
	SetTunable(4715, yes);
	SetTunable(3094, yes);
	SetTunable(3505, yes);
	SetTunable(3642, yes);
	SetTunable(2953, yes);
	SetTunable(3231, yes);
	SetTunable(3368, yes);
	return 0;
}

int SuperBountyAmount(int amount)
{
	SetTunable(2312, amount); // BOUNTY_AWARD_LEVEL_1_MODIFIER
	SetTunable(2313, amount); // BOUNTY_AWARD_LEVEL_2_MODIFIER
	SetTunable(2314, amount); // BOUNTY_AWARD_LEVEL_3_MODIFIER
	SetTunable(2315, amount); // BOUNTY_AWARD_LEVEL_4_MODIFIER
	SetTunable(2316, amount); // BOUNTY_AWARD_LEVEL_5_MODIFIER
	return 0;
}

void drawNotification(char* msg)
{
	UI::_0xF42C43C7("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(msg);
	UI::_0x38F82261(3000, 1);
}
void drawNotification2(char* msg)
{
	UI::_0xF42C43C7("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(msg);
	UI::_0x38F82261(6000, 1);
}

bool isNumericChar(char x)
{
	return (x >= '0' && x <= '9') ? true : false;
}
int StoI(char *str)
{
	if (*str == NULL)
		return 0;

	int res = 0,
		sign = 1,
		i = 0;

	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	for (; str[i] != '\0'; ++i)
	{
		if (isNumericChar(str[i]) == false)
			return 0;
		res = res * 10 + str[i] - '0';
	}
	return sign*res;
}
char *ItoS(int num)
{
	char buf[30];
	snprintf(buf, sizeof(buf), "%i", num);
	return buf;
}
char* FtoS(float input)
{
	char returnvalue[64];
	int wholenumber = (int)input;
	input -= wholenumber;
	input *= 100;
	sprintf(returnvalue, "%d.%d", wholenumber, (int)input);
	return returnvalue;
}
void drawText(char * text, int font, float x, float y, float scalex, float scaley, int r, int g, int b, int a, bool center)
{
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(scalex, scaley);
	UI::SET_TEXT_COLOUR(r, g, b, a);
	UI::SET_TEXT_WRAP(0.0f, 1.0f);
	UI::SET_TEXT_CENTRE(center);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_OUTLINE();
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	UI::_DRAW_TEXT(x, y);
}

void LoadGarage() {
	for (DWORD i = 0; i < 0x10; i++) {
		int Vehicle = *(PDWORD)(DWORD)(0x83DDDD20 + 0xB0 + (DWORD)(i * 0x190));
		drawText((PCHAR)(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(Vehicle)), 1, 0.68, (float)(i * 0.035 + 0.194), 0.7, 0.7, 255, 255, 255, 255, false);
	}
}

void startKeyboard(int action, char *defaultText, int maxLength)
{
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(0, "FMMC_KEY_TIP8", "", defaultText, "", "", "", maxLength);
	keyboardAction = action;
	keyboardActive = true;
}
Hash getHashKey(char *str)
{
	return GAMEPLAY::GET_HASH_KEY(str);
}
#pragma endregion
#pragma region Instructions
void set_text_component(char *text)
{
	GRAPHICS::_0x3AC9CB55("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	GRAPHICS::_0x386CE0B8();
}

bool RequestNetworkControl(int playerHandle, int carHandle)
{
	int Vehicle = PED::GET_VEHICLE_PED_IS_IN(playerHandle, 0);
	if (ENTITY::DOES_ENTITY_EXIST(carHandle) && ENTITY::IS_ENTITY_A_VEHICLE(carHandle))
	{
		if (NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(carHandle))
		{
			if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(carHandle))
			{
				return true;
			}
		}
	}
	return false;
}
bool RequestNetworkControl(uint vehID)
{
	int Tries = 0;
	bool
		hasControl = false,
		giveUp = false;
	do
	{
		hasControl = NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehID);
		Tries++;
		if (Tries > 300)
			giveUp = true;
	} while (!hasControl && !giveUp);

	if (giveUp)
		return false;
	else return true;
}
bool GetPedLastWeaponImpactCoord(Ped ped, Vector3* coords)
{
	float tmp[6];
	bool ret = WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(ped, tmp);
	Vector3 tempCoords = { tmp[0], tmp[2], tmp[4] };
	*coords = tempCoords;
	return ret;
}

Vector3 GetCoordsFromCam(float distance)
{
	Vector3 Rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
	static Vector3 Coord = CAM::GET_GAMEPLAY_CAM_COORD();
	Rot.y = distance * cos(Rot.x);
	Coord.x = Coord.x + Rot.y * sin(Rot.z * -1.0f);
	Coord.y = Coord.y + Rot.y * cos(Rot.z * -1.0f);
	Coord.z = Coord.z + distance * sin(Rot.x);
	return Coord;
}

void VectorToFloat(Vector3 unk, float *Out)
{
	Out[0] = unk.x;
	Out[1] = unk.y;
	Out[2] = unk.z;
}

void RequestControlEntity(Entity entity)
{
	int tick = 0;
	while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity) && tick <= 12)
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);

		tick++;
	}
}

void offset_from_entity(int entity, float X, float Y, float Z, float * Out)
{
	VectorToFloat(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(entity, X, Y, Z), Out);
}

void NotifyAboveMap(std::string Message)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)Message.c_str());
	UI::_DRAW_NOTIFICATION2(2500, 1);
}



void(*periodic_feature_call)(void) = NULL;

void set_periodic_feature_call(void method(void))
{
	periodic_feature_call = method;
}

void make_periodic_feature_call()
{
	periodic_feature_call();
}

void RequestControlOfEnt(int entity)
{
	int tick = 0;

	while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity) && tick <= 12)
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
		tick++;
	}
}

void instructionsSetup()
{
	mov = GRAPHICS::REQUEST_SCALEFORM_MOVIE("instructional_buttons");
	GRAPHICS::_0x7B48E696(mov, 255, 255, 255, 0);
	GRAPHICS::_0x215ABBE8(mov, "CLEAR_ALL");
	GRAPHICS::_0x02DBF2D7();
	GRAPHICS::_0x215ABBE8(mov, "SET_CLEAR_SPACE");
	GRAPHICS::_0x716777CB(200);
	GRAPHICS::_0x02DBF2D7();
	instructCount = 0;
}
void addInstruction(int button, char *text)
{
	if (!instructionsSetupThisFrame)
	{
		instructionsSetup();
		instructionsSetupThisFrame = true;
	}
	GRAPHICS::_0x215ABBE8(mov, "SET_DATA_SLOT");
	GRAPHICS::_0x716777CB(instructCount);
	GRAPHICS::_0x716777CB(button);
	set_text_component(text);
	GRAPHICS::_0x02DBF2D7();
	instructCount++;
}
void instructionsClose()
{
	GRAPHICS::_0x215ABBE8(mov, "DRAW_INSTRUCTIONAL_BUTTONS");
	GRAPHICS::_0x02DBF2D7();
	GRAPHICS::_0x215ABBE8(mov, "SET_BACKGROUND_COLOUR");
	GRAPHICS::_0x716777CB(0);
	GRAPHICS::_0x716777CB(0);
	GRAPHICS::_0x716777CB(0);
	GRAPHICS::_0x716777CB(80);
	GRAPHICS::_0x02DBF2D7();
}
#pragma endregion
#pragma region Misc
void SetupTimer(int tickTime)
{
	if (newTimerTick) {
		maxTimerCount = GAMEPLAY::GET_GAME_TIMER() + tickTime;
		newTimerTick = false;
	}
}

int getHost()
{
	return NETWORK::NETWORK_GET_HOST_OF_SCRIPT("Freemode", 4294967295, 0);
}
char* getHostName()
{
	return PLAYER::GET_PLAYER_NAME(getHost());
}

void ShowMessageOnScreen(char *format, ...)
{
	char messageBuffer[256];
	va_list args;
	va_start(args, format);
	vsprintf(messageBuffer, format, args);
	va_end(args);
	drawNotification(messageBuffer);
}

bool IsTimerReady()
{
	return GAMEPLAY::GET_GAME_TIMER() > maxTimerCount;
}
void ResetTimer()
{
	newTimerTick = true;
}
void SetupTimer2(int tickTime)
{
	if (newTimerTick2) {
		maxTimerCount2 = GAMEPLAY::GET_GAME_TIMER() + tickTime;
		newTimerTick2 = false;
	}
}

void NotifyAboveMap2(std::string Message, ...)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)Message.c_str());
	UI::_DRAW_NOTIFICATION2(2500, 1);
}

void NotifyAboveMap3(std::string Message, std::string Message2)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)Message.c_str());
	UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)Message2.c_str());
	UI::_DRAW_NOTIFICATION2(2500, 1);
}

void ShowPlayerTalking(char *player, float x, float y, int R, int G, int B, int A)
{
	UI::SET_TEXT_FONT(6);
	UI::SET_TEXT_COLOUR(R, G, B, A);
	UI::SET_TEXT_SCALE(0.6050f, 0.6050f);
	UI::SET_TEXT_CENTRE(0);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(player);
	UI::_DRAW_TEXT(x, y);
}
void PrintToScreen(char *text, float x, float y, int r, int g, int b, int a, float scaleX, float scaleY, int centerText, int font)
{
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_COLOUR(r, g, b, a);
	UI::SET_TEXT_SCALE(scaleX, scaleY);
	UI::SET_TEXT_CENTRE(centerText);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	UI::_DRAW_TEXT(x, y);
}
void WhoYouMuted(char *player, float x, float y)
{
	UI::SET_TEXT_FONT(4);
	UI::SET_TEXT_SCALE(0.44f, 0.44f);
	UI::SET_TEXT_COLOUR(0, 125, 255, 255);
	UI::SET_TEXT_CENTRE(2);
	UI::_SET_TEXT_ENTRY("STRING"); //text display type
	UI::_ADD_TEXT_COMPONENT_STRING(player); // add the text component
	UI::_DRAW_TEXT(x, y);//actually draw the text
	PrintToScreen("Muted:", 0.19f, 0.02f, 0, 125, 255, 255, 0.80000000, 0.80000000, 0, 6);
}
void Draw_TextEliteMods(char* Text, int Font, float X, float Y, float Scale_X, float Scale_Y, int Red, int Green, int Blue, int Alpha, bool Shadow = false, bool Outline = false, bool Center = false)
{
	UI::SET_TEXT_FONT(Font);
	UI::SET_TEXT_SCALE(Scale_X, Scale_Y);
	UI::SET_TEXT_COLOUR(Red, Green, Blue, Alpha);
	if (Shadow)
		UI::SET_TEXT_DROP_SHADOW();
	UI::SET_TEXT_CENTRE(Center);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(Text);
	UI::_DRAW_TEXT(X, Y);
}
void PrintToScreenNum(int number, float x, float y, int r, int g, int b, int a, float scaleX, float scaleY, int centerText, int font)
{
	snprintf(printMessageBuffer, sizeof(printMessageBuffer), "%i", number);
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_COLOUR(r, g, b, a);
	UI::SET_TEXT_SCALE(scaleX, scaleY);
	UI::SET_TEXT_CENTRE(centerText);
	UI::_ADD_TEXT_COMPONENT_STRING(printMessageBuffer);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_DRAW_TEXT(x, y);
}
int FreeSlots()
{
	int slots = 0;
	for (int i = 0; i < 16; i++)
	{
		int ped = PLAYER::GET_PLAYER_PED(i);
		if (!ENTITY::DOES_ENTITY_EXIST(ped))
		{
			slots++;
		}
	}
	return slots;
}

bool IsTimerReady2()
{
	return GAMEPLAY::GET_GAME_TIMER() > maxTimerCount2;
}
void ResetTimer2()
{
	newTimerTick2 = true;
}
void playSound(char* sound)
{
	if (menuSounds)
		AUDIO::PLAY_SOUND_FRONTEND(-1, sound, "HUD_FRONTEND_DEFAULT_SOUNDSET");
}
void teleport(float x, float y, float z)
{
	Ped ped = PLAYER::PLAYER_PED_ID();
	Entity entityToTele = ped;
	if (PED::IS_PED_SITTING_IN_ANY_VEHICLE(ped))
		entityToTele = PED::GET_VEHICLE_PED_IS_USING(ped);
	ENTITY::SET_ENTITY_COORDS(entityToTele, x, y, z, true, false, false, true);
}
#pragma endregion
#pragma region Vehicle
//addVehicleSpawnOption in Menu/Option Helpers pragma
#pragma endregion
#pragma region Menu
void changeSubmenu(int newSubmenu)
{
	lastSubmenu[submenuLevel] = submenu;
	lastOption[submenuLevel] = currentOption;
	currentOption = 1;
	submenu = newSubmenu;
	submenuLevel++;
}

void MenuTitle()
{
	//DrawSprite("mpmissmarkers256", "bike_race_icon", menuXCoord, 0.53f, 0.25, 0.86f, 0.0f, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity);

}

void WeaponSprite()
{
	//GRAPHICS::DRAW_RECT(menuXCoord, 0.130f, 0.230f, 0.127f, 220, 20, 60, 255);
	//DrawSprite("shopui_title_gunclub", "shopui_title_gunclub", menuXCoord, 0.145f, 0.210f, 0.100f, 0.0f, 255, 255, 255, 255);
	//DrawSprite("hud", "ammunation", menuXCoord, 0.130f, 0.230f, 0.127f, 0.0f, 255, 255, 255, 255);
	//DrawSprite("hud", "ammunation", menuXCoord, *(float*)0x83A81010, *(float*)0x83A81014, *(float*)0x83A81018, 0.0f, 255, 255, 255, 255);
	//GRAPHICS::DRAW_RECT(menuXCoord, 0.130f, 0.230f, 0.127f, 220, 20, 60, 255);
	//GRAPHICS::DRAW_RECT(menuXCoord, 0.130f, 0.230f, 0.127f, 220, 20, 60, 255);
	//GRAPHICS::DRAW_RECT(menuXCoord, *(float*)0x83A81010, *(float*)0x83A81014, *(float*)0x83A81018, 220, 20, 60, 255);
	//GRAPHICS::DRAW_RECT(menuXCoord, ((maxOptions * 0.035f) + 0.2110f), 0.23f, 0.035f, scrollerRed, scrollerGreen, scrollerBlue, scrollerOpacity); //Scroller
}

void ModShop_Sprite()
{
	//DrawSprite("shopui_title_carmod", "shopui_title_carmod", menuXCoord, 0.145f, 0.210f, 0.100f, 0.0f, 255, 255, 255, 255);
}

void VehicleSpawner_Sprite()
{
	//DrawSprite("shopui_title_carmod2", "shopui_title_carmod2", menuXCoord, 0.145f, 0.210f, 0.100f, 0.0f, 255, 255, 255, 255);
}

void Planes_Sprite()
{
	//DrawSprite("char_planesite", "char_planesite", menuXCoord, 0.53f, 0.25, 0.86f, 0.0f, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity);
}

void Bike_Sprite()
{
	//DrawSprite("char_bikesite", "char_bikesite", menuXCoord, 0.53f, 0.25, 0.86f, 0.0f, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity);

}

void DrawDankMenu()
{
	//drawText("Zenyle Menu (1.27)", 1, textXCoord, 0.116f, 0.90f, 0.90f, 255, 255, 255, bannerTextOpacity, false);
	//drawText("Version 2.0 Beta", 6, menuverxcoord, menuverycoord, 0.45f, 0.45f, 255, 255, 255, bannerTextOpacity, false);
	//GRAPHICS::DRAW_RECT(menuXCoord, 0.130f, 0.230f, 0.127f, 255, 255, 255, 13);
	//GRAPHICS::DRAW_RECT(menuXCoord, 0.145f, 0.210f, 0.100f, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity);
	//GRAPHICS::DRAW_RECT(menuXCoord, 0.130f, 0.230f, 0.127f, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity);
	//DrawSprite("mpmissmarkers256", "vehicledeathmatch_icon", menuXCoord, 0.130f, 0.230f, 0.127f, 0.0f, 255, 255, 255, 255);
}
float ytext = 0.157f;
void drawTextxxx(char * text, int font, float x, float y, float scalex, float scaley, int r, int g, int b, int a, bool center)
{
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(scalex, scaley);
	UI::SET_TEXT_CENTRE(center);
	if (currentOption == optionCount)
	{
		UI::SET_TEXT_WRAP(0.0f, 1.0f);
		UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		UI::SET_TEXT_OUTLINE();
		UI::SET_TEXT_COLOUR(0, 50, 255, 255);
		UI::_SET_TEXT_ENTRY("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING(text);
	}
	else {
		UI::SET_TEXT_COLOUR(r, g, b, a);
		UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		UI::SET_TEXT_OUTLINE();
		UI::_SET_TEXT_ENTRY("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING(text);
		UI::SET_TEXT_FONT(font);
		UI::SET_TEXT_SCALE(scalex, scaley);
		UI::SET_TEXT_WRAP(0.0f, 1.0f);
		UI::SET_TEXT_CENTRE(center);
	}
	UI::_DRAW_TEXT(x, y);
}

void drawTextxxx2(char * text, int font, float x, float y, float scalex, float scaley, int r, int g, int b, int a, bool center)
{
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(scalex, scaley);
	UI::SET_TEXT_COLOUR(r, g, b, a);
	UI::SET_TEXT_WRAP(0.0f, 1.0f);
	UI::SET_TEXT_CENTRE(center);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	UI::_DRAW_TEXT(x, y);
}
float menurecty = 0.214;
void addOption(char *option, char *info = NULL)
{
	optionCount++;
	if (currentOption == optionCount)
		infoText = info;
	if (currentOption <= maxOptions && optionCount <= maxOptions)
		drawText(option, optionsFont, textXCoord, (optionCount * 0.035f + 0.125f), 0.4f, 0.4f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
		drawText(option, optionsFont, textXCoord, ((optionCount - (currentOption - maxOptions)) * 0.035f + 0.125f), 0.4f, 0.4f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
}


void addSubmenuOption(char *option, int newSubmenu, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		if (optionPress)
			changeSubmenu(newSubmenu);
	}
}

void DrawSprite1(char * Streamedtexture, char * textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
{
	GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(Streamedtexture, false);
	if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(Streamedtexture));
	GRAPHICS::DRAW_SPRITE(Streamedtexture, textureName, x, y, width, height, rotation, r, g, b, a);
}

void AddCheckBooloff(char *option, bool b00l1, char *info = NULL)//AddCheckBool
{
	char buf[30];
	if (b00l1)
	{
		snprintf(buf, sizeof(buf), "%s", option);
		DrawSprite1("commonmenu", "shop_box_tick", CheckBoolX, (optionCount * BackGPos1 + CheckBoolY), CheckBoolZ, 0.04, 0, 255, 255, 255, 255);
		addOption(buf, info);
	}
	else
	{
		snprintf(buf, sizeof(buf), "%s", option);
		DrawSprite1("commonmenu", "shop_box_blank", CheckBoolX, (optionCount * BackGPos1 + CheckBoolY), CheckBoolZ, 0.04, 0, 255, 255, 255, 255);
		addOption(buf, info);

	}
}
void textureconfig()
{
	if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED("commonmenu"))
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("commonmenu", 0);
	}
}
void addBoolOption(char *option, bool b00l1, char *info = NULL)
{
	char buf[30];
	if (b00l1)
	{
		snprintf(buf, sizeof(buf), "%s: On", option);
		addOption(buf, info);
	}
	else
	{
		snprintf(buf, sizeof(buf), "%s: Off");
		addOption(buf, info);
	}
}

void CheckBoolMapPl(char *option, bool b00l1, char *info = NULL)
{
	char buf[30];
	if (b00l1)
	{
		snprintf(buf, sizeof(buf), "%s", option);
		DrawSprite1("shared", "info_icon_32", CheckBoolX, (optionCount * BackGPos1 + CheckBoolY), 0.02, 0.03, 0, 255, 255, 255, 255);
		addOption(buf, info);
	}
	else {
		snprintf(buf, sizeof(buf), "%s", option);
		addOption(buf, info);

	}
}


float CheckW = 0.02, CheckH = 0.03;
void CheckBoolVehicle(char *option, bool b00l1, char *info = NULL)
{
	char buf[30];
	if (b00l1)
	{
		snprintf(buf, sizeof(buf), "%s", option);
		DrawSprite1("commonmenu", "shop_garage_icon_a", CheckBoolX, (optionCount * BackGPos1 + 0.175f), CheckW, CheckH, 0, 255, 255, 255, 255);
		addOption(buf, info);
	}
	else
	{
		snprintf(buf, sizeof(buf), "%s", option);
		//DrawSprite1("", "", Checkbox, (optionCount * BackGPos1 + 0.175f), 0.03, 0.04, 0, 255, 255, 255, 255);
		addOption(buf, info);

	}
}


void CheckBoolWeapon(char *option, bool b00l1, char *info = NULL)
{
	char buf[30];
	if (b00l1)
	{
		snprintf(buf, sizeof(buf), "%s", option);
		DrawSprite1("commonmenu", "shop_gunclub_icon_a", CheckBoolX, (optionCount * BackGPos1 + 0.175f), CheckW, CheckH, 0, 255, 255, 255, 255);
		addOption(buf, info);
	}
	else
	{
		snprintf(buf, sizeof(buf), "%s", option);
		//DrawSprite1("", "", Checkbox, (optionCount * BackGPos1 + 0.175f), 0.03, 0.04, 0, 255, 255, 255, 255);
		addOption(buf, info);

	}
}


template<typename TYPE>
void addCustomBoolOption(char *option, TYPE value, TYPE match, char *info = NULL)
{
	char buf[30];
	if (value == match)
	{
		snprintf(buf, sizeof(buf), "%s: ~f~On", option);
		addOption(buf, info);
	}
	else
	{
		snprintf(buf, sizeof(buf), "%s: ~r~Off", option);
		addOption(buf, info);
	}
}
void addIntOption(char *option, int *var, int min, int max, bool keyboard, char *info = NULL)
{
	char buf[3000];
	snprintf(buf, sizeof(buf), "%s: [%i]", option, *var);
	addOption(buf, info);
	if (currentOption == optionCount)
	{
		lrInstruction = true;
		if (rightPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var >= max)
				*var = min;
			else
				*var = *var + 1;
		}
		else if (leftPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var <= min)
				*var = max;
			else
				*var = *var - 1;
		}
		if (keyboard)
		{
			squareInstruction = true;
			if (squarePress)
			{
				startKeyboard(0, "", (strlen(ItoS(max)) + 1));
				keyboardVar = var;
			}
		}
	}
}
int GET_VEHICLE_ADD(int index)
{
	int Tmp = *(int*)(0x83AF8858);
	return *(int*)(Tmp + (index * 0x04)) + 0x04;
}
void SET_HANDLING_MOD(int index, int mod, float value)
{
	int Tmp = GET_VEHICLE_ADD(index) + mod;
	*(float*)(Tmp) = value;
}
float susp = 0.0;
void SET_SUSPENSION(float susp)
{
	int VehicleID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);

	NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(VehicleID);

	if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(VehicleID))
	{
		for (int i = 0; i < 0x133; i++)
			SET_HANDLING_MOD(i, 0xBC, susp);
	}
}
void addSuspensionOption(char *option, float *var, float min, float max, bool holdPress, char *info = NULL)
{
	char buf[30];
	snprintf(buf, sizeof(buf), "%s: < %s >", option, FtoS(*var));
	addOption(buf, info);
	SET_SUSPENSION(*var);
	if (currentOption == optionCount)
	{
		lrInstruction = true;
		if (holdPress)
		{
			if (fastRightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + 0.01f;
			}
			else if (fastLeftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 0.01f;
			}
		}
		else
		{
			if (rightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + 0.01f;
			}
			else if (leftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 0.01f;
			}
		}
	}
}
void addNotifyOption(char *option, char *notification)
{
	addOption(option);
	if (currentOption == optionCount && optionPress)
	{
		//drawNotification(notification);
	}
}

void addKeyboard(char *option, int action, char *defaultText, int maxLength, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		if (optionPress)
			startKeyboard(action, defaultText, maxLength);
	}
}
#pragma endregion

int getOption()
{
	if (optionPress)
		return currentOption;
	else return 0;
}

class Timer
{
public:
	Timer()
	{
		TargetTime = 0;
	}

	void Delay(int MilliSeconds)
	{
		TargetTime = GAMEPLAY::GET_GAME_TIMER() + MilliSeconds;
	}

	bool IsTimerGood()
	{
		if (TargetTime <= GAMEPLAY::GET_GAME_TIMER())
			return true;
		else
			return false;
	}

private:
	unsigned int TargetTime;
public:
	bool enabled;
};
int AdjustB = BUTTON_RB;
int AdjustB2 = Dpad_Down;
Timer MainTimer;
bool firstopenmenu = false;
void drawWelcome()
{
	char buf[300];
	snprintf(buf, sizeof(buf), "~w~Welcome %s To INF3C7ION Menu\nMenu Made by ModzMster", PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID()));
	drawNotification2(buf);
}
void monitorButtons()
{
	SetupTimer(10);
	if (submenu == Closed)
	{
		if (IsTimerReady())
		{
			if (CONTROLS::IS_CONTROL_PRESSED(0, Dpad_Down) && CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_X))
			{
				submenu = !submenu;
				submenuLevel = 0;
				currentOption = 1;
				playSound("YES");
			}
			ResetTimer();
		}
	}
	else {
		if (IsTimerReady())
		{
			if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_B))
			{
				if (submenu == Main_Menu)
				{
					submenu = Closed;
					playSound("NO");
				}
				else {
					submenu = lastSubmenu[submenuLevel - 1];
					currentOption = lastOption[submenuLevel - 1];
					submenuLevel--;
				}
				playSound("Back");
			}
			else if (CONTROLS::IS_CONTROL_PRESSED(0, Dpad_Down) && CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_X))
			{
				if (submenu)
				{
					submenu = !submenu;
					submenu = Closed;
					playSound("NO");
				}
			}
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_A))
			{
				optionPress = true;
				playSound("SELECT");
			}
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Dpad_Up))
			{
				currentOption--;
				if (currentOption < 1)
				{
					currentOption = optionCount;
				}
				playSound("NAV_UP_DOWN");
			}
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Dpad_Down))
			{
				currentOption++;
				if (currentOption > optionCount)
				{
					currentOption = 1;
				}
				playSound("NAV_UP_DOWN");
			}
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Dpad_Right))
			{
				rightPress = true;
			}
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Dpad_Left))
			{
				leftPress = true;
			}
			else if (CONTROLS::IS_CONTROL_PRESSED(0, Dpad_Right))
			{
				fastRightPress = true;
			}
			else if (CONTROLS::IS_CONTROL_PRESSED(0, Dpad_Left))
			{
				fastLeftPress = true;
			}
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_X))
			{
				squarePress = true;
			}
			ResetTimer();
		}
	}
}




float Subx1 = 0.85;
float Suby1 = 0.20;
float Subx2 = 0.20f;
float Suby2 = 0.32f;
int spritecolorhud = 50;
void drawText2(char * text, int font, float x, float y, float scalex, float scaley, int r, int g, int b, int a, bool center)
{
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(scalex, scaley);
	UI::SET_TEXT_COLOUR(r, g, b, a);
	UI::SET_TEXT_CENTRE(center);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_OUTLINE();
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	UI::_DRAW_TEXT(x, y);
}
int indicatorRed = 255;
int indicatorGreen = 255;
int indicatorBlue = 255;
int indicatorOpacity = 255;

void normalMenuActions()
{
	//UI::HIDE_HELP_TEXT_THIS_FRAME();
	UI::HIDE_HELP_TEXT_THIS_FRAME();
	CAM::SET_CINEMATIC_BUTTON_ACTIVE(0);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(10);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(6);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(7);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(9);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(8);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 19);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 20);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 21);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 27);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 54);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 123);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 124);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 125);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 126);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 138);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 139);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 140);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 177);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 178);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 179);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 207);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 166);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 167);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 177);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 178);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 193);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 194);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 195);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 202);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 203);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 204);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 205);
	if (optionCount > maxOptions)
	{

		GRAPHICS::DRAW_RECT(menuXCoord, (((maxOptions * 0.035f) / 2) + 0.159f), 0.19f, (maxOptions * 0.035f), backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity); //Background
		if (currentOption > maxOptions)
		{
			GRAPHICS::DRAW_RECT(menuXCoord, ((maxOptions * 0.035f) + 0.1415f), 0.19f, 0.035f, scrollerRed, scrollerGreen, scrollerBlue, scrollerOpacity); //Scroller
			GRAPHICS::DRAW_RECT(menuXCoord, 0.156f, 0.19f, 0.005f, indicatorRed, indicatorGreen, indicatorBlue, indicatorOpacity); //Up Indicator
		}
		else
		{
			GRAPHICS::DRAW_RECT(menuXCoord, ((currentOption * 0.035f) + 0.1415f), 0.19f, 0.035f, scrollerRed, scrollerGreen, scrollerBlue, scrollerOpacity); //Scroller
		}
		if (currentOption != optionCount)
		{
			GRAPHICS::DRAW_RECT(menuXCoord, ((maxOptions * 0.035f) + 0.161f), 0.19f, 0.005f, indicatorRed, indicatorGreen, indicatorBlue, indicatorOpacity); //Down Indicator

		}
	}
	else
	{
		GRAPHICS::DRAW_RECT(menuXCoord, (((optionCount * 0.035f) / 2) + 0.159f), 0.19f, (optionCount * 0.035f), backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity); //Background
		GRAPHICS::DRAW_RECT(menuXCoord, ((currentOption * 0.035f) + 0.1415f), 0.19f, 0.035f, scrollerRed, scrollerGreen, scrollerBlue, scrollerOpacity); //Scroller



	}
	if (!GAMEPLAY::IS_STRING_NULL_OR_EMPTY(infoText))
	{
		if (optionCount > maxOptions)
		{
			drawText(infoText, optionsFont, menuXCoord, ((maxOptions + 1) * 0.035f + 0.125f), 0.4f, 0.4f, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, true);
			GRAPHICS::DRAW_RECT(menuXCoord, (((maxOptions + 1) * 0.035f) + 0.1415f), 0.19f, 0.035f, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity); //Info Box


		}
		else
		{
			drawText(infoText, optionsFont, menuXCoord, ((optionCount + 1) * 0.035f + 0.125f), 0.4f, 0.4f, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, true);
			GRAPHICS::DRAW_RECT(menuXCoord, (((optionCount + 1) * 0.035f) + 0.1415f), 0.19f, 0.035f, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity); //Info Box


		}
	}



	SetupTimer2(20);
	if (instructions)
	{
		if (IsTimerReady2())
		{
			if (xInstruction)
				addInstruction(BUTTON_A, "Select");
			if (squareInstruction)
				addInstruction(BUTTON_X, "Keyboard");
			if (lrInstruction)
				addInstruction(BUTTON_DPAD_LEFT_RIGHT, "Scroll");
			addInstruction(BUTTON_DPAD_UP_DOWN, "Scroll");
			addInstruction(BUTTON_B, "Back");
			instructionsClose();
			ResetTimer2();
		}
	}
}

void resetVars()
{
	if (submenu != Closed)
		normalMenuActions();
	optionPress = false;
	rightPress = false;
	leftPress = false;
	fastRightPress = false;
	fastLeftPress = false;
	squarePress = false;
	infoText = NULL;
	instructionsSetupThisFrame = false;
	squareInstruction = false;
	lrInstruction = false;
}
void addKeyboardOption(char *option, int action, char *defaultText, int maxLength, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress)
			startKeyboard(action, defaultText, maxLength);
	}
}
int irand(int min, int max, int Add = 0)
{
	srand(GetTickCount() + Add);
	return min + (rand() % (int)(max - min + 1));
}

void DrawTextEliteMods(char* Text, int Font, float X, float Y, float Scale_X, float Scale_Y, int Red, int Green, int Blue, int Alpha, bool Shadow = false, bool Outline = false, bool Center = false)
{
	UI::SET_TEXT_FONT(Font);
	UI::SET_TEXT_SCALE(Scale_X, Scale_Y);
	UI::SET_TEXT_COLOUR(Red, Green, Blue, Alpha);
	if (Shadow)
		UI::SET_TEXT_DROP_SHADOW();
	UI::SET_TEXT_CENTRE(Center);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(Text);
	UI::_DRAW_TEXT(X, Y);
}

void SET_INTO_VEHICLE(int VehicleHandle)
{
	bool Max = VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(VehicleHandle), Existing = VEHICLE::GET_VEHICLE_NUMBER_OF_PASSENGERS(VehicleHandle);
	if (!Max == Existing)
	{
		for (int SeatIndex = -1; SeatIndex <= Max; SeatIndex++)
		{
			if (VEHICLE::IS_VEHICLE_SEAT_FREE(VehicleHandle, SeatIndex))
			{
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), VehicleHandle, SeatIndex);
				SeatIndex = Max + 1;
			}
		}
	}
}

void addVehicleOption(char *option, Hash vehicle, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress && STREAMING::IS_MODEL_VALID(vehicle))
		{
			vehicleToSpawnHash = vehicle;
			vehicleSpawnNeeded = true;
			deleteMyVeh = true;
			NotifyAboveMap3(option, "Spawned");
			STREAMING::REQUEST_MODEL(vehicle);
			STREAMING::REQUEST_NAMED_PTFX_ASSET("proj_xmas_firework");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("proj_xmas_firework");
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_firework_xmas_burst_rgw", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.0, false, false, false);
		}
	}
}

void addWeapTintOption(char *option, int TintIndex, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress)
		{
			Hash WeaponID;
			WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &WeaponID, true);
			WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), WeaponID, TintIndex);
		}
	}
}

void addParticleEffectOption(char *option, char* FX, char* Effect, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress)
		{
			Vector3 PedCoords;
			PedCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			STREAMING::_REQUEST_DLC_PTFX_ASSET(FX);
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL(FX);
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2(Effect, PedCoords.x, PedCoords.y, PedCoords.z, 0.0f, 0.0f, 0.0f, 1, 0, 0, 0);
		}
	}
}

void addParticleEffectAllOption(char *option, char* FX, char* Effect, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress)
		{
			int i = 0;
			int Handle;
			for (i = 0; i<16; i++)
			{
				if (i == PLAYER::PLAYER_ID()) continue;
				Handle = PLAYER::GET_PLAYER_PED(i);
				if (!ENTITY::DOES_ENTITY_EXIST(Handle)) continue;
				Vector3 PedCoords;
				PedCoords = ENTITY::GET_ENTITY_COORDS(i, true);
				STREAMING::_REQUEST_DLC_PTFX_ASSET(FX);
				GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL(FX);
				GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2(Effect, PedCoords.x, PedCoords.y, PedCoords.z, 0.0f, 0.0f, 0.0f, 1, 0, 0, 0);
			}
		}
	}
}

void addWeapAttachOption(char *option, int WeaponID, int Compent, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress)
		{
			WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::PLAYER_PED_ID(), WeaponID, Compent);
			WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(PLAYER::PLAYER_PED_ID(), WeaponID, Compent);
		}
	}
}

void addPresetVehicleColour(char *option, int Decimal, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress)
		{
			Vehicle VehicleHandle;
			VehicleHandle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::SET_VEHICLE_DIRT_LEVEL(VehicleHandle, 0.0f);
			VEHICLE::SET_VEHICLE_COLOURS(VehicleHandle, Decimal, Decimal);
			VEHICLE::SET_VEHICLE_EXTRA_COLOURS(VehicleHandle, Decimal, Decimal);
		}
	}
}

void addVehicleOptionBlista(char *option, Hash vehicle, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress && STREAMING::IS_MODEL_VALID(vehicle))
		{
			BlistaHash = vehicle;
			vehicleSpawnNeededBlista = true;
			STREAMING::REQUEST_MODEL(vehicle);
			STREAMING::REQUEST_NAMED_PTFX_ASSET("proj_xmas_firework");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("proj_xmas_firework");
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_firework_xmas_burst_rgw", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.0, false, false, false);
		}
	}
}

void addVehicleOptionCarbonRS(char *option, Hash vehicle, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress && STREAMING::IS_MODEL_VALID(vehicle))
		{
			CarbonRSHash = vehicle;
			vehicleSpawnNeededCarbonRS = true;
			NotifyAboveMap3(option, "Spawned");
			STREAMING::REQUEST_MODEL(vehicle);
			STREAMING::REQUEST_NAMED_PTFX_ASSET("proj_xmas_firework");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("proj_xmas_firework");
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_firework_xmas_burst_rgw", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.0, false, false, false);
		}
	}
}

void addOnlineVehicleOption(char *option, Hash vehicle, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress && STREAMING::IS_MODEL_VALID(vehicle))
		{
			vehicleToSpawnHash = vehicle;
			vehicleOnlineSpawnNeeded = true;
			NotifyAboveMap3(option, "Spawned");
			STREAMING::REQUEST_MODEL(vehicle);
			Ped ped = PLAYER::GET_PLAYER_PED(selectedPlayer);
			Vector3 Vehcoords = ENTITY::GET_ENTITY_COORDS(ped, false);
			STREAMING::REQUEST_NAMED_PTFX_ASSET("proj_xmas_firework");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("proj_xmas_firework");
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_firework_xmas_burst_rgw", PLAYER::GET_PLAYER_PED(selectedPlayer), Vehcoords.x, Vehcoords.y, Vehcoords.z, 0.0, 0.0, 0.0, 1.0, false, false, false);
		}
	}
}

void addOnlineVehicleOptionCrash(char *option, Hash vehicle, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress && STREAMING::IS_MODEL_VALID(vehicle))
		{
			vehicleToSpawnHash = vehicle;
			vehicleOnlineSpawnNeededCrash = true;
			NotifyAboveMap3(option, "Spawned");
			STREAMING::REQUEST_MODEL(vehicle);
		}
	}
}

void SpawnVehiclesAtAll(char *option, Hash vehicle, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress && STREAMING::IS_MODEL_VALID(vehicle))
		{
			vehicleToSpawnHash = vehicle;
			vehicleOnlineAllSpawnNeeded = true;
			NotifyAboveMap3(option, "Spawned");
			STREAMING::REQUEST_MODEL(vehicle);
		}
	}
}



void addModelOption(char *option, Hash model, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress && STREAMING::IS_MODEL_VALID(model))
		{
			ModelChangerToHash = model;
			ModelChangerNeeded = true;
			STREAMING::REQUEST_MODEL(model);
		}
	}
}

void ObjectSpawnerOption(char *option, Hash model, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress && STREAMING::IS_MODEL_VALID(model))
		{
			ObjectSpawnerHash = model;
			ObjectSpawnerNeeded = true;
			STREAMING::REQUEST_MODEL(model);
		}
	}
}



#pragma endregion
#pragma endregion
#pragma endregion

//APENAS LO GUA PONER EN IF COMO BOOL :V
int rideDeer_pedBone(int ped, int boneIndex)
{
	return PED::GET_PED_BONE_INDEX(ped, boneIndex);
}

double cosine(double x)
{
	double t = -x*x / 2;
	double sum = 1 + t;
	for (int i = 2; i<20; ++i)
	{
		t *= -x*x / (2 * i*(2 * i - 1));
		sum += t;
	}
	return sum;
}
double sine(double x)
{
	double term = x;
	double sum = x;
	for (int n = 1; n<10; ++n)
	{
		term *= x*x / (2 * n * (2 * n + 1));
		sum += n % 2 ? -term : term;
	}
	return sum;
}



void GetcoordsInfrontOfSelf(float *OutX, float *OutY, float *OutZ)
{
	Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
	float coords[3] = { pos.x, pos.y, pos.z };
	float Heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
	double test = Heading;
	*OutX = coords[0], *OutY = coords[1], *OutZ = coords[2];
	*OutX += (10 * sine(-1 * Heading));
	*OutZ += (10 * cosine(-1 * Heading));
}

float* GET_COORD_IN_FRONT_OF_GAMEPLAYCAM(float range, float* Outcoords)
{

	Vector3 Cam_Rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
	Vector3 Cam_Coord = CAM::GET_GAMEPLAY_CAM_COORD();
	float adj = range * cos(Cam_Rot.z);

	Outcoords[0] = (adj * sin(Cam_Rot.z * -1.0f)) + Cam_Coord.x;//x plane
	Outcoords[1] = (adj * cos(Cam_Rot.z * -1.0f)) + Cam_Coord.y;//y plane
	Outcoords[2] = (range * sin(Cam_Rot.x)) + Cam_Coord.z;//z plane
	return Outcoords;
}

void AddOptionPedSpawner(char *option, Hash model, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress && STREAMING::IS_MODEL_VALID(model))
		{
			PedSpawnerHash = model;
			PedSpawner = true;
			STREAMING::REQUEST_MODEL(model);
		}
	}
}

void AddOptionPigSpawner(char *option, Hash model, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress && STREAMING::IS_MODEL_VALID(model))
		{
			PigHash = model;
			PigSpawner = true;
			STREAMING::REQUEST_MODEL(model);
		}
	}
}

void sendText(int player, char *text)
{
	int NetHandleBuffer = 0xC0A80118;
	NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, NetHandleBuffer, 13);
	NETWORK::NETWORK_SEND_TEXT_MESSAGE(text, NetHandleBuffer);
}

void AddOptionBoarSpawner(char *option, Hash model, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress && STREAMING::IS_MODEL_VALID(model))
		{
			BoarHash = model;
			BoarSpawner = true;
			STREAMING::REQUEST_MODEL(model);
		}
	}
}

void AddOptionCowSpawner(char *option, Hash model, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress && STREAMING::IS_MODEL_VALID(model))
		{
			CowHash = model;
			CowSpawner = true;
			STREAMING::REQUEST_MODEL(model);
		}
	}
}

void AddOptionSharkSpawner(char *option, Hash model, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress && STREAMING::IS_MODEL_VALID(model))
		{
			SharkHash = model;
			SharkSpawner = true;
			STREAMING::REQUEST_MODEL(model);
		}
	}
}

void AddOptionDeerSpawner(char *option, Hash model, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress && STREAMING::IS_MODEL_VALID(model))
		{
			DeerHash = model;
			DeerSpawner = true;
			STREAMING::REQUEST_MODEL(model);
		}
	}
}

int SelectedClient;
bool AnimationsPlayerOnline = false;
char* AnimDict;
char* AnimnName;

void doAnimation(Ped ped, char *animSet, char *animName)
{
	animNeeded = true;
	pedToDoAnimOn = ped;
	animSetToDo = animSet;
	animNameToDo = animName;
	STREAMING::REQUEST_ANIM_DICT(animSetToDo);
}

bool iamrich = false;
bool Caosmode = false;
bool car11 = false;
int chop;
int modelHash;
int modelHash1;
int handle;
int modelHash2;
int vehToSpawnHash1;

bool doWheelbarrow = false;
bool doBumpercar = false;
bool doWheelchair = false;
bool doCouch = false;
bool doToilet = false;
bool doTrolley = false;
bool spawnTrolley()
{
	uint Handle = PLAYER::PLAYER_PED_ID();
	Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
	Vector3 null; null.x = 0, null.y = 0; null.z = 0;
	Vector3 a; a.x = 0, a.y = 0, a.z = 0;
	Vector3 b; b.x = 0, b.y = 2, b.z = 0;
	int hash = GAMEPLAY::GET_HASH_KEY("carbonrs");
	int hash2 = GAMEPLAY::GET_HASH_KEY("prop_rub_trolley01a");
	STREAMING::REQUEST_MODEL(hash);
	STREAMING::REQUEST_MODEL(hash2);
	if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
	{
		int Object = OBJECT::CREATE_OBJECT(hash2, null.x, null.y, null.z, 1, 1, 1);
		if (ENTITY::DOES_ENTITY_EXIST(Object))
		{
			int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
			{
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
				ENTITY::SET_ENTITY_VISIBLE(Vehicle, false);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
				drawNotification("Spawned: ~b~Trolley~HUD_COLOUR_WHITE~!");
				ENTITY::SET_ENTITY_VISIBLE(Handle, true);
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

void spawnToilet()
{
	uint Handle = PLAYER::PLAYER_PED_ID();
	Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(Handle, 1);
	Vector3 null; null.x = 0, null.y = 0; null.z = 0;
	Vector3 a; a.x = 0, a.y = -0.4f, a.z = 0.1f;
	Vector3 b; b.x = 0, b.y = 0, b.z = -90;
	int hash = GAMEPLAY::GET_HASH_KEY("hydra");
	int hash2 = GAMEPLAY::GET_HASH_KEY("p_seabed_whalebones");
	STREAMING::REQUEST_MODEL(hash);
	STREAMING::REQUEST_MODEL(hash2);
	if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
	{
		int Object = OBJECT::CREATE_OBJECT(hash2, null.x, null.y, null.z, 1, 1, 1);
		if (ENTITY::DOES_ENTITY_EXIST(Object))
		{
			int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
			{
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
				ENTITY::SET_ENTITY_VISIBLE(Vehicle, false);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
				drawNotification("Spawned: ~b~Toilet~HUD_COLOUR_WHITE~!");
				ENTITY::SET_ENTITY_VISIBLE(Handle, true);
			}
		}
	}
}

bool spawnCouch()
{
	uint Handle = PLAYER::PLAYER_PED_ID();
	Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(Handle, 1);
	Vector3 null; null.x = 0, null.y = 0; null.z = 0;
	Vector3 a; a.x = 0, a.y = -0.4f, a.z = 0;
	Vector3 b; b.x = 0, b.y = 0, b.z = 180.0f;
	int hash = GAMEPLAY::GET_HASH_KEY("dune");
	int hash2 = GAMEPLAY::GET_HASH_KEY("prop_t_sofa");
	STREAMING::REQUEST_MODEL(hash);
	STREAMING::REQUEST_MODEL(hash2);
	if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
	{
		int Object = OBJECT::CREATE_OBJECT(hash2, null.x, null.y, null.z, 1, 1, 1);
		if (ENTITY::DOES_ENTITY_EXIST(Object))
		{
			int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
			{
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
				ENTITY::SET_ENTITY_VISIBLE(Vehicle, false);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
				drawNotification("Spawned: ~b~Couch~HUD_COLOUR_WHITE~!");
				ENTITY::SET_ENTITY_VISIBLE(Handle, true);
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

bool spawnWheelchair()
{
	uint Handle = PLAYER::PLAYER_PED_ID();
	Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(Handle, 1);
	Vector3 null; null.x = 0, null.y = 0; null.z = 0;
	Vector3 a; a.x = -0.27, a.y = -0.24, a.z = 0.13f;
	Vector3 b; b.x = 0, b.y = 0, b.z = 180;
	int hash = GAMEPLAY::GET_HASH_KEY("caddy2");
	int hash2 = GAMEPLAY::GET_HASH_KEY("prop_wheelchair_01");
	STREAMING::REQUEST_MODEL(hash);
	STREAMING::REQUEST_MODEL(hash2);
	if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
	{
		int Object = OBJECT::CREATE_OBJECT(hash2, null.x, null.y, null.z, 1, 1, 1);
		if (ENTITY::DOES_ENTITY_EXIST(Object))
		{
			int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
			{
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
				ENTITY::SET_ENTITY_VISIBLE(Vehicle, false);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
				drawNotification("Spawned: ~b~Wheelchair~HUD_COLOUR_WHITE~!");
				ENTITY::SET_ENTITY_VISIBLE(Handle, true);
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

bool spawnBumpercar()
{
	uint Handle = PLAYER::PLAYER_PED_ID();
	Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(Handle, 1);
	Vector3 null; null.x = 0, null.y = 0; null.z = 0;
	Vector3 a; a.x = -0.34, a.y = 0.32, a.z = -0.25;
	Vector3 b; b.x = 0, b.y = 0, b.z = 180;
	int hash = GAMEPLAY::GET_HASH_KEY("blista");
	int hash2 = GAMEPLAY::GET_HASH_KEY("prop_bumper_car_01");
	STREAMING::REQUEST_MODEL(hash);
	STREAMING::REQUEST_MODEL(hash2);
	if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
	{
		int Object = OBJECT::CREATE_OBJECT(hash2, null.x, null.y, null.z, 1, 1, 1);
		if (ENTITY::DOES_ENTITY_EXIST(Object))
		{
			int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
			{
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
				ENTITY::SET_ENTITY_VISIBLE(Vehicle, false);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
				drawNotification("Spawned: ~b~Bumper Car~HUD_COLOUR_WHITE~!");
				ENTITY::SET_ENTITY_VISIBLE(Handle, true);
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

bool spawnWheelbarrow()
{
	uint Handle = PLAYER::PLAYER_PED_ID();
	Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(Handle, 1);
	Vector3 null; null.x = 0, null.y = 0; null.z = 0;
	Vector3 a; a.x = 0, a.y = -0.62, a.z = 0.12;
	Vector3 b; b.x = 0, b.y = 41.0, b.z = 90.0;
	int hash = GAMEPLAY::GET_HASH_KEY("bati");
	int hash2 = GAMEPLAY::GET_HASH_KEY("prop_wheelbarrow01a");
	STREAMING::REQUEST_MODEL(hash);
	STREAMING::REQUEST_MODEL(hash2);
	if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(hash2))
	{
		int Object = OBJECT::CREATE_OBJECT(hash2, null.x, null.y, null.z, 1, 1, 1);
		if (ENTITY::DOES_ENTITY_EXIST(Object))
		{
			int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
			{
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
				ENTITY::SET_ENTITY_VISIBLE(Vehicle, false);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, Vehicle, 0, a.x, a.y, a.z, b.x, b.y, b.z, 0, 1, 0, 0, 2, 1);
				drawNotification("Spawned: ~b~Wheelbarrow~HUD_COLOUR_WHITE~!");
				ENTITY::SET_ENTITY_VISIBLE(Handle, true);
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

void AddOnlinePedSpawner(char *option, Hash model, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress && STREAMING::IS_MODEL_VALID(model))
		{
			PedSpawnerHash = model;
			PedOnlineSpawner = true;
			STREAMING::REQUEST_MODEL(model);
		}
	}
}


bool Check_self_in_vehicle()
{
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) return true; else return false;
}

void set_gta2_cam_rot()
{
	Vector3 Rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
	if (!Check_self_in_vehicle()) {
		ENTITY::SET_ENTITY_ROTATION(PLAYER::PLAYER_PED_ID(), Rot.x, Rot.y, Rot.z, 2, 1);
	}
	else {
		ENTITY::SET_ENTITY_ROTATION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), Rot.x, Rot.y, Rot.z, 2, 1);
	}
}


Vector3 _GET_CAMERA_DIRECTION(float distance)
{
	Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
	float tX = rot.x * 0.0174532924;
	float tZ = rot.z * 0.0174532924;
	float num = abs(cos(tX));

	Vector3 dir = { ((-sin(tZ)) * (num + distance)), (cos(tZ) * (num + distance)), (sin(tX) * 8) };
	return dir;


}

void EnableVehicleMods()
{
	int vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
	VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
}

bool cstrcmp(const char* s1, const char* s2)
{
	while (*s1 && (*s1 == *s2))
		s1++, s2++;
	if (*(const unsigned char*)s1 - *(const unsigned char*)s2 == 0)
		return true;
	else
		return false;
}

void AddAnimationOnline(char* AnimDict, char* AnimnName)
{
	int POnline = PLAYER::GET_PLAYER_PED(selectedPlayer);
	Vector3 coords = ENTITY::GET_ENTITY_COORDS(POnline, 1);
	STREAMING::REQUEST_ANIM_DICT(AnimDict);
	if (STREAMING::HAS_ANIM_DICT_LOADED(AnimDict))
	{
		int AnimID = CLIENT::CLIENT_CREATE_ANIMATION(coords.x, coords.y, coords.z, 0, 0, 0, 2, 0, 1, 1.0f, 0.0f, 1.0f);
		CLIENT::ADD_CLIENT_ANIMATION(POnline, AnimID, AnimDict, AnimnName, 8.0f, -8.0f, 120, 0, 100, 0);
		CLIENT::CLIENT_START_ANIMATION(AnimID);
		AnimationsPlayerOnline = false;
	}
}
bool AnimationsPlayerOnline2 = false;
void AddAnimationOnline2(char* AnimDict, char* AnimnName)
{
	int i = 0;
	int Handle;
	Vector3 coords;
	for (i = 0; i<16; i++)
	{
		if (i == PLAYER::PLAYER_ID()) continue;
		Handle = PLAYER::GET_PLAYER_PED(i);
		coords = ENTITY::GET_ENTITY_COORDS(i, 1);
		if (!ENTITY::DOES_ENTITY_EXIST(Handle)) continue;

		int POnline = Handle;
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(POnline, 1);
		STREAMING::REQUEST_ANIM_DICT(AnimDict);
		if (STREAMING::HAS_ANIM_DICT_LOADED(AnimDict))
		{
			int AnimID = CLIENT::CLIENT_CREATE_ANIMATION(coords.x, coords.y, coords.z, 0, 0, 0, 2, 0, 1, 1.0f, 0.0f, 1.0f);
			CLIENT::ADD_CLIENT_ANIMATION(POnline, AnimID, AnimDict, AnimnName, 8.0f, -8.0f, 120, 0, 100, 0);
			CLIENT::CLIENT_START_ANIMATION(AnimID);
			AnimationsPlayerOnline2 = false;
		}
	}
}

void ResetAppearance()
{
	PED::CLEAR_ALL_PED_PROPS(PLAYER::PLAYER_PED_ID());
	PED::CLEAR_PED_DECORATIONS(PLAYER::PLAYER_PED_ID());
	PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0);
	PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 1, 0, 0, 0);
	PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 3, 0, 0, 0);
	PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 4, 0, 0, 0);
	PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 5, 0, 0, 0);
	PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 6, 0, 0, 0);
	PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 7, 0, 0, 0);
	PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 8, 0, 0, 0);
	PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 9, 0, 0, 0);
	PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 10, 0, 0, 0);
	PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 11, 0, 0, 0);
	PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 12, 0, 0, 0);
	PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 13, 0, 0, 0);
}

int fam;
int PaletteID;
void changeAppearance(char* family, int model, int texture)
{
	if (cstrcmp(family, "HATS") || cstrcmp(family, "GLASSES") || cstrcmp(family, "EARS"))
	{
		if (cstrcmp(family, "HATS"))
			fam = 0;
		else if (cstrcmp(family, "GLASSES"))
			fam = 1;
		else if (cstrcmp(family, "EARS"))
			fam = 2;
		PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), fam, model - 1, texture, PaletteID);
	}
	else
	{
		if (cstrcmp(family, "FACE"))
			fam = 0;
		else if (cstrcmp(family, "MASK"))
			fam = 1;
		else if (cstrcmp(family, "HAIR"))
			fam = 2;
		else if (cstrcmp(family, "TORSO"))
			fam = 3;
		else if (cstrcmp(family, "LEGS"))
			fam = 4;
		else if (cstrcmp(family, "HANDS"))
			fam = 5;
		else if (cstrcmp(family, "SHOES"))
			fam = 6;
		else if (cstrcmp(family, "SPECIAL1"))
			fam = 7;
		else if (cstrcmp(family, "SPECIAL2"))
			fam = 8;
		else if (cstrcmp(family, "SPECIAL3"))
			fam = 9;
		else if (cstrcmp(family, "TEXTURE"))
			fam = 10;
		else if (cstrcmp(family, "TORSO2"))
			fam = 11;
		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), fam, model, texture, PaletteID);
	}
}

void createEscortOption(char *option, Ped model, Vehicle Vehicle, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress && STREAMING::IS_MODEL_VALID(model) && STREAMING::IS_MODEL_VALID(Vehicle))
		{
			VehicleHashEscort = Vehicle;
			PedModelHashEscort = model;
			createEscort = true;
			STREAMING::REQUEST_MODEL(model);
			STREAMING::REQUEST_MODEL(Vehicle);
		}
	}
}

int PlaceObject(int Hash, float X, float Y, float Z, float Pitch, float Roll, float Yaw)
{
	STREAMING::REQUEST_MODEL(Hash);
	int object;
	object = OBJECT::CREATE_OBJECT(Hash, X, Y, Z, 1, 1, 0);
	ENTITY::SET_ENTITY_ROTATION(object, Pitch, Roll, Yaw, 2, 1);
	ENTITY::FREEZE_ENTITY_POSITION(object, 1);
	ENTITY::SET_ENTITY_LOD_DIST(object, 696969);
	STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Hash);
	ENTITY::SET_OBJECT_AS_NO_LONGER_NEEDED(&object);
	STREAMING::HAS_MODEL_LOADED(Hash);
	return object;
}



void maxVehicle(int VehicleHandle)
{
	int R = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255);
	int G = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255);
	int B = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255);
	VEHICLE::SET_VEHICLE_MOD_KIT(VehicleHandle, 0);
	VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(VehicleHandle, R, G, B);
	VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(VehicleHandle, R, G, B);
	VEHICLE::SET_VEHICLE_COLOURS(VehicleHandle, 131, 131);
	VEHICLE::SET_VEHICLE_EXTRA_COLOURS(VehicleHandle, 131, 131);
	VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(VehicleHandle, "AMEngine");
	VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(VehicleHandle, 5);
	VEHICLE::TOGGLE_VEHICLE_MOD(VehicleHandle, 18, 1);
	VEHICLE::TOGGLE_VEHICLE_MOD(VehicleHandle, 22, 1);
	VEHICLE::TOGGLE_VEHICLE_MOD(VehicleHandle, 20, 1);
	VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(VehicleHandle, 0, 0, 0);
	VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 16, 5, 0);
	VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 12, 2, 0);
	VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 11, 3, 0);
	VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 14, 14, 0);
	VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 15, 3, 0);
	VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 13, 2, 0);
	VEHICLE::SET_VEHICLE_WHEEL_TYPE(VehicleHandle, 6);
	VEHICLE::SET_VEHICLE_WINDOW_TINT(VehicleHandle, 5);
	VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 23, 19, 1);
	VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 0, 1, 0);
	VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 1, 1, 0);
	VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 2, 1, 0);
	VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 3, 1, 0);
	VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 4, 1, 0);
	VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 5, 1, 0);
	VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 6, 1, 0);
	VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 7, 1, 0);
	VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 8, 1, 0);
	VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 9, 1, 0);
	VEHICLE::SET_VEHICLE_MOD(VehicleHandle, 10, 1, 0);
}

void sendArmyAttackers()
{
	Ped targetPed = NULL;
	if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED(selectedPlayer)) && !ENTITY::IS_ENTITY_DEAD(PLAYER::GET_PLAYER_PED(selectedPlayer)))
		targetPed = PLAYER::GET_PLAYER_PED(selectedPlayer);
	else {
		NotifyAboveMap("Cannot Find Your Target.");
		return;
	}

	int vehmodel = GAMEPLAY::GET_HASH_KEY("RHINO");
	int firingPattern = GAMEPLAY::GET_HASH_KEY("FIRING_PATTERN_BURST_FIRE_DRIVEBY");
	if (STREAMING::IS_MODEL_IN_CDIMAGE(vehmodel) && STREAMING::IS_MODEL_A_VEHICLE(vehmodel))
	{
		STREAMING::REQUEST_MODEL(vehmodel);
		while (!STREAMING::HAS_MODEL_LOADED(vehmodel))
		{
			//make_periodic_feature_call();
			SYSTEM::WAIT(0);
		}

		Vector3 minDimens;
		Vector3 maxDimens;
		GAMEPLAY::GET_MODEL_DIMENSIONS2(vehmodel, &minDimens, &maxDimens);
		float spawnOffY = max(5.0f, 2.0f + 0.5f * (maxDimens.y - minDimens.y));

		FLOAT lookDir = ENTITY::GET_ENTITY_HEADING(targetPed);
		Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(targetPed, 0.0, spawnOffY + 20, 0.0);
		Vehicle veh = VEHICLE::CREATE_VEHICLE(vehmodel, coords.x, coords.y, coords.z, lookDir - 180, 1, 0);
		RequestControlOfEnt(veh);
		VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
		VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0.0f);
		VEHICLE::_SET_VEHICLE_PAINT_FADE(veh, 0.0f);
		maxVehicle(veh);
		SYSTEM::WAIT(0);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehmodel);
		Ped ped = PED::CREATE_PED(1, 0x39D6E83F, coords.x, coords.y, coords.z, 0.0f, 1, 1);
		AI::CLEAR_PED_TASKS(ped);
		int tick = 0;
		while (!ENTITY::DOES_ENTITY_EXIST(ped) && tick <= 12) SYSTEM::WAIT(0);
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {
			PED::SET_PED_RELATIONSHIP_GROUP_HASH(ped, GAMEPLAY::GET_HASH_KEY("ARMY"));
			PED::SET_PED_INTO_VEHICLE(ped, veh, -1);
			VEHICLE::SET_VEHICLE_DOORS_LOCKED_FOR_ALL_PLAYERS(veh, true);
			VEHICLE::SET_VEHICLE_NEEDS_TO_BE_HOTWIRED(veh, false);
			VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true);
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 15.0);

			PED::SET_PED_KEEP_TASK(ped, 1);
			Object task;
			PED::SET_PED_FIRING_PATTERN(ped, firingPattern);
			AI::OPEN_SEQUENCE_TASK(&task);
			AI::TASK_COMBAT_HATED_TARGETS_AROUND_PED(ped, 5000, 0);
			AI::TASK_VEHICLE_CHASE(ped, targetPed);
			PED::REGISTER_TARGET(ped, targetPed);
			AI::TASK_COMBAT_PED(ped, targetPed, 0, 16);
			AI::TASK_SHOOT_AT_ENTITY(ped, targetPed, 4000, firingPattern);
			AI::CLOSE_SEQUENCE_TASK(task);
			AI::TASK_PERFORM_SEQUENCE(ped, task);
		}
	}
}

Vector3 GetCoordsInfrontOfCam(float Distance)
{
	Vector3 GameplayCamRot = CAM::GET_GAMEPLAY_CAM_ROT(2);
	Vector3 GameplayCamCoord = CAM::GET_GAMEPLAY_CAM_COORD();

	float tan = (float)(cos(GameplayCamRot.x) * Distance);
	float xPlane = (float)((sin(GameplayCamRot.z * -1.0f) * tan) + GameplayCamCoord.x);
	float yPlane = (float)((cos(GameplayCamRot.z * -1.0f) * tan) + GameplayCamCoord.y);
	float zPlane = (float)((sin(GameplayCamRot.x) * Distance) + GameplayCamCoord.z);
	Vector3 Coords = { xPlane, yPlane, zPlane };
	return Coords;
}

void addAttachmentOption(char *option, Hash model, int BoneIndex, float x10, float y10, float z10, float x20, float y20, float z20, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress)
		{
			STREAMING::REQUEST_MODEL(model);
			Ped ped = PLAYER::GET_PLAYER_PED(selectedPlayer);
			Vector3 Attachcoords;
			Attachcoords = ENTITY::GET_ENTITY_COORDS(ped, 1);
			int Bone = PED::GET_PED_BONE_INDEX(ped, BoneIndex);
			if (STREAMING::HAS_MODEL_LOADED(model)) {
				int attachobj = OBJECT::CREATE_OBJECT(model, Attachcoords.x, Attachcoords.y, Attachcoords.z, 0, 0, 0);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(attachobj, ped, Bone, x10, y10, z10, x20, y20, z20, 0, 0, 0, 0, 0, 0);
			}
		}
	}
}

void addTeleportOption(char *option, float x, float y, float z, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress)
		{
			Ped ped = PLAYER::PLAYER_PED_ID();
			Entity entityToTele = ped;
			if (PED::IS_PED_SITTING_IN_ANY_VEHICLE(ped))
				entityToTele = PED::GET_VEHICLE_PED_IS_USING(ped);
			Vector3 PedCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			ENTITY::SET_ENTITY_COORDS(entityToTele, x, y, z, false, false, false, true);
		}
	}
}

void GiveWeaponPed(int Ped, int WeaponHash)
{
	WEAPON::GIVE_WEAPON_TO_PED(Ped, WeaponHash, 9999, 1, 1);

}


void DeletePed(int pedID)
{
	if (!NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(pedID))
		while (!NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(pedID));

	ENTITY::SET_ENTITY_AS_MISSION_ENTITY(pedID, 1, 1);
	PED::DELETE_PED(&pedID);
}

void makePedHostile(uint Ped, int Target, bool choporswat = false, bool isClone = false)
{
	if (choporswat)
	{
		int TargetHandle = PLAYER::GET_PLAYER_PED(Target);
		AI::TASK_COMBAT_PED(Ped, TargetHandle, 0, 16);
		PED::SET_PED_CAN_SWITCH_WEAPON(Ped, true);
	}
	else
	{
		if (isClone)
		{
			int Hash = ENTITY::GET_ENTITY_MODEL(Ped);
			DeletePed(Ped);

			STREAMING::REQUEST_MODEL(Hash);
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(Target), 1);
			if (STREAMING::HAS_MODEL_LOADED(Hash))
			{
				int newPed = PED::CREATE_PED(21, Hash, coords.x, coords.y, coords.z, 0, 1, 0);
				if (ENTITY::GET_ENTITY_HEALTH(newPed) == ENTITY::GET_ENTITY_MAX_HEALTH(newPed))
				{
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Hash);
					RequestNetworkControl(newPed);
					int TargetHandle = PLAYER::GET_PLAYER_PED(Target);
					AI::TASK_COMBAT_PED(newPed, TargetHandle, 0, 16);
					PED::SET_PED_CAN_SWITCH_WEAPON(Ped, true);
				}
			}
		}
		else
		{
			int TargetHandle = PLAYER::GET_PLAYER_PED(Target);
			AI::TASK_COMBAT_PED(Ped, TargetHandle, 0, 16);
		}
	}
}
int veh;
bool SpawningVehicle;
int CREATE_VEHICLE(char* hash)
{
	if (SpawningVehicle)
	{

		int model = GAMEPLAY::GET_HASH_KEY(hash);
		if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
		{
			STREAMING::REQUEST_MODEL(model);
			if (STREAMING::HAS_MODEL_LOADED(model))
			{
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
				veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0.0, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
				ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);

				ENTITY::SET_ENTITY_CAN_BE_DAMAGED(veh, false);

				SpawningVehicle = false;
			}
		}
	}
	return veh;
}

bool doStripperVeh = false;
bool spawnStripperVeh()
{
	if (doStripperVeh)
	{
		STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("csb_stripper_02"));
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 1);
		if (STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("csb_stripper_02")))
		{
			int Ped = PED::CREATE_PED(21, GAMEPLAY::GET_HASH_KEY("csb_stripper_02"), coords.x, coords.y, coords.z, 0, 1, 0);
			int Veh = CREATE_VEHICLE("adder");
			if (ENTITY::DOES_ENTITY_EXIST(Ped))
			{
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(GAMEPLAY::GET_HASH_KEY("csb_stripper_02"));
				char buf[100];
				RequestNetworkControl(Ped);
				makePedHostile(Ped, selectedPlayer, true);
				PED::SET_PED_INTO_VEHICLE(Ped, Veh, -1);
				VEHICLE::SET_VEHICLE_DOORS_LOCKED(Veh, true);
				return true;
			}
			return false;
		}
		return false;
	}
}

bool doClown = false;
bool spawnClown()
{
	if (doClown)
	{
		STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("s_m_y_clown_01"));
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 1);
		if (STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("s_m_y_clown_01")))
		{
			int Ped = PED::CREATE_PED(21, GAMEPLAY::GET_HASH_KEY("s_m_y_clown_01"), coords.x, coords.y, coords.z, 0, 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(Ped))
			{
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(GAMEPLAY::GET_HASH_KEY("s_m_y_clown_01"));
				char buf[100];
				RequestNetworkControl(Ped);
				GiveWeaponPed(Ped, 0x958A4A8F);
				makePedHostile(Ped, selectedPlayer, true);
				return true;
			}
			return false;
		}
		return false;
	}
}
bool doChop = false;
bool spawnChop()
{
	if (doChop)
	{
		int ChopHash = GAMEPLAY::GET_HASH_KEY("a_c_chop");
		STREAMING::REQUEST_MODEL(ChopHash);
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 0);
		if (STREAMING::HAS_MODEL_LOADED(ChopHash))
		{
			int Ped = PED::CREATE_PED(21, ChopHash, coords.x, coords.y, coords.z, 0, 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(Ped))
			{
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(ChopHash);
				char buf[100];
				RequestNetworkControl(Ped);
				//GiveWeaponPed(Ped, 0x958A4A8F);
				makePedHostile(Ped, selectedPlayer, true);
				return true;
			}
			return false;
		}
		return false;
	}
}
bool doStripper = false;//csb_stripper_02
bool spawnStripper()
{
	if (doStripper)
	{
		STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("csb_stripper_02"));
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 1);
		if (STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("csb_stripper_02")))
		{
			int Ped = PED::CREATE_PED(21, GAMEPLAY::GET_HASH_KEY("csb_stripper_02"), coords.x, coords.y, coords.z, 0, 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(Ped))
			{
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(GAMEPLAY::GET_HASH_KEY("csb_stripper_02"));
				char buf[100];
				RequestNetworkControl(Ped);
				GiveWeaponPed(Ped, 0x958A4A8F);
				makePedHostile(Ped, selectedPlayer, true);
				return true;
			}
			return false;
		}
		return false;
	}
}
bool doLion = false;//a_c_mtlion
bool spawnLion()
{
	if (doLion)
	{
		STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("a_c_mtlion"));
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 1);
		if (STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("a_c_mtlion")))
		{
			int Ped = PED::CREATE_PED(21, GAMEPLAY::GET_HASH_KEY("a_c_mtlion"), coords.x, coords.y, coords.z, 0, 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(Ped))
			{
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(GAMEPLAY::GET_HASH_KEY("a_c_mtlion"));
				char buf[100];
				RequestNetworkControl(Ped);
				//GiveWeaponPed(Ped, 0x958A4A8F);
				makePedHostile(Ped, selectedPlayer, true);
				return true;
			}
			return false;
		}
		return false;
	}
}
bool doSwatRPG = false;
bool spawnSwatRPG()//s_m_y_swat_01//0xB1CA77B1
{
	if (doSwatRPG)
	{

		STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("s_m_y_swat_01"));
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 1);
		if (STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("s_m_y_swat_01")))
		{
			int Ped = PED::CREATE_PED(21, GAMEPLAY::GET_HASH_KEY("s_m_y_swat_01"), coords.x, coords.y, coords.z, 0, 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(Ped))
			{
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(GAMEPLAY::GET_HASH_KEY("s_m_y_swat_01"));
				char buf[100];
				RequestNetworkControl(Ped);
				GiveWeaponPed(Ped, 0xB1CA77B1);
				makePedHostile(Ped, selectedPlayer, true);
				return true;
			}
			return false;
		}
		return false;
	}
}
bool doSwatTazer = false;
bool spawnSwatTazer()//0x47757124
{
	if (doSwatTazer)
	{

		STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("s_m_y_swat_01"));
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 1);
		if (STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("s_m_y_swat_01")))
		{
			int Ped = PED::CREATE_PED(21, GAMEPLAY::GET_HASH_KEY("s_m_y_swat_01"), coords.x, coords.y, coords.z, 0, 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(Ped))
			{
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(GAMEPLAY::GET_HASH_KEY("s_m_y_swat_01"));
				char buf[100];
				RequestNetworkControl(Ped);
				GiveWeaponPed(Ped, 0x47757124);
				makePedHostile(Ped, selectedPlayer, true);
				return true;
			}
			return false;
		}
		return false;
	}
}
bool doCopTazer = false;
bool spawnCopTazer()//s_m_y_cop_01
{
	if (doCopTazer)
	{

		STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("s_m_y_cop_01"));
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 1);
		if (STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("s_m_y_cop_01")))
		{
			int Ped = PED::CREATE_PED(21, GAMEPLAY::GET_HASH_KEY("s_m_y_cop_01"), coords.x, coords.y, coords.z, 0, 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(Ped))
			{
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(GAMEPLAY::GET_HASH_KEY("s_m_y_cop_01"));
				char buf[100];
				RequestNetworkControl(Ped);
				GiveWeaponPed(Ped, 0x47757124);
				makePedHostile(Ped, selectedPlayer, true);
				return true;
			}
			return false;
		}
		return false;
	}
}
bool doCopMG = false;
bool spawnCopMG()//0x7FD62962
{
	if (doCopMG)
	{
		STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("s_m_y_cop_01"));
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 1);
		if (STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("s_m_y_cop_01")))
		{
			int Ped = PED::CREATE_PED(21, GAMEPLAY::GET_HASH_KEY("s_m_y_cop_01"), coords.x, coords.y, coords.z, 0, 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(Ped))
			{
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(GAMEPLAY::GET_HASH_KEY("s_m_y_cop_01"));
				char buf[100];
				RequestNetworkControl(Ped);
				GiveWeaponPed(Ped, 0x7FD62962);
				makePedHostile(Ped, selectedPlayer, true);
				return true;
			}
			return false;
		}
		return false;
	}
}

int pedattackers;
int pedattackers1;
int pedattackers2;
int pedattackers3;
int vehattackers;
bool vehspawncheck = false;
bool pedspawncheck;

float XCoord = 0;
float YCoord = 0;
float ZCoord = 0;
float RollCoord = 0;
float PitchCoord = 0;
float YawCoord = 0;
void attacher()
{
	int Vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
	ENTITY::ATTACH_ENTITY_TO_ENTITY(SpawnedObject[SelectedObject], Vehicle, 0, XCoord, YCoord, ZCoord, RollCoord, PitchCoord, YawCoord, 0, 1, 0, 0, 2, 1);
}
void attacher2()
{
	ENTITY::ATTACH_ENTITY_TO_ENTITY(SpawnedObject[SelectedObject], PLAYER::PLAYER_PED_ID(), 0, XCoord, YCoord, ZCoord, RollCoord, PitchCoord, YawCoord, 0, 1, 0, 0, 2, 1);
}
void attacher3()
{
	ENTITY::ATTACH_ENTITY_TO_ENTITY(SpawnedObject[SelectedObject], PLAYER::PLAYER_PED_ID(), 31086, XCoord, YCoord, ZCoord, RollCoord, PitchCoord, YawCoord, 0, 1, 0, 0, 2, 1);
}
void attacher4()
{
	ENTITY::ATTACH_ENTITY_TO_ENTITY(SpawnedObject[SelectedObject], PLAYER::PLAYER_PED_ID(), 28422, XCoord, YCoord, ZCoord, RollCoord, PitchCoord, YawCoord, 0, 1, 0, 0, 2, 1);
}
void attacher5()
{
	ENTITY::ATTACH_ENTITY_TO_ENTITY(SpawnedObject[SelectedObject], PLAYER::PLAYER_PED_ID(), 60309, XCoord, YCoord, ZCoord, RollCoord, PitchCoord, YawCoord, 0, 1, 0, 0, 2, 1);
}
void addX(char *option, float *var, float min, float max, bool holdPress, char *info = NULL)
{
	char buf[300];
	snprintf(buf, sizeof(buf), "%s: [%f]", option, *var);
	addOption(buf, info);
	if (currentOption == optionCount)
	{
		lrInstruction = true;
		XCoord = *var;
		if (holdPress)
		{
			if (fastRightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + 0.1f;
			}
			else if (fastLeftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 0.1f;
			}
		}
		else
		{
			if (rightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + 0.1f;
			}
			else if (leftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 0.1f;
			}
		}
	}
}
void addY(char *option, float *var, float min, float max, bool holdPress, char *info = NULL)
{
	char buf[300];
	snprintf(buf, sizeof(buf), "%s: [%f]", option, *var);
	addOption(buf, info);
	if (currentOption == optionCount)
	{
		lrInstruction = true;
		YCoord = *var;
		if (holdPress)
		{
			if (fastRightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + 0.1f;
			}
			else if (fastLeftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 0.1f;
			}
		}
		else
		{
			if (rightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + 0.1f;
			}
			else if (leftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 0.1f;
			}
		}
	}
}
void addZ(char *option, float *var, float min, float max, bool holdPress, char *info = NULL)
{
	char buf[300];
	snprintf(buf, sizeof(buf), "%s: [%f]", option, *var);
	addOption(buf, info);
	if (currentOption == optionCount)
	{
		lrInstruction = true;
		ZCoord = *var;
		if (holdPress)
		{
			if (fastRightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + 0.1f;
			}
			else if (fastLeftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 0.1f;
			}
		}
		else
		{
			if (rightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + 0.1f;
			}
			else if (leftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 0.1f;
			}
		}
	}
}
void addRoll(char *option, float *var, float min, float max, bool holdPress, char *info = NULL)
{
	char buf[300];
	snprintf(buf, sizeof(buf), "%s: [%f]", option, *var);
	addOption(buf, info);
	if (currentOption == optionCount)
	{
		lrInstruction = true;
		RollCoord = *var;
		if (holdPress)
		{
			if (fastRightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + 1.0f;
			}
			else if (fastLeftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 1.0f;
			}
		}
		else
		{
			if (rightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + 1.0f;
			}
			else if (leftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 1.0f;
			}
		}
	}
}
void addPitch(char *option, float *var, float min, float max, bool holdPress, char *info = NULL)
{
	char buf[300];
	snprintf(buf, sizeof(buf), "%s: [%f]", option, *var);
	addOption(buf, info);
	if (currentOption == optionCount)
	{
		lrInstruction = true;
		PitchCoord = *var;
		if (holdPress)
		{
			if (fastRightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + 1.0f;
			}
			else if (fastLeftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 1.0f;
			}
		}
		else
		{
			if (rightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + 1.0f;
			}
			else if (leftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 1.0f;
			}
		}
	}
}
void addYaw(char *option, float *var, float min, float max, bool holdPress, char *info = NULL)
{
	char buf[300];
	snprintf(buf, sizeof(buf), "%s: [%f]", option, *var);
	addOption(buf, info);
	if (currentOption == optionCount)
	{
		lrInstruction = true;
		YawCoord = *var;
		if (holdPress)
		{
			if (fastRightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + 1.0f;
			}
			else if (fastLeftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 1.0f;
			}
		}
		else
		{
			if (rightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + 1.0f;
			}
			else if (leftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 1.0f;
			}
		}
	}
}

bool hostilesavage = false;
bool HostileSavage()
{
	if (hostilesavage)
	{
		if (vehspawncheck)
		{
			int model = GAMEPLAY::GET_HASH_KEY("savage");
			float speed = ENTITY::GET_ENTITY_SPEED(PLAYER::PLAYER_PED_ID());
			STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("savage"));
			if (STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("savage")))
			{
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 6.0, 0.0, 0.0);
				vehattackers = VEHICLE::CREATE_VEHICLE(GAMEPLAY::GET_HASH_KEY("savage"), coords.x, coords.y + 20, coords.z + 50, 0, 1, 0);
				if (ENTITY::DOES_ENTITY_EXIST(vehattackers))
				{
					vehspawncheck = false;
					pedattackers = true;
					if (pedattackers)
					{
						STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("s_m_y_blackops_01"));
						if (STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("s_m_y_blackops_01")))
						{
							Vector3 coords_ = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 6.0, 0.0, 0.0);
							pedattackers = PED::CREATE_PED(21, GAMEPLAY::GET_HASH_KEY("s_m_y_blackops_01"), coords_.x, coords_.y, coords_.z, 1, 1, 0);
							if (ENTITY::DOES_ENTITY_EXIST(pedattackers))
							{
								PED::SET_PED_INTO_VEHICLE(pedattackers, vehattackers, -1);
								VEHICLE::SET_VEHICLE_DOORS_LOCKED(vehattackers, true);
								VEHICLE::SET_VEHICLE_ENGINE_ON(vehattackers, true, true);
								VEHICLE::SET_HELI_BLADES_FULL_SPEED(vehattackers);
								AI::TASK_VEHICLE_SHOOT_AT_PED(0, 0, 0);
								AI::TASK_LEAVE_ANY_VEHICLE(pedattackers, false, false);
								//GiveWeaponPed(pedattackers, 0x2BE6766B);
								int TargetHandle = PLAYER::GET_PLAYER_PED(selectedPlayer);
								AI::TASK_COMBAT_PED(pedattackers, TargetHandle, 0, 16);
								AI::TASK_VEHICLE_CHASE(pedattackers, PLAYER::GET_PLAYER_PED(selectedPlayer));
								PED::SET_PED_CAN_SWITCH_WEAPON(pedattackers, true);
								pedattackers = false;
								return true;
							}
							return false;
						}
						return false;
					}
					return false;
				}
				return false;
			}
			return false;
		}
	}
}
bool hostilehydra = false;
bool HostileHydra()
{
	if (hostilehydra)
	{
		if (vehspawncheck)
		{
			int model = GAMEPLAY::GET_HASH_KEY("hydra");
			float speed = ENTITY::GET_ENTITY_SPEED(PLAYER::PLAYER_PED_ID());
			STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("hydra"));
			if (STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("hydra")))
			{
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 6.0, 0.0, 0.0);
				vehattackers = VEHICLE::CREATE_VEHICLE(GAMEPLAY::GET_HASH_KEY("hydra"), coords.x, coords.y + 20, coords.z + 50, 0, 1, 0);
				if (ENTITY::DOES_ENTITY_EXIST(vehattackers))
				{
					vehspawncheck = false;
					pedattackers = true;
					if (pedattackers)
					{
						STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("s_m_y_blackops_01"));
						if (STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("s_m_y_blackops_01")))
						{
							Vector3 coords_ = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 6.0, 0.0, 0.0);
							pedattackers = PED::CREATE_PED(21, GAMEPLAY::GET_HASH_KEY("s_m_y_blackops_01"), coords_.x, coords_.y, coords_.z, 1, 1, 0);
							if (ENTITY::DOES_ENTITY_EXIST(pedattackers))
							{
								PED::SET_PED_INTO_VEHICLE(pedattackers, vehattackers, -1);
								VEHICLE::SET_VEHICLE_DOORS_LOCKED(vehattackers, true);
								VEHICLE::SET_VEHICLE_ENGINE_ON(vehattackers, true, true);
								VEHICLE::SET_HELI_BLADES_FULL_SPEED(vehattackers);
								AI::TASK_VEHICLE_SHOOT_AT_PED(0, 0, 0);
								AI::TASK_LEAVE_ANY_VEHICLE(pedattackers, false, false);
								//GiveWeaponPed(pedattackers, 0x2BE6766B);
								int TargetHandle = PLAYER::GET_PLAYER_PED(selectedPlayer);
								AI::TASK_COMBAT_PED(pedattackers, TargetHandle, 0, 16);
								AI::TASK_VEHICLE_CHASE(pedattackers, PLAYER::GET_PLAYER_PED(selectedPlayer));
								PED::SET_PED_CAN_SWITCH_WEAPON(pedattackers, true);
								pedattackers = false;
								return true;
							}
							return false;
						}
						return false;
					}
					return false;
				}
				return false;
			}
			return false;
		}
	}
}
bool hostileinsurgent = false;
bool HostileInsurgent()
{
	if (hostileinsurgent)
	{
		if (vehspawncheck)
		{
			int movdel = GAMEPLAY::GET_HASH_KEY("insurgent2");
			float speed = ENTITY::GET_ENTITY_SPEED(PLAYER::PLAYER_PED_ID());
			STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("insurgent2"));
			if (STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("insurgent2")))
			{
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 6.0, 0.0, 0.0);
				vehattackers = VEHICLE::CREATE_VEHICLE(GAMEPLAY::GET_HASH_KEY("insurgent2"), coords.x, coords.y + 10, coords.z, 0, 1, 0);
				if (ENTITY::DOES_ENTITY_EXIST(vehattackers))
				{
					vehspawncheck = false;
					pedattackers = true;
					if (pedattackers)
					{
						STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("s_m_y_blackops_01"));
						if (STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("s_m_y_blackops_01")))
						{
							Vector3 coords_ = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 6.0, 0.0, 0.0);
							pedattackers = PED::CREATE_PED(21, GAMEPLAY::GET_HASH_KEY("s_m_y_blackops_01"), coords_.x, coords_.y, coords_.z, 1, 1, 0);
							//pedattackers1 = PED::CREATE_PED(21, GAMEPLAY::GET_HASH_KEY("s_m_y_blackops_01"), coords_.x, coords_.y, coords_.z, 1, 1, 0);
							//pedattackers2 = PED::CREATE_PED(21, GAMEPLAY::GET_HASH_KEY("s_m_y_blackops_01"), coords_.x, coords_.y, coords_.z, 1, 1, 0);
							if (ENTITY::DOES_ENTITY_EXIST(pedattackers))
							{
								PED::SET_PED_INTO_VEHICLE(pedattackers, vehattackers, -1);
								//	PED::SET_PED_INTO_VEHICLE(pedattackers1, vehattackers, -2);
								//PED::SET_PED_INTO_VEHICLE(pedattackers2, vehattackers, -3);
								VEHICLE::SET_VEHICLE_DOORS_LOCKED(vehattackers, true);
								VEHICLE::SET_VEHICLE_ENGINE_ON(vehattackers, true, true);
								VEHICLE::SET_HELI_BLADES_FULL_SPEED(vehattackers);
								AI::TASK_VEHICLE_SHOOT_AT_PED(0, 0, 0);
								AI::TASK_LEAVE_ANY_VEHICLE(pedattackers, false, false);
								//AI::TASK_LEAVE_ANY_VEHICLE(pedattackers1, false, false);
								//AI::TASK_LEAVE_ANY_VEHICLE(pedattackers2, false, false);
								//GiveWeaponPed(pedattackers, 0x2BE6766B);
								int TargetHandle = PLAYER::GET_PLAYER_PED(selectedPlayer);
								AI::TASK_COMBAT_PED(pedattackers, TargetHandle, 0, 16);
								//AI::TASK_COMBAT_PED(pedattackers1, TargetHandle, 0, 16);
								//AI::TASK_COMBAT_PED(pedattackers2, TargetHandle, 0, 16);
								AI::TASK_VEHICLE_CHASE(pedattackers, PLAYER::GET_PLAYER_PED(selectedPlayer));
								PED::SET_PED_CAN_SWITCH_WEAPON(pedattackers, true);
								//PED::SET_PED_CAN_SWITCH_WEAPON(pedattackers1, true);
								//PED::SET_PED_CAN_SWITCH_WEAPON(pedattackers2, true);
								pedattackers = false;
								return true;
							}
							return false;
						}
						return false;
					}
					return false;
				}
				return false;
			}
			return false;
		}
	}
}
bool hostiletank = false;
bool HostileTank()
{
	if (hostiletank)
	{
		if (vehspawncheck)
		{
			int movdel = GAMEPLAY::GET_HASH_KEY("rhino");
			float speed = ENTITY::GET_ENTITY_SPEED(PLAYER::PLAYER_PED_ID());
			STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("rhino"));
			if (STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("rhino")))
			{
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 6.0, 0.0, 0.0);
				vehattackers = VEHICLE::CREATE_VEHICLE(GAMEPLAY::GET_HASH_KEY("rhino"), coords.x, coords.y + 10, coords.z, 0, 1, 0);
				if (ENTITY::DOES_ENTITY_EXIST(vehattackers))
				{
					vehspawncheck = false;
					pedattackers = true;
					if (pedattackers)
					{
						STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("s_m_y_blackops_01"));
						if (STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("s_m_y_blackops_01")))
						{
							Vector3 coords_ = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 6.0, 0.0, 0.0);
							pedattackers = PED::CREATE_PED(21, GAMEPLAY::GET_HASH_KEY("s_m_y_blackops_01"), coords_.x, coords_.y, coords_.z, 1, 1, 0);
							//pedattackers1 = PED::CREATE_PED(21, GAMEPLAY::GET_HASH_KEY("s_m_y_blackops_01"), coords_.x, coords_.y, coords_.z, 1, 1, 0);
							//pedattackers2 = PED::CREATE_PED(21, GAMEPLAY::GET_HASH_KEY("s_m_y_blackops_01"), coords_.x, coords_.y, coords_.z, 1, 1, 0);
							if (ENTITY::DOES_ENTITY_EXIST(pedattackers))
							{
								PED::SET_PED_INTO_VEHICLE(pedattackers, vehattackers, -1);
								//	PED::SET_PED_INTO_VEHICLE(pedattackers1, vehattackers, -2);
								//PED::SET_PED_INTO_VEHICLE(pedattackers2, vehattackers, -3);
								VEHICLE::SET_VEHICLE_DOORS_LOCKED(vehattackers, true);
								VEHICLE::SET_VEHICLE_ENGINE_ON(vehattackers, true, true);
								VEHICLE::SET_HELI_BLADES_FULL_SPEED(vehattackers);
								AI::TASK_VEHICLE_SHOOT_AT_PED(0, 0, 0);
								AI::TASK_LEAVE_ANY_VEHICLE(pedattackers, true, false);
								//AI::TASK_LEAVE_ANY_VEHICLE(pedattackers1, false, false);
								//AI::TASK_LEAVE_ANY_VEHICLE(pedattackers2, false, false);
								//GiveWeaponPed(pedattackers, 0x2BE6766B);
								int TargetHandle = PLAYER::GET_PLAYER_PED(selectedPlayer);
								AI::TASK_COMBAT_PED(pedattackers, TargetHandle, 0, 16);
								//AI::TASK_COMBAT_PED(pedattackers1, TargetHandle, 0, 16);
								//AI::TASK_COMBAT_PED(pedattackers2, TargetHandle, 0, 16);
								AI::TASK_VEHICLE_CHASE(pedattackers, PLAYER::GET_PLAYER_PED(selectedPlayer));
								PED::SET_PED_CAN_SWITCH_WEAPON(pedattackers, true);
								//PED::SET_PED_CAN_SWITCH_WEAPON(pedattackers1, true);
								//PED::SET_PED_CAN_SWITCH_WEAPON(pedattackers2, true);
								pedattackers = false;
								return true;
							}
							return false;
						}
						return false;
					}
					return false;
				}
				return false;
			}
			return false;
		}
	}
}

Vector3 get_coords_from_cam(float distance)
{
	Vector3 Rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
	static Vector3 Coord = CAM::GET_GAMEPLAY_CAM_COORD();

	Rot.y = distance * cos(Rot.x);
	Coord.x = Coord.x + Rot.y * sin(Rot.z * -1.0f);
	Coord.y = Coord.y + Rot.y * cos(Rot.z * -1.0f);
	Coord.z = Coord.z + distance * sin(Rot.x);
	return Coord;
}
void addCharSwap(char *option, char **From, int*var, int min, int max, bool holdPress = false)
{
	char buf[50];
	snprintf(buf, sizeof(buf), "%s: -~r~%s~w~+ ", option, From[*var]);
	addOption(buf);
	if (currentOption == optionCount)
	{
		lrInstruction = true;
		if (holdPress)
		{
			if (fastRightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + 1;
			}
			else if (fastLeftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 0.01f;
			}
		}
		else
		{
			if (rightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + 1;
			}
			else if (leftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 1;
			}
		}
	}
}

bool aimbot = false;
void Aimbot()
{
	int player = PLAYER::PLAYER_ID();
	int playerPed = PLAYER::PLAYER_PED_ID();

	for (int i = 0; i < 16; i++)
	{
		if (i != player)
		{
			if (PLAYER::IS_PLAYER_FREE_AIMING(player))
			{
				Ped targetPed = PLAYER::GET_PLAYER_PED(i);
				Vector3 targetPos = ENTITY::GET_ENTITY_COORDS(targetPed, 1);
				BOOL exists = ENTITY::DOES_ENTITY_EXIST(targetPed);
				BOOL dead = PLAYER::IS_PLAYER_DEAD(targetPed);

				if (exists && !dead)
				{
					float screenX, screenY;
					BOOL onScreen = GRAPHICS::_WORLD3D_TO_SCREEN2D2(targetPos.x, targetPos.y, targetPos.z, &screenX, &screenY);
					if (ENTITY::IS_ENTITY_VISIBLE(targetPed) && onScreen)
					{
						if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(playerPed, targetPed, 17))
						{
							Vector3 targetCoords = PED::GET_PED_BONE_COORDS(targetPed, 31086, 0, 0, 0);
							PED::SET_PED_SHOOTS_AT_COORD(playerPed, targetCoords.x, targetCoords.y, targetCoords.z, 1);

						}
					}
				}
			}
		}
	}
}
float pcoords[3];
int CREATE_VEHICLE_NORMAL4(Hash VehicleName, float Location, float Location2, float Location3, float haiding, int n, int y)
{
	Hash VehicleHash = (VehicleName);
	Vehicle Handle = 0;
	if (!STREAMING::HAS_MODEL_LOADED(VehicleHash))
		STREAMING::REQUEST_MODEL(VehicleHash);
	if (STREAMING::HAS_MODEL_LOADED(VehicleHash))
	{
		Handle = VEHICLE::CREATE_VEHICLE(VehicleHash, Location, Location2, Location3, haiding, n, y);//Doesn't normal use this? idk, compare this with above
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(VehicleHash);
	}
	return Handle;
}

void creatorRocketRTLoop() {

	float dim_min[3],
		dim_max[3],
		targetpos1[3],
		launchpos1[3],
		rocket_speed;
	Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
	Vector3  dir = _GET_CAMERA_DIRECTION(5.0);
	Vector3 Position = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
	int PedID;
	PedID = PLAYER::PLAYER_PED_ID();
	int hand = PED::GET_PED_BONE_INDEX(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_PED_ID()), 28422);
	int myhandle = PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_PED_ID());
	if (CONTROLS::IS_CONTROL_PRESSED(2, Button_R2) && PED::IS_PED_ON_FOOT(PedID) && PED::IS_PED_SHOOTING(myhandle))
	{
		int vehicle = PedID,
			Model = ENTITY::GET_ENTITY_MODEL(vehicle);
		GAMEPLAY::GET_MODEL_DIMENSIONS(Model, dim_min, dim_max);

		if (CONTROLS::IS_CONTROL_PRESSED(2, 198))
		{
			ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS2(vehicle, dim_min[0] + 1, dim_min[1] + 0.5f, 0.0f, launchpos1);
			ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS2(vehicle, dim_min[0] + 1, dim_min[1] + 300.5f, 0.5f, targetpos1);
		}
		else
		{
			ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS2(vehicle, dim_min[0] + 1, dim_min[1] + 0.5f, 0.0f, launchpos1);
			ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS2(vehicle, dim_min[0] + 1, dim_min[1] + 300.5f, 0.5f, targetpos1);


			targetpos1[2]--;
		}
		rocket_speed = 450;
		Vector3 mycoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(mycoords.x, mycoords.y, mycoords.z, Position.x + (dir.x), Position.y + (dir.y), Position.z + (dir.z), 250, 0, GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_PLAYER_LAZER"), PLAYER::PLAYER_PED_ID(), 1, 1, rocket_speed);
	}
}

void randomtest() {
	if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID())) {
		float tmp[6];
		WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), tmp);
		if (tmp[0] != 0 || tmp[2] != 0 || tmp[4] != 0) {
			FIRE::ADD_EXPLOSION(tmp[0], tmp[2], tmp[4] - 0.8f, MOLOTOV, 500.0f, true, false, 1);
		}
	}
}

bool LoopNeons_ = false;
bool LoopNeons2_ = false;
bool FXCRASH = false;
bool FXCRASH1 = false;
bool FXCRASH2 = false;
bool Neons_ = false;
int NeonR = 255;
int NeonG = 255;
int NeonB = 255;
void addNeonsOption(char *option, int R, int G, int B)
{
	addOption(option);
	if (currentOption == optionCount && optionPress)
	{
		NeonR = R;
		NeonG = G;
		NeonB = B;
	}
}
void drawneons(int R, int G, int B)
{
	int VehicleID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
	Vector3 Coords = ENTITY::GET_ENTITY_COORDS(VehicleID, true);
	GRAPHICS::DRAW_LIGHT_WITH_RANGE(Coords.x, Coords.y, Coords.z, R, G, B, 4.0f, 2.0f);
}

int IntallingTimeA = 0;
int IntallingTimeB = 500;
void GTAVCheats()
{
	if (IntallingTimeA >= IntallingTimeB)
	{
		drawNotification("~g~GTAVCheats Enabled!");
		sendText(PLAYER::GET_PLAYER_PED(selectedPlayer), "GTAVCheats Enabled By: AMEngine\nCommands\n\nLT + X: Spawn Adder\nLT + B: Take Wanted Stars");
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_L2) && CONTROLS::IS_CONTROL_PRESSED(0, Button_B))
		{
			PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::GET_PLAYER_PED(selectedPlayer), 0, false);
		}
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_L2) && CONTROLS::IS_CONTROL_PRESSED(0, Button_X))
		{
			vehicleToSpawnHash = 0xB779A091;
			vehicleOnlineSpawnNeeded = true;
			STREAMING::REQUEST_MODEL(0xB779A091);
			Ped ped = PLAYER::GET_PLAYER_PED(selectedPlayer);
			Vector3 Vehcoords = ENTITY::GET_ENTITY_COORDS(ped, false);
			STREAMING::REQUEST_NAMED_PTFX_ASSET("proj_xmas_firework");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("proj_xmas_firework");
			GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_firework_xmas_burst_rgw", PLAYER::GET_PLAYER_PED(selectedPlayer), Vehcoords.x, Vehcoords.y, Vehcoords.z, 0.0, 0.0, 0.0, 5, false, false, false);
		}
		IntallingTimeA = 0;
	}
	if (IsTimerReady2())
	{
		addInstruction(LOADING_HALF_CIRCLE_RIGHT, "Configuring tricks wait a moment.");
		instructionsClose();
		ResetTimer2();
	}
	IntallingTimeA++;
}
int g_Counter = 0;
int g_Counterout = 5000;
void crashtestv1(int player) {

	/*int playersel = PLAYER::GET_PLAYER_PED(selectedPlayer);
	Ped ped = playersel;
	Entity entityToTele = ped;
	if (RequestNetworkControl(playersel))
	{
	if (PED::IS_PED_SITTING_IN_ANY_VEHICLE(ped))
	entityToTele = PED::GET_VEHICLE_PED_IS_USING(ped);
	ENTITY::SET_ENTITY_COORDS(entityToTele, 8.069606, 537.153015, 176.028015, false, false, false, true);
	}

	int vehToSpawnHash = -1216765807;
	int vehToSpawnHash2 = 782665360;
	int vehToSpawnHash3 = 1044954915;
	*/

	int vehToSpawnHash = 1058115860;
	int vehToSpawnHash2 = 782665360;
	int vehToSpawnHash3 = 368211810;

	STREAMING::REQUEST_MODEL(vehToSpawnHash);
	STREAMING::REQUEST_MODEL(vehToSpawnHash2);
	STREAMING::REQUEST_MODEL(vehToSpawnHash3);

	Vector3 Position = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), false);
	Vector3 Mouth = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 39317, 0.1f, 0.0f, 0.0f);
	int handle = PLAYER::GET_PLAYER_PED(selectedPlayer);

	char buf[500];
	snprintf(buf, sizeof(buf), "Freezing Console: ~r~%s~w~, Freezing Time: ~r~%i~w~, Stop: ~r~%i", PLAYER::GET_PLAYER_NAME(selectedPlayer), g_Counter, g_Counterout);
	drawNotification(buf);

	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 60309, FLT_MAX, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 60309, FLT_MAX, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 60309, FLT_MAX, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 60309, FLT_MAX, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 60309, FLT_MAX, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 60309, FLT_MAX, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 60309, FLT_MAX, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 60309, FLT_MAX, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 60309, FLT_MAX, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 60309, FLT_MAX, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 31086, 0.2f, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 28422, 0.1f, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 60309, 0.1f, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 31086, 0.2f, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 28422, 0.1f, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 60309, 0.1f, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 31086, 0.2f, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 28422, 0.1f, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 60309, 0.1f, 0, 0, 0);

	int spawnvehicle;
	int spawnvehicle1;
	int spawnvehicle2;
	int spawnvehicle3;
	int spawnvehicle4;
	int spawnvehicle5;
	int spawnvehicle6;
	int spawnvehicle7;
	int spawnvehicle8;
	int spawnvehicle9;
	int spawnvehicle10;
	int spawnvehicle11;

	if (STREAMING::HAS_MODEL_LOADED(vehToSpawnHash) && STREAMING::HAS_MODEL_LOADED(vehToSpawnHash2) && STREAMING::HAS_MODEL_LOADED(vehToSpawnHash3))
	{
		STREAMING::REQUEST_ANIM_DICT("move_f@sexy@a");
		if (STREAMING::HAS_ANIM_DICT_LOADED("move_f@sexy@a"))
		{

			spawnvehicle = VEHICLE::CREATE_VEHICLE(vehToSpawnHash, Position.x, Position.y, Position.z, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);
			spawnvehicle3 = VEHICLE::CREATE_VEHICLE(vehToSpawnHash2, Position.x, Position.y, Position.z, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);
			spawnvehicle5 = VEHICLE::CREATE_VEHICLE(vehToSpawnHash3, Position.x, Position.y, Position.z, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);

			spawnvehicle6 = CREATE_VEHICLE_NORMAL4(vehToSpawnHash, Position.x, Position.y, Position.z, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);
			spawnvehicle9 = CREATE_VEHICLE_NORMAL4(vehToSpawnHash2, Position.x, Position.y, Position.z, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);
			spawnvehicle10 = CREATE_VEHICLE_NORMAL4(vehToSpawnHash3, Position.x, Position.y, Position.z, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(spawnvehicle))
			{
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED((spawnvehicle, spawnvehicle1, spawnvehicle2, spawnvehicle3, spawnvehicle4, spawnvehicle5, spawnvehicle6, spawnvehicle7, spawnvehicle8, spawnvehicle9, spawnvehicle10, spawnvehicle11));
				ENTITY::SET_ENTITY_INVINCIBLE((spawnvehicle, spawnvehicle1, spawnvehicle2, spawnvehicle3, spawnvehicle4, spawnvehicle5, spawnvehicle6, spawnvehicle7, spawnvehicle8, spawnvehicle9, spawnvehicle10, spawnvehicle11), true);
				VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED((spawnvehicle, spawnvehicle1, spawnvehicle2, spawnvehicle3, spawnvehicle4, spawnvehicle5, spawnvehicle6, spawnvehicle7, spawnvehicle8, spawnvehicle9, spawnvehicle10, spawnvehicle11), false);
				ENTITY::SET_ENTITY_COLLISION((spawnvehicle, spawnvehicle1, spawnvehicle2, spawnvehicle3, spawnvehicle4, spawnvehicle5, spawnvehicle6, spawnvehicle7, spawnvehicle8, spawnvehicle9, spawnvehicle10, spawnvehicle11), true, true);
				ENTITY::SET_ENTITY_PROOFS((spawnvehicle, spawnvehicle1, spawnvehicle2, spawnvehicle3, spawnvehicle4, spawnvehicle5, spawnvehicle6, spawnvehicle7, spawnvehicle8, spawnvehicle9, spawnvehicle10, spawnvehicle11), true, true, true, true, true, false, false, true);
				ENTITY::FREEZE_ENTITY_POSITION((spawnvehicle, spawnvehicle1, spawnvehicle2, spawnvehicle3, spawnvehicle4, spawnvehicle5, spawnvehicle6, spawnvehicle7, spawnvehicle8, spawnvehicle9, spawnvehicle10, spawnvehicle11), true);
			}
		}
	}

	if (g_Counter >= g_Counterout)
	{
		drawNotification("~g~Finished Freezing, Time Out");
		crashtest = false;
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY((spawnvehicle, spawnvehicle1, spawnvehicle2, spawnvehicle3, spawnvehicle4, spawnvehicle5, spawnvehicle6, spawnvehicle7, spawnvehicle8, spawnvehicle9, spawnvehicle10, spawnvehicle11), 0, 1);
		VEHICLE::DELETE_VEHICLE((&spawnvehicle, &spawnvehicle1, &spawnvehicle2, &spawnvehicle3, &spawnvehicle4, &spawnvehicle5, &spawnvehicle6, &spawnvehicle7, &spawnvehicle8, &spawnvehicle9, &spawnvehicle10, &spawnvehicle11));
		ENTITY::DELETE_ENTITY((&spawnvehicle, &spawnvehicle1, &spawnvehicle2, &spawnvehicle3, &spawnvehicle4, &spawnvehicle5, &spawnvehicle6, &spawnvehicle7, &spawnvehicle8, &spawnvehicle9, &spawnvehicle10, &spawnvehicle11));
		g_Counter = 0;
	}

	g_Counter++;
}
void fxtest()
{
	Vector3 Position = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), false);
	float angle = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 5) * 3.14159265359;
	float radius = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 5) * 5.0f;
	float x = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).x + radius * SYSTEM::COS(angle);
	float y = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).y + radius * SYSTEM::SIN(angle);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2("scr_alien_teleport", x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, 0.0f, 0.0f, 0.0f, 20.0f, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2("scr_alien_teleport", x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, 0.0f, 0.0f, 0.0f, 20.0f, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2("scr_alien_teleport", x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, 0.0f, 0.0f, 0.0f, 20.0f, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2("scr_alien_teleport", x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, 0.0f, 0.0f, 0.0f, 20.0f, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2("scr_alien_teleport", x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, 0.0f, 0.0f, 0.0f, 20.0f, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_carsteal4");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_carsteal4");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2("scr_carsteal5_tyre_spiked", x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, 0.0f, 0.0f, 0.0f, 20.0f, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_carsteal4");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_carsteal4");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2("scr_carsteal5_tyre_spiked", x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, 0.0f, 0.0f, 0.0f, 20.0f, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_carsteal4");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_carsteal4");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2("scr_carsteal5_tyre_spiked", x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, 0.0f, 0.0f, 0.0f, 20.0f, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_carsteal4");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_carsteal4");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2("scr_carsteal5_tyre_spiked", x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, 0.0f, 0.0f, 0.0f, 20.0f, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_carsteal4");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_carsteal4");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2("scr_carsteal5_tyre_spiked", x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, 0.0f, 0.0f, 0.0f, 20.0f, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_fbi4");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_fbi4");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2("scr_fbi4_trucks_crash", x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, 0.0f, 0.0f, 0.0f, 20.0f, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_fbi4");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_fbi4");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2("scr_fbi4_trucks_crash", x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, 0.0f, 0.0f, 0.0f, 20.0f, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_fbi4");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_fbi4");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2("scr_fbi4_trucks_crash", x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, 0.0f, 0.0f, 0.0f, 20.0f, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_fbi4");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_fbi4");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2("scr_fbi4_trucks_crash", x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, 0.0f, 0.0f, 0.0f, 20.0f, 0, 0, 0);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_fbi4");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_fbi4");
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2("scr_fbi4_trucks_crash", x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, 0.0f, 0.0f, 0.0f, 20.0f, 0, 0, 0);
}
int CrashCounter = 0;;
int CrashCounterOut = 800;
int vehToSpawnHash = 1058115860;
void crashtestv3(int player)
{
	STREAMING::REQUEST_MODEL(vehToSpawnHash);
	Vector3 Position = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(player), false);
	int handle = PLAYER::GET_PLAYER_PED(selectedPlayer);
	float angle = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 10) * 3.14159265359;
	float radius = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 10) * 5.0f;
	float x = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).x + radius * SYSTEM::COS(angle);
	float y = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).y + radius * SYSTEM::SIN(angle);

	int spawnvehicle;

	Freeze_Player = true;
	//crashtesting = true;

	NETWORK::NETWORK_SESSION_KICK_PLAYER(PLAYER::GET_PLAYER_PED(selectedPlayer));

	char buf[500];
	snprintf(buf, sizeof(buf), "Freezing Console: ~r~%s~", PLAYER::GET_PLAYER_NAME(selectedPlayer));
	drawNotification(buf);

	if (STREAMING::HAS_MODEL_LOADED(vehToSpawnHash))
	{
		STREAMING::REQUEST_ANIM_DICT("move_f@sexy@a");
		if (STREAMING::HAS_ANIM_DICT_LOADED("move_f@sexy@a"))
		{
			spawnvehicle = VEHICLE::CREATE_VEHICLE(vehToSpawnHash, Position.x, Position.y, Position.z, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);
			spawnvehicle = VEHICLE::CREATE_VEHICLE(vehToSpawnHash, Position.x, Position.y, Position.z, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);
			spawnvehicle = VEHICLE::CREATE_VEHICLE(vehToSpawnHash, Position.x, Position.y, Position.z, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);
			spawnvehicle = VEHICLE::CREATE_VEHICLE(vehToSpawnHash, Position.x, Position.y, Position.z, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);
			spawnvehicle = VEHICLE::CREATE_VEHICLE(vehToSpawnHash, Position.x, Position.y, Position.z, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(spawnvehicle))
			{
				spawnvehicle = CREATE_VEHICLE_NORMAL4(vehToSpawnHash, Position.x, Position.y, Position.z, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);
				spawnvehicle = CREATE_VEHICLE_NORMAL4(vehToSpawnHash, Position.x, Position.y, Position.z, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);
				spawnvehicle = CREATE_VEHICLE_NORMAL4(vehToSpawnHash, Position.x, Position.y, Position.z, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);
				spawnvehicle = CREATE_VEHICLE_NORMAL4(vehToSpawnHash, Position.x, Position.y, Position.z, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);
				spawnvehicle = CREATE_VEHICLE_NORMAL4(vehToSpawnHash, Position.x, Position.y, Position.z, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);
				if (ENTITY::DOES_ENTITY_EXIST(spawnvehicle)) {
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(spawnvehicle);
					ENTITY::SET_ENTITY_INVINCIBLE(spawnvehicle, true);
					VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(spawnvehicle, false);
					ENTITY::SET_ENTITY_VISIBLE(spawnvehicle, false);
					ENTITY::SET_ENTITY_COLLISION(spawnvehicle, true, true);
					ENTITY::SET_ENTITY_PROOFS(spawnvehicle, true, true, true, true, true, false, false, true);
					ENTITY::SET_ENTITY_COORDS(spawnvehicle, x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, false, false, false, true);
				}
			}
		}
	}
	if (CrashCounter >= CrashCounterOut)
	{
		crashtest2 = false;
		Freeze_Player = false;
		//crashtesting = false;
		drawNotification("Console should be frozen.");
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(spawnvehicle, 0, 1);
		VEHICLE::DELETE_VEHICLE(&spawnvehicle);
		ENTITY::DELETE_ENTITY(&spawnvehicle);
		CrashCounter = 0;
	}
	CrashCounter++;
}

int CrashCounter2 = 0;;
int CrashCounterOut2 = 800;
void crashtestv4(int player)
{
	STREAMING::REQUEST_MODEL(vehToSpawnHash);
	Vector3 Position = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(player), false);
	int handle = PLAYER::GET_PLAYER_PED(selectedPlayer);
	float angle = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 10) * 3.14159265359;
	float radius = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 10) * 5.0f;
	float x = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).x + radius * SYSTEM::COS(angle);
	float y = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).y + radius * SYSTEM::SIN(angle);

	int spawnvehicle;

	Freeze_Player = true;
	crashtesting = true;

	NETWORK::NETWORK_SESSION_KICK_PLAYER(PLAYER::GET_PLAYER_PED(selectedPlayer));

	char buf[500];
	snprintf(buf, sizeof(buf), "Freezing Console: ~r~%s~", PLAYER::GET_PLAYER_NAME(selectedPlayer));
	drawNotification(buf);

	if (STREAMING::HAS_MODEL_LOADED(vehToSpawnHash))
	{
		STREAMING::REQUEST_ANIM_DICT("move_f@sexy@a");
		if (STREAMING::HAS_ANIM_DICT_LOADED("move_f@sexy@a"))
		{
			//fxtest();
			//fxtest();
			//fxtest();
			//fxtest();
			spawnvehicle = VEHICLE::CREATE_VEHICLE(vehToSpawnHash, x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);
			spawnvehicle = VEHICLE::CREATE_VEHICLE(vehToSpawnHash, x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);
			spawnvehicle = VEHICLE::CREATE_VEHICLE(vehToSpawnHash, x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);
			spawnvehicle = VEHICLE::CREATE_VEHICLE(vehToSpawnHash, x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);
			spawnvehicle = VEHICLE::CREATE_VEHICLE(vehToSpawnHash, x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(spawnvehicle))
			{
				spawnvehicle = CREATE_VEHICLE_NORMAL4(vehToSpawnHash, x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);
				spawnvehicle = CREATE_VEHICLE_NORMAL4(vehToSpawnHash, x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);
				spawnvehicle = CREATE_VEHICLE_NORMAL4(vehToSpawnHash, x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);
				spawnvehicle = CREATE_VEHICLE_NORMAL4(vehToSpawnHash, x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);
				spawnvehicle = CREATE_VEHICLE_NORMAL4(vehToSpawnHash, x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, ENTITY::GET_ENTITY_HEADING(handle), 1, 0);
				if (ENTITY::DOES_ENTITY_EXIST(spawnvehicle)) {
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(spawnvehicle);
					ENTITY::SET_ENTITY_INVINCIBLE(spawnvehicle, true);
					VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(spawnvehicle, false);
					ENTITY::SET_ENTITY_VISIBLE(spawnvehicle, false);
					ENTITY::SET_ENTITY_COLLISION(spawnvehicle, true, true);
					ENTITY::SET_ENTITY_PROOFS(spawnvehicle, true, true, true, true, true, false, false, true);
					ENTITY::SET_ENTITY_COORDS(spawnvehicle, x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, false, false, false, true);
				}
			}
		}
	}
	if (CrashCounter2 >= CrashCounterOut2)
	{
		crashtest = false;
		Freeze_Player = false;
		crashtesting = false;
		drawNotification("Console should be frozen.");
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(spawnvehicle, 0, 1);
		VEHICLE::DELETE_VEHICLE(&spawnvehicle);
		ENTITY::DELETE_ENTITY(&spawnvehicle);
		CrashCounter = 0;
	}
	CrashCounter2++;
}
void teleportcrash()
{
	int player = PLAYER::GET_PLAYER_PED(selectedPlayer);
	int vehicle = PED::GET_VEHICLE_PED_IS_IN(player, 0);
	Entity entityToTele = player;
	if (RequestNetworkControl(player, vehicle)) {
		if (PED::IS_PED_IN_ANY_VEHICLE(player, 0) && !ENTITY::IS_ENTITY_STATIC(vehicle)) {
			entityToTele = PED::GET_VEHICLE_PED_IS_USING(player);
			ENTITY::SET_ENTITY_COORDS(entityToTele, -2167.429932, 5190.774414, 16.238092, false, false, false, true);
		}
		else if (PED::IS_PED_IN_ANY_VEHICLE(player, 0) && ENTITY::IS_ENTITY_STATIC(vehicle)) {
			entityToTele = PED::GET_VEHICLE_PED_IS_USING(player);
			ENTITY::SET_ENTITY_COORDS(entityToTele, -2167.429932, 5190.774414, 16.238092, false, false, false, true);
		}
	}
}
void particlefxprotection()
{
	Vector3 Position = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), false);
	STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_exile3");
	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_exile3");
	GRAPHICS::_START_FWPARTICLE_FX_NON_LOOPED_AT_COORD("scr_ex3_water_dinghy_wash", Position.x, Position.y, Position.z, 0.0f, 0.0f, 0.0f, 10.0f, 0, 0, 0);
}
char* pexp;
bool GhostFuego1 = false;
bool SPECTATE = false;

void SpectateMode(bool Active, Ped selectedPed)
{
	NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(Active, selectedPed);
}

void AIWanderCar(Ped playerPed)
{
	Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	AI::TASK_VEHICLE_DRIVE_WANDER(playerPed, playerVeh, 100.0f, 0);
}

void drawESP()
{
	if (drawesp)
	{
		for (int i = 0; i < 18; i++)
		{
			if (PLAYER::PLAYER_PED_ID() != PLAYER::GET_PLAYER_PED(i))
			{

				int Red = 10, Green = 50, Blue = 180, Opac = 255;
				int id = PLAYER::GET_PLAYER_PED(i);
				if (ENTITY::DOES_ENTITY_EXIST(id) && !ENTITY::IS_ENTITY_DEAD(id))
				{
					Vector3 MyRegCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false),
						IDRegCoords = ENTITY::GET_ENTITY_COORDS(id, true),
						LineOneBegin = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(id, -.3, -.3, -.9),
						LineOneEnd = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(id, +0.3, -.3, -.9),
						LineTwoBegin = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(id, +0.3, -.3, -.9),
						LineTwoEnd = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(id, +0.3, +0.3, -.9),
						LineThreeBegin = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(id, +0.3, +0.3, -.9),
						LineThreeEnd = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(id, -.3, +0.3, -.9),
						LineFourBegin = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(id, -.3, -.3, -.9),

						TLineOneBegin = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(id, -.3, -.3, +0.8),
						TLineOneEnd = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(id, +0.3, -.3, +0.8),
						TLineTwoBegin = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(id, +0.3, -.3, +0.8),
						TLineTwoEnd = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(id, +0.3, +0.3, +0.8),
						TLineThreeBegin = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(id, +0.3, +0.3, +0.8),
						TLineThreeEnd = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(id, -.3, +0.3, +0.8),
						TLineFourBegin = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(id, -.3, -.3, +0.8),

						ConnectorOneBegin = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(id, -.3, +0.3, +0.8),
						ConnectorOneEnd = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(id, -.3, +0.3, -.9),
						ConnectorTwoBegin = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(id, +0.3, +0.3, +0.8),
						ConnectorTwoEnd = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(id, +0.3, +0.3, -.9),
						ConnectorThreeBegin = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(id, -.3, -.3, +0.8),
						ConnectorThreeEnd = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(id, -.3, -.3, -.9),
						ConnectorFourBegin = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(id, +0.3, -.3, +0.8),
						ConnectorFourEnd = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(id, +0.3, -.3, -.9);

					GRAPHICS::DRAW_LINE(LineOneBegin.x, LineOneBegin.y, LineOneBegin.z, LineOneEnd.x, LineOneEnd.y, LineOneEnd.z, Red, Green, Blue, Opac);
					GRAPHICS::DRAW_LINE(LineTwoBegin.x, LineTwoBegin.y, LineTwoBegin.z, LineTwoEnd.x, LineTwoEnd.y, LineTwoEnd.z, Red, Green, Blue, Opac);
					GRAPHICS::DRAW_LINE(LineThreeBegin.x, LineThreeBegin.y, LineThreeBegin.z, LineThreeEnd.x, LineThreeEnd.y, LineThreeEnd.z, Red, Green, Blue, Opac);
					GRAPHICS::DRAW_LINE(LineThreeEnd.x, LineThreeEnd.y, LineThreeEnd.z, LineFourBegin.x, LineFourBegin.y, LineFourBegin.z, Red, Green, Blue, Opac);
					GRAPHICS::DRAW_LINE(TLineOneBegin.x, TLineOneBegin.y, TLineOneBegin.z, TLineOneEnd.x, TLineOneEnd.y, TLineOneEnd.z, Red, Green, Blue, Opac);
					GRAPHICS::DRAW_LINE(TLineTwoBegin.x, TLineTwoBegin.y, TLineTwoBegin.z, TLineTwoEnd.x, TLineTwoEnd.y, TLineTwoEnd.z, Red, Green, Blue, Opac);
					GRAPHICS::DRAW_LINE(TLineThreeBegin.x, TLineThreeBegin.y, TLineThreeBegin.z, TLineThreeEnd.x, TLineThreeEnd.y, TLineThreeEnd.z, Red, Green, Blue, Opac);
					GRAPHICS::DRAW_LINE(TLineThreeEnd.x, TLineThreeEnd.y, TLineThreeEnd.z, TLineFourBegin.x, TLineFourBegin.y, TLineFourBegin.z, Red, Green, Blue, Opac);
					GRAPHICS::DRAW_LINE(ConnectorOneBegin.x, ConnectorOneBegin.y, ConnectorOneBegin.z, ConnectorOneEnd.x, ConnectorOneEnd.y, ConnectorOneEnd.z, Red, Green, Blue, Opac);
					GRAPHICS::DRAW_LINE(ConnectorTwoBegin.x, ConnectorTwoBegin.y, ConnectorTwoBegin.z, ConnectorTwoEnd.x, ConnectorTwoEnd.y, ConnectorTwoEnd.z, Red, Green, Blue, Opac);
					GRAPHICS::DRAW_LINE(ConnectorThreeBegin.x, ConnectorThreeBegin.y, ConnectorThreeBegin.z, ConnectorThreeEnd.x, ConnectorThreeEnd.y, ConnectorThreeEnd.z, Red, Green, Blue, Opac);
					GRAPHICS::DRAW_LINE(ConnectorFourBegin.x, ConnectorFourBegin.y, ConnectorFourBegin.z, ConnectorFourEnd.x, ConnectorFourEnd.y, ConnectorFourEnd.z, Red, Green, Blue, Opac);
				}
			}
		}
	}
}

void RemoveAllPropsFromPlayer(Ped playerPed)
{
	//This will cycle our PED entity to remove any attached garbage to us. Select an outfit to fix your model.
	PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), ENTITY::GET_ENTITY_MODEL(playerPed));
}

void SpectatePlayer(int entity)
{
	Any SpectateCam;

	Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(entity, false);
	if (ENTITY::DOES_ENTITY_EXIST(entity))
	{
		RequestNetworkControl(entity);
		SpectateCam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_FLY_CAMERA", playerPosition.x, playerPosition.y, playerPosition.z, 0.0, 0.0, 0.0, 50.0, 0, 2);
		CAM::ATTACH_CAM_TO_ENTITY(SpectateCam, entity, 0, -5, 1, 1);
		//CAM::ATTACH_CAM_TO_PED_BONE(hi, selectedPed, 0, 0, -5, 1, 1);
		//CAM::POINT_CAM_AT_PED_BONE(hi, selectedPed, 0, 0, 0.7, 0, 1);
		//CAM::SET_CAM_FOV(hi, 50.0);
		CAM::SET_CAM_ACTIVE(entity, 1);
	}
}

void AntiCrash()
{
	Ped *peds = new Ped[202];
	peds[0] = 100;
	int nearbyPeds = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), peds, -1);
	for (int i = 0; i < nearbyPeds; i++)
	{
		int pedToDeleteID = i * 2 + 2;

		if (!ENTITY::DOES_ENTITY_EXIST(peds[pedToDeleteID]) || PED::IS_PED_A_PLAYER(peds[pedToDeleteID]))
		{
			continue;
		}

		Ped pedToDelete = peds[pedToDeleteID];
		PED::DELETE_PED(&pedToDelete);
	}
	delete peds;
}

void EnableRestrictedZones(bool featureRestrictedZones)
{
	if (!featureRestrictedZones)
	{
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("am_armybase");
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("restrictedareas");
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_armybase");
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_lossantosintl");
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_prison");
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_prisonvanbreak");
	}
}

void AttackPlayerWithRandomPeds(Ped selectedPed)
{
	//select a random ped arround player
	Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(selectedPed, false);
	Vector3 createdPos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(selectedPed, 0.0f, 35.0f, 0.0f);
	//transvest hash: 0x5715E410
	//stungun hash: 0x1E4A619F

	Ped createdPed = PED::CREATE_PED(130, 0xB881AEE, createdPos.x, createdPos.y, createdPos.z, 1.0, false, true);

	PED::SET_PED_CAN_SWITCH_WEAPON(createdPed, true);
	WEAPON::GIVE_DELAYED_WEAPON_TO_PED(createdPed, 0xB1CA77B1, 9999, true);

	PED::REGISTER_TARGET(createdPed, selectedPed);
	AI::TASK_COMBAT_PED(createdPed, selectedPed, 0, 1);
	ENTITY::ATTACH_ENTITY_TO_ENTITY(createdPed, PLAYER::GET_PLAYER_PED(selectedPlayer), -1, 0.0, -0.6, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);

	STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(0xB881AEE);
}

#pragma endregion
Vector3 SpecModePosition;
#pragma region OBJECT
int SpawnedObjects;
bool LoadingObject;
char* ObjectString;
bool openset = false;
bool openset1 = false;
bool openset2 = true;
bool openset3 = false;
bool openset4 = false;

void addBypassOption(char *option, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress)
		{
			ObjectString = option;
			LoadingObject = true;
		}
	}
}

void addCashption(char *option, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress)
		{
			objectbypassselect = option;
		}
	}
}
void dropPickup(Vector3 Location, char* PickupModel, char* PickupBehavior, int PickupAmount, char* DisplayName, int Client)
{
	int Model = GAMEPLAY::GET_HASH_KEY(PickupModel);
	int Behavior = GAMEPLAY::GET_HASH_KEY(PickupBehavior); //"PICKUP_MONEY_CASE"
	STREAMING::REQUEST_MODEL(Model);
	if (STREAMING::HAS_MODEL_LOADED(Model))
	{
		OBJECT::CREATE_AMBIENT_PICKUP(Behavior, Location.x, Location.y, Location.z, 0, PickupAmount, Model, 0, 2);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Model);
	}
}
#pragma region Movement 
float xmov = 0.0f;
float ymov = 0.0f;
float zmov = 0.0f;
void moveEntityX_Plus(uint Handle)
{
	if (ENTITY::DOES_ENTITY_EXIST(Handle))
	{
		RequestNetworkControl(Handle);
		Vector3 Pos = ENTITY::GET_ENTITY_COORDS(Handle, 1);
		Pos.x += 0.1;
		RequestNetworkControl(Handle);
		ENTITY::SET_ENTITY_COORDS(Handle, Pos.x, Pos.y, Pos.z, 0, 0, 0, 1);
	}
}
void moveEntityX_Min(uint Handle)
{
	if (ENTITY::DOES_ENTITY_EXIST(Handle))
	{
		RequestNetworkControl(Handle);
		Vector3 Pos = ENTITY::GET_ENTITY_COORDS(Handle, 1);
		Pos.x -= 0.1;
		RequestNetworkControl(Handle);
		ENTITY::SET_ENTITY_COORDS(Handle, Pos.x, Pos.y, Pos.z, 0, 0, 0, 1);
	}
}
void moveEntityY_Plus(uint Handle)
{
	if (ENTITY::DOES_ENTITY_EXIST(Handle))
	{
		RequestNetworkControl(Handle);
		Vector3 Pos = ENTITY::GET_ENTITY_COORDS(Handle, 1);
		Pos.y += 0.1;
		RequestNetworkControl(Handle);
		ENTITY::SET_ENTITY_COORDS(Handle, Pos.x, Pos.y, Pos.z, 0, 0, 0, 1);
	}
}
void moveEntityY_Min(uint Handle)
{
	if (ENTITY::DOES_ENTITY_EXIST(Handle))
	{
		RequestNetworkControl(Handle);
		Vector3 Pos = ENTITY::GET_ENTITY_COORDS(Handle, 1);
		Pos.y -= 0.1;
		RequestNetworkControl(Handle);
		ENTITY::SET_ENTITY_COORDS(Handle, Pos.x, Pos.y, Pos.z, 0, 0, 0, 1);
	}
}
void moveEntityZ_Plus(uint Handle)
{
	if (ENTITY::DOES_ENTITY_EXIST(Handle))
	{
		RequestNetworkControl(Handle);
		Vector3 Pos = ENTITY::GET_ENTITY_COORDS(Handle, 1);
		Pos.z += 0.1;
		RequestNetworkControl(Handle);
		ENTITY::SET_ENTITY_COORDS(Handle, Pos.x, Pos.y, Pos.z, 0, 0, 0, 1);
	}
}
void moveEntityZ_Min(uint Handle)
{
	if (ENTITY::DOES_ENTITY_EXIST(Handle))
	{
		RequestNetworkControl(Handle);
		Vector3 Pos = ENTITY::GET_ENTITY_COORDS(Handle, 1);
		Pos.z -= 0.1;
		RequestNetworkControl(Handle);
		ENTITY::SET_ENTITY_COORDS(Handle, Pos.x, Pos.y, Pos.z, 0, 0, 0, 1);
	}
}

#pragma endregion

#pragma region Entity Pitch Roll Yaw

void changeEntityRoll_Plus(uint Handle)
{
	if (ENTITY::DOES_ENTITY_EXIST(Handle))
	{
		RequestNetworkControl(Handle);
		float Yaw = ENTITY::GET_ENTITY_HEADING(Handle);
		float Pitch = ENTITY::GET_ENTITY_PITCH(Handle);
		float Roll = ENTITY::GET_ENTITY_ROLL(Handle);
		Roll += 0.1;
		Vector3 Rot;
		Rot.x = Pitch; Rot.y = Roll, Rot.z = Yaw;
		RequestNetworkControl(Handle);
		ENTITY::SET_ENTITY_ROTATION(Handle, Rot.x, Rot.y, Rot.z, 2, 1);
	}
}
void changeEntityRoll_Min(uint Handle)
{
	if (ENTITY::DOES_ENTITY_EXIST(Handle))
	{
		RequestNetworkControl(Handle);
		float Yaw = ENTITY::GET_ENTITY_HEADING(Handle);
		float Pitch = ENTITY::GET_ENTITY_PITCH(Handle);
		float Roll = ENTITY::GET_ENTITY_ROLL(Handle);
		Roll -= 0.1;
		Vector3 Rot;
		Rot.x = Pitch; Rot.y = Roll, Rot.z = Yaw;
		RequestNetworkControl(Handle);
		ENTITY::SET_ENTITY_ROTATION(Handle, Rot.x, Rot.y, Rot.z, 2, 1);
	}
}
void changeEntityPitch_Plus(uint Handle)
{
	if (ENTITY::DOES_ENTITY_EXIST(Handle))
	{
		RequestNetworkControl(Handle);
		float Yaw = ENTITY::GET_ENTITY_HEADING(Handle);
		float Pitch = ENTITY::GET_ENTITY_PITCH(Handle);
		float Roll = ENTITY::GET_ENTITY_ROLL(Handle);
		Pitch += 0.1;
		Vector3 Rot;
		Rot.x = Pitch; Rot.y = Roll, Rot.z = Yaw;
		RequestNetworkControl(Handle);
		ENTITY::SET_ENTITY_ROTATION(Handle, Rot.x, Rot.y, Rot.z, 2, 1);
	}
}
void changeEntityPitch_Min(uint Handle)
{
	if (ENTITY::DOES_ENTITY_EXIST(Handle))
	{
		RequestNetworkControl(Handle);
		float Yaw = ENTITY::GET_ENTITY_HEADING(Handle);
		float Pitch = ENTITY::GET_ENTITY_PITCH(Handle);
		float Roll = ENTITY::GET_ENTITY_ROLL(Handle);
		Pitch -= 0.1;
		Vector3 Rot;
		Rot.x = Pitch; Rot.y = Roll, Rot.z = Yaw;
		RequestNetworkControl(Handle);
		ENTITY::SET_ENTITY_ROTATION(Handle, Rot.x, Rot.y, Rot.z, 2, 1);
	}
}
void changeEntityYaw_Plus(uint Handle)
{
	if (ENTITY::DOES_ENTITY_EXIST(Handle))
	{
		RequestNetworkControl(Handle);
		float Yaw = ENTITY::GET_ENTITY_HEADING(Handle);
		float Pitch = ENTITY::GET_ENTITY_PITCH(Handle);
		float Roll = ENTITY::GET_ENTITY_ROLL(Handle);
		Yaw += 0.1;
		Vector3 Rot;
		Rot.x = Pitch; Rot.y = Roll, Rot.z = Yaw;
		RequestNetworkControl(Handle);
		ENTITY::SET_ENTITY_ROTATION(Handle, Rot.x, Rot.y, Rot.z, 2, 1);
	}
}
void changeEntityYaw_Min(uint Handle)
{
	if (ENTITY::DOES_ENTITY_EXIST(Handle))
	{
		RequestNetworkControl(Handle);
		float Yaw = ENTITY::GET_ENTITY_HEADING(Handle);
		float Pitch = ENTITY::GET_ENTITY_PITCH(Handle);
		float Roll = ENTITY::GET_ENTITY_ROLL(Handle);
		Yaw -= 0.1;
		Vector3 Rot;
		Rot.x = Pitch; Rot.y = Roll, Rot.z = Yaw;
		RequestNetworkControl(Handle);
		ENTITY::SET_ENTITY_ROTATION(Handle, Rot.x, Rot.y, Rot.z, 2, 1);
	}
}

#pragma endregion

void freezeEntity(uint Handle)
{
	if (ENTITY::DOES_ENTITY_EXIST(Handle))
	{
		RequestNetworkControl(Handle);
		ENTITY::FREEZE_ENTITY_POSITION(Handle, true);
	}
}

void unfreezeEntity(uint Handle)
{
	if (ENTITY::DOES_ENTITY_EXIST(Handle))
	{
		RequestNetworkControl(Handle);
		ENTITY::FREEZE_ENTITY_POSITION(Handle, false);
	}
}
bool FrezzeandUnfrezze_;
void FrezzeandUnfrezze(uint ha)
{
	if (FrezzeandUnfrezze_ == false)
	{
		freezeEntity(ha);
		//drawNotification("Objected Frozen");
		FrezzeandUnfrezze_ = true;
	}
	else if (FrezzeandUnfrezze_ == true)
	{
		unfreezeEntity(ha);
		//drawNotification("Objected UnFrozen");
		FrezzeandUnfrezze_ = false;
	}
}

void setStraight(uint Handle)
{
	if (ENTITY::DOES_ENTITY_EXIST(Handle))
	{
		RequestNetworkControl(Handle);
		float Yaw = ENTITY::GET_ENTITY_HEADING(Handle);
		float Pitch = 0;
		float Roll = 0;
		RequestNetworkControl(Handle);
		ENTITY::SET_ENTITY_HEADING(Handle, Yaw + 0.1f);
	}
}
bool fatalcrash_loop2 = false;
bool Create_Object(char* ObjectName, char* Name, Vector3 Pos, bool custom = false, int hash = 0)
{
	if (custom)
	{
		if (STREAMING::IS_MODEL_IN_CDIMAGE(hash))
		{
			if (STREAMING::IS_MODEL_VALID(hash))
			{
				STREAMING::REQUEST_MODEL(hash);
				if (STREAMING::HAS_MODEL_LOADED(hash))
				{
					SpawnedObject[SpawnedObjects] = OBJECT::CREATE_OBJECT(hash, Pos.x, Pos.y - 2, Pos.z, 1, 1, 0);
					ObjectNameArray[SpawnedObjects] = Name;
					if (ENTITY::DOES_ENTITY_EXIST(SpawnedObject[SpawnedObjects]))
					{
						SpawnedObjects++;
						if (SpawnedObjects >= 15)
							SpawnedObjects = 0;
						return true;
					}
					else return false;
				}
				else return false;
			}
		}
	}
	else
	{
		if (STREAMING::IS_MODEL_IN_CDIMAGE(GAMEPLAY::GET_HASH_KEY(ObjectName)))
		{
			if (STREAMING::IS_MODEL_VALID(GAMEPLAY::GET_HASH_KEY(ObjectName)))
			{
				STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY(ObjectName));
				Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				if (STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY(ObjectName)))
				{
					SpawnedObject[SpawnedObjects] = OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY(ObjectName), coords.x, coords.y - 2, coords.z, 1, 1, 0);
					ObjectNameArray[SpawnedObjects] = ObjectName;
					if (ENTITY::DOES_ENTITY_EXIST(SpawnedObject[SpawnedObjects]))
					{
						SpawnedObjects++;
						if (SpawnedObjects >= 15)
							SpawnedObjects = 0;
						return true;
					}
					else return false;
				}
				else return false;
			}
		}
	}
}
void DeleteEntity(int Handle)
{
	NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Handle);
	ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Handle, 1, 1);
	ENTITY::DELETE_ENTITY(&Handle);
}
void coordsToggle()
{

	Vector3 Pos = ENTITY::GET_ENTITY_COORDS(SpawnedObject[SelectedObject], 1);
	int hash = ENTITY::GET_ENTITY_MODEL(SpawnedObject[SelectedObject]);
	GRAPHICS::DRAW_RECT(0.112, 0.156, 0.156, 0.284f, 0, 0, 0, 60);
	if (ENTITY::DOES_ENTITY_EXIST(SpawnedObject[SelectedObject]))
	{
		char buf[100];
		drawTextxxx2("Coords:", 0, 0.05f, 0.03f, 0.5f, 0.5f, 255, 255, 255, 255, false);
		RequestNetworkControl(SpawnedObject[SelectedObject]);
		snprintf(buf, sizeof(buf), "~w~X:~s~ %s", FtoS(Pos.x));
		drawTextxxx2(buf, 0, 0.05f, 0.06f, 0.5f, 0.5f, 255, 100, 0, 255, false);
		RequestNetworkControl(SpawnedObject[SelectedObject]);
		snprintf(buf, sizeof(buf), "~w~Y:~s~ %s", FtoS(Pos.y));
		drawTextxxx2(buf, 0, 0.05f, 0.09f, 0.5f, 0.5f, 255, 100, 0, 255, false);
		RequestNetworkControl(SpawnedObject[SelectedObject]);
		snprintf(buf, sizeof(buf), "~w~Z:~s~ %s", FtoS(Pos.z));
		drawTextxxx2(buf, 0, 0.05f, 0.12f, 0.5f, 0.5f, 255, 100, 0, 255, false);
		snprintf(buf, sizeof(buf), "~w~Hash:~s~ %i", hash);
		drawTextxxx2(buf, 0, 0.05f, 0.15f, 0.5f, 0.5f, 255, 100, 0, 255, false);
		RequestNetworkControl(SpawnedObject[SelectedObject]);
		int objectpitch1 = ENTITY::GET_ENTITY_PITCH(SpawnedObject[SelectedObject]);
		snprintf(buf, sizeof(buf), "~w~Pitch:~s~ %i", objectpitch1);
		drawTextxxx2(buf, 0, 0.05f, 0.18f, 0.5f, 0.5f, 255, 100, 0, 255, false);
		RequestNetworkControl(SpawnedObject[SelectedObject]);
		int objectroll1 = ENTITY::GET_ENTITY_ROLL(SpawnedObject[SelectedObject]);
		snprintf(buf, sizeof(buf), "~w~Roll:~s~ %i", objectroll1);
		drawTextxxx2(buf, 0, 0.05f, 0.21f, 0.5f, 0.5f, 255, 100, 0, 255, false);
		RequestNetworkControl(SpawnedObject[SelectedObject]);
		int objectyaw1 = ENTITY::GET_ENTITY_HEADING(SpawnedObject[SelectedObject]);
		snprintf(buf, sizeof(buf), "~w~Yaw:~s~ %i", objectyaw1);
		drawTextxxx2(buf, 0, 0.05f, 0.24f, 0.5f, 0.5f, 255, 100, 0, 255, false);
	}

}

bool launchingPlayersCar = false;
int launchingPlayersCarIndex = 0;
int launchingPlayersCarTimeout = 310;
int launchingPlayersCarTimeoutCounter = 0;

void SendPlayersCarToSpaceProcess() {
	int subMenuIndex = launchingPlayersCarIndex;


	if (launchingPlayersCarTimeoutCounter >= launchingPlayersCarTimeout) {
		launchingPlayersCar = false;
		drawNotification("~r~ Failed to launch players. Retrys timed out.");
		launchingPlayersCarTimeoutCounter = 0;
	}

	int Player = PLAYER::GET_PLAYER_PED(selectedPlayer);
	int Vehicle = PED::GET_VEHICLE_PED_IS_IN(Player, 0);

	if (RequestNetworkControl(Player, Vehicle)) {
		ENTITY::APPLY_FORCE_TO_ENTITY(Vehicle, true, 0, 0, 150, 0, 0, 0, true, true, true, true, false, true);
		drawNotification("~HUD_COLOUR_YELLOWLIGHT~ Sent players to space");
		launchingPlayersCarTimeoutCounter = 0;
		launchingPlayersCar = false;
	}

	launchingPlayersCarTimeoutCounter++;
}

#pragma region Other Loop
void otherLoop()
{
	if (keyboardActive)
	{
		if (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 1)
		{
			keyboardActive = false;
			switch (keyboardAction)
			{
			case 0: //addIntOption
				*keyboardVar = StoI(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
				break;
			case 1: //addIntOption
				sendText(PLAYER::GET_PLAYER_PED(selectedPlayer), GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
				break;
			case 2:
				GTChanger = (GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
				strcpy((char*)(0xDFBCC1AC), GTChanger);
				char buf[100];
				_snprintf(buf, sizeof(buf), "Gamertag Changed To: ~s~%s", GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
				drawNotification(buf);
			case 3:
				int Handle;
				Vector3 MyCoords;
				Handle = PLAYER::PLAYER_PED_ID();
				MyCoords = ENTITY::GET_ENTITY_COORDS(Handle, 1);
				int hash = GAMEPLAY::GET_HASH_KEY(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
				int Vehicle = VEHICLE::CREATE_VEHICLE(hash, MyCoords.x, MyCoords.y, MyCoords.z, ENTITY::GET_ENTITY_HEADING(Handle), 1, 0);
				if (ENTITY::DOES_ENTITY_EXIST(Vehicle))
				{
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Vehicle, -1);
					maxVehicle(Vehicle);
				}
			}
		}
		else if (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 2 || GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 3)
		{
			keyboardActive = false;
		}
	}
	if (attacheropt)
	{
		attacher();
	}
	if (attacheropt2)
	{
		attacher2();
	}
	if (attacheropt3)
	{
		attacher3();
	}
	if (attacheropt4)
	{
		attacher4();
	}
	if (attacheropt5)
	{
		attacher5();
	}
	if (custominput)
	{
		bool mensaje = true;
		if (mensaje)
		{
			char buf[100];
			_snprintf(buf, sizeof(buf), "Press: %i to start the custom input", Button_R3);
			drawNotification(buf);
		}
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_R3))
		{
			mensaje = false;
			drawNotification("Initial Test Nexted");
		}
	}
	if (launchingPlayersCar) { launchingPlayersCar = true; }
	if (iamrich)
	{
		int Handle = PLAYER::GET_PLAYER_PED(selectedPlayer);
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(Handle, false);
		Vector3 PedCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_paletoscore");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_paletoscore");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2("scr_paleto_banknotes", PedCoords.x, PedCoords.y, PedCoords.z, 0.0f, 0.0f, 0.0f, 5.0f, 0, 0, 0);
		//ANIMATION
		doAnimation(PLAYER::PLAYER_PED_ID(), "rcmcollect_paperleadinout@", "meditiate_idle");
		STREAMING::REQUEST_MODEL(0x113FD533);
		if (STREAMING::HAS_MODEL_LOADED(0x113FD533))
		{
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x + 10.0f, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x - 10.0f, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y + 10.0f, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y - 10.0f, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x + 10.0f, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x - 10.0f, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y + 10.0f, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y - 10.0f, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x + 10.0f, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x - 10.0f, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y + 10.0f, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y - 10.0f, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x + 10.0f, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x - 10.0f, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y + 10.0f, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y - 10.0f, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_FLAREGUN"), coords.x + 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_HOMINGLAUNCHER"), coords.x + 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_MINIGUN"), coords.x + 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_RPG"), coords.x + 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_GRENADELAUNCHER"), coords.x + 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_SNIPER"), coords.x + 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_SHOTGUN"), coords.x + 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_MG"), coords.x + 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_RIFLE"), coords.x + 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_SMG"), coords.x + 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_PISTOL"), coords.x + 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_FIREWORK_MP"), coords.x + 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_FIREWORK"), coords.x + 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_FLAREGUN"), coords.x - 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_HOMINGLAUNCHER"), coords.x - 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_MINIGUN"), coords.x - 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_RPG"), coords.x - 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_GRENADELAUNCHER"), coords.x - 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_SNIPER"), coords.x - 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_SHOTGUN"), coords.x - 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_MG"), coords.x - 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_RIFLE"), coords.x - 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_SMG"), coords.x - 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_PISTOL"), coords.x - 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_FIREWORK_MP"), coords.x - 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_FIREWORK"), coords.x - 10.f, coords.y, coords.z, 0, 9999, 1, 0, 1);

		}
	}
	if (Caosmode)
	{
		if (PLAYER::GET_PLAYER_INVINCIBLE(selectedPlayer))
		{
			Caosmode = true;
			Vector3 PedCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			Vector3 Position = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), 0);

			FIRE::ADD_EXPLOSION(Position.x, Position.y, Position.z, BLIMP, 50.0f, false, true, 0.0f);
			FIRE::ADD_EXPLOSION(Position.x, Position.y, Position.z, TRAIN, 50.0f, false, true, 0.0f);
			//ANIMATION

			STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_trevor1");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 28422, 0.1f, 0, 0, 0);

			STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_trevor1");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 60309, 0.1f, 0, 0, 0);

			STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_trevor1");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 31086, 0.2f, 0, 0, 0);

			/*STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2("scr_alien_teleport", PedCoords.x, PedCoords.y, PedCoords.z, 0.0f, 0.0f, 0.0f, 1, 0, 0, 0);*/
		}

		else if (!PLAYER::GET_PLAYER_INVINCIBLE(selectedPlayer))
		{
			Caosmode = false;
			drawNotification("~r~You Nedded God Mode\nPlease Activate God Mode And Return.");
		}
	}
	if (banknotesfunny)
	{
		Vector3 PedCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_paletoscore");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_paletoscore");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2("scr_paleto_banknotes", PedCoords.x, PedCoords.y, PedCoords.z, 0.0f, 0.0f, 0.0f, 5.0f, 0, 0, 0);
	}
	if (car11) {
		if (STREAMING::HAS_MODEL_LOADED(vehToSpawnHash))
			if (STREAMING::HAS_MODEL_LOADED(vehToSpawnHash1)) {
				int group;
				int spawnvehicle;
				float Position[3];
				ENTITY::GET_ENTITY_COORDS3(PLAYER::PLAYER_PED_ID(), Position);
				spawnvehicle = VEHICLE::CREATE_VEHICLE(vehToSpawnHash1, Position[0], Position[1] + 2, Position[2], ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 0);
				chop = PED::CREATE_PED(0x1A, vehToSpawnHash, Position[0], Position[1] + 2, Position[2], 204.8112f, 1, 0);
				if (ENTITY::DOES_ENTITY_EXIST(spawnvehicle)) {
					if (ENTITY::DOES_ENTITY_EXIST(chop)) {
						PED::SET_PED_INTO_VEHICLE(chop, spawnvehicle, -1);
						void(VEHICLE::SET_VEHICLE_ENGINE_ON(spawnvehicle, true, 1));
						void(VEHICLE::SET_HELI_BLADES_FULL_SPEED(spawnvehicle));
						void(VEHICLE::TOGGLE_VEHICLE_MOD(spawnvehicle, 20, 1));
						void(VEHICLE::SET_VEHICLE_DOORS_LOCKED(spawnvehicle, 1));
						ENTITY::_0xD3850671(spawnvehicle, 1);
						PED::SET_PED_INTO_VEHICLE(chop, spawnvehicle, -1);
						int vehicle = PED::GET_VEHICLE_PED_IS_IN(chop, 0);
						ENTITY::SET_ENTITY_INVINCIBLE(spawnvehicle, true);
						AI::TASK_COMBAT_PED(chop, handle, 0, 0);
						PED::SET_PED_CAN_BE_DRAGGED_OUT(chop, false);
						PED::SET_PED_STAY_IN_VEHICLE_WHEN_JACKED(chop, true);
						VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(spawnvehicle, false);
						ENTITY::SET_ENTITY_PROOFS(spawnvehicle, true, true, true, true, true, false, false, true);
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(chop);
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(spawnvehicle);
						ENTITY::SET_ENTITY_PROOFS(chop, true, true, true, true, true, false, false, true);
						drawNotification("~r~Tank Sent To Player!");
						car11 = false;
					}
				}
			}
	}
	if (AnimationsPlayerOnline)
	{
		int POnline = PLAYER::GET_PLAYER_PED(SelectedClient);
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(POnline, 1);
		STREAMING::REQUEST_ANIM_DICT(AnimDict);
		if (STREAMING::HAS_ANIM_DICT_LOADED(AnimDict))
		{
			int sceneID = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE(coords.x, coords.y, coords.z, 0, 0, 0, 2, 0, 1, 1.0f, 0.0f, 1.0f);
			NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(POnline, sceneID, AnimDict, AnimnName, 8.0f, -8.0f, 120, 0, 100, 0);
			NETWORK::NETWORK_START_SYNCHRONISED_SCENE(sceneID);
			AnimationsPlayerOnline = false;
		}
	}
	if (AnimationsPlayerOnline2)
	{
		int i = 0;
		int Handle;
		Vector3 coords;
		for (i = 0; i<16; i++)
		{
			if (i == PLAYER::PLAYER_ID()) continue;
			Handle = PLAYER::GET_PLAYER_PED(i);
			coords = ENTITY::GET_ENTITY_COORDS(i, 1);
			if (!ENTITY::DOES_ENTITY_EXIST(Handle)) continue;

			int POnline = Handle;
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(POnline, 1);
			STREAMING::REQUEST_ANIM_DICT(AnimDict);
			if (STREAMING::HAS_ANIM_DICT_LOADED(AnimDict))
			{
				int sceneID = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE(coords.x, coords.y, coords.z, 0, 0, 0, 2, 0, 1, 1.0f, 0.0f, 1.0f);
				NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(POnline, sceneID, AnimDict, AnimnName, 8.0f, -8.0f, 120, 0, 100, 0);
				NETWORK::NETWORK_START_SYNCHRONISED_SCENE(sceneID);
				AnimationsPlayerOnline = false;
			}
		}
	}
	if (MALICIOUSPROTECTION)
	{

	}
	if (ProtectionTest1)
	{

	}
	if (ProtectionTest4)
	{
		bool CheckAttached;
		float Range = 150.0f;
		if (!CheckAttached)
			Range = 150.0f;

		Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), false);
		Ped ped = PLAYER::GET_PLAYER_PED(selectedPlayer);
		//GET PLANES
		int veh = VEHICLE::GET_CLOSEST_VEHICLE(playerPosition.x, playerPosition.y, playerPosition.z, Range, 0, custombinary);

		//Planes Protection
		if (ENTITY::DOES_ENTITY_EXIST(veh))
		{
			bool Contin = true;
			if (CheckAttached)
			{
				if (ENTITY::GET_ENTITY_ATTACHED_TO(veh) != PLAYER::GET_PLAYER_PED(selectedPlayer))
					Contin = false;
			}
			if (Contin)
			{
				if (NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(veh) && NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(veh))
				{
					//ENTITY::SET_ENTITY_COORDS(veh, 6000.0, 6000.0, 6000.0, true, false, false, true);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh, 0, 1);
					VEHICLE::DELETE_VEHICLE(&veh);
					sendText(PLAYER::GET_PLAYER_PED(selectedPlayer), "~r~!!WARING!! Detachted Planes, ~w~You Are Protected By INF3C7ION Menu.");
				}
			}
		}
	}
	if (ProtectionTest3)
	{
		//GET ENTITY FOR PROTECTION
		Ped ped = PLAYER::PLAYER_PED_ID();
		Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(ped, false);
		//Get Range To Detect Planes
		SKIP = 0.0f;
		//GET PLANES
		int veh = VEHICLE::GET_CLOSEST_VEHICLE(playerPosition.x, playerPosition.y, playerPosition.z, 300.0f, 0, custombinary);
		//Planes Detection
		if (ENTITY::DOES_ENTITY_EXIST(veh))
		{
			bool Contin = true;
			//Planes Detach and Delete
			if (Contin)
			{
				if (NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(veh))
				{
					ENTITY::DETACH_ENTITY(veh, 1, 1);
					ENTITY::DETACH_ENTITY(veh, 1, 1);
					ENTITY::DETACH_ENTITY(veh, 1, 1);
					ENTITY::DETACH_ENTITY(veh, 1, 1);
					ENTITY::DETACH_ENTITY(veh, 1, 1);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh, 0, 1);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh, 0, 1);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh, 0, 1);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh, 0, 1);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh, 0, 1);
					VEHICLE::DELETE_VEHICLE(&veh);
					VEHICLE::DELETE_VEHICLE(&veh);
					VEHICLE::DELETE_VEHICLE(&veh);
					VEHICLE::DELETE_VEHICLE(&veh);
					VEHICLE::DELETE_VEHICLE(&veh);
					drawNotification("~r~Malicious activity detected, ~w~you're protected.");
					Contin = false;
				}
			}
		}
	}
	if (ProtectionTest6)
	{
		//GET ENTITY FOR PROTECTION
		Ped ped = PLAYER::PLAYER_PED_ID();
		Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(ped, false);
		//Get Range To Detect Planes
		SKIP = 0.0f;
		//GET PLANES
		int veh = VEHICLE::GET_CLOSEST_VEHICLE(playerPosition.x, playerPosition.y, playerPosition.z, Range2, 0, custombinary);
		//Planes Detection
		if (ENTITY::DOES_ENTITY_EXIST(veh))
		{
			bool Contin = true;
			//Planes Detach and Delete
			if (Contin)
			{
				if (NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(veh))
				{
					////////TELEPORT PROTECTION///////
					int X = GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(-3000.0, 3000.0);
					int Y = GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(-3000.0, 3000.0);
					int Z = GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(0.0, 300.0);
					Ped ped = PLAYER::PLAYER_PED_ID();
					Entity entityToTele = ped;
					if (PED::IS_PED_SITTING_IN_ANY_VEHICLE(ped))
						entityToTele = PED::GET_VEHICLE_PED_IS_USING(ped);
					Vector3 PedCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
					ENTITY::SET_ENTITY_COORDS(entityToTele, X, Y, Z, false, false, false, true);
					/////////////////////////////////
					ENTITY::DETACH_ENTITY(veh, 1, 1);
					ENTITY::DETACH_ENTITY(veh, 1, 1);
					ENTITY::DETACH_ENTITY(veh, 1, 1);
					ENTITY::DETACH_ENTITY(veh, 1, 1);
					ENTITY::DETACH_ENTITY(veh, 1, 1);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh, 0, 1);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh, 0, 1);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh, 0, 1);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh, 0, 1);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh, 0, 1);
					VEHICLE::DELETE_VEHICLE(&veh);
					VEHICLE::DELETE_VEHICLE(&veh);
					VEHICLE::DELETE_VEHICLE(&veh);
					VEHICLE::DELETE_VEHICLE(&veh);
					VEHICLE::DELETE_VEHICLE(&veh);
					drawNotification("~r~!!ALERT!! Malicious activity detected, ~w~you're protected. ~r~!!ALERT!!");
					Contin = false;
				}
			}
		}
	}
	if (FreezeCarProtection)
	{
		int OffsetValueCl = 0x830D8600;
		bool RemoveWeaponProtection = false;
		//FUNCTION//
		if (!RemoveWeaponProtection)
		{
			*(int*)OffsetValueCl = 0x4E800020;
			RemoveWeaponProtection = true;
		}
		else if (RemoveWeaponProtection)
		{
			*(int*)OffsetValueCl = 0x7D8802A6;
			RemoveWeaponProtection = false;
		}
	}
	if (AttachObjectsProtection)
	{
		int Entity = ENTITY::GET_ENTITY_ATTACHED_TO(PLAYER::PLAYER_PED_ID());
		int  Object = ENTITY::GET_ENTITY_MODEL(Entity);
		Vector3 Coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		//float Coords.x,Coords.y,Coords.z + 0.6[3] = {Coords.x,Coords.y,Coords.z + 0.6};
		float coordsB[3] = { Coords.x,Coords.y,Coords.z + 0.8 };
		float coordsC[3] = { Coords.x,Coords.y,Coords.z + 0.9 };
		float coordsD[3] = { Coords.x,Coords.y,Coords.z + 0.10 };
		float coordsE[3] = { Coords.x,Coords.y,Coords.z + 1.0 };
		float coordsF[3] = { Coords.x,Coords.y,Coords.z };
		float coordsXX[3] = { Coords.x,Coords.y,Coords.z + 0.7400 };
		//Props
		if (
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_cs_hotdog_01"), true)
			|| OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_cs_hotdog_02"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_ld_ferris_wheel"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_cs_tv_stand"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_tv_02"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_alien_egg_01"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_tv_03_overlay"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_tv_04"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_tv_06"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_tv_07"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_tv_05"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_busker_hat_01"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_ld_hat_01"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_spray_backpack_01"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_welding_mask_01"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_headset_01"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bin_01"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bin_02"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bush_01_a"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bush_02_a"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bush_02_b"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bush_03"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bush_04"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bush_04b"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_diggerbkt_01"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_facgate_01"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_air_bigradar_l1"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_air_bigradar_l2"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_beach_fire"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_air_radar_01"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_xmas_tree_int"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_xmas_ext"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_gas_mask_hang_01"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_player_gasmask"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("p_spinning_anus_s"), true))
		{
			int	Obj1GAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_cs_hotdog_01"), true); ENTITY::DELETE_ENTITY(&Obj1GAA);
			int	Obj2GAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_cs_hotdog_02"), true); ENTITY::DELETE_ENTITY(&Obj2GAA);
			int	Obj3GAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_ld_ferris_wheel"), true); ENTITY::DELETE_ENTITY(&Obj3GAA);
			int	Obj88GAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_alien_egg_01"), true); ENTITY::DELETE_ENTITY(&Obj88GAA);
			int	Obj4GAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_cs_tv_stand"), true); ENTITY::DELETE_ENTITY(&Obj4GAA);
			int	Obj5GAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_tv_02"), true); ENTITY::DELETE_ENTITY(&Obj5GAA);
			int	Obj6GAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_tv_03_overlay"), true); ENTITY::DELETE_ENTITY(&Obj6GAA);
			int	Obj7GAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_tv_04"), true); ENTITY::DELETE_ENTITY(&Obj7GAA);
			int	Obj8GSD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_tv_06"), true); ENTITY::DELETE_ENTITY(&Obj8GSD);
			int	Obj9GSD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_tv_07"), true); ENTITY::DELETE_ENTITY(&Obj9GSD);
			int	Obj4GAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_tv_05"), true); ENTITY::DELETE_ENTITY(&Obj4GAAA);
			int	Obj5GAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_busker_hat_01"), true); ENTITY::DELETE_ENTITY(&Obj5GAAA);
			int	Obj6GAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_ld_hat_01"), true); ENTITY::DELETE_ENTITY(&Obj6GAAA);
			int	Obj7GAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_spray_backpack_01"), true); ENTITY::DELETE_ENTITY(&Obj7GAAA);
			int	Obj8GSDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_welding_mask_01"), true); ENTITY::DELETE_ENTITY(&Obj8GSDD);
			int	Obj9GSDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_headset_01"), true); ENTITY::DELETE_ENTITY(&Obj9GSDD);
			int	Obj4GAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bin_01"), true); ENTITY::DELETE_ENTITY(&Obj4GAAAA);
			int	Obj5GAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bin_02"), true); ENTITY::DELETE_ENTITY(&Obj5GAAAA);
			int	Obj6AAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bush_01_a"), true); ENTITY::DELETE_ENTITY(&Obj6AAAA);
			int	Obj7AAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bush_02_a"), true); ENTITY::DELETE_ENTITY(&Obj7AAAA);
			int	Obj8SDDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bush_02_b"), true); ENTITY::DELETE_ENTITY(&Obj8SDDD);
			int	Obj9SDDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bush_03"), true); ENTITY::DELETE_ENTITY(&Obj9SDDD);
			int	Obj4AAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bush_04"), true); ENTITY::DELETE_ENTITY(&Obj4AAAAA);
			int	Obj5AAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bush_04b"), true); ENTITY::DELETE_ENTITY(&Obj5AAAAA);
			int	Obj6AAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_diggerbkt_01"), true); ENTITY::DELETE_ENTITY(&Obj6AAAAA);
			int	Obj7AAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_facgate_01"), true); ENTITY::DELETE_ENTITY(&Obj7AAAAA);
			int	Obj8SDDDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_air_bigradar_l1"), true); ENTITY::DELETE_ENTITY(&Obj8SDDDD);
			int	Obj9SDDDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_air_bigradar_l2"), true); ENTITY::DELETE_ENTITY(&Obj9SDDDD);
			int	Obj4AAAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_beach_fire"), true); ENTITY::DELETE_ENTITY(&Obj4AAAAAA);
			int	Obj5AAAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_air_radar_01"), true); ENTITY::DELETE_ENTITY(&Obj5AAAAAA);
			int	Obj6AAAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_xmas_tree_int"), true); ENTITY::DELETE_ENTITY(&Obj6AAAAAA);
			int	Obj7AAAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_xmas_ext"), true); ENTITY::DELETE_ENTITY(&Obj7AAAAAA);
			int	Obj8SDDDDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_gas_mask_hang_01"), true); ENTITY::DELETE_ENTITY(&Obj8SDDDDD);
			int	Obj9SDDDDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_player_gasmask"), true); ENTITY::DELETE_ENTITY(&Obj9SDDDDD);
			int	Obj10SDDDDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("p_spinning_anus_s"), true); ENTITY::DELETE_ENTITY(&Obj10SDDDDD);
		}
	}
	if (AttachObjectsProtection2)
	{
		int Entity = ENTITY::GET_ENTITY_ATTACHED_TO(PLAYER::GET_PLAYER_PED(selectedPlayer));
		int  Object = ENTITY::GET_ENTITY_MODEL(Entity);
		Vector3 Coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true);
		float coordsB[3] = { Coords.x,Coords.y,Coords.z + 0.8 };
		float coordsC[3] = { Coords.x,Coords.y,Coords.z + 0.9 };
		float coordsD[3] = { Coords.x,Coords.y,Coords.z + 0.10 };
		float coordsE[3] = { Coords.x,Coords.y,Coords.z + 1.0 };
		float coordsF[3] = { Coords.x,Coords.y,Coords.z };
		float coordsXX[3] = { Coords.x,Coords.y,Coords.z + 0.7400 };
		//Props
		if (
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_cs_hotdog_01"), true)
			|| OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_cs_hotdog_02"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_ld_ferris_wheel"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_cs_tv_stand"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_tv_02"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_alien_egg_01"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_tv_03_overlay"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_tv_04"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_tv_06"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_tv_07"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_tv_05"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_busker_hat_01"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_ld_hat_01"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_spray_backpack_01"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_welding_mask_01"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_headset_01"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bin_01"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bin_02"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bush_01_a"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bush_02_a"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bush_02_b"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bush_03"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bush_04"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bush_04b"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_diggerbkt_01"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_facgate_01"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_air_bigradar_l1"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_air_bigradar_l2"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_beach_fire"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_air_radar_01"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_xmas_tree_int"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_xmas_ext"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_gas_mask_hang_01"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_player_gasmask"), true) ||
			OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("p_spinning_anus_s"), true))
		{
			int	Obj1GAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_cs_hotdog_01"), true); ENTITY::DELETE_ENTITY(&Obj1GAA);
			int	Obj2GAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_cs_hotdog_02"), true); ENTITY::DELETE_ENTITY(&Obj2GAA);
			int	Obj3GAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_ld_ferris_wheel"), true); ENTITY::DELETE_ENTITY(&Obj3GAA);
			int	Obj88GAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_alien_egg_01"), true); ENTITY::DELETE_ENTITY(&Obj88GAA);
			int	Obj4GAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_cs_tv_stand"), true); ENTITY::DELETE_ENTITY(&Obj4GAA);
			int	Obj5GAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_tv_02"), true); ENTITY::DELETE_ENTITY(&Obj5GAA);
			int	Obj6GAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_tv_03_overlay"), true); ENTITY::DELETE_ENTITY(&Obj6GAA);
			int	Obj7GAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_tv_04"), true); ENTITY::DELETE_ENTITY(&Obj7GAA);
			int	Obj8GSD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_tv_06"), true); ENTITY::DELETE_ENTITY(&Obj8GSD);
			int	Obj9GSD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_tv_07"), true); ENTITY::DELETE_ENTITY(&Obj9GSD);
			int	Obj4GAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_tv_05"), true); ENTITY::DELETE_ENTITY(&Obj4GAAA);
			int	Obj5GAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_busker_hat_01"), true); ENTITY::DELETE_ENTITY(&Obj5GAAA);
			int	Obj6GAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_ld_hat_01"), true); ENTITY::DELETE_ENTITY(&Obj6GAAA);
			int	Obj7GAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_spray_backpack_01"), true); ENTITY::DELETE_ENTITY(&Obj7GAAA);
			int	Obj8GSDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_welding_mask_01"), true); ENTITY::DELETE_ENTITY(&Obj8GSDD);
			int	Obj9GSDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_headset_01"), true); ENTITY::DELETE_ENTITY(&Obj9GSDD);
			int	Obj4GAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bin_01"), true); ENTITY::DELETE_ENTITY(&Obj4GAAAA);
			int	Obj5GAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bin_02"), true); ENTITY::DELETE_ENTITY(&Obj5GAAAA);
			int	Obj6AAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bush_01_a"), true); ENTITY::DELETE_ENTITY(&Obj6AAAA);
			int	Obj7AAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bush_02_a"), true); ENTITY::DELETE_ENTITY(&Obj7AAAA);
			int	Obj8SDDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bush_02_b"), true); ENTITY::DELETE_ENTITY(&Obj8SDDD);
			int	Obj9SDDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bush_03"), true); ENTITY::DELETE_ENTITY(&Obj9SDDD);
			int	Obj4AAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bush_04"), true); ENTITY::DELETE_ENTITY(&Obj4AAAAA);
			int	Obj5AAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_bush_04b"), true); ENTITY::DELETE_ENTITY(&Obj5AAAAA);
			int	Obj6AAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_diggerbkt_01"), true); ENTITY::DELETE_ENTITY(&Obj6AAAAA);
			int	Obj7AAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_snow_facgate_01"), true); ENTITY::DELETE_ENTITY(&Obj7AAAAA);
			int	Obj8SDDDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_air_bigradar_l1"), true); ENTITY::DELETE_ENTITY(&Obj8SDDDD);
			int	Obj9SDDDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_air_bigradar_l2"), true); ENTITY::DELETE_ENTITY(&Obj9SDDDD);
			int	Obj4AAAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_beach_fire"), true); ENTITY::DELETE_ENTITY(&Obj4AAAAAA);
			int	Obj5AAAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_air_radar_01"), true); ENTITY::DELETE_ENTITY(&Obj5AAAAAA);
			int	Obj6AAAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_xmas_tree_int"), true); ENTITY::DELETE_ENTITY(&Obj6AAAAAA);
			int	Obj7AAAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_xmas_ext"), true); ENTITY::DELETE_ENTITY(&Obj7AAAAAA);
			int	Obj8SDDDDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_gas_mask_hang_01"), true); ENTITY::DELETE_ENTITY(&Obj8SDDDDD);
			int	Obj9SDDDDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("prop_player_gasmask"), true); ENTITY::DELETE_ENTITY(&Obj9SDDDDD);
			int	Obj10SDDDDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x, Coords.y, Coords.z + 0.6, 1.0f, GAMEPLAY::GET_HASH_KEY("p_spinning_anus_s"), true); ENTITY::DELETE_ENTITY(&Obj10SDDDDD);
		}
	}
	if (spectatormode)
	{
		if (spectatormode1)//Set up
		{
			SpecModePosition = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), false);
			ENTITY::SET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID(), 0, 0);
			spectatormode1 = false;
		}
		else
		{
			int PlayerID = SpawnedObject[SelectedObject];
			char buffer[100];
			memset(buffer, 0, sizeof(buffer));
			snprintf(buffer, 100, "Free Camera");
			Draw_TextEliteMods(buffer, 0, 0.5, 0.1, 0.4, 0.4, 255, 255, 255, 255, true, true, true);

			if (PlayerID != 0 && PlayerID != PLAYER::PLAYER_PED_ID())
			{
				Vector3 PlayerLoc = ENTITY::GET_ENTITY_COORDS(PlayerID, true);
				PlayerLoc.z += 2;
				PlayerLoc.x -= 2;
				PlayerLoc.y -= 2;
				ENTITY::SET_ENTITY_COORDS2(PLAYER::PLAYER_PED_ID(), PlayerLoc.x, PlayerLoc.y, PlayerLoc.z, false, false, true, true);
			}
			else
			{
				Vector3 Location = { 707.365, 1045.961, 348.909 };
				ENTITY::SET_ENTITY_COORDS2(PLAYER::PLAYER_PED_ID(), Location.x, Location.y, Location.z, true, false, false, true);
			}
		}
	}
	if (spectatormode2)
	{
		ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), SpecModePosition.x, SpecModePosition.y, SpecModePosition.z, true, false, false, true);
		ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), false);
		ENTITY::SET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID(), 255, 255);
		spectatormode2 = false;
	}
	if (SPECTATE == true)
	{
		AIWanderCar(PLAYER::PLAYER_PED_ID());
		SpectateMode(true, PLAYER::GET_PLAYER_PED(selectedPlayer));
	}
	if (SPECTATE == false)
	{
		AI::CLEAR_PED_TASKS(PLAYER::PLAYER_ID());
		SpectateMode(false, PLAYER::GET_PLAYER_PED(selectedPlayer));
	}
	if (invisibleveh == true)
	{
		int vehicle;
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
		{
			vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			ENTITY::SET_ENTITY_VISIBLE(vehicle, false);
		}
	}
	if (invisibleveh == false)
	{
		int vehicle;
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
		{
			vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			ENTITY::SET_ENTITY_VISIBLE(vehicle, true);
		}
	}
	if (AdvOpt)
	{
		CONTROLS::DISABLE_CONTROL_ACTION(0, 19);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 20);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 21);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 27);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 54);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 123);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 124);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 125);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 126);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 138);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 139);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 140);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 177);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 178);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 179);
		CONTROLS::DISABLE_CONTROL_ACTION(0, 207);
		CONTROLS::SET_INPUT_EXCLUSIVE(2, 166);
		CONTROLS::SET_INPUT_EXCLUSIVE(2, 167);
		CONTROLS::SET_INPUT_EXCLUSIVE(2, 177);
		CONTROLS::SET_INPUT_EXCLUSIVE(2, 178);
		CONTROLS::SET_INPUT_EXCLUSIVE(2, 193);
		CONTROLS::SET_INPUT_EXCLUSIVE(2, 194);
		CONTROLS::SET_INPUT_EXCLUSIVE(2, 195);
		CONTROLS::SET_INPUT_EXCLUSIVE(2, 202);
		CONTROLS::SET_INPUT_EXCLUSIVE(2, 203);
		CONTROLS::SET_INPUT_EXCLUSIVE(2, 204);
		CONTROLS::SET_INPUT_EXCLUSIVE(2, 205);

		ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), false);

		coordsToggle();
		if (IsTimerReady2())
		{
			addInstruction(BUTTON_B, "Leave");
			addInstruction(BUTTON_DPAD_RIGHT, "+ X");
			addInstruction(BUTTON_DPAD_LEFT, "- X");
			addInstruction(BUTTON_DPAD_UP, "+ Y");
			addInstruction(BUTTON_DPAD_DOWN, "- Y");
			addInstruction(BUTTON_RB, "Move Down");
			addInstruction(BUTTON_LB, "Move Up");
			addInstruction(BUTTON_RT, "Move + Yaw");
			addInstruction(BUTTON_LT, "Move - Yaw");
			addInstruction(BUTTON_RSTICK, "Freeze");
			addInstruction(BUTTON_LSTICK, "UnFreeze");
			addInstruction(BUTTON_X, "Drop Money");
			instructionsClose();
			ResetTimer2();
		}
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_B))
		{
			changeSubmenu(Object_Movement);
			ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true);
			AdvOpt = false;
			spectatormode = false;
			spectatormode1 = false;
			spectatormode2 = false;
		}
		if (CONTROLS::IS_CONTROL_PRESSED(0, Dpad_Left))
		{
			if (ENTITY::DOES_ENTITY_EXIST(SpawnedObject[SelectedObject]));
			{
				moveEntityX_Plus(SpawnedObject[SelectedObject]);
			}
		}

		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_R3))
		{
			if (ENTITY::DOES_ENTITY_EXIST(SpawnedObject[SelectedObject]));
			{
				freezeEntity(SpawnedObject[SelectedObject]);
			}
		}
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_L3))
		{
			if (ENTITY::DOES_ENTITY_EXIST(SpawnedObject[SelectedObject]));
			{
				unfreezeEntity(SpawnedObject[SelectedObject]);
			}
		}
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_X))
		{
			if (ENTITY::DOES_ENTITY_EXIST(SpawnedObject[SelectedObject]));
			{
				if (ENTITY::DOES_ENTITY_EXIST(SpawnedObject[SelectedObject])) {
					RequestNetworkControl(SpawnedObject[SelectedObject]);
					Vector3 coords = ENTITY::GET_ENTITY_COORDS(SpawnedObject[SelectedObject], 1);
					STREAMING::REQUEST_MODEL(0x113FD533);
					if (STREAMING::HAS_MODEL_LOADED(0x113FD533))
					{
						OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y, coords.z, 0, 40000, 0x113FD533, 0, 1);
						OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y, coords.z, 0, 40000, 0x113FD533, 0, 1);
						OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y, coords.z, 0, 40000, 0x113FD533, 0, 1);
						OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y, coords.z, 0, 40000, 0x113FD533, 0, 1);
					}
				}
			}
		}
		if (CONTROLS::IS_CONTROL_PRESSED(0, Dpad_Right))
		{
			if (ENTITY::DOES_ENTITY_EXIST(SpawnedObject[SelectedObject]));
			{
				moveEntityX_Min(SpawnedObject[SelectedObject]);
			}
		}
		if (CONTROLS::IS_CONTROL_PRESSED(0, Dpad_Down))
		{
			if (ENTITY::DOES_ENTITY_EXIST(SpawnedObject[SelectedObject]));
			{
				moveEntityY_Plus(SpawnedObject[SelectedObject]);
			}
		}
		if (CONTROLS::IS_CONTROL_PRESSED(0, Dpad_Up))
		{
			if (ENTITY::DOES_ENTITY_EXIST(SpawnedObject[SelectedObject]));
			{
				moveEntityY_Min(SpawnedObject[SelectedObject]);
			}
		}
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_R1))
		{
			if (ENTITY::DOES_ENTITY_EXIST(SpawnedObject[SelectedObject]));
			{
				moveEntityZ_Plus(SpawnedObject[SelectedObject]);
			}
		}
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_L1))
		{
			if (ENTITY::DOES_ENTITY_EXIST(SpawnedObject[SelectedObject]));
			{
				moveEntityZ_Min(SpawnedObject[SelectedObject]);
			}
		}
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_R2))
		{
			if (ENTITY::DOES_ENTITY_EXIST(SpawnedObject[SelectedObject]));
			{
				changeEntityYaw_Plus(SpawnedObject[SelectedObject]);
			}
		}
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_L2))
		{
			if (ENTITY::DOES_ENTITY_EXIST(SpawnedObject[SelectedObject]));
			{
				changeEntityYaw_Min(SpawnedObject[SelectedObject]);
			}
		}
	}
	if (neverwanted)
		PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 0, false);
	if (superjump)
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());
	if (animNeeded)
	{

		if (STREAMING::HAS_ANIM_DICT_LOADED(animSetToDo))
		{
			AI::TASK_PLAY_ANIM(pedToDoAnimOn, animSetToDo, animNameToDo, 8.0f, 0.0f, -1, 9, 0.0f, false, false, false);
			animNeeded = false;
		}
	}
	if (Neons_)
	{
		drawneons(NeonR, NeonG, NeonB);
	}
	if (LoopNeons_)
	{
		NeonR = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255); NeonG = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 150); NeonB = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 100);
	}
	if (pinfo)
	{
		/*DRAW ENTITY OF PLAYER VISUAL*/
		//ARROWS
		int maker = 22;
		float maker2 = 1.40;
		Vector3 Loc = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 0.0, 0.0, 1.5f);
		GRAPHICS::DRAW_MARKER(maker, Loc.x, Loc.y, Loc.z, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f, 0.0f, 0.7f, 0.7f, 0.7f, 0, 50, 255, 50, 1, 1, 2, 1, 0, 0, 0);
		int maker1 = 27;
		float maker12 = -2.46;
		GRAPHICS::DRAW_MARKER(maker1, Loc.x, Loc.y, Loc.z + maker12, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f, 0.0f, 0.7f, 0.7f, 0.7f, 0, 50, 255, 50, 0, 1, 2, 1, 0, 0, 0);
		//LINE
		Vector3 Pos777;
		Vector3 Pos2;
		int PedID = PLAYER::GET_PLAYER_PED(selectedPlayer);
		Pos777 = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
		Pos2 = ENTITY::GET_ENTITY_COORDS(PedID, false);
		GRAPHICS::DRAW_LINE(Pos777.x, Pos777.y, Pos777.z, Pos2.x, Pos2.y, Pos2.z, 0, 50, 255, 255);
		/*DRAW PLAYER INFO*/
		int playerHealt = ENTITY::GET_ENTITY_HEALTH(PLAYER::GET_PLAYER_PED(selectedPlayer));
		Vector3 Pos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 1);
		int playerCar = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(selectedPlayer), 0);
		int thisPlayersCar = ENTITY::GET_ENTITY_MODEL(playerCar);
		char buf[1000];
		char buf2[1000];

		snprintf(buf2, sizeof(buf2), "~w~Player Name: ~s~%s", PLAYER::GET_PLAYER_NAME(selectedPlayer));
		drawTextxxx2(buf2, 0, 0.2f, 0.775f, Subx2, Suby2, 0, 50, 255, 255, false);

		snprintf(buf, sizeof(buf), "~w~Position: ~s~X = %f, Y = %f, Z = %f", Pos.x, Pos.y, Pos.z);
		drawTextxxx2(buf, 0, 0.2f, 0.80f, Subx2, Suby2, 0, 50, 255, 255, false);

		snprintf(buf2, sizeof(buf2), "~w~Vehicle: ~s~%s", VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(thisPlayersCar));
		drawTextxxx2(buf2, 0, 0.2f, 0.825f, Subx2, Suby2, 0, 50, 255, 255, false);

		{
			if (NETWORK::NETWORK_PLAYER_HAS_HEADSET(selectedPlayer))
			{
				char buf[30];
				snprintf(buf, sizeof(buf), "~w~Headset: ~s~Has Headset");
				drawTextxxx2(buf, 0, 0.2f, 0.85f, Subx2, Suby2, 0, 50, 255, 255, false);
			}

			else if (!NETWORK::NETWORK_PLAYER_HAS_HEADSET(selectedPlayer))
			{
				char buf[30];
				snprintf(buf, sizeof(buf), "~w~Headset: ~s~No Headset");
				drawTextxxx2(buf, 0, 0.2f, 0.85, Subx2, Suby2, 0, 50, 255, 255, false);
			}
		}
		{
			if (NETWORK::NETWORK_IS_PLAYER_MUTED_BY_ME(selectedPlayer))
			{
				char buf[30];
				snprintf(buf, sizeof(buf), "~w~Muted Me: ~s~Yes");
				drawTextxxx2(buf, 0, 0.2f, 0.875, Subx2, Suby2, 0, 50, 255, 255, false);
			}

			else if (!NETWORK::NETWORK_IS_PLAYER_MUTED_BY_ME(selectedPlayer))
			{
				char buf[30];
				snprintf(buf, sizeof(buf), "~w~Muted Me: ~s~No");
				drawTextxxx2(buf, 0, 0.2f, 0.875, Subx2, Suby2, 0, 50, 255, 255, false);
			}
		}
	}
	if (PrintHeadset) // Put this inside hook
	{
		if (NETWORK::NETWORK_PLAYER_HAS_HEADSET(onlinePlayerinfo1))
		{
			//drawText("YES", itemfont, 0.32, 0.9, 0.5f, 0.5f, infor, infog, infob, 255, true);
			PrintToScreen("YES", 0.32, 0.9, infor, infog, infob, 255, 0.5f, 0.5f, 0, itemfont);
			//drawText("Headset:", itemfont, 0.28f, 0.9, 0.5f, 0.5f, 255, 255, 255, 255, true);
			PrintToScreen("Headset:", 0.28f, 0.9, 255, 255, 255, 255, 0.5f, 0.5f, 0, itemfont);
		}

		else if (!NETWORK::NETWORK_PLAYER_HAS_HEADSET(onlinePlayerinfo1))
		{
			//drawText("NO", itemfont, 0.32, 0.9, 0.5f, 0.5f, infor, infog, infob, 255, true);
			PrintToScreen("NO", 0.32, 0.9, infor, infog, infob, 255, 0.5f, 0.5f, 0, itemfont);
			//drawText("Headset:", itemfont, 0.28f, 0.9, 0.5f, 0.5f, 255, 255, 255, 255, true);
			PrintToScreen("Headset:", 0.28f, 0.9, 255, 255, 255, 255, 0.5f, 0.5f, 0, itemfont);
		}
	}

	if (ModShop)
	{

	}

	if (ModShop2)
	{

	}

	if (Toggle_XMas)
	{
		GAMEPLAY::SET_OVERRIDE_WEATHER("XMAS");
		if (!STREAMING::_HAS_DLC_PTFX_LOADED("core_snow"))
			STREAMING::_REQUEST_DLC_PTFX_ASSET("core_snow");
		Vector3 PedCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2("core_snow", PedCoords.x, PedCoords.y, PedCoords.z, 0.0f, 0.0f, 0.0f, 1, 0, 0, 0);

	}
	if (Toggle_Lower)
	{
		int myhandle = PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID());
		int myvehicle;
		if (PED::IS_PED_IN_ANY_VEHICLE(myhandle, 0))
		{
			myvehicle = PED::GET_VEHICLE_PED_IS_IN(myhandle, 0);
			if (ENTITY::DOES_ENTITY_EXIST(myvehicle) && ENTITY::IS_ENTITY_A_VEHICLE(myvehicle))
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(myvehicle, true, 0, 0, -0.10, 0, 0, 0, true, true, true, true, false, true);
			}
		}
	}
	if (Toggle_Lower2)
	{
		int LeftRight = CONTROLS::GET_CONTROL_VALUE(0, 188);
		int UpDown = CONTROLS::GET_CONTROL_VALUE(0, 189);
		int VehicleHandle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(VehicleHandle))
		{
			if (UpDown == 254)
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(VehicleHandle, 1, 0, 0, 0.068, 0, 3.05, 0, 1, 1, 1, 1, 0, 1);
			}
			if (UpDown == 0)
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(VehicleHandle, 1, 0, 0, 0.068, 0, -3.05, 0, 1, 1, 1, 1, 0, 1);
			}
			if (LeftRight == 254)
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(VehicleHandle, 1, 0, 0, 0.13, 0.98, 0, 0, 1, 1, 1, 1, 0, 1);
			}
			if (LeftRight == 0)
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(VehicleHandle, 1, 0, 0, 0.13, -0.98, 0, 0, 1, 1, 1, 1, 0, 1);
			}
		}
	}
	if (Toggle_RainBowCar)
	{
		Primary_Paint = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255),
			Primary_Paint2 = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255),
			Primary_Paint3 = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255);
		Secondary_Paint3 = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255),
			Secondary_Paint4 = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255),
			Secondary_Paint5 = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255);
		CPaintMenu = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(CPaintMenu, Primary_Paint, Primary_Paint2, Primary_Paint3);
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(CPaintMenu, Secondary_Paint3, Secondary_Paint4, Secondary_Paint5);
	}

	if (Drive_On_Water)
	{
		VehicleID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		Vector3 mycoords = ENTITY::GET_ENTITY_COORDS(VehicleID, 1);
		mycoords.z = mycoords.z - 2.75;
		mycoords.x = mycoords.x - 3;
		obj = GAMEPLAY::GET_HASH_KEY("prop_ld_ferris_wheel");
		waterobj = OBJECT::CREATE_OBJECT(obj, mycoords.x, mycoords.y, mycoords.z, 1, 1, 0);
		ENTITY::SET_ENTITY_VISIBLE(waterobj, false);
	}
	if (vehicleOnlineSpawnNeeded)
	{
		if (STREAMING::HAS_MODEL_LOADED(vehicleToSpawnHash))
		{
			char *PedVehicle;
			PedVehicle = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(onlinePlayerinfo1), 0)));
			Ped ped = PLAYER::GET_PLAYER_PED(selectedPlayer);
			Vector3 Vehcoords = ENTITY::GET_ENTITY_COORDS(ped, false);
			Vehicle vehicle = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, Vehcoords.x + 2.0f, Vehcoords.y, Vehcoords.z, 0.0f, true, false);
			if (ENTITY::DOES_ENTITY_EXIST(vehicle))
			{
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehicleToSpawnHash);
				vehicleOnlineSpawnNeeded = false;
			}
		}
	}
	if (vehicleOnlineSpawnNeededCrash)
	{
		if (STREAMING::HAS_MODEL_LOADED(vehicleToSpawnHash))
		{
			char *PedVehicle;
			PedVehicle = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(onlinePlayerinfo1), 0)));
			Ped ped = PLAYER::GET_PLAYER_PED(selectedPlayer);
			Vector3 Vehcoords = ENTITY::GET_ENTITY_COORDS(ped, false);
			Vehicle vehicle;
			vehicle = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, Vehcoords.x + 2.0f, Vehcoords.y, Vehcoords.z, 0.0f, true, false);
			vehicle = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, Vehcoords.x + 2.0f, Vehcoords.y, Vehcoords.z, 0.0f, true, false);
			vehicle = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, Vehcoords.x + 2.0f, Vehcoords.y, Vehcoords.z, 0.0f, true, false);
			vehicle = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, Vehcoords.x + 2.0f, Vehcoords.y, Vehcoords.z, 0.0f, true, false);
			vehicle = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, Vehcoords.x + 2.0f, Vehcoords.y, Vehcoords.z, 0.0f, true, false);
			vehicle = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, Vehcoords.x + 2.0f, Vehcoords.y, Vehcoords.z, 0.0f, true, false);
			vehicle = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, Vehcoords.x + 2.0f, Vehcoords.y, Vehcoords.z, 0.0f, true, false);
			vehicle = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, Vehcoords.x + 2.0f, Vehcoords.y, Vehcoords.z, 0.0f, true, false);
			vehicle = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, Vehcoords.x + 2.0f, Vehcoords.y, Vehcoords.z, 0.0f, true, false);
			vehicle = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, Vehcoords.x + 2.0f, Vehcoords.y, Vehcoords.z, 0.0f, true, false);
			vehicle = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, Vehcoords.x + 2.0f, Vehcoords.y, Vehcoords.z, 0.0f, true, false);
			vehicle = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, Vehcoords.x + 2.0f, Vehcoords.y, Vehcoords.z, 0.0f, true, false);
			vehicle = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, Vehcoords.x + 2.0f, Vehcoords.y, Vehcoords.z, 0.0f, true, false);
			vehicle = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, Vehcoords.x + 2.0f, Vehcoords.y, Vehcoords.z, 0.0f, true, false);
			vehicle = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, Vehcoords.x + 2.0f, Vehcoords.y, Vehcoords.z, 0.0f, true, false);
			vehicle = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, Vehcoords.x + 2.0f, Vehcoords.y, Vehcoords.z, 0.0f, true, false);
			vehicle = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, Vehcoords.x + 2.0f, Vehcoords.y, Vehcoords.z, 0.0f, true, false);
			vehicle = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, Vehcoords.x + 2.0f, Vehcoords.y, Vehcoords.z, 0.0f, true, false);
			vehicle = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, Vehcoords.x + 2.0f, Vehcoords.y, Vehcoords.z, 0.0f, true, false);
			vehicle = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, Vehcoords.x + 2.0f, Vehcoords.y, Vehcoords.z, 0.0f, true, false);
			if (ENTITY::DOES_ENTITY_EXIST(vehicle))
			{
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehicleToSpawnHash);
				vehicleOnlineSpawnNeededCrash = false;
			}
		}
	}
	if (vehicleOnlineAllSpawnNeeded)
	{
		if (STREAMING::HAS_MODEL_LOADED(vehicleToSpawnHash))
		{
			char *PedVehicle;
			int i = 0;
			int Handle;
			for (i = 0; i<16; i++)
			{
				if (i == PLAYER::PLAYER_ID()) continue;
				Handle = PLAYER::GET_PLAYER_PED(i);
				if (!ENTITY::DOES_ENTITY_EXIST(Handle)) continue;
				PedVehicle = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(onlinePlayerinfo1), 0)));
				Ped ped = PLAYER::GET_PLAYER_PED(i);
				Vector3 Vehcoords = ENTITY::GET_ENTITY_COORDS(ped, false);
				Vehicle vehicle = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, Vehcoords.x + 2.0f, Vehcoords.y, Vehcoords.z, 0.0f, true, false);
				if (ENTITY::DOES_ENTITY_EXIST(vehicle))
				{
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehicleToSpawnHash);
					vehicleOnlineAllSpawnNeeded = false;
				}
			}
		}
	}
	if (MoveObjectUp_Loop)
	{
		if (ENTITY::DOES_ENTITY_EXIST(objecthandle))
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(objecthandle);
			Vector3 coords;
			coords = ENTITY::GET_ENTITY_COORDS(objecthandle, 1);
			objectcoordz = coords.z;
			objectcoordz += 0.1;
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(objecthandle);
			ENTITY::SET_ENTITY_COORDS(objecthandle, coords.x, coords.y, objectcoordz, 1, 0, 0, 1);
		}
	}
	if (MoveObjectDown_Loop)
	{
		if (ENTITY::DOES_ENTITY_EXIST(objecthandle))
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(objecthandle);
			Vector3 coords2;
			coords2 = ENTITY::GET_ENTITY_COORDS(objecthandle, 1);
			objectcoordz = coords2.z;
			objectcoordz -= 0.1;
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(objecthandle);
			ENTITY::SET_ENTITY_COORDS(objecthandle, coords2.x, coords2.y, objectcoordz, 1, 0, 0, 1);
		}
	}
	if (ShootBulletAPlayer)
	{
		Vector3 mycoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		Vector3 pcoords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 1);
		int hash;
		hash = GAMEPLAY::GET_HASH_KEY(BulletAtPlayerString);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(mycoords.x, mycoords.y, mycoords.z, pcoords.x, pcoords.y, pcoords.z, 0, 0, hash, PLAYER::PLAYER_PED_ID(), 0, 0, 500);
		ShootBulletAPlayer = false;
	}
	if (Explosions)
	{
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 1);
		FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, ExplosionType, 100.0f, 1, 0, 5);
		Explosions = false;
	}
	if (ObjectSpawnerVeh)
	{
		if (STREAMING::HAS_MODEL_LOADED(ObjectType))
		{
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
			Object Object = OBJECT::CREATE_OBJECT(ObjectType, coords.x, coords.y, coords.z, 1, 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(Object))
			{
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(ObjectType);
				ObjectSpawnerVeh = false;
			}
		}
	}
	if (ShootRockets)
	{
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_X))
		{
			int VehicleHandle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			int launchDistance = 250;
			int weaponHash = GAMEPLAY::GET_HASH_KEY("WEAPON_VEHICLE_ROCKET");
			int launchSpeed = 1500.0f;
			float idkcoords1[] = { 0.6f, 0.6707f, 0.3711f };
			Vector3 getcoords1 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords1[0], idkcoords1[1], idkcoords1[2]);
			float idkcoords2[] = { -0.6f, 0.6707f, 0.3711f };
			Vector3 getcoords2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords2[0], idkcoords2[1], idkcoords2[2]);
			float idkcoords3[] = { 0.6f, 5.0707f, 0.3711f };
			Vector3 getcoords3 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords3[0], idkcoords3[1], idkcoords3[2]);
			float idkcoords4[] = { -0.6f, 5.0707f, 0.3711f };
			Vector3 getcoords4 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords4[0], idkcoords4[1], idkcoords4[2]);
			float coords1[] = { getcoords1.x, getcoords1.y, getcoords1.z };
			float coords2[] = { getcoords2.x, getcoords2.y, getcoords2.z };
			float coords3[] = { getcoords3.x, getcoords3.y, getcoords3.z };
			float coords4[] = { getcoords4.x, getcoords4.y, getcoords4.z };
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1[0], coords1[1], coords1[2], coords3[0], coords3[1], coords3[2], launchDistance, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords2[0], coords2[1], coords2[2], coords4[0], coords4[1], coords4[2], launchDistance, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
		}
	}
	if (neverwantedonline)
	{
		PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 1);
		PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::GET_PLAYER_PED(selectedPlayer), 1);
	}
	if (neverwantedonlineall)
	{
		int i = 0;
		int Handle;
		for (i = 0; i < 16; i++)
		{
			if (i == PLAYER::PLAYER_ID()) continue;
			Handle = PLAYER::GET_PLAYER_PED(i);
			if (!ENTITY::DOES_ENTITY_EXIST(Handle)) continue;
			float angle = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, MoneyRange_) * 3.14159265359;
			float radius = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, MoneyRange_) * 5.0f;
			float x = ENTITY::GET_ENTITY_COORDS(Handle, true).x + radius * SYSTEM::COS(angle);
			float y = ENTITY::GET_ENTITY_COORDS(Handle, true).y + radius * SYSTEM::SIN(angle);
			STREAMING::REQUEST_MODEL(0x113FD533);
			if (STREAMING::HAS_MODEL_LOADED(0x113FD533))
			{
				OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(i), true).z + moneyzcoord, 0, amount, 0x113FD533, 0, 1);
			}
		}
	}
	if (funnytest)
	{
		creatorRocketRTLoop();
	}
	if (givemoneygun)
	{
		if (PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED(selectedPlayer)))
		{
			Vector3 PlayerPos;
			if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD2(PLAYER::GET_PLAYER_PED(selectedPlayer), &PlayerPos))
			{
				STREAMING::REQUEST_MODEL(0x113FD533);
				if (STREAMING::HAS_MODEL_LOADED(0x113FD533))
				{
					OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, PlayerPos.x, PlayerPos.y, PlayerPos.z, 0, 40000, 0x113FD533, 0, 1);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(0x113FD533);
				}
			}

		}
	}
	if (givebullets)
	{
		if (PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED(selectedPlayer)))
		{
			Vector3 PlayerPos;
			WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD2(PLAYER::GET_PLAYER_PED(selectedPlayer), &PlayerPos);
			FIRE::ADD_EXPLOSION(PlayerPos.x, PlayerPos.y, PlayerPos.z, PLANE, 0.5f, true, true, 1.0f);

		}
	}
	if (ShootGreenLazers)
	{
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_X))
		{
			int VehicleHandle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			int launchDistance = 250;
			int weaponHash = 0xE2822A29;
			int weaponHash2 = 0xEFFD014B;
			int launchSpeed = 1500.0f;
			float idkcoords1[] = { 0.6f, 0.6707f, 0.3711f };
			Vector3 getcoords1 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords1[0], idkcoords1[1], idkcoords1[2]);
			float idkcoords2[] = { -0.6f, 0.6707f, 0.3711f };
			Vector3 getcoords2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords2[0], idkcoords2[1], idkcoords2[2]);
			float idkcoords3[] = { 0.6f, 5.0707f, 0.3711f };
			Vector3 getcoords3 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords3[0], idkcoords3[1], idkcoords3[2]);
			float idkcoords4[] = { -0.6f, 5.0707f, 0.3711f };
			Vector3 getcoords4 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords4[0], idkcoords4[1], idkcoords4[2]);
			float coords1[] = { getcoords1.x, getcoords1.y, getcoords1.z };
			float coords2[] = { getcoords2.x, getcoords2.y, getcoords2.z };
			float coords3[] = { getcoords3.x, getcoords3.y, getcoords3.z };
			float coords4[] = { getcoords4.x, getcoords4.y, getcoords4.z };
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1[0], coords1[1], coords1[2], coords3[0], coords3[1], coords3[2], launchDistance, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords2[0], coords2[1], coords2[2], coords4[0], coords4[1], coords4[2], launchDistance, 0, weaponHash2, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1[0], coords1[1], coords1[2], coords3[0], coords3[1], coords3[2], launchDistance, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords2[0], coords2[1], coords2[2], coords4[0], coords4[1], coords4[2], launchDistance, 0, weaponHash2, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
		}
	}
	if (ShootRedLazers)
	{
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_X))
		{
			int VehicleHandle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			int launchDistance = 250;
			int weaponHash = 0xE2822A29;
			int weaponHash2 = 0x5D6660AB;
			int launchSpeed = 1500.0f;
			float idkcoords1[] = { 0.6f, 0.6707f, 0.3711f };
			Vector3 getcoords1 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords1[0], idkcoords1[1], idkcoords1[2]);
			float idkcoords2[] = { -0.6f, 0.6707f, 0.3711f };
			Vector3 getcoords2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords2[0], idkcoords2[1], idkcoords2[2]);
			float idkcoords3[] = { 0.6f, 5.0707f, 0.3711f };
			Vector3 getcoords3 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords3[0], idkcoords3[1], idkcoords3[2]);
			float idkcoords4[] = { -0.6f, 5.0707f, 0.3711f };
			Vector3 getcoords4 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords4[0], idkcoords4[1], idkcoords4[2]);
			float coords1[] = { getcoords1.x, getcoords1.y, getcoords1.z };
			float coords2[] = { getcoords2.x, getcoords2.y, getcoords2.z };
			float coords3[] = { getcoords3.x, getcoords3.y, getcoords3.z };
			float coords4[] = { getcoords4.x, getcoords4.y, getcoords4.z };
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1[0], coords1[1], coords1[2], coords3[0], coords3[1], coords3[2], launchDistance, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords2[0], coords2[1], coords2[2], coords4[0], coords4[1], coords4[2], launchDistance, 0, weaponHash2, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1[0], coords1[1], coords1[2], coords3[0], coords3[1], coords3[2], launchDistance, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords2[0], coords2[1], coords2[2], coords4[0], coords4[1], coords4[2], launchDistance, 0, weaponHash2, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
		}
	}
	if (ShootFlares)
	{
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_X))
		{
			int VehicleHandle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			int launchDistance = 250;
			int weaponHash = 0x497FACC3;
			int launchSpeed = 1500.0f;
			float idkcoords1[] = { 0.6f, 0.6707f, 0.3711f };
			Vector3 getcoords1 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords1[0], idkcoords1[1], idkcoords1[2]);
			float idkcoords2[] = { -0.6f, 0.6707f, 0.3711f };
			Vector3 getcoords2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords2[0], idkcoords2[1], idkcoords2[2]);
			float idkcoords3[] = { 0.6f, 5.0707f, 0.3711f };
			Vector3 getcoords3 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords3[0], idkcoords3[1], idkcoords3[2]);
			float idkcoords4[] = { -0.6f, 5.0707f, 0.3711f };
			Vector3 getcoords4 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords4[0], idkcoords4[1], idkcoords4[2]);
			float coords1[] = { getcoords1.x, getcoords1.y, getcoords1.z };
			float coords2[] = { getcoords2.x, getcoords2.y, getcoords2.z };
			float coords3[] = { getcoords3.x, getcoords3.y, getcoords3.z };
			float coords4[] = { getcoords4.x, getcoords4.y, getcoords4.z };
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1[0], coords1[1], coords1[2], coords3[0], coords3[1], coords3[2], launchDistance, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords2[0], coords2[1], coords2[2], coords4[0], coords4[1], coords4[2], launchDistance, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
		}
	}
	if (ShootSnowballs)
	{
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_X))
		{
			int VehicleHandle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			int launchDistance = 250;
			int weaponHash = 0x787F0BB;
			int launchSpeed = 1500.0f;
			float idkcoords1[] = { 0.6f, 0.6707f, 0.3711f };
			Vector3 getcoords1 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords1[0], idkcoords1[1], idkcoords1[2]);
			float idkcoords2[] = { -0.6f, 0.6707f, 0.3711f };
			Vector3 getcoords2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords2[0], idkcoords2[1], idkcoords2[2]);
			float idkcoords3[] = { 0.6f, 5.0707f, 0.3711f };
			Vector3 getcoords3 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords3[0], idkcoords3[1], idkcoords3[2]);
			float idkcoords4[] = { -0.6f, 5.0707f, 0.3711f };
			Vector3 getcoords4 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords4[0], idkcoords4[1], idkcoords4[2]);
			float coords1[] = { getcoords1.x, getcoords1.y, getcoords1.z };
			float coords2[] = { getcoords2.x, getcoords2.y, getcoords2.z };
			float coords3[] = { getcoords3.x, getcoords3.y, getcoords3.z };
			float coords4[] = { getcoords4.x, getcoords4.y, getcoords4.z };
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1[0], coords1[1], coords1[2], coords3[0], coords3[1], coords3[2], launchDistance, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords2[0], coords2[1], coords2[2], coords4[0], coords4[1], coords4[2], launchDistance, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
		}
	}
	if (ShootSmokes)
	{
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_X))
		{
			int VehicleHandle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			int launchDistance = 250;
			int weaponHash = 0x4DD2DC56;
			int launchSpeed = 1500.0f;
			float idkcoords1[] = { 0.6f, 0.6707f, 0.3711f };
			Vector3 getcoords1 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords1[0], idkcoords1[1], idkcoords1[2]);
			float idkcoords2[] = { -0.6f, 0.6707f, 0.3711f };
			Vector3 getcoords2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords2[0], idkcoords2[1], idkcoords2[2]);
			float idkcoords3[] = { 0.6f, 5.0707f, 0.3711f };
			Vector3 getcoords3 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords3[0], idkcoords3[1], idkcoords3[2]);
			float idkcoords4[] = { -0.6f, 5.0707f, 0.3711f };
			Vector3 getcoords4 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords4[0], idkcoords4[1], idkcoords4[2]);
			float coords1[] = { getcoords1.x, getcoords1.y, getcoords1.z };
			float coords2[] = { getcoords2.x, getcoords2.y, getcoords2.z };
			float coords3[] = { getcoords3.x, getcoords3.y, getcoords3.z };
			float coords4[] = { getcoords4.x, getcoords4.y, getcoords4.z };
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1[0], coords1[1], coords1[2], coords3[0], coords3[1], coords3[2], launchDistance, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords2[0], coords2[1], coords2[2], coords4[0], coords4[1], coords4[2], launchDistance, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
		}
	}
	if (VehicleMachineguns)
	{
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_X))
		{
			int VehicleHandle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			int launchDistance = 250;
			int weaponHash = 0xF33C83B0;
			int launchSpeed = 1500.0f;
			float idkcoords1[] = { 0.6f, 0.6707f, 0.3711f };
			Vector3 getcoords1 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords1[0], idkcoords1[1], idkcoords1[2]);
			float idkcoords2[] = { -0.6f, 0.6707f, 0.3711f };
			Vector3 getcoords2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords2[0], idkcoords2[1], idkcoords2[2]);
			float idkcoords3[] = { 0.6f, 5.0707f, 0.3711f };
			Vector3 getcoords3 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords3[0], idkcoords3[1], idkcoords3[2]);
			float idkcoords4[] = { -0.6f, 5.0707f, 0.3711f };
			Vector3 getcoords4 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords4[0], idkcoords4[1], idkcoords4[2]);
			float coords1[] = { getcoords1.x, getcoords1.y, getcoords1.z };
			float coords2[] = { getcoords2.x, getcoords2.y, getcoords2.z };
			float coords3[] = { getcoords3.x, getcoords3.y, getcoords3.z };
			float coords4[] = { getcoords4.x, getcoords4.y, getcoords4.z };
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1[0], coords1[1], coords1[2], coords3[0], coords3[1], coords3[2], launchDistance, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords2[0], coords2[1], coords2[2], coords4[0], coords4[1], coords4[2], launchDistance, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
		}
	}
	if (partWater)
	{
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		WATER::MODIFY_WATER(coords.x, coords.y, coords.z, 50);
	}
	if (loop_gta2cam)
	{
		if (CAM::DOES_CAM_EXIST(cam_gta2)) CAM::SET_CAM_ACTIVE(cam_gta2, 1);
		else
		{
			cam_gta2 = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
			CAM::ATTACH_CAM_TO_ENTITY(cam_gta2, PLAYER::PLAYER_PED_ID(), 0.0f, 0.0f, 8.5f, 1);
			Vector3 Pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
			CAM::POINT_CAM_AT_COORD(cam_gta2, Pos.x, Pos.y, -1000000);
			CAM::SET_CAM_ACTIVE(cam_gta2, 1);
		}
		CAM::RENDER_SCRIPT_CAMS(1, 0, 3000, 1, 0);
	}
	else if (CAM::DOES_CAM_EXIST(cam_gta2))
	{
		CAM::SET_CAM_ACTIVE(cam_gta2, 0);
		CAM::DESTROY_CAM(cam_gta2, 0);
		CAM::RENDER_SCRIPT_CAMS(0, 0, 3000, 1, 0);
	}
	if (VehicleFireworks)
	{
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_R3))
		{
			int VehicleHandle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			int launchDistance = 250;
			int weaponHash = 0x7F7497E5;
			int launchSpeed = 1500.0f;
			float idkcoords1[] = { 0.6f, 0.6707f, 0.3711f };
			Vector3 getcoords1 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords1[0], idkcoords1[1], idkcoords1[2]);
			float idkcoords2[] = { -0.6f, 0.6707f, 0.3711f };
			Vector3 getcoords2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords2[0], idkcoords2[1], idkcoords2[2]);
			float idkcoords3[] = { 0.6f, 5.0707f, 0.3711f };
			Vector3 getcoords3 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords3[0], idkcoords3[1], idkcoords3[2]);
			float idkcoords4[] = { -0.6f, 5.0707f, 0.3711f };
			Vector3 getcoords4 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords4[0], idkcoords4[1], idkcoords4[2]);
			float coords1[] = { getcoords1.x, getcoords1.y, getcoords1.z };
			float coords2[] = { getcoords2.x, getcoords2.y, getcoords2.z };
			float coords3[] = { getcoords3.x, getcoords3.y, getcoords3.z };
			float coords4[] = { getcoords4.x, getcoords4.y, getcoords4.z };
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1[0], coords1[1], coords1[2], coords3[0], coords3[1], coords3[2], launchDistance, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords2[0], coords2[1], coords2[2], coords4[0], coords4[1], coords4[2], launchDistance, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
		}
	}
	if (SuperMachineguns)
	{
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_R3))
		{
			int VehicleHandle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			int launchDistance = 250;
			int weaponHash = 0x33058E22;
			int launchSpeed = 1500.0f;
			float idkcoords1[] = { 0.6f, 0.6707f, 0.3711f };
			Vector3 getcoords1 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords1[0], idkcoords1[1], idkcoords1[2]);
			float idkcoords2[] = { -0.6f, 0.6707f, 0.3711f };
			Vector3 getcoords2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords2[0], idkcoords2[1], idkcoords2[2]);
			float idkcoords3[] = { 0.6f, 5.0707f, 0.3711f };
			Vector3 getcoords3 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords3[0], idkcoords3[1], idkcoords3[2]);
			float idkcoords4[] = { -0.6f, 5.0707f, 0.3711f };
			Vector3 getcoords4 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords4[0], idkcoords4[1], idkcoords4[2]);
			float coords1[] = { getcoords1.x, getcoords1.y, getcoords1.z };
			float coords2[] = { getcoords2.x, getcoords2.y, getcoords2.z };
			float coords3[] = { getcoords3.x, getcoords3.y, getcoords3.z };
			float coords4[] = { getcoords4.x, getcoords4.y, getcoords4.z };
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1[0], coords1[1], coords1[2], coords3[0], coords3[1], coords3[2], launchDistance, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords2[0], coords2[1], coords2[2], coords4[0], coords4[1], coords4[2], launchDistance, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
		}
	}
	if (CarGun)
	{
		Ped player = PLAYER::PLAYER_PED_ID();
		if (PED::IS_PED_SHOOTING(player) && !PED::IS_PED_IN_ANY_VEHICLE(player, 1))
		{
			Hash model = 0xB779A091; // adder
			STREAMING::REQUEST_MODEL(model);
			if (STREAMING::HAS_MODEL_LOADED(model))
			{
				Vector3 coords = ENTITY::GET_ENTITY_COORDS(player, 1);
				Vector3 direction = ENTITY::GET_ENTITY_FORWARD_VECTOR(player);
				coords.x += direction.x + 1.0f;
				coords.y += direction.y + 1.0f;
				coords.z += 0.50f;
				Vehicle vehicle = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, ENTITY::GET_ENTITY_HEADING(player), 1, 0);
				ENTITY::_0xD3850671(vehicle, 1);
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(NETWORK::VEH_TO_NET(vehicle), 1);
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, 40.0f);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
			}
		}
	}

	if (GravityGunLoop)
	{
		Player player = PLAYER::PLAYER_ID();
		if (PLAYER::IS_PLAYER_FREE_AIMING(player))
		{
			PLAYER::_GET_AIMED_ENTITY(player, &GravityEntity);
		}
		else
		{
			GravityEntity = 0;
		}
		if (GravityEntity)
		{
			Ped player = PLAYER::PLAYER_PED_ID();
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(player, 1);
			Vector3 direction = ENTITY::GET_ENTITY_FORWARD_VECTOR(player);
			coords.x += direction.x + 2.0f;
			coords.y += direction.y + 2.0f;
			coords.z += 0.50f;
			ENTITY::SET_ENTITY_COORDS(GravityEntity, coords.x, coords.y, coords.z, 1, 1, 1, 1);
		}
	}
	/*
	if(FreezeStungunProtection)
	{
	int i;
	for (i = 0; i <= 16; i++)
	{
	int HashWeap;
	if(PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i),-1469565163) && WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::GET_PLAYER_PED(i)) == 0x3656C8C1)
	{
	PED::SET_PED_AS_COP(PLAYER::GET_PLAYER_PED(i), 1);
	Sleep(20);
	NotifyAboveMap("~r~You are Protected By ~h~XBLZenyle");
	Sleep(10);
	return  WEAPON::REMOVE_WEAPON_FROM_PED(PLAYER::GET_PLAYER_PED(i),0x3656C8C1); Sleep(50);
	}
	}
	}
	if(AttachObjectsProtection)
	{
	int Entity = ENTITY::GET_ENTITY_ATTACHED_TO(PLAYER::PLAYER_PED_ID());
	int  Object = ENTITY::GET_ENTITY_MODEL(Entity);
	Vector3 Coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),true);
	//float Coords.x,Coords.y,Coords.z + 0.6[3] = {Coords.x,Coords.y,Coords.z + 0.6};
	float coordsB[3] = {Coords.x,Coords.y,Coords.z + 0.8};
	float coordsC[3] = {Coords.x,Coords.y,Coords.z + 0.9};
	float coordsD[3] = {Coords.x,Coords.y,Coords.z + 0.10};
	float coordsE[3] = {Coords.x,Coords.y,Coords.z + 1.0};
	float coordsF[3] = {Coords.x,Coords.y,Coords.z};
	float coordsXX[3] = {Coords.x,Coords.y,Coords.z + 0.7400};
	//Props
	if(
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_cs_hotdog_01"),true)
	||OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_cs_hotdog_02"),true)||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_ld_ferris_wheel"),true)||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_cs_tv_stand"),true)||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_tv_02"),true)||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_alien_egg_01"),true)||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_tv_03_overlay"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_tv_04"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_tv_06"),true)||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_tv_07"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_tv_05"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_busker_hat_01"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_ld_hat_01"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_spray_backpack_01"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_welding_mask_01"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_headset_01"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_snow_bin_01"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_snow_bin_02"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_snow_bush_01_a"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_snow_bush_02_a"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_snow_bush_02_b"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_snow_bush_03"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_snow_bush_04"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_snow_bush_04b"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_snow_diggerbkt_01"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_snow_facgate_01"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_air_bigradar_l1"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_air_bigradar_l2"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_beach_fire"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_air_radar_01"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_xmas_tree_int"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_xmas_ext"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_gas_mask_hang_01"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("prop_player_gasmask"),true) ||
	OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6,1.0f,GAMEPLAY::GET_HASH_KEY("p_spinning_anus_s"),true))
	{
	int	Obj1GAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_cs_hotdog_01"), true);ENTITY::DELETE_ENTITY(&Obj1GAA);
	int	Obj2GAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_cs_hotdog_02"), true);ENTITY::DELETE_ENTITY(&Obj2GAA);
	int	Obj3GAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_ld_ferris_wheel"), true);ENTITY::DELETE_ENTITY(&Obj3GAA);
	int	Obj88GAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_alien_egg_01"), true);ENTITY::DELETE_ENTITY(&Obj88GAA);
	int	Obj4GAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_cs_tv_stand"), true);ENTITY::DELETE_ENTITY(&Obj4GAA);
	int	Obj5GAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_tv_02"), true);ENTITY::DELETE_ENTITY(&Obj5GAA);
	int	Obj6GAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_tv_03_overlay"), true);ENTITY::DELETE_ENTITY(&Obj6GAA);
	int	Obj7GAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_tv_04"), true);ENTITY::DELETE_ENTITY(&Obj7GAA);
	int	Obj8GSD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_tv_06"), true);ENTITY::DELETE_ENTITY(&Obj8GSD);
	int	Obj9GSD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_tv_07"), true);ENTITY::DELETE_ENTITY(&Obj9GSD);
	int	Obj4GAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_tv_05"), true);ENTITY::DELETE_ENTITY(&Obj4GAAA);
	int	Obj5GAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_busker_hat_01"), true);ENTITY::DELETE_ENTITY(&Obj5GAAA);
	int	Obj6GAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_ld_hat_01"), true);ENTITY::DELETE_ENTITY(&Obj6GAAA);
	int	Obj7GAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_spray_backpack_01"), true);ENTITY::DELETE_ENTITY(&Obj7GAAA);
	int	Obj8GSDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_welding_mask_01"), true);ENTITY::DELETE_ENTITY(&Obj8GSDD);
	int	Obj9GSDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_headset_01"), true);ENTITY::DELETE_ENTITY(&Obj9GSDD);
	int	Obj4GAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_snow_bin_01"), true);ENTITY::DELETE_ENTITY(&Obj4GAAAA);
	int	Obj5GAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_snow_bin_02"), true);ENTITY::DELETE_ENTITY(&Obj5GAAAA);
	int	Obj6AAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_snow_bush_01_a"), true);ENTITY::DELETE_ENTITY(&Obj6AAAA);
	int	Obj7AAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_snow_bush_02_a"), true);ENTITY::DELETE_ENTITY(&Obj7AAAA);
	int	Obj8SDDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_snow_bush_02_b"), true);ENTITY::DELETE_ENTITY(&Obj8SDDD);
	int	Obj9SDDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_snow_bush_03"), true);ENTITY::DELETE_ENTITY(&Obj9SDDD);
	int	Obj4AAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_snow_bush_04"), true);ENTITY::DELETE_ENTITY(&Obj4AAAAA);
	int	Obj5AAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_snow_bush_04b"), true);ENTITY::DELETE_ENTITY(&Obj5AAAAA);
	int	Obj6AAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_snow_diggerbkt_01"), true);ENTITY::DELETE_ENTITY(&Obj6AAAAA);
	int	Obj7AAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_snow_facgate_01"), true);ENTITY::DELETE_ENTITY(&Obj7AAAAA);
	int	Obj8SDDDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_air_bigradar_l1"), true);ENTITY::DELETE_ENTITY(&Obj8SDDDD);
	int	Obj9SDDDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_air_bigradar_l2"), true);ENTITY::DELETE_ENTITY(&Obj9SDDDD);
	int	Obj4AAAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_beach_fire"), true);ENTITY::DELETE_ENTITY(&Obj4AAAAAA);
	int	Obj5AAAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_air_radar_01"), true);ENTITY::DELETE_ENTITY(&Obj5AAAAAA);
	int	Obj6AAAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_xmas_tree_int"), true);ENTITY::DELETE_ENTITY(&Obj6AAAAAA);
	int	Obj7AAAAAA = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_xmas_ext"), true);ENTITY::DELETE_ENTITY(&Obj7AAAAAA);
	int	Obj8SDDDDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_gas_mask_hang_01"), true);ENTITY::DELETE_ENTITY(&Obj8SDDDDD);
	int	Obj9SDDDDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("prop_player_gasmask"), true);ENTITY::DELETE_ENTITY(&Obj9SDDDDD);
	int	Obj10SDDDDD = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Coords.x,Coords.y,Coords.z + 0.6, 1.0f,GAMEPLAY::GET_HASH_KEY("p_spinning_anus_s"), true);ENTITY::DELETE_ENTITY(&Obj10SDDDDD);
	}
	}

	if(FreezeCarProtection)
	{
	int i;
	for (i = 0; i <= 16; i++)
	{
	if(PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(i), 0))
	{
	int Vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(i));
	//int Entity = Func::GET_ENTITY_MODEL(Vehicle);
	if(VEHICLE::IS_THIS_MODEL_A_HELI(Vehicle) || VEHICLE::IS_THIS_MODEL_A_PLANE(Vehicle) && VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehicle))
	{
	AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED(i));
	NotifyAboveMap("~r~Kicked Player from Car");
	}
	}
	}
	}
	*/
	//if(FreezeModelProtection)
	//{
	//	int i;
	//	for (i = 0; i <= 16; i++)
	//	{
	//		if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i), 0x1250D7BA) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0) == 3)//LION
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i), 1318032802) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0) == 3)//HUSKY
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i), -1715797768) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0) == 1)//Hacker
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i), 882848737)  && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0) == 4)//retriever
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i), 1126154828) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0) == 3)//shepherd
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i), 943915367) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),3 ) == 1  && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0) == 1 )//marston
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i), 1641334641)  && PED::GET_PED_DRAWABLE_VARIATION(PLAYER::GET_PLAYER_PED(i),8) == 1XBLOnline && PED::GET_PED_DRAWABLE_VARIATION(PLAYER::GET_PLAYER_PED(i),7) == 1/* Special 1*/ && PED::GET_PED_DRAWABLE_VARIATION(PLAYER::GET_PLAYER_PED(i),0) == 0/* Face*/ && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),2  ) == 1 /* Hair*/ && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),3  ) == 1 /* Torse*/ && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),4  ) == 1 /* Legs */ && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),5 ) == 1 /* Hands */ && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),7) == 0 /* Special 1  */ && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),8) == 0 XBLOnline)//Yeti
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i), 193469166) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 1XBLOnline)//Gun Man
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i), -287649847) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),3  ) == 1 &&  PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 1)//Niko
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i), -1057787465) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),3  ) == 1 &&  PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 1)//Claude
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i), -785842275) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),3  ) == 1 &&  PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 1)//misty
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}			
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i), -1111799518) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 1XBLOnline)//Brad
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i), 1830688247) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 3)//Amanda
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i), 1206185632) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 1)//Andreas
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i), 1302784073) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 1)//Lester
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i), -538688539) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 2)//Lester
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i), 1706635382) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 2)//Lamar
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i), 1459905209) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 1)//jimmydisanto
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i), 2050158196) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 1)//jay norris
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i), -1313761614) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 2)//Floyd
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i), -795819184) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 2)//Fabin
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i),  -872673803) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 1)//Drfried
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i),  -1674727288) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 1)//Dom
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i),  1952555184) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 2)//Devin
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i),  -2113195075) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 2)//Denise
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i),  65775923) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 3)//Dave
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i),  -886023758) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 1)//Milton
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i),  -1358701087) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 1)//Molly
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i),  -304305299) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 3)//Mrk
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i),  1625728984) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 1)//omega
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i),  -1124046095) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 1)//nervousron
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i),  -982642292) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 1)//partical
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i),  1283141381) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 1)//SOMON
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i),  -2034368986) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 1)//SOMON
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i),  941695432) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 1)//Steven
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i),  915948376) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 1)//Stract
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i),  -597926235) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 2)//tao
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i),  2089096292) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 2)//tao2
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i),  -1573167273) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 1)//tennsi
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i),  416176080) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 3)//Shop
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i),  994527967) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),0  ) == 1)//Driver
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i),  51016938) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),4  ) == 1)//legs
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i),  882848737) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),4  ) == 3)//legs
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//		else if (PED::IS_PED_MODEL(PLAYER::GET_PLAYER_PED(i),  882848737) && PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED(i),4  ) == 3)//legs
	//		{
	//			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), 225514697);
	//			NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
	//			FreezeModelProtection = false;
	//		}
	//	}
	//}
	//*/

	if (castRayTestBool)
	{


		Vector3 camCoords = CAM::GET_GAMEPLAY_CAM_COORD();
		Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
		Vector3 farCoords;
		int entdistance = 5000;
		float Pos[3];
		float x, y, z;
		//	_GET_CAMERA_DIRECTION(&x, &y, &z);
		Vector3  dir = _GET_CAMERA_DIRECTION(5.0);

		Vector3 Position = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);

		//int ray = WORLDPROBE::_CAST_RAY_POINT_TO_POINT(Pos[0] + x, Pos[1] + y, Pos[2] + z, Pos[0] + (x*entdistance), Pos[1] + (y*entdistance), Pos[2] + (z*entdistance), -1, 0, 7);

		int ray = WORLDPROBE::_CAST_RAY_POINT_TO_POINT(Position.x + (dir.x), Position.y + (dir.y), Position.z + (dir.z), Position.x + (dir.x*entdistance), Position.y + (dir.y*entdistance), Position.z + (dir.z*entdistance), -1, 0, 7);
		WORLDPROBE::_GET_RAYCAST_RESULT(ray, &hit, &endCoords, &surfaceNormal, &entityHandle);

		//	GRAPHICS::DRAW_LINE(Position.x + (dir.x), Position.y + (dir.y), Position.z + (dir.z), Position.x + (dir.x*entdistance), Position.y + (dir.y*entdistance), Position.z + (dir.z*entdistance), 0, 0, 255, 255);
		GRAPHICS::DRAW_LINE(Position.x, Position.y, Position.z, Position.x + (dir.x*entdistance), Position.y + (dir.y*entdistance), Position.z + (dir.z*entdistance), 0, 255, 0, 255);
		if (hit/* && (ENTITY::DOES_ENTITY_EXIST(entityHandle))*/)
		{
			GRAPHICS::DRAW_LINE(Position.x, Position.y, Position.z, endCoords.x, endCoords.y, endCoords.z, 255, 0, 0, 255);
			/*	if (ENTITY::IS_ENTITY_A_VEHICLE(entityHandle))
			ShowMessageOnScreen("veh");
			else if (ENTITY::IS_ENTITY_A_PED(entityHandle))
			ShowMessageOnScreen("ped");
			else if (ENTITY::IS_ENTITY_AN_OBJECT(entityHandle))
			ShowMessageOnScreen("obj");*/
		}


	}
	bool nocliploop34 = false;
	if (nocliploop34)
	{
		Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
		Vector3  dir = _GET_CAMERA_DIRECTION(5.0);
		float d = 0.09;


		if (CONTROLS::IS_CONTROL_PRESSED(0, 52), CONTROLS::IS_CONTROL_PRESSED(0, 55))
			d -= 0.0;
		int vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		Vector3 Position = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
		int ent = vehicle == 0 ? PLAYER::PLAYER_PED_ID() : vehicle;
		ENTITY::SET_ENTITY_COLLISION(ent, 0, false);
		ENTITY::SET_ENTITY_ROTATION(ent, rot.x, rot.y, rot.z, 2, 1);
		ENTITY::SET_ENTITY_COORDS(ent, Position.x, Position.y, Position.z - 1, 1, 0, 0, 1);
		if (CONTROLS::IS_CONTROL_PRESSED(2, 0xC6))
		{
			if (ent == vehicle)
				if (ent == PLAYER::PLAYER_PED_ID())
				{
					ENTITY::SET_ENTITY_COLLISION(ent, 0, false);
					ENTITY::SET_ENTITY_ROTATION(ent, rot.x, rot.y, rot.z, 2, 1);
				}

			ENTITY::SET_ENTITY_COORDS(ent, Position.x + (dir.x), Position.y + (dir.y), Position.z + (dir.z), 1, 0, 0, 1);
		}
	}
	if (GravityGunLoop2)
	{
		Player player = PLAYER::PLAYER_ID();
		if (PLAYER::IS_PLAYER_FREE_AIMING(player))
		{
			PLAYER::_GET_AIMED_ENTITY(player, &GravityEntity2);
		}
		else
		{
			GravityEntity2 = 0;
		}
		if (GravityEntity2)
		{
			Ped player = PLAYER::PLAYER_PED_ID();
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(player, 1);
			Vector3 direction = ENTITY::GET_ENTITY_FORWARD_VECTOR(player);
			//Vector3 CamCoords = get_coords_from_cam(*(float*)0x83A81010);
			//ENTITY::SET_ENTITY_HEADING(Object, ENTITY::GET_ENTITY_HEADING(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0)));
			coords.x += direction.x + 2.0f;
			coords.y += direction.y + 2.0f;
			coords.z += 2.0f;
			ENTITY::SET_ENTITY_COORDS(GravityEntity2, coords.x, coords.y, coords.z, 1, 1, 1, 1);
		}
	}


	if (RemoveObjectGun)
	{
		PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &EntityID);
		if (ENTITY::IS_ENTITY_AN_OBJECT(EntityID) == true)
		{
			ENTITY::DELETE_ENTITY(&EntityID);
		}
	}

	if (Toggle_NoClip)
	{
		Ped Player = PLAYER::PLAYER_PED_ID();
		Vector3 Coords = ENTITY::GET_ENTITY_COORDS(Player, 1);
		//float Coords2[3] = { Coords.x, Coords.y, Coords.z };
		GetcoordsInfrontOfSelf(&Coords.x, &Coords.y, &Coords.z);
		ENTITY::SET_ENTITY_COORDS(Player, Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
	}
	if (fieldloop)
	{
		Vector3 Position = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), 0);
		FIRE::ADD_EXPLOSION(Position.x, Position.y, Position.z, BLIMP, FLT_MAX, false, true, 0.0f);
		FIRE::ADD_EXPLOSION(Position.x, Position.y, Position.z, TRAIN, FLT_MAX, false, true, 0.0f);
	}
	if (tWallCrawlVehLoop)
	{
		if (!PED::IS_PED_ON_FOOT(PLAYER::PLAYER_PED_ID()))
		{
			int myvehicle;
			myvehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			if (ENTITY::DOES_ENTITY_EXIST(myvehicle) && ENTITY::IS_ENTITY_A_VEHICLE(myvehicle))
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(myvehicle, true, 0, 0, -0.3, 0, 0, 0, true, true, true, true, false, true);
			}
			if (CONTROLS::IS_CONTROL_PRESSED(0, Dpad_Right))
			{
				int myvehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				if (ENTITY::DOES_ENTITY_EXIST(myvehicle) && ENTITY::IS_ENTITY_A_VEHICLE(myvehicle))
				{
					ENTITY::APPLY_FORCE_TO_ENTITY(myvehicle, true, 0, 0, 1.5, 0, 0, 0, true, true, true, true, false, true);
				}
			}
			if (CONTROLS::IS_CONTROL_PRESSED(0, Button_R1))
			{
				int myvehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				if (ENTITY::DOES_ENTITY_EXIST(myvehicle) && ENTITY::IS_ENTITY_A_VEHICLE(myvehicle))
				{
					ENTITY::APPLY_FORCE_TO_ENTITY(myvehicle, true, 0, 1, 0, 0, 0, 0, true, true, true, true, false, true);
				}
			}
			if (CONTROLS::IS_CONTROL_PRESSED(0, Button_X) && CONTROLS::IS_CONTROL_PRESSED(0, Button_A))
			{
				int myvehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				if (ENTITY::DOES_ENTITY_EXIST(myvehicle) && ENTITY::IS_ENTITY_A_VEHICLE(myvehicle))
				{
					ENTITY::APPLY_FORCE_TO_ENTITY(myvehicle, true, 0, 1.5, 0.3, 0, 0, -7, true, true, true, true, false, true);
				}
			}
		}
	}

	if (drawLasers)
	{
		int VehHandle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		float Offset1[] = { 0.6f, 0.6707f, 0.3711f };
		float Offset2[] = { -0.6f, 0.6707f, 0.3711f };
		float Offset3[] = { 0.6f, 25.0707f, 0.3711f };
		float Offset4[] = { -0.6f, 25.0707f, 0.3711f };
		Vector3 getcoords1 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehHandle, Offset1[0], Offset1[1], Offset1[2]);
		Vector3 getcoords2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehHandle, Offset2[0], Offset2[1], Offset2[2]);
		Vector3 getcoords3 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehHandle, Offset3[0], Offset3[1], Offset3[2]);
		Vector3 getcoords4 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehHandle, Offset4[0], Offset4[1], Offset4[2]);
		float StartCoords1[] = { getcoords1.x, getcoords1.y, getcoords1.z };
		float StartCoords2[] = { getcoords2.x, getcoords2.y, getcoords2.z };
		float EndCoords1[] = { getcoords3.x, getcoords3.y, getcoords3.z };
		float EndCoords2[] = { getcoords4.x, getcoords4.y, getcoords4.z };
		GRAPHICS::DRAW_LINE(StartCoords1[0], StartCoords1[1], StartCoords1[2], EndCoords1[0], EndCoords1[1], EndCoords1[2], 255, 0, 0, 255);
		GRAPHICS::DRAW_LINE(StartCoords2[0], StartCoords2[1], StartCoords2[2], EndCoords2[0], EndCoords2[1], EndCoords2[2], 255, 0, 0, 255);
	}

	if (superveh)
	{
		//VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0));
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_R3))
		{
			Vector3 a = { 0, 7, 0 };
			Vector3 b = { 0, 0, 0 };
			int vehid = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			GRAPHICS::START_SCREEN_EFFECT("RaceTurbo", 0, 0);
			ENTITY::APPLY_FORCE_TO_ENTITY(vehid, 1, a.x, a.y, a.z, b.x, b.y, b.z, 1, 1, 1, 1, 0, 1);
		}
	}
	if (Flying_Vehicle)
	{
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_R1))
		{
			int Handle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			if (Handle != 0)
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(Handle, true, 0, 1, 0.3f, 0, 0, 0, true, true, true, true, false, true);
			}
		}
	}

	if (Flying_Vehicle2)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
		{
			int Vehid = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);

			if (CONTROLS::IS_CONTROL_PRESSED(2, 67) == true) //Forward
			{
				float Speed = ENTITY::GET_ENTITY_SPEED(Vehid) + 0.5;
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(Vehid, Speed);
			}

			if (CONTROLS::IS_CONTROL_PRESSED(2, 196) && !VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehid)) //Left
			{
				Vector3 Rot;
				Rot = ENTITY::GET_ENTITY_ROTATION(Vehid, 2);
				Rot.z = Rot.z + 1.0;
				float newRot[] = { Rot.x, Rot.y, Rot.z };
				ENTITY::SET_ENTITY_ROTATION(Vehid, newRot[0], newRot[1], newRot[2], 2, 1);
			}
			if (CONTROLS::IS_CONTROL_PRESSED(2, 197) && !VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehid)) //Right
			{
				Vector3 Rot = ENTITY::GET_ENTITY_ROTATION(Vehid, 2);
				Rot.z = Rot.z - 1.0;
				float newRot[] = { Rot.x, Rot.y, Rot.z };
				ENTITY::SET_ENTITY_ROTATION(Vehid, newRot[0], newRot[1], newRot[2], 2, 1);
			}
		}
	}
	if (flyingcar)
	{
		int Handle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) ENTITY::APPLY_FORCE_TO_ENTITY(Handle, true, 0, 1.0f, 0, 0, 0, 0, true, true, true, true, false, true);
		if (CONTROLS::IS_CONTROL_ENABLED(0, Button_L2)) {
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(Handle, 0);
			if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, Button_X)) {
				PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0);
				ENTITY::APPLY_FORCE_TO_ENTITY(Handle, true, 0, 0, 0.01f, 0, 45.0f, 0, true, true, true, true, false, true);
			}
		}
	}
	if (Fun_Gun)
	{
		int myhandle = PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID());
		if (PED::IS_PED_ON_FOOT(myhandle))
		{
			if (PED::IS_PED_SHOOTING(myhandle))
			{
				//Declaring
				Vector3 Pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
				Vector3 Pos2 = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);

				//int dildohandle = create_object(get_hash_key("prop_cs_dildo_01"), Pos[0], Pos[1], Pos[2]);
				int funitemhandle = OBJECT::CREATE_OBJECT(FunGunItem, Pos.x, Pos.y, Pos.z, 1, 1, 0);

				//GetcoordsInfrontOfSelf(&Pos[0], &Pos[1], &Pos[2]);//Spawns the object at some bullshit location

				if (NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(funitemhandle))
				{
					float x, y, z;
					//The three items below may cause problems spawning after first time due to redefining x,y,z.
					//x = directioncoords[0];//Currently not using...
					//y = directioncoords[1];//Currently not using...
					//z = directioncoords[2];//Currently not using...

					ENTITY::FREEZE_ENTITY_POSITION(funitemhandle, true);
					ENTITY::SET_ENTITY_COORDS(funitemhandle, Pos.x, Pos.y + 1, Pos.z, 0, 0, 0, 1);//Added 1 to the y coord
					ENTITY::SET_ENTITY_HEADING(funitemhandle, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
					//set_entity_heading(dildohandle, directioncoords[3]);//Testing... If this doesn't work, switch to above method!
					ENTITY::FREEZE_ENTITY_POSITION(funitemhandle, false);
					ENTITY::APPLY_FORCE_TO_ENTITY(funitemhandle, 1, 0.0, 1000.0f, 0.0, 0.0, -1.5f, 0.0f, 0, 1, 1, 1, false, true);
					//set_entity_rotation(objecthandle,0,0,heading,2,1);//Leaving this here just in case we need it.
				}
			}
		}
	}
	if (Show_Host)
	{
		PrintToScreen("Host:", 0.05f, 0.03f, 255, 255, 255, 255, 0.6050f, 0.6050f, 0, 6);
		PrintToScreen(getHostName(), 0.08f, 0.03f, infor, infog, infob, 255, 0.6050f, 0.6050f, 0, 6);
	}
	if (Show_Info)
	{
		float pos = 0.05f;
		PrintToScreen("Talking:", 0.05f, 0.12f, 255, 255, 255, 255, 0.6050f, 0.6050f, 0, 6);
		//ShowPlayerTalking("TN Elite Venom", *(float*)0x83A81010, pos += *(float*)0x83A81014, infor, infob, infog, 255);
		for (int i = 0; i < 16; i++)
		{
			if (i != PLAYER::PLAYER_PED_ID())
			{
				if (NETWORK::NETWORK_IS_PLAYER_TALKING(i))
				{
					if (!NETWORK::NETWORK_IS_PLAYER_MUTED_BY_ME(i))
					{
						//ShowPlayerTalking(PLAYER::GET_PLAYER_NAME(i), 0.08f, pos += 0.09f, infor, infob, infog, 255);
						ShowPlayerTalking(PLAYER::GET_PLAYER_NAME(i), 0.14, pos += 0.072, infor, infob, infog, 255);
					}
				}
			}
		}
	}
	if (RPG_GUN)
	{
		Vector3 spawnPosition = GetCoordsInfrontOfCam(5.0);
		Vector3 endPosition = GetCoordsInfrontOfCam(50.0);
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		if (PED::IS_PED_SHOOTING(playerPed))
		{
			Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("WEAPON_VEHICLE_ROCKET");
			if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
			{
				WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, 0);
				while (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket)) SYSTEM::WAIT(0);
			}
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(spawnPosition.x, spawnPosition.y, spawnPosition.z, endPosition.x, endPosition.y, endPosition.z, 250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		}
	}

	if (Show_FPS_Counter)
	{
		Frames++;
		CurrentTime = GetTickCount();
		ElapsedTime = CurrentTime - LastUpdateTime;
		if (ElapsedTime >= 1000)
		{
			Frames = 0;
			LastUpdateTime = CurrentTime;
			wsprintf(FPS, "%u", (UINT)(Frames * 1000.0 / ElapsedTime));
		}
		PrintToScreen("FPS:", 0.05f, 0.09f, 255, 255, 255, 255, 0.6050f, 0.6050f, 0, 6);
		drawText(FPS, itemfont, 0.08f, 0.09f, 0.6050f, 0.6050f, infor, infob, infog, 255, false);
	}
	if (AtlasOpenText)
	{
		PrintToScreen("Free Slots:", 0.05f, 0.06f, 255, 255, 255, 255, 0.6050f, 0.6050f, 0, itemfont);
		//PrintToScreen("Talking:", pos += 0.03f, 0.07f, 255, 255, 255, 255, 0.05f, 0.05f, 0, 6);
		drawText(ItoS(FreeSlots()), itemfont, 0.11f, 0.06f, 0.6050f, 0.6050f, infor, infob, infog, 255, false);
		//char *string = (char*)0x10060200;
		//strcpy(string, "Free slots: ");
	}

	if (Cash_Drop)
	{
		int Handle = PLAYER::GET_PLAYER_PED(selectedPlayer);
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(Handle, false);
		STREAMING::REQUEST_MODEL(CashDropItem);
		if (STREAMING::HAS_MODEL_LOADED(CashDropItem))
		{
			OBJECT::CREATE_AMBIENT_PICKUP(CashDropItem, coords.x, coords.y, coords.z + 1, 0, MoneySet, CashDropItem, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(CashDropItem, coords.x + 0.1, coords.y, coords.z + 1, 0, MoneySet, CashDropItem, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(CashDropItem, coords.x, coords.y, coords.z + 1, 0, MoneySet, CashDropItem, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(CashDropItem, coords.x + 0.1, coords.y, coords.z + 1, 0, MoneySet, CashDropItem, 0, 1);
		}
	}
	if (Cash_Drop40K)
	{
		int Handle = PLAYER::GET_PLAYER_PED(selectedPlayer);
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(Handle, false);
		STREAMING::REQUEST_MODEL(0x113FD533);
		if (STREAMING::HAS_MODEL_LOADED(0x113FD533))
		{
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
		}
	}
	if (Cashdropadv)
	{
		int Handle = PLAYER::GET_PLAYER_PED(selectedPlayer);
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(Handle, false);
		float angle = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, MoneyRange_) * 3.14159265359;
		float radius = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, MoneyRange_) * 5.0f;
		float x = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).x + radius * SYSTEM::COS(angle);
		float y = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).y + radius * SYSTEM::SIN(angle);
		STREAMING::REQUEST_MODEL(0x113FD533);
		if (STREAMING::HAS_MODEL_LOADED(0x113FD533))
		{
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + moneyzcoord, 0, amount, 0x113FD533, 0, 1);
		}
	}
	if (Cashdropadv2)
	{
		int Handle = PLAYER::GET_PLAYER_PED(selectedPlayer);
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(Handle, false);
		float angle = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, MoneyRange_) * 3.14159265359;
		float radius = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, MoneyRange_) * 5.0f;
		float x = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).x + radius * SYSTEM::COS(angle);
		float y = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).y + radius * SYSTEM::SIN(angle);
		STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY(objectbypassselect));
		if (STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY(objectbypassselect)))
		{
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + moneyzcoord, 0, amount, GAMEPLAY::GET_HASH_KEY(objectbypassselect), 0, 1);
		}
	}
	if (Ammo_Drop)
	{
		int Handle = PLAYER::GET_PLAYER_PED(selectedPlayer);
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(Handle, false);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_FLAREGUN"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_HOMINGLAUNCHER"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_MINIGUN"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_RPG"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_GRENADELAUNCHER"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_SNIPER"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_SHOTGUN"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_MG"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_RIFLE"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_SMG"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_PISTOL"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_FIREWORK_MP"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_AMMO_FIREWORK"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
	}
	if (Give_Health)
	{
		int Handle = PLAYER::GET_PLAYER_PED(selectedPlayer);
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(Handle, false);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_HEALTH_STANDARD"), coords.x, coords.y, coords.z, 0, 100000, 1, 0, 1);
	}
	//if (DrawTV)
	//{
	//	//GRAPHICS::DRAW_TV_CHANNEL(0.4575, 0.2353463587921847, 0.405, 0.38188277087033745, 0, 0, 255,255);
	//	GRAPHICS::DRAW_TV_CHANNEL(0.5, 0.5, 0.7375, 1.0, 0.0, 255, 255, 255, 255);
	//}
	//else 
	//{ 
	//		GRAPHICS::DRAW_TV_CHANNEL(0.5, 0.5, 1.0, 1.0, 0.0, 255, 255, 255, 255);
	//}
	if (Clone_Player)
	{
		int Handle = PLAYER::GET_PLAYER_PED(selectedPlayer);
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(Handle, false);
		PED::CLONE_PED(Handle, coords.x, coords.y, coords.z);
	}
	if (Snack_Drop)
	{
		int Handle = PLAYER::GET_PLAYER_PED(selectedPlayer);
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(Handle, false);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_HEALTH_SNACK"), coords.x, coords.y, coords.z, 0, 100000, 1, 0, 1);
	}
	if (Ghost_Rider)
	{
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry2");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_clown_death", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 31086, 0.2f, 0, 0, 0);
	}
	if (Ghost_RiderOnline)
	{
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry2");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_clown_death", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 31086, 0.2f, 0, 0, 0);
	}
	if (Ghost_RiderOnline2)
	{
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry2");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_clown_death", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 60309, 0.2f, 0, 0, 0);
	}
	if (Ghost_RiderOnline3)
	{
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry2");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_clown_death", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 28422, 0.2f, 0, 0, 0);
	}
	if (Ghost_RiderOnline21)
	{
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_trevor1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_trev1_trailer_boosh", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 31086, 0.2f, 0, 0, 0);
	}
	if (Ghost_RiderOnline22)
	{
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_trevor1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_trev1_trailer_boosh", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 60309, 0.2f, 0, 0, 0);
	}
	if (Ghost_RiderOnline23)
	{
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_trevor1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_trev1_trailer_boosh", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 28422, 0.2f, 0, 0, 0);
	}
	if (Ghost_Rider_Head2)
	{
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_trevor1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_trevor1");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_trev1_trailer_boosh", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 31086, 0.2f, 0, 0, 0);
	}
	if (FXCRASH)
	{
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 31086, 100.0f, 0, 0, 0);
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 31086, 100.0f, 0, 0, 0);
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 31086, 100.0f, 0, 0, 0);
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 31086, 100.0f, 0, 0, 0);
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 31086, 100.0f, 0, 0, 0);
	}
	if (FXCRASH1)
	{
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 28422, 100.0f, 0, 0, 0);
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 28422, 100.0f, 0, 0, 0);
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 28422, 100.0f, 0, 0, 0);
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 28422, 100.0f, 0, 0, 0);
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 28422, 100.0f, 0, 0, 0);
	}
	if (FXCRASH2)
	{
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 60309, 100.0f, 0, 0, 0);
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 60309, 100.0f, 0, 0, 0);
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 60309, 100.0f, 0, 0, 0);
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 60309, 100.0f, 0, 0, 0);
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0, 0, 0, 0, 0, 60309, 100.0f, 0, 0, 0);
	}
	if (FireStormHead)
	{
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 31086, 0.2f, 0, 0, 0);
	}
	if (FireStormArm)
	{
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 28422, 0.1f, 0, 0, 0);
	}
	if (FireStormArm2)
	{
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry1");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_alien_teleport", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 60309, 0.1f, 0, 0, 0);
	}
	if (Ghost_Rider2)
	{
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry2");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_clown_death", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 28422, 0.1f, 0, 0, 0);
	}
	if (Ghost_Rider3)
	{
		STREAMING::_REQUEST_DLC_PTFX_ASSET("scr_rcbarry2");
		GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2("scr_clown_death", PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0, 0, 0, 60309, 0.1f, 0, 0, 0);
	}
	if (Weapon_Drop)
	{
		int Handle = PLAYER::GET_PLAYER_PED(selectedPlayer);
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(Handle, false);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_HEALTH_STANDARD"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_ARMOUR_STANDARD"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_PARACHUTE"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_LOUDHAILER"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_LASSO"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_FIREEXTINGUISHER"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_NIGHTSTICK"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_CROWBAR"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_HAMMER"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_BAT"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_KNIFE"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_SMOKEGRENADE"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_PETROLCAN"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_MOLOTOV"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_Shoot"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_STICKYBOMB"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_GRENADE"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_MINIGUN"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_RPG"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_GRENADELAUNCHER"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_COMBATMG"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_MG"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_HEAVYSNIPER"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_SNIPERRIFLE"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_ASSAULTSHOTGUN"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_PUMPSHOTGUN"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_SAWNOFFSHOTGUN"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_ADVANCEDRIFLE"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_CARBINERIFLE"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_ASSAULTRIFLE"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_SMG"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_MICROSMG"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_APPISTOL"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_COMBATPISTOL"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_PISTOL"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_FIREWORK"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_HOMINGLAUNCHER"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_PROXMINE"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_FLAREGUN"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_MARKSMANRIFLE"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_HEAVYSHOTGUN"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_MUSKET"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_VINTAGEPISTOL"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_DAGGER"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_SPECIALCARBINE"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_HEAVYPISTOL"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_GUSENBERG"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_SNSPISTOL"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_BOTTLE"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_WEAPON_BULLPUPRIFLE"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICK_WEAPON_COMBATPDW"), coords.x, coords.y, coords.z, 0, 9999, 1, 0, 1);
	}
	if (Armour_Drop)
	{
		int Handle = PLAYER::GET_PLAYER_PED(selectedPlayer);
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(Handle, false);
		OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_ARMOUR_STANDARD"), coords.x, coords.y, coords.z, 0, 100000, 1, 0, 1);
	}
	if (Cash_DropInsane)
	{
		int Handle = PLAYER::GET_PLAYER_PED(selectedPlayer);
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(Handle, false);
		STREAMING::REQUEST_MODEL(0x113FD533);
		if (STREAMING::HAS_MODEL_LOADED(0x113FD533))
		{
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x + 0.1, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x + 0.1, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x + 0.1, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x + 0.1, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x + 0.1, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y + 0.1, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y + 0.1, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y + 0.1, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y + 0.1, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y + 0.1, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x + 0.1, coords.y + 0.1, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x + 0.1, coords.y + 0.1, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x + 0.1, coords.y + 0.1, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x + 0.1, coords.y + 0.1, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x + 0.1, coords.y + 0.1, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x - 0.1, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x - 0.1, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x - 0.1, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x - 0.1, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x - 0.1, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y - 0.1, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y - 0.1, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y - 0.1, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y - 0.1, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y - 0.1, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x - 0.1, coords.y - 0.1, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x - 0.1, coords.y - 0.1, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x - 0.1, coords.y - 0.1, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x - 0.1, coords.y - 0.1, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x - 0.1, coords.y - 0.1, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x + 0.1, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x + 0.1, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x + 0.1, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x + 0.1, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, coords.x + 0.1, coords.y, coords.z + 1, 0, 40000, 0x113FD533, 0, 1);
		}
	}
	if (nocliploop)
	{
		Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
		Vector3  dir = _GET_CAMERA_DIRECTION(0);
		float d = 0.09;

		doAnimation(PLAYER::PLAYER_PED_ID(), "rcmcollect_paperleadinout@", "meditiate_idle");

		if (CONTROLS::IS_CONTROL_PRESSED(0, 52), CONTROLS::IS_CONTROL_PRESSED(0, 55))
			d -= 0.0;
		int vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		Vector3 Position = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
		int ent = vehicle == 0 ? PLAYER::PLAYER_PED_ID() : vehicle;
		ENTITY::SET_ENTITY_ROTATION(ent, rot.x, rot.y, rot.z, 2, 1);
		ENTITY::SET_ENTITY_COORDS(ent, Position.x, Position.y, Position.z - 1, 1, 0, 0, 1);
		if (CONTROLS::IS_CONTROL_PRESSED(2, 0xC6))
		{
			if (ent == vehicle)
				if (ent == PLAYER::PLAYER_PED_ID())
				{
					ENTITY::SET_ENTITY_ROTATION(ent, rot.x, rot.y, rot.z, 2, 1);
				}

			ENTITY::SET_ENTITY_COORDS(ent, Position.x + (dir.x), Position.y + (dir.y), Position.z + (dir.z), 1, 0, 0, 1);
		}
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_A))
		{
			int VehicleHandle = PED::IS_PED_ON_FOOT(PLAYER::PLAYER_PED_ID());
			int launchDistance = 250;
			int weaponHash = 0xE2822A29;
			int weaponHash2 = 0xEFFD014B;
			int launchSpeed = 100.0f;
			float idkcoords1[] = { 0.6f, 0.6707f, 0.3711f };
			Vector3 getcoords1 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords1[0], idkcoords1[1], idkcoords1[2]);
			float idkcoords2[] = { -0.6f, 0.6707f, 0.3711f };
			Vector3 getcoords2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords2[0], idkcoords2[1], idkcoords2[2]);
			float idkcoords3[] = { 0.6f, 5.0707f, 0.3711f };
			Vector3 getcoords3 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords3[0], idkcoords3[1], idkcoords3[2]);
			float idkcoords4[] = { -0.6f, 5.0707f, 0.3711f };
			Vector3 getcoords4 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords4[0], idkcoords4[1], idkcoords4[2]);
			float coords1[] = { getcoords1.x, getcoords1.y, getcoords1.z };
			float coords2[] = { getcoords2.x, getcoords2.y, getcoords2.z };
			float coords3[] = { getcoords3.x, getcoords3.y, getcoords3.z };
			float coords4[] = { getcoords4.x, getcoords4.y, getcoords4.z };
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1[0], coords1[1], coords1[2], Position.x + (dir.x), Position.y + (dir.y), Position.z + (dir.z), launchDistance, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords2[0], coords2[1], coords2[2], Position.x + (dir.x), Position.y + (dir.y), Position.z + (dir.z), launchDistance, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1[0], coords1[1], coords1[2], Position.x + (dir.x), Position.y + (dir.y), Position.z + (dir.z), launchDistance, 0, weaponHash2, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords2[0], coords2[1], coords2[2], Position.x + (dir.x), Position.y + (dir.y), Position.z + (dir.z), launchDistance, 0, weaponHash2, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
		}
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_X))
		{
			int VehicleHandle = PED::IS_PED_ON_FOOT(PLAYER::PLAYER_PED_ID());
			int launchDistance = 250;
			int weaponHash = GAMEPLAY::GET_HASH_KEY("WEAPON_VEHICLE_ROCKET");
			int launchSpeed = 100.0f;
			float idkcoords1[] = { 0.6f, 0.6707f, 0.3711f };
			Vector3 getcoords1 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords1[0], idkcoords1[1], idkcoords1[2]);
			float idkcoords2[] = { -0.6f, 0.6707f, 0.3711f };
			Vector3 getcoords2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords2[0], idkcoords2[1], idkcoords2[2]);
			float idkcoords3[] = { 0.6f, 5.0707f, 0.3711f };
			Vector3 getcoords3 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords3[0], idkcoords3[1], idkcoords3[2]);
			float idkcoords4[] = { -0.6f, 5.0707f, 0.3711f };
			Vector3 getcoords4 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, idkcoords4[0], idkcoords4[1], idkcoords4[2]);
			float coords1[] = { getcoords1.x, getcoords1.y, getcoords1.z };
			float coords2[] = { getcoords2.x, getcoords2.y, getcoords2.z };
			float coords3[] = { getcoords3.x, getcoords3.y, getcoords3.z };
			float coords4[] = { getcoords4.x, getcoords4.y, getcoords4.z };
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1[0], coords1[1], coords1[2], Position.x + (dir.x), Position.y + (dir.y), Position.z + (dir.z), launchDistance, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords2[0], coords2[1], coords2[2], Position.x + (dir.x), Position.y + (dir.y), Position.z + (dir.z), launchDistance, 0, weaponHash, PLAYER::PLAYER_PED_ID(), 1, 1, launchSpeed);
		}
	}
	if (Freeze_Player)
		AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED(selectedPlayer));
	if (Freeze_AllPlayers)
	{
		int i = 0;
		for (i = 0; i<16; i++)
		{
			if (i == PLAYER::PLAYER_ID()) continue;
			int Handle = PLAYER::GET_PLAYER_PED(i);
			if (!ENTITY::DOES_ENTITY_EXIST(Handle)) continue;
			AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED(i));
		}
	}
	if (Freeze_AllPlayersCars)
	{
		int i = 0;
		int Vehicle = PED::GET_VEHICLE_PED_IS_IN(i, 0);
		for (i = 0; i<16; i++)
		{
			if (i == PLAYER::PLAYER_ID()) continue;
			int Handle = PLAYER::GET_PLAYER_PED(i);
			if (!ENTITY::DOES_ENTITY_EXIST(Handle)) continue;
			ENTITY::FREEZE_ENTITY_POSITION(Vehicle, true);
		}
	}
	if (Toggle_featureNameESP)
	{
		for (int i = 0; i < 18; i++)
		{
			Ped playerHandle = PLAYER::GET_PLAYER_PED(i);
			Vector3 handleCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerHandle, 0, 0, 0), playerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
			if (ENTITY::DOES_ENTITY_EXIST(playerHandle))
			{
				float x, y;
				GRAPHICS::_WORLD3D_TO_SCREEN2D(handleCoords.x, handleCoords.y, handleCoords.z, &x, &y);
				int name_color[4] = { 0, 0, 0, 0 };
				UI::SET_TEXT_FONT(4);
				UI::SET_TEXT_SCALE(0.0, 0.40);
				UI::SET_TEXT_CENTRE(1);
				UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
				UI::_SET_TEXT_ENTRY("STRING");
				if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(PLAYER::PLAYER_PED_ID(), playerHandle, 17))
				{
					name_color[0] = 0, name_color[1] = 125, name_color[2] = 255, name_color[3] = 255;
				}
				else
				{
					name_color[0] = 0, name_color[1] = 125, name_color[2] = 255, name_color[3] = 255;
				}
				UI::SET_TEXT_COLOUR(name_color[0], name_color[1], name_color[2], name_color[3]);
				UI::_ADD_TEXT_COMPONENT_STRING(PLAYER::GET_PLAYER_NAME((i)));
				UI::_DRAW_TEXT(x, y);
				UI::SET_TEXT_DROPSHADOW(5, 0, 78, 255, 255);
			}
		}
	}
	if (Line_ESP)
	{
		drawESP();
		for (int i = 0; i < 18; i++)
		{
			Vector3 Pos;
			Vector3 Pos2;
			int PedID = PLAYER::GET_PLAYER_PED(i);
			Pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
			Pos2 = ENTITY::GET_ENTITY_COORDS(PedID, false);
			GRAPHICS::DRAW_LINE(Pos.x, Pos.y, Pos.z, Pos2.x, Pos2.y, Pos2.z, 0, 125, 255, 255);
		}
	}
	if (explosive_ammo)
		GAMEPLAY::SET_EXPLOSIVE_AMMO_THIS_FRAME(PLAYER::PLAYER_ID());
	if (SuperPunch)
		GAMEPLAY::SET_EXPLOSIVE_MELEE_THIS_FRAME(PLAYER::PLAYER_ID());  //Cash_Drop
	if (Unlimited_Ammo)
		WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), true);
	if (GodMode_VehicleLoop)
	{
		int car = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		RequestNetworkControl(PLAYER::PLAYER_PED_ID(), car);
		if (RequestNetworkControl(PLAYER::PLAYER_PED_ID(), car))
		{
			ENTITY::SET_ENTITY_PROOFS(car, true, true, true, true, true, true, true, true);
			ENTITY::SET_ENTITY_INVINCIBLE(car, true);
			VEHICLE::SET_VEHICLE_STRONG(car, true);
		}
	}
	if (createEscort)
	{
		if (!UI::IS_WAYPOINT_ACTIVE()) NotifyAboveMap("~r~Error:~s~ No waypoint set.");
		else
		{
			float Pos[3];
			Vector3 Coord = UI::GET_BLIP_COORDS(UI::GET_FIRST_BLIP_INFO_ID(UI::_GET_BLIP_INFO_ID_ITERATOR()));
			GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(Coord.x, Coord.y, Coord.z, &Coord.z);
			VectorToFloat(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0f, 5.0f, 1.0f), Pos);
			SYSTEM::WAIT(10);
			Ped tempPed = PED::CREATE_PED(1, PedModelHashEscort/*"A_C_CHIMP"*/, Pos[0], Pos[1], Pos[2], 0.0f, 1, 1);
			Vehicle tempVehicle = VEHICLE::CREATE_VEHICLE(VehicleHashEscort/*"KURUMA2"*/, Pos[0], Pos[1], Pos[2] + 2.0f, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 1);
			RequestControlOfEnt(tempVehicle);
			VEHICLE::SET_VEHICLE_COLOURS(tempVehicle, 0, 0);
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(tempVehicle, "VIP");
			for (int i = -1; i <= 20; i++)
			{
				if (!VEHICLE::IS_VEHICLE_SEAT_FREE(tempVehicle, i)) continue;
				//AI::TASK_WARP_PED_INTO_VEHICLE(tempPed, tempVehicle, 1); 
				PED::SET_PED_INTO_VEHICLE(tempPed, tempVehicle, 1);
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), tempVehicle, 2); break;
			}
			AI::TASK_VEHICLE_MISSION_COORS_TARGET(tempPed, tempVehicle, Coord.x, Coord.y, Coord.z, 4, 20.0f, 786469, 20.0f, 10.0f, 1);
			createEscort = false;
		}
	}
	if (FluxCar)
	{
		int color1;
		int color2;
		int color3;
		if (PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1))
		{
			CPaintMenu = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			if (ENTITY::DOES_ENTITY_EXIST(CPaintMenu) && ENTITY::IS_ENTITY_A_VEHICLE(CPaintMenu))
			{
				VEHICLE::SET_VEHICLE_DIRT_LEVEL(CPaintMenu, 0.0f);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(CPaintMenu, 0, 50, 255);
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(CPaintMenu, 0, 50, 255);
			}
		}
	}
	if (Flux)
	{
		if (RainbowTime < GAMEPLAY::GET_GAME_TIMER())
		{
			if (MenuColourStage == 0)
			{
				MenuColour.B++;
				if (MenuColour.B == 255)
					MenuColourStage = 1;
			}
			else if (MenuColourStage == 1)
			{
				MenuColour.R--;
				if (MenuColour.R == 0)
					MenuColourStage = 2;
			}
			else if (MenuColourStage == 2)
			{
				MenuColour.G++;
				if (MenuColour.G == 255)
					MenuColourStage = 3;
			}
			else if (MenuColourStage == 3)
			{
				MenuColour.B--;
				if (MenuColour.B == 0)
					MenuColourStage = 4;
			}
			else if (MenuColourStage == 4)
			{
				MenuColour.R++;
				if (MenuColour.R == 255)
					MenuColourStage = 5;
			}
			else if (MenuColourStage == 5)
			{
				MenuColour.G--;
				if (MenuColour.G == 0)
					MenuColourStage = 0;
			}
			bannerRectRed = MenuColour.R;
			bannerRectGreen = MenuColour.G;
			bannerRectBlue = MenuColour.B;
			RainbowTime = GAMEPLAY::GET_GAME_TIMER() + 10;
		}
	}
	if (aimbot)
	{
		Aimbot();
	}
	if (Aimbot_Toggle)
		PLAYER::IS_PLAYER_FREE_AIMING(PLAYER::PLAYER_PED_ID()) || PLAYER::IS_PLAYER_TARGETTING_ANYTHING(PLAYER::PLAYER_PED_ID());
	if (fire_gun)
		GAMEPLAY::SET_FIRE_AMMO_THIS_FRAME(PLAYER::PLAYER_ID());
	if (featureExplosionGun)
	{
		if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
		{
			float tmp[3];
			WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), tmp);
			FIRE::ADD_OWNED_EXPLOSION(PLAYER::PLAYER_PED_ID(), tmp[0], tmp[1], tmp[2], 5, .75, true, false, .1);
		}
	}

	if (PedSpawner) //PedSpawner
	{
		if (STREAMING::HAS_MODEL_LOADED(PedSpawnerHash))
		{
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
			PedID = PED::CREATE_PED(0x1A, PedSpawnerHash, coords.x, coords.y, coords.z, 204.8112f, 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(PedID))
			{
				int netID = NETWORK::PED_TO_NET(PedID);
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(netID, true);
				PED::SET_PED_RANDOM_COMPONENT_VARIATION(PedID, 0);
				//PED::SET_PED_AS_GROUP_MEMBER(ped, group);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(PedSpawnerHash);
				PedSpawner = false;
			}
		}
	}

	if (DeerSpawner) //PedSpawner
	{
		if (STREAMING::HAS_MODEL_LOADED(DeerHash))
		{
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
			DeerID = PED::CREATE_PED(0x1A, DeerHash, coords.x, coords.y, coords.z, 204.8112f, 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(DeerID))
			{
				int netID = NETWORK::PED_TO_NET(DeerID);
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(netID, true);
				PED::SET_PED_RANDOM_COMPONENT_VARIATION(DeerID, 0);
				//PED::SET_PED_AS_GROUP_MEMBER(ped, group);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(DeerHash);
				DeerSpawner = false;
			}
		}
	}

	if (PigSpawner) //PedSpawner
	{
		if (STREAMING::HAS_MODEL_LOADED(PigHash))
		{
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
			PigID = PED::CREATE_PED(0x1A, PigHash, coords.x, coords.y, coords.z, 204.8112f, 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(PigID))
			{
				int netID = NETWORK::PED_TO_NET(PigID);
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(netID, true);
				PED::SET_PED_RANDOM_COMPONENT_VARIATION(PigID, 0);
				//PED::SET_PED_AS_GROUP_MEMBER(ped, group);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(PigHash);
				PigSpawner = false;
			}
		}
	}

	if (BoarSpawner) //PedSpawner
	{
		if (STREAMING::HAS_MODEL_LOADED(BoarHash))
		{
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
			BoarID = PED::CREATE_PED(0x1A, BoarHash, coords.x, coords.y, coords.z, 204.8112f, 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(BoarID))
			{
				int netID = NETWORK::PED_TO_NET(BoarID);
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(netID, true);
				PED::SET_PED_RANDOM_COMPONENT_VARIATION(BoarID, 0);
				//PED::SET_PED_AS_GROUP_MEMBER(ped, group);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(BoarHash);
				BoarSpawner = false;
			}
		}
	}

	if (CowSpawner) //PedSpawner
	{
		if (STREAMING::HAS_MODEL_LOADED(CowHash))
		{
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
			CowID = PED::CREATE_PED(0x1A, CowHash, coords.x, coords.y, coords.z, 204.8112f, 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(CowID))
			{
				int netID = NETWORK::PED_TO_NET(CowID);
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(netID, true);
				PED::SET_PED_RANDOM_COMPONENT_VARIATION(CowID, 0);
				//PED::SET_PED_AS_GROUP_MEMBER(ped, group);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(CowHash);
				CowSpawner = false;
			}
		}
	}

	if (SharkSpawner) //PedSpawner
	{
		if (STREAMING::HAS_MODEL_LOADED(CowHash))
		{
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
			SharkID = PED::CREATE_PED(0x1A, SharkHash, coords.x, coords.y, coords.z, 204.8112f, 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(SharkID))
			{
				int netID = NETWORK::PED_TO_NET(SharkID);
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(netID, true);
				PED::SET_PED_RANDOM_COMPONENT_VARIATION(SharkID, 0);
				//PED::SET_PED_AS_GROUP_MEMBER(ped, group);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(SharkHash);
				SharkSpawner = false;
			}
		}
	}

	if (ControllDeer)
	{
		float goToOffsetBro[3];
		range = 4.0f;
		DeerSpeed = 2.0;
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_A))
		{
			range = 8.0f;
			DeerSpeed = 4.0;
		}
		GET_COORD_IN_FRONT_OF_GAMEPLAYCAM(range, goToOffsetBro);
		AI::TASK_LOOK_AT_COORD(DeerID, goToOffsetBro[0], goToOffsetBro[1], goToOffsetBro[2], 0, 0, 0);
		AI::TASK_GO_STRAIGHT_TO_COORD(DeerID, goToOffsetBro[0], goToOffsetBro[1], goToOffsetBro[2], DeerSpeed, 20000, 40000.0f, 0.5f);
	}

	if (ControllPig)
	{
		float goToOffsetBro[3];
		range = 4.0f;
		PigSpeed = 2.0;
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_A))
		{
			range = 8.0f;
			PigSpeed = 4.0;
		}
		GET_COORD_IN_FRONT_OF_GAMEPLAYCAM(range, goToOffsetBro);
		AI::TASK_LOOK_AT_COORD(PigID, goToOffsetBro[0], goToOffsetBro[1], goToOffsetBro[2], 0, 0, 0);
		AI::TASK_GO_STRAIGHT_TO_COORD(PigID, goToOffsetBro[0], goToOffsetBro[1], goToOffsetBro[2], PigSpeed, 20000, 40000.0f, 0.5f);
	}

	if (ControllBoar)
	{
		float goToOffsetBro[3];
		range = 4.0f;
		BoarSpeed = 2.0;
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_A))
		{
			range = 8.0f;
			BoarSpeed = 4.0;
		}
		GET_COORD_IN_FRONT_OF_GAMEPLAYCAM(range, goToOffsetBro);
		AI::TASK_LOOK_AT_COORD(BoarID, goToOffsetBro[0], goToOffsetBro[1], goToOffsetBro[2], 0, 0, 0);
		AI::TASK_GO_STRAIGHT_TO_COORD(BoarID, goToOffsetBro[0], goToOffsetBro[1], goToOffsetBro[2], BoarSpeed, 20000, 40000.0f, 0.5f);
	}

	if (ControllCow)
	{
		float goToOffsetBro[3];
		range = 4.0f;
		CowSpeed = 2.0;
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_A))
		{
			range = 8.0f;
			CowSpeed = 4.0;
		}
		GET_COORD_IN_FRONT_OF_GAMEPLAYCAM(range, goToOffsetBro);
		AI::TASK_LOOK_AT_COORD(CowID, goToOffsetBro[0], goToOffsetBro[1], goToOffsetBro[2], 0, 0, 0);
		AI::TASK_GO_STRAIGHT_TO_COORD(CowID, goToOffsetBro[0], goToOffsetBro[1], goToOffsetBro[2], CowSpeed, 20000, 40000.0f, 0.5f);
	}

	if (ControllShark)
	{
		float goToOffsetBro[3];
		range = 4.0f;
		SharkSpeed = 2.0;
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_A))
		{
			range = 8.0f;
			SharkSpeed = 4.0;
		}
		GET_COORD_IN_FRONT_OF_GAMEPLAYCAM(range, goToOffsetBro);
		AI::TASK_LOOK_AT_COORD(SharkID, goToOffsetBro[0], goToOffsetBro[1], goToOffsetBro[2], 0, 0, 0);
		AI::TASK_GO_STRAIGHT_TO_COORD(SharkID, goToOffsetBro[0], goToOffsetBro[1], goToOffsetBro[2], SharkSpeed, 20000, 40000.0f, 0.5f);
	}
	if (PedOnlineSpawner) //PedSpawner
	{
		if (STREAMING::HAS_MODEL_LOADED(PedSpawnerHash))
		{
			Ped Player = PLAYER::GET_PLAYER_PED(selectedPlayer);
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(Player, false);
			Ped ped = PED::CREATE_PED(0x1A, PedSpawnerHash, coords.x, coords.y, coords.z, 204.8112f, 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(ped))
			{
				int netID = NETWORK::PED_TO_NET(ped);
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(netID, true);
				PED::SET_PED_RANDOM_COMPONENT_VARIATION(ped, 0);
				//PED::SET_PED_AS_GROUP_MEMBER(ped, group);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(PedSpawnerHash);
				PedOnlineSpawner = false;
			}
		}
	}

	if (ObjectSpawnerNeeded)
	{
		if (STREAMING::HAS_MODEL_LOADED(ObjectSpawnerHash))
		{
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
			Object Object = OBJECT::CREATE_OBJECT(ObjectSpawnerHash, coords.x, coords.y + 6, coords.z, 1, 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(Object))
			{
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(ObjectSpawnerHash);
				ObjectSpawnerNeeded = false;
			}
		}
	}


	if (ModelChangerNeeded)
	{
		if (STREAMING::HAS_MODEL_LOADED(ModelChangerToHash))
		{
			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), ModelChangerToHash);
			PED::SET_PED_RANDOM_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 0);
			ModelChangerNeeded = false;
		}
	}

	if (deleteMyVeh)
	{
		Vehicle myVeh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1);
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(myVeh, 0, 1);
		VEHICLE::DELETE_VEHICLE(&myVeh);
		deleteMyVeh = false;
	}

	if (vehicleSpawnNeeded)
	{
		if (STREAMING::HAS_MODEL_LOADED(vehicleToSpawnHash))
		{
			Ped ped = PLAYER::PLAYER_PED_ID();
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(ped, false);
			Vehicle vehicle = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, coords.x, coords.y, coords.z, 0.0f, true, false);
			if (ENTITY::DOES_ENTITY_EXIST(vehicle))
			{
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, -1);
				maxVehicle(vehicle);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehicleToSpawnHash);
				vehicleSpawnNeeded = false;
			}
		}
	}
	if (vehicleSpawnNeededBlista)
	{
		if (STREAMING::HAS_MODEL_LOADED(BlistaHash))
		{
			Ped ped = PLAYER::PLAYER_PED_ID();
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(ped, false);
			blistaVeh = VEHICLE::CREATE_VEHICLE(BlistaHash, coords.x, coords.y, coords.z, 0.0f, true, false);
			if (ENTITY::DOES_ENTITY_EXIST(blistaVeh))
			{
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), blistaVeh, -1);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(BlistaHash);
				vehicleSpawnNeededBlista = false;
			}
		}
	}
	if (vehicleSpawnNeededBlista)
	{
		if (STREAMING::HAS_MODEL_LOADED(CarbonRSHash))
		{
			Ped ped = PLAYER::PLAYER_PED_ID();
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(ped, false);
			CarbonRSVeh = VEHICLE::CREATE_VEHICLE(CarbonRSHash, coords.x, coords.y, coords.z, 0.0f, true, false);
			if (ENTITY::DOES_ENTITY_EXIST(CarbonRSVeh))
			{
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), CarbonRSVeh, -1);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(CarbonRSHash);
				vehicleSpawnNeededBlista = false;
			}
		}
	}
	if (DragonMode)
	{
		Vector3 Mouth = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), 39317, 0.1f, 0.0f, 0.0f);
		FIRE::_ADD_SPECFX_EXPLOSION(Mouth.x, Mouth.y, Mouth.z, EXPLOSION_DIR_FLAME, EXPLOSION_DIR_FLAME, 1.0f, true, true, 0.0f);
	}
	if (DragonMode2)
	{
		Vector3 Mouth = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), 39317, 0.1f, 0.0f, 0.0f);
		FIRE::_ADD_SPECFX_EXPLOSION(Mouth.x, Mouth.y, Mouth.z, EXPLOSION_DIR_FLAME, EXPLOSION_DIR_FLAME, 1.0f, true, true, 0.0f);
	}
	if (DragonMode3)
	{
		int i = 0;
		int Handle2;
		for (i = 0; i < 16; i++)
		{
			if (i == PLAYER::PLAYER_ID()) continue;
			Handle2 = PLAYER::GET_PLAYER_PED(i);
			if (!ENTITY::DOES_ENTITY_EXIST(Handle2)) continue;
			Vector3 Mouth = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED(i), 39317, 0.1f, 0.0f, 0.0f);
			FIRE::_ADD_SPECFX_EXPLOSION(Mouth.x, Mouth.y, Mouth.z, EXPLOSION_DIR_FLAME, EXPLOSION_DIR_FLAME, 1.0f, true, true, 0.0f);
		}
	}
	if (Quick_Fix)
	{
		if (CONTROLS::IS_CONTROL_PRESSED(0, Button_R1))
		{
			int myvehicle;
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), 0))
			{
				myvehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), 0);
				if (ENTITY::DOES_ENTITY_EXIST(myvehicle) && ENTITY::IS_ENTITY_A_VEHICLE(myvehicle))
				{
					VEHICLE::SET_VEHICLE_FIXED(myvehicle);
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(myvehicle, 0.0f);
				}
			}
		}
	}
	/*
	if (ChangeGTName)
	{
	if (CONTROLS::IS_CONTROL_PRESSED(0, Button_R1))
	{
	GTChanger = "~r~Rockstar Support";
	strcpy((char*)(0x83DAC614), GTChanger); // GT CHanger 0x83DAC614
	strcpy((char*)(0xDFBCC1AC), GTChanger); // GT CHanger 0xDFBCC1AC
	}
	}
	if (TNChangeGTName)
	{
	if (CONTROLS::IS_CONTROL_PRESSED(0, Button_R1))
	{
	GTChanger = "~p~TN ~b~Elite Venom";
	//strcpy((char*)(0x83DAC614), GTChanger); // GT CHanger 0x83DAC614
	strcpy((char*)(0xDFBCC1AC), GTChanger); // GT CHanger 0xDFBCC1AC
	}
	}
	if (DevChangeGTName)
	{
	if (CONTROLS::IS_CONTROL_PRESSED(0, Button_R1))
	{
	GTChanger = "R* ~r~Dev";
	//strcpy((char*)(0x83DAC614), GTChanger); // GT CHanger 0x83DAC614
	strcpy((char*)(0xDFBCC1AC), GTChanger); // GT CHanger 0xDFBCC1AC
	}
	}
	if (PurgeChangeGTName)
	{
	if (CONTROLS::IS_CONTROL_PRESSED(0, Button_R1))
	{
	GTChanger = "~r~Purge ~b~Sucks";
	//strcpy((char*)(0x83DAC614), GTChanger); // GT CHanger 0x83DAC614
	strcpy((char*)(0xDFBCC1AC), GTChanger); // GT CHanger 0xDFBCC1AC
	}
	}
	if (AfricanChangeGTName)
	{
	if (CONTROLS::IS_CONTROL_PRESSED(0, Button_R1))
	{
	GTChanger = "~y~Aficans ~o~Suck";
	//strcpy((char*)(0x83DAC614), GTChanger); // GT CHanger 0x83DAC614
	strcpy((char*)(0xDFBCC1AC), GTChanger); // GT CHanger 0xDFBCC1AC
	}
	}
	if (ZenyleChangeGTName)
	{
	if (CONTROLS::IS_CONTROL_PRESSED(0, Button_R1))
	{
	GTChanger = "~g~Zenyle ~p~Menu";
	//strcpy((char*)(0x83DAC614), GTChanger); // GT CHanger 0x83DAC614
	strcpy((char*)(0xDFBCC1AC), GTChanger); // GT CHanger 0xDFBCC1AC
	}
	}
	if (XeTrinityChangeGTName)
	{
	if (CONTROLS::IS_CONTROL_PRESSED(0, Button_R1))
	{
	GTChanger = "~b~XeTrinityz ~c~HD";
	//strcpy((char*)(0x83DAC614), GTChanger); // GT CHanger 0x83DAC614
	strcpy((char*)(0xDFBCC1AC), GTChanger); // GT CHanger 0xDFBCC1AC
	}
	}
	if (DylN20ChangeGTName)
	{
	if (CONTROLS::IS_CONTROL_PRESSED(0, Button_R1))
	{
	GTChanger = "~r~DYL~g~4N.~y~20";
	//strcpy((char*)(0x83DAC614), GTChanger); // GT CHanger 0x83DAC614
	strcpy((char*)(0xDFBCC1AC), GTChanger); // GT CHanger 0xDFBCC1AC
	}
	}
	*/


	if (LoadingObject)
	{
		Vector3 Pos;
		if (Create_Object(ObjectString, "", Pos) == true)
		{
			LoadingObject = false;
			ObjectString = "";
		}
	}
	if (crashtesting)
	{
		Vector3 Position = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), false);

		float angle = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 10) * 3.14159265359;
		float radius = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 10) * 5.0f;
		float x = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).x + radius * SYSTEM::COS(angle);
		float y = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).y + radius * SYSTEM::SIN(angle);

		FIRE::ADD_EXPLOSION(x, y, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true).z + 1.0f, BLIMP, 0, 1, 0, 3.0f);

		int vehicles = VEHICLE::GET_CLOSEST_VEHICLE(Position.x, Position.y, Position.z, 500.0f, 0, 70);

		if (ENTITY::DOES_ENTITY_EXIST(vehicles))
		{
			if (NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehicles))
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(vehicles, 1, 5.0f, 5.0f, 5.0f, Position.x, Position.y, Position.z, 1, 1, 1, 1, 0, 1);
				ENTITY::SET_ENTITY_COORDS(vehicles, Position.x, Position.y + 20.0f, Position.z, true, false, false, true);
			}
		}
	}
	if (set_massacre_mode)
	{
		float tempCoords1[3];
		int tempHash;
		int tempPed = PLAYER::PLAYER_PED_ID();
		int tempVehicle;
		bool tick = 0;

		offset_from_entity(tempPed, GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(5.0f, 25.0f), GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(5.0f, 25.0f), GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(0.4f, 20.0f), tempCoords1);
		// Kick away naughty players
		for (int i = 0; i <= 29; i++)
		{
			if (PLAYER::IS_PLAYER_TARGETTING_ENTITY(i, tempPed) || PLAYER::IS_PLAYER_FREE_AIMING_AT_ENTITY(i, tempPed))
			{
				if (!tick)
				{
					NotifyAboveMap("~h~You~s~ are being aimed at. Taking care of it!");
					tick = true;
				}
				ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::GET_PLAYER_PED(i), 1, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 1, 1, 1, 1, 0, 1);
			}
		}
		// Kick away nearest vehicle
		tempVehicle = VEHICLE::GET_CLOSEST_VEHICLE(tempCoords1[0], tempCoords1[1], tempCoords1[2], 400.0f, 0, 16384);
		if (ENTITY::DOES_ENTITY_EXIST(tempVehicle)) ENTITY::APPLY_FORCE_TO_ENTITY(tempVehicle, 1, 5.0f, 5.0f, 5.0f, 5.0f, 13.0f, 6.5f, 1, 1, 1, 1, 0, 1);

		// Exploding vehicles
		switch (GAMEPLAY::GET_RANDOM_INT_IN_RANGE(1, 10))
		{
		case 1: tempHash = 3945366167; break;
		case 2: tempHash = 92612664; break;
		case 3: tempHash = 1488164764; break;
		case 4: tempHash = 117401876; break;
		case 5: tempHash = 408192225; break;
		case 6: tempHash = 3863274624; break;
		case 7: tempHash = 165154707; break;
		case 8: tempHash = 1011753235; break;
		case 9: tempHash = 941800958; break;
		case 10: tempHash = 970385471; break;
		}
		tempVehicle = VEHICLE::CREATE_VEHICLE(tempHash, tempCoords1[0], tempCoords1[1], tempCoords1[2], GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(0.0f, 360.0f), 1, 1);
		ENTITY::APPLY_FORCE_TO_ENTITY(tempVehicle, 1, 5.0f, 5.0f, 5.0f, 5.0f, 13.0f, 6.5f, 1, 1, 1, 1, 0, 1);
		NETWORK::NETWORK_EXPLODE_VEHICLE(tempVehicle, 1, 1, 1);

		// Dying peds
		switch (GAMEPLAY::GET_RANDOM_INT_IN_RANGE(1, 10))
		{
		case 1: tempHash = 1682622302; break;
		case 2: tempHash = 113504370; break;
		case 3: tempHash = 4244282910; break;
		case 4: tempHash = 808859815; break;
		case 5: tempHash = 1004114196; break;
		case 6: tempHash = 3696858125; break;
		case 7: tempHash = 921110016; break;
		case 8: tempHash = 880829941; break;
		case 9: tempHash = 1462895032; break;
		case 10: tempHash = 773063444; break;
		}

		offset_from_entity(tempPed, GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(5.0f, 25.0f), GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(5.0f, 25.0f), GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(0.4f, 20.0f), tempCoords1);
		tempPed = PED::CREATE_PED(22, tempHash, tempCoords1[0], tempCoords1[1], tempCoords1[2], GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(0.0f, 360.0f), 1, 1);
		ENTITY::APPLY_FORCE_TO_ENTITY(tempPed, 1, 5.0f, 5.0f, 5.0f, 5.0f, 13.0f, 6.5f, 1, 1, 1, 1, 0, 1);
		PED::EXPLODE_PED_HEAD(tempPed, 324506233);
		FIRE::ADD_EXPLOSION(tempCoords1[0], tempCoords1[1], tempCoords1[2], 26, 4.0f, 1, 0, 3.0f);

		// Water hydrants
		offset_from_entity(tempPed, GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(5.0f, 25.0f), GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(5.0f, 25.0f), GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(0.4f, 20.0f), tempCoords1);
		FIRE::ADD_EXPLOSION(tempCoords1[0], tempCoords1[1], tempCoords1[2], 13, 8.0f, 1, 0, 3.0f);

		// Zombies
		offset_from_entity(tempPed, GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(5.0f, 25.0f), GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(5.0f, 25.0f), GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(0.4f, 20.0f), tempCoords1);
		tempPed = PED::CREATE_PED(22, -1404353274, tempCoords1[0], tempCoords1[1], tempCoords1[2], GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(0.0f, 360.0f), 1, 1);
		NETWORK::PED_TO_NET(tempPed);
		PED::SET_PED_COMBAT_ABILITY(tempPed, 100);
		AI::TASK_COMBAT_HATED_TARGETS_AROUND_PED(tempPed, 400.0f, 0);
	}

	if (Cash_Gun)
	{
		if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
		{
			//float COORDS[6];
			//WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), COORDS);
			//float COORDS[6];
			//WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), COORDS);
			Vector3 COORDS;
			GetPedLastWeaponImpactCoord(PLAYER::PLAYER_PED_ID(), &COORDS);
			//FIRE::ADD_EXPLOSION( COORDS.x, COORDS.y, COORDS.z, DIR_FLAME, 5, 1, 0, 5);
			VEHICLE::CREATE_VEHICLE(0x6322B39A, COORDS.x, COORDS.y, COORDS.z, 0.0f, true, false);
			printf("\Coords = {%f, %f, %f};\n", COORDS.x, COORDS.y, COORDS.z);
			ShowMessageOnScreen("~b~ Coords = %f, %f, %f", COORDS.x, COORDS.y, COORDS.z);
		}
	}
	if (Creator_Mode)
	{
		if (PLAYER::_GET_AIMED_ENTITY(PLAYER::PLAYER_ID(), &objecthandle))
		{
			if (ENTITY::IS_ENTITY_A_VEHICLE(objecthandle))
			{
			}
			if (ENTITY::IS_ENTITY_AN_OBJECT(objecthandle))
			{
			}
		}
	}
	if (ObjectCashDrop)
	{
		float ObjCashcoords[3];
		ENTITY::GET_ENTITY_COORDS3(objecthandle, ObjCashcoords);
		STREAMING::REQUEST_MODEL(0x113FD533);
		if (STREAMING::HAS_MODEL_LOADED(0x113FD533))
		{
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, ObjCashcoords[0], ObjCashcoords[1], ObjCashcoords[2] + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, ObjCashcoords[0], ObjCashcoords[1], ObjCashcoords[2] + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, ObjCashcoords[0], ObjCashcoords[1], ObjCashcoords[2] + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, ObjCashcoords[0], ObjCashcoords[1], ObjCashcoords[2] + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, ObjCashcoords[0], ObjCashcoords[1], ObjCashcoords[2] + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, ObjCashcoords[0], ObjCashcoords[1], ObjCashcoords[2] + 1.1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, ObjCashcoords[0], ObjCashcoords[1], ObjCashcoords[2] + 1.1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, ObjCashcoords[0], ObjCashcoords[1], ObjCashcoords[2] + 1.1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, ObjCashcoords[0], ObjCashcoords[1], ObjCashcoords[2] + 1.1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, ObjCashcoords[0], ObjCashcoords[1], ObjCashcoords[2] + 1.1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, ObjCashcoords[0] + 0.1, ObjCashcoords[1], ObjCashcoords[2] + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, ObjCashcoords[0] + 0.1, ObjCashcoords[1], ObjCashcoords[2] + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, ObjCashcoords[0] + 0.1, ObjCashcoords[1], ObjCashcoords[2] + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, ObjCashcoords[0] + 0.1, ObjCashcoords[1], ObjCashcoords[2] + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, ObjCashcoords[0] + 0.1, ObjCashcoords[1], ObjCashcoords[2] + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, ObjCashcoords[0], ObjCashcoords[1] + 0.1, ObjCashcoords[2] + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, ObjCashcoords[0], ObjCashcoords[1] + 0.1, ObjCashcoords[2] + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, ObjCashcoords[0], ObjCashcoords[1] + 0.1, ObjCashcoords[2] + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, ObjCashcoords[0], ObjCashcoords[1] + 0.1, ObjCashcoords[2] + 1, 0, 40000, 0x113FD533, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, ObjCashcoords[0], ObjCashcoords[1] + 0.1, ObjCashcoords[2] + 1, 0, 40000, 0x113FD533, 0, 1);
		}
	}
	if (ObjectCashDrop2k)
	{
		float ObjCashcoords[3];
		ENTITY::GET_ENTITY_COORDS3(objecthandle, ObjCashcoords);
		STREAMING::REQUEST_MODEL(CashDropItem);
		if (STREAMING::HAS_MODEL_LOADED(CashDropItem))
		{
			OBJECT::CREATE_AMBIENT_PICKUP(CashDropItem, ObjCashcoords[0], ObjCashcoords[1], ObjCashcoords[2] + 1, 0, 2000, CashDropItem, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(CashDropItem, ObjCashcoords[0], ObjCashcoords[1], ObjCashcoords[2] + 1, 0, 2000, CashDropItem, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(CashDropItem, ObjCashcoords[0], ObjCashcoords[1], ObjCashcoords[2] + 1, 0, 2000, CashDropItem, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(CashDropItem, ObjCashcoords[0], ObjCashcoords[1], ObjCashcoords[2] + 1, 0, 2000, CashDropItem, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(CashDropItem, ObjCashcoords[0], ObjCashcoords[1], ObjCashcoords[2] + 1, 0, 2000, CashDropItem, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(CashDropItem, ObjCashcoords[0], ObjCashcoords[1], ObjCashcoords[2] + 1.1, 0, 2000, CashDropItem, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(CashDropItem, ObjCashcoords[0], ObjCashcoords[1], ObjCashcoords[2] + 1.1, 0, 2000, CashDropItem, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(CashDropItem, ObjCashcoords[0], ObjCashcoords[1], ObjCashcoords[2] + 1.1, 0, 2000, CashDropItem, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(CashDropItem, ObjCashcoords[0], ObjCashcoords[1], ObjCashcoords[2] + 1.1, 0, 2000, CashDropItem, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(CashDropItem, ObjCashcoords[0], ObjCashcoords[1], ObjCashcoords[2] + 1.1, 0, 2000, CashDropItem, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(CashDropItem, ObjCashcoords[0] + 0.1, ObjCashcoords[1], ObjCashcoords[2] + 1, 0, 2000, CashDropItem, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(CashDropItem, ObjCashcoords[0] + 0.1, ObjCashcoords[1], ObjCashcoords[2] + 1, 0, 2000, CashDropItem, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(CashDropItem, ObjCashcoords[0] + 0.1, ObjCashcoords[1], ObjCashcoords[2] + 1, 0, 2000, CashDropItem, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(CashDropItem, ObjCashcoords[0] + 0.1, ObjCashcoords[1], ObjCashcoords[2] + 1, 0, 2000, CashDropItem, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(CashDropItem, ObjCashcoords[0] + 0.1, ObjCashcoords[1], ObjCashcoords[2] + 1, 0, 2000, CashDropItem, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(CashDropItem, ObjCashcoords[0], ObjCashcoords[1] + 0.1, ObjCashcoords[2] + 1, 0, 2000, CashDropItem, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(CashDropItem, ObjCashcoords[0], ObjCashcoords[1] + 0.1, ObjCashcoords[2] + 1, 0, 2000, CashDropItem, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(CashDropItem, ObjCashcoords[0], ObjCashcoords[1] + 0.1, ObjCashcoords[2] + 1, 0, 2000, CashDropItem, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(CashDropItem, ObjCashcoords[0], ObjCashcoords[1] + 0.1, ObjCashcoords[2] + 1, 0, 2000, CashDropItem, 0, 1);
			OBJECT::CREATE_AMBIENT_PICKUP(CashDropItem, ObjCashcoords[0], ObjCashcoords[1] + 0.1, ObjCashcoords[2] + 1, 0, 2000, CashDropItem, 0, 1);
		}
	}
}
#pragma endregion
#pragma region Text
//Star

void ShowMessageOnScreen(char* msg)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(msg);
	UI::_DRAW_NOTIFICATION(0, 1);
}

int scaleform;
int gGlareHandle;
float gGlareDir;

float conv360(float base, float min, float max) {
	// This is the function the script used. I just adapted it for C++.
	float fVar0;
	if (min == max) return min;
	fVar0 = max - min;
	//  base -= round(base - min / fVar0) * fVar0;
	if (base < min) base += fVar0;
	return base;
}

void drawGlare(float PX, float PY, float SX, float SY, int ColorR, int ColorG, int ColorB) {
	// Request the scaleform
	gGlareHandle = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_MENU_GLARE");
	// Get Player Camera Rotation
	Vector3 rot = CAM::_GET_GAMEPLAY_CAM_ROT(2);
	// Calculate Glare Rotation
	float dir = conv360(rot.z, 0, 360);
	// Check if custom rotation is necessary for the rotation component.
	if ((gGlareDir == 0 || gGlareDir - dir > 0.5) || gGlareDir - dir < -0.5) {
		// Set global variable to current direction
		gGlareDir = dir;
		// Open Data Slot Function
		CAM::_PUSH_SCALEFORM_MOVIE_FUNCTION(gGlareHandle, "SET_DATA_SLOT");
		// Set Data Slot Value/Parameter
		CAM::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_FLOAT(gGlareDir);
		// Close Data Slot Function
		CAM::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
	}
	// Draw Scaleform
	CAM::DRAW_SCALEFORM_MOVIE(gGlareHandle, PX, PY, SX, SY, ColorR, ColorG, ColorB, 220, 0); // Custom positioning & size
																							 // DRAW_SCALEFORM_MOVIE_FULLSCREEN(gGlareHandle, r, g, b, 255, 0); // Default positioning & size
}


bool Title;
float dx = 0.16f, dy = 0.081f, dsx = 0.40, dxy = 0.20;
void AddSubTitle(char *title)
{
	drawText(title, bannerSubTextFont, menuXCoord, TitleY, TitleX, TitleY2, bannerSubTextRed, bannerSubTextGreen, bannerSubTextBlue, bannerSubTextOpacity, true);
	GRAPHICS::DRAW_RECT(menuXCoord, DrawTittleY, DrawTittleX, DrawTittleY2, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity);
	drawGlare(GlobeCoordX, GlobeCoordY, GlobeCoordSX, Globecord, bannerRectRed, bannerRectGreen, bannerRectBlue);
}

void gradientconfig()
{
	if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED("shared"))
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("shared", 0);
	}
}
int Globe;
void MENU_GLARE() {

	Globe = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_MENU_GLARE");
	GRAPHICS::_0x215ABBE8(Globe, "SET_DATA_SLOT");
	GRAPHICS::_0x9A01FFDA(33);
	GRAPHICS::_0x02DBF2D7();
	float menuXCoord = 0.847f;
	GRAPHICS::DRAW_SCALEFORM_MOVIE(Globe, menuXCoord + 0.295, 0.525f, 0.90f, 1.0300f, 255, 0, 0, 255, 0);
	GRAPHICS::_0x76C641E4(0.500, 0.0, 0.2, 0.2);
	GRAPHICS::_0x228A2598(76, 84);
	GRAPHICS::_0x76C641E4(0.1500, 0.02000, 0, 0);
	GRAPHICS::_0x3FE33BD6();

}
void addTitle(char *title)
{
	drawText(title, bannerTextFont, menuXCoord, 0.1f, 0.20f, 0.75f, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, true);
	UI::SET_TEXT_DROPSHADOW(5, 0, 78, 255, 255);
	//GRAPHICS::DRAW_RECT(menuXCoord, 0.1175f, 0.19f, 0.110f, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity);
	MENU_GLARE();
}


void makerobject()
{
	int maker = 22;
	Vector3 Loc = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(SpawnedObject[SelectedObject]), 0.0, 0.0, 1.5f);
	GRAPHICS::DRAW_MARKER(maker, Loc.x, Loc.y, Loc.z, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f, 0.0f, 0.7f, 0.7f, 0.7f, 0, 50, 255, 50, 1, 1, 2, 1, 0, 0, 0);
}
bool IS_PLAYER_FRIEND(Player player)
{
	bool PyIsFriend = false;
	int handle[76];
	NETWORK::NETWORK_HANDLE_FROM_PLAYER12(player, &handle[0], 13);
	if (NETWORK::NETWORK_IS_HANDLE_VALID(&handle[0], 13))
	{
		PyIsFriend = NETWORK::NETWORK_IS_FRIEND(&handle[0]);
	}
	if (PyIsFriend)
		PyIsFriend = true;
	else
		PyIsFriend = false;

	return PyIsFriend;
}
bool PLAYER_PLAYING_INF_SELC = false;
void PlayerInfo(bool selectedPlayerinf)
{
	Player ui_slectedPlayer = selectedPlayerinf, ui_currentPlayer = (currentOption - 1);
	/*DRAW ENTITY OF PLAYER VISUAL*/
	//ARROWS
	int maker = 22;
	float maker2 = 1.40;
	Vector3 Loc = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayerinf ? ui_slectedPlayer : ui_currentPlayer), 0.0, 0.0, 1.5f);
	GRAPHICS::DRAW_MARKER(maker, Loc.x, Loc.y, Loc.z, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f, 0.0f, 0.7f, 0.7f, 0.7f, 0, 50, 255, 50, 1, 1, 2, 1, 0, 0, 0);
	int maker1 = 27;
	float maker12 = -2.46;
	GRAPHICS::DRAW_MARKER(maker1, Loc.x, Loc.y, Loc.z + maker12, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f, 0.0f, 0.7f, 0.7f, 0.7f, 0, 50, 255, 50, 0, 1, 2, 1, 0, 0, 0);
	//LINE
	Vector3 Pos777;
	Vector3 Pos2;
	int PedID = PLAYER::GET_PLAYER_PED(selectedPlayerinf ? ui_slectedPlayer : ui_currentPlayer);
	Pos777 = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
	Pos2 = ENTITY::GET_ENTITY_COORDS(PedID, false);
	GRAPHICS::DRAW_LINE(Pos777.x, Pos777.y, Pos777.z, Pos2.x, Pos2.y, Pos2.z, 0, 50, 255, 255);
	/*DRAW PLAYER INFO*/
	int playerHealt = ENTITY::GET_ENTITY_HEALTH(PLAYER::GET_PLAYER_PED(selectedPlayerinf ? ui_slectedPlayer : ui_currentPlayer));
	Vector3 Pos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayerinf ? ui_slectedPlayer : ui_currentPlayer), 1);
	int playerCar = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(selectedPlayerinf ? ui_slectedPlayer : ui_currentPlayer), 0);
	int thisPlayersCar = ENTITY::GET_ENTITY_MODEL(playerCar);
	char buf[1000];
	char buf2[1000];

	snprintf(buf2, sizeof(buf2), "~w~Player Name: ~s~%s", PLAYER::GET_PLAYER_NAME(selectedPlayerinf ? ui_slectedPlayer : ui_currentPlayer));
	drawTextxxx2(buf2, 0, 0.2f, 0.775f, Subx2, Suby2, 0, 50, 255, 255, false);

	snprintf(buf, sizeof(buf), "~w~Position: ~s~X = %f, Y = %f, Z = %f", Pos.x, Pos.y, Pos.z);
	drawTextxxx2(buf, 0, 0.2f, 0.80f, Subx2, Suby2, 0, 50, 255, 255, false);

	snprintf(buf2, sizeof(buf2), "~w~Vehicle: ~s~%s", VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(thisPlayersCar));
	drawTextxxx2(buf2, 0, 0.2f, 0.825f, Subx2, Suby2, 0, 50, 255, 255, false);

	{
		if (NETWORK::NETWORK_PLAYER_HAS_HEADSET(selectedPlayerinf ? ui_slectedPlayer : ui_currentPlayer))
		{
			char buf[30];
			snprintf(buf, sizeof(buf), "~w~Headset: ~s~Has Headset");
			drawTextxxx2(buf, 0, 0.2f, 0.85f, Subx2, Suby2, 0, 50, 255, 255, false);
		}

		else if (!NETWORK::NETWORK_PLAYER_HAS_HEADSET(selectedPlayerinf ? ui_slectedPlayer : ui_currentPlayer))
		{
			char buf[30];
			snprintf(buf, sizeof(buf), "~w~Headset: ~s~No Headset");
			drawTextxxx2(buf, 0, 0.2f, 0.85, Subx2, Suby2, 0, 50, 255, 255, false);
		}
	}
	{
		if (NETWORK::NETWORK_IS_PLAYER_MUTED_BY_ME(selectedPlayerinf ? ui_slectedPlayer : ui_currentPlayer))
		{
			char buf[30];
			snprintf(buf, sizeof(buf), "~w~Muted Me: ~s~Yes");
			drawTextxxx2(buf, 0, 0.2f, 0.875, Subx2, Suby2, 0, 50, 255, 255, false);
		}

		else if (!NETWORK::NETWORK_IS_PLAYER_MUTED_BY_ME(selectedPlayerinf ? ui_slectedPlayer : ui_currentPlayer))
		{
			char buf[30];
			snprintf(buf, sizeof(buf), "~w~Muted Me: ~s~No");
			drawTextxxx2(buf, 0, 0.2f, 0.875, Subx2, Suby2, 0, 50, 255, 255, false);
		}
	}
	if (openset)
	{
		AdjustB = Button_R1;
		AdjustB2 = Button_X;
	}
	if (openset1)
	{
		AdjustB = Button_R1;
		AdjustB2 = Button_A;
	}
	if (openset2)
	{
		AdjustB = Button_R1;
		AdjustB2 = Dpad_Down;
	}
	if (openset3)
	{
		AdjustB = Dpad_Right;
		AdjustB2 = Button_X;
	}
	if (openset4)
	{
		AdjustB = Dpad_Left;
		AdjustB2 = Button_X;
	}
	if (crashtest)
	{
		crashtestv4(selectedPlayer);
	}
	if (crashtest2)
	{
		crashtestv3(selectedPlayer);
	}
	if (GTAVOnlineCheatsTest)
	{
		if (!STREAMING::_HAS_DLC_PTFX_LOADED("scr_rcbarry1")) {
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry1");
		}
		else {
			float f1;
			f1 = 1.0;
			GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry1");
			GRAPHICS::_START_FWPARTICLE_FX_NON_LOOPED_AT_COORD("scr_alien_teleport", pcoords[0], pcoords[1], pcoords[2], 0.0f, 0.0f, 0.0f, 10.0f, 0, 0, 0);
			GTAVOnlineCheatsTest = false;
		}
	}
	if (GhostFuego1) {//ghost rider head
		if (!STREAMING::_HAS_DLC_PTFX_LOADED("scr_rcbarry1")) {
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry1");
		}
		else {
			float f1;
			f1 = 1.0;
			GRAPHICS::_0x9C720B61_PALOMO("scr_rcbarry1");
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2(pexp, pcoords[0], pcoords[1], pcoords[2], 0.0f, 0.0f, 0.0f, 50.0f, 0, 0, 0);
			GhostFuego1 = true;
		}
	}
	if (doWheelbarrow)
	{
		if (spawnWheelbarrow())
		{
			doWheelbarrow = false;
		}
	}
	if (doBumpercar)
	{
		if (spawnBumpercar())
		{
			doBumpercar = false;
		}
	}
	if (doWheelchair)
	{
		if (spawnWheelchair())
		{
			doWheelchair = false;
		}
	}
	if (doCouch)
	{
		if (spawnCouch())
		{
			doCouch = false;
		}
	}
	if (doToilet)
	{
		{
			doToilet = false;
		}
	}
	if (doTrolley)
	{
		if (spawnTrolley())
		{
			doTrolley = false;
		}
	}
}


