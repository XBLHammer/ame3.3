#include "Variables.h"

#pragma region Internal
int snprintf(char *buffer, size_t len, const char *fmt, ...)
{
	va_list args;
	int i;

	va_start(args, fmt);
	i = vsnprintf(buffer, len, fmt, args);
	va_end(args);
	return i;
}
void drawNotification(char* msg)
{
	UI::_0xF42C43C7("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(msg);
	UI::_0x38F82261(3000, 1);
}
void InfoBox(char* Message)
{
	UI::_SET_TEXT_COMPONENT_FORMAT("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(Message);
	UI::_DISPLAY_HELP_TEXT_FROM_STRING_LABEL(0, false, false, -1);
}
char printMessageBuffer[256];
void PrintToScreenNum(int number, float x, float y, int r, int g, int b, int a, float scaleX, float scaleY, int centerText, int font) {
	
	sprintf(printMessageBuffer, "%d", number);
	VMArgs[2][0] = (int)printMessageBuffer;
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_COLOUR(r, g, b, a);
	UI::SET_TEXT_SCALE(scaleX, scaleY);
	UI::SET_TEXT_OUTLINE();
	UI::SET_TEXT_CENTRE(centerText);
	UI::_SET_TEXT_ENTRY("STRING");
	int (__cdecl *unk)(void *) = (int (__cdecl *)(void *))0x8291CA80;
	unk(printMessageBuffer);
	UI::_DRAW_TEXT(x, y);
}
void PrintToScreen(char *str, float x, float y, int r, int g, int b, int a, float scaleX, float scaleY, int centerText, int font) {

	VMArgs[2][0] = (int)str;
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_COLOUR(r, g, b, a);
	UI::SET_TEXT_SCALE(scaleX, scaleY);
	UI::SET_TEXT_OUTLINE();
	UI::SET_TEXT_CENTRE(centerText);
	UI::_SET_TEXT_ENTRY("STRING");
	int (__cdecl *unk)(void *) = (int (__cdecl *)(void *))0x8291CA80;
	unk(str);
	UI::_DRAW_TEXT(x, y);
}
void PrintToScreenFloat(float number, float x, float y, int r, int g, int b, int a, float scaleX, float scaleY, int centerText, int font) {

	sprintf(printMessageBuffer, "%f", number);
	VMArgs[2][0] = (int)printMessageBuffer;
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_COLOUR(r, g, b, a);
	UI::SET_TEXT_SCALE(scaleX, scaleY);
	UI::SET_TEXT_OUTLINE();
	UI::SET_TEXT_CENTRE(centerText);
	UI::_SET_TEXT_ENTRY("STRING");
	int (__cdecl *unk)(void *) = (int (__cdecl *)(void *))0x8291CA80;
	unk(printMessageBuffer);
	UI::_DRAW_TEXT(x, y);
}
float PixelX(int Input)
{
	return (float)Input / (float)1280;
}
float PixelY(int Input)
{
	return (float)Input / (float)720;
}
void SetupTimer(int tickTime)
{
	if (newTimerTick) {
		maxTimerCount = GAMEPLAY::GET_GAME_TIMER() + tickTime;
		newTimerTick = false;
	}
}
bool IsTimerReady()
{
	return GAMEPLAY::GET_GAME_TIMER() > maxTimerCount;
}
void ResetTimer()
{
	newTimerTick = true;
}
void SetupTimer1(int tickTime)
{
	if (newTimerTick1) {
		maxTimerCount1 = GAMEPLAY::GET_GAME_TIMER() + tickTime;
		newTimerTick1 = false;
	}
}
bool IsTimerReady1()
{
	return GAMEPLAY::GET_GAME_TIMER() > maxTimerCount1;
}
void ResetTimer1()
{
	newTimerTick1 = true;
}
void set_text_component(char *text)
{
	GRAPHICS::_0x3AC9CB55("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	GRAPHICS::_0x386CE0B8();
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
void startKeyboard(int action, char *defaultText, int maxLength)
{
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(0, "FMMC_KEY_TIP8", "", defaultText, "", "", "", maxLength);
	keyboardAction = action;
	keyboardActive = true;
}
void playSound(char* sound)
{
	if (menuSounds)
		AUDIO::PLAY_SOUND_FRONTEND(-1, sound, "HUD_FRONTEND_DEFAULT_SOUNDSET");
}
void drawText(char * text, int font, float x, float y, float scalex, float scaley, int r, int b, int g, int a, bool center)
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
void addSprite(char * streamed_texture, char * texture_name, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
{
	if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(streamed_texture))
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(streamed_texture, false);
	}
	GRAPHICS::DRAW_SPRITE(streamed_texture, texture_name, x, y, width, height, rotation, r, g, b, a);
}
#pragma endregion
#pragma region Option Helpers
int getOption()
{
	xInstruction = true;
	if (optionPress)
		return currentOption;
	else return 0;
}
void addTitle(char *title)
{
	drawText(title, bannerTextFont, menuXCoord, 0.1f, 0.75f, 0.75f, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, true);
	GRAPHICS::DRAW_RECT(menuXCoord, 0.11f, 0.20f, 0.0995f, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity);

	int movie = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_MENU_GLARE");
	GRAPHICS::DRAW_SCALEFORM_MOVIE(movie, menuXCoord + 0.303, 0.525f, 0.90f, 1.0300f, 255, 255, 255, 255, 0);
	GRAPHICS::_0x215ABBE8(movie, "SET_DATA_SLOT");
	GRAPHICS::_0x02DBF2D7();
	GRAPHICS::_0x215ABBE8(movie, "SET_CLEAR_SPACE");
	GRAPHICS::_0x9A01FFDA(200);
	GRAPHICS::_0x02DBF2D7();
}
void addOption(char *option, char *info = NULL)
{
	optionCount++;
	char buf[120];
	if (currentOption == optionCount)
	{
		infoText = info;
		snprintf(buf, sizeof(buf), " %s", option);
	} else {
		snprintf(buf, sizeof(buf), "%s", option);
	}
	if (currentOption <= maxOptions && optionCount <= maxOptions)
	{
		drawText(buf, optionsFont, textXCoord, (optionCount * 0.035f + 0.125f), 0.4f, 0.4f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
	}
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
	{
		drawText(buf, optionsFont, textXCoord, ((optionCount - (currentOption - maxOptions)) * 0.035f + 0.125f), 0.4f, 0.4f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
	}
}
void changeSubmenu(int newSubmenu)
{
	lastSubmenu[submenuLevel] = submenu;
	lastOption[submenuLevel] = currentOption;
	currentOption = 1;
	submenu = newSubmenu;
	submenuLevel++;
}
void addSubmenuOption(char *option, int newSubmenu, char *info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress)
		{
			changeSubmenu(newSubmenu);
		}
	}
}
void addBoolOption(char *option, bool b00l, char *info = NULL)
{
	char buf[120];
	if (b00l)
	{
		if (currentOption <= maxOptions && optionCount <= maxOptions)
		{
			addSprite("CommonMenu", "Shop_Box_TickB", menuXCoord + 0.09, (((optionCount + 1) * 0.035f) + 0.1415f), 0.03f, 0.04f, 0.0f, 255, 255, 255, 255);
		}
		else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
		{
			addSprite("CommonMenu", "Shop_Box_TickB", menuXCoord + 0.09, ((optionCount - (currentOption - maxOptions)) * 0.035f + 0.2175f), 0.03f, 0.04f, 0.0f, 255, 255, 255, 255);
		}
		snprintf(buf, sizeof(buf), "%s", option);
		addOption(buf, info);
	}
	else if(!b00l)
	{
		if (currentOption <= maxOptions && optionCount <= maxOptions)
		{
			addSprite("CommonMenu", "Shop_Box_BlankB", menuXCoord + 0.09, (((optionCount + 1) * 0.035f) + 0.1415f), 0.03f, 0.04f, 0.0f, 255, 255, 255, 255);
		}
		else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
		{
			addSprite("CommonMenu", "Shop_Box_BlankB", menuXCoord + 0.09, ((optionCount - (currentOption - maxOptions)) * 0.035f + 0.2175f), 0.03f, 0.04f, 0.0f, 255, 255, 255, 255);
		}
		snprintf(buf, sizeof(buf), "%s", option);
		addOption(buf, info);
	}
}
template<typename TYPE>
void addCustomBoolOption(char *option, TYPE value, TYPE match, char *info = NULL)
{
	char buf[120];
	if (value == match)
	{
		snprintf(buf, sizeof(buf), "%s: On", option);
		addOption(buf, info);
	}
	else
	{
		snprintf(buf, sizeof(buf), "%s: Off", option);
		addOption(buf, info);
	}
}
void varXYCoord(char *var)
{
	unsigned char* string = (unsigned char*)var;
	int str = strlen((char*)string);
	float len = str * 0.0035f;

	if (currentOption <= maxOptions && optionCount <= maxOptions)
	{
		drawText(var, optionsFont, textXCoord - len + 0.1975, (optionCount * 0.035f + 0.125f), 0.4f, 0.4f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, 1);
	}
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
	{
		drawText(var, optionsFont, textXCoord - len + 0.1975, ((optionCount - (currentOption - maxOptions)) * 0.035f + 0.125f), 0.4f, 0.4f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, 1);
	}
}
void addIntOption(char *option, int *var, int min, int max, bool keyboard, char *info = NULL)
{
	char buf[120];
	snprintf(buf, sizeof(buf), "%s: ", option);
	addOption(buf, info);

	char bufvar[30];
	snprintf(bufvar, sizeof(bufvar), "[ %i ]", *var);
	varXYCoord(bufvar);
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
void addFloatStringOption(char *option, float *var, float varIncrement, float min, float max, bool holdPress, char *info = NULL)
{
	char buf[120];
	snprintf(buf, sizeof(buf), "%s: [ %s ]", option, FtoS(*var));
	addOption(buf, info);
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
					*var = *var + varIncrement;
			}
			else if (fastLeftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - varIncrement;
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
					*var = *var + varIncrement;
			}
			else if (leftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - varIncrement;
			}
		}
	}
}
void addBoolFloatOption(char *option, float *var, bool b00l, float min, float max, bool holdPress, char *info = NULL)
{
	char buf[120];
	snprintf(buf, sizeof(buf), "%s: [ %f ]", option, *var);
	addBoolOption(buf, b00l, info);
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
void addFloatOption(char *option, float *var, float min, float max, bool holdPress, char *info = NULL)
{
	char buf[120];
	snprintf(buf, sizeof(buf), "%s: [ %g ]", option, *var);
	addOption(buf, info);
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
					*var = *var + 0.008f;
			}
			else if (fastLeftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 0.008f;
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
					*var = *var + 0.008f;
			}
			else if (leftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 0.008f;
			}
		}
	}
}
void addCustomFloatOption(char *option, float *var, float varIncrement, float min, float max, bool holdPress, char *info = NULL)
{
	char buf[120];
	snprintf(buf, sizeof(buf), "%s: [ %g ]", option, *var);
	addOption(buf, info);
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
					*var = *var + varIncrement;
			}
			else if (fastLeftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - varIncrement;
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
					*var = *var + varIncrement;
			}
			else if (leftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - varIncrement;
			}
		}
	}
}
void addCharOption(char *optionName, char *string, int *var, int max, char *info = NULL)
{
	char buf[120];
	snprintf(buf, sizeof(buf), "%s: [ %s ]", optionName, string);
	addOption(buf, info);
	if (currentOption == optionCount)
	{
		lrInstruction = true;
		if (rightPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var >= max)
				*var = 0;
			else
				*var = *var + 1;
		}
		else if (leftPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var <= 0)
				*var = max;
			else
				*var = *var - 1;
		}
	}
}
void addCharCustomOption(char *string, int *var, int max, char *info = NULL)
{
	char buf[120];
	snprintf(buf, sizeof(buf), "[ %s ]", string);
	addOption(buf, info);
	if (currentOption == optionCount)
	{
		lrInstruction = true;
		if (rightPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var >= max)
				*var = 0;
			else
				*var = *var + 1;
		}
		else if (leftPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var <= 0)
				*var = max;
			else
				*var = *var - 1;
		}
	}
}
void addCharBoolOption(char *optionName, bool b00l, char *string, int *var, int max, char *info = NULL)
{
	char buf[120];
	snprintf(buf, sizeof(buf), "%s: [ %s ]", optionName, string);
	addBoolOption(buf, b00l, info);
	if (currentOption == optionCount)
	{
		lrInstruction = true;
		if (rightPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var >= max)
				*var = 0;
			else
				*var = *var + 1;
		}
		else if (leftPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var <= 0)
				*var = max;
			else
				*var = *var - 1;
		}
	}
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
#pragma endregion
void normalMenuActions()
{
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
		GRAPHICS::DRAW_RECT(menuXCoord, (((maxOptions * 0.035f) / 2) + 0.159f), 0.20f, (maxOptions * 0.035f), backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity); //Background
		if (currentOption > maxOptions)
		{
			GRAPHICS::DRAW_RECT(menuXCoord, ((maxOptions * 0.035f) + 0.1415f), 0.20f, 0.031f, bannerRectRed, bannerRectGreen, bannerRectBlue, scrollerOpacity);
			addSprite("helicopterhud", "hud_corner", (textXCoord + 0.002f), ((maxOptions * 0.035f) + 0.1315f), 0.025f, 0.025f, 0, 255, 255, 255, 255);
			addSprite("helicopterhud", "hud_corner", (textXCoord + 0.188f), ((maxOptions * 0.035f) + 0.1515f), 0.025f, 0.025f, 180, 255, 255, 255, 255);
		}
		else
		{
			GRAPHICS::DRAW_RECT(menuXCoord, ((currentOption * 0.035f) + 0.1415f), 0.20f, 0.031f, bannerRectRed, bannerRectGreen, bannerRectBlue, scrollerOpacity);
			addSprite("helicopterhud", "hud_corner", (textXCoord + 0.002f), ((currentOption * 0.035f) + 0.1315f), 0.025f, 0.025f, 0, 255, 255, 255, 255);
			addSprite("helicopterhud", "hud_corner", (textXCoord + 0.188f), ((currentOption * 0.035f) + 0.1515f), 0.025f, 0.025f, 180, 255, 255, 255, 255);
		}
	}
	else
	{
		GRAPHICS::DRAW_RECT(menuXCoord, (((optionCount * 0.035f) / 2) + 0.159f), 0.20f, (optionCount * 0.035f), backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity); //Background
		GRAPHICS::DRAW_RECT(menuXCoord, ((currentOption * 0.035f) + 0.1415f), 0.20f, 0.031f, bannerRectRed, bannerRectGreen, bannerRectBlue, scrollerOpacity);
		addSprite("helicopterhud", "hud_corner", (textXCoord + 0.002f), ((currentOption * 0.035f) + 0.1315f), 0.025f, 0.025f, 0, 255, 255, 255, 255);
		addSprite("helicopterhud", "hud_corner", (textXCoord + 0.188f), ((currentOption * 0.035f) + 0.1515f), 0.025f, 0.025f, 180, 255, 255, 255, 255);
	}
	if (!GAMEPLAY::IS_STRING_NULL_OR_EMPTY(infoText))
	{
		if (optionCount > maxOptions)
		{
			drawText(infoText, optionsFont, menuXCoord, ((maxOptions + 1) * 0.035f + 0.125f), 0.4f, 0.4f, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, true);
			GRAPHICS::DRAW_RECT(menuXCoord, (((maxOptions + 1) * 0.035f) + 0.1415f), 0.20f, 0.035f, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity); //Info Box
		}
		else
		{
			drawText(infoText, optionsFont, menuXCoord, ((optionCount + 1) * 0.035f + 0.125f), 0.4f, 0.4f, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, true);
			GRAPHICS::DRAW_RECT(menuXCoord, (((optionCount + 1) * 0.035f) + 0.1415f), 0.20f, 0.035f, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity); //Info Box
		}
	}
	if (instructions)
	{
		if (xInstruction)
			addInstruction(BUTTON_A, "Select");
		if (squareInstruction)
			addInstruction(BUTTON_X, "Keyboard");
		if (squareInstruction2)
			addInstruction(BUTTON_X, "Favorite");
		if (squareInstruction3)
			addInstruction(BUTTON_X, "Delete");
		if (squareInstruction4)
			addInstruction(BUTTON_X, "Delete All");
		if (lrInstruction)
			addInstruction(BUTTON_DPAD_LEFT_RIGHT, "Scroll");
		addInstruction(BUTTON_DPAD_UP_DOWN, "Scroll");
		addInstruction(BUTTON_B, "Back");
		instructionsClose();
	}
}

bool inputButtonsPressed = false, menuopened = false;
bool aButtonPressed = false, bButtonPressed = false, DupButtonPressed = false, DdownButtonPressed = false, dpadRightPressed = false, dpadLeftPressed = false, xButtonPressed = false;
bool resetFastScrollUp = true, resetFastScrollDown = true;
Input *menuInputHandler;

void monitorButtons()
{
    if (submenu == Closed)
    {
        menuInputHandler->UpdateInput();
		if (MenuOpenClose == 0)
		{
			if (menuInputHandler->DPadRightDown() && menuInputHandler->XButtonDown() && !inputButtonsPressed)
			{
				menuopened = !menuopened;
				inputButtonsPressed = true;
			}
			else if (!menuInputHandler->DPadRightDown() && !menuInputHandler->XButtonDown())
			{
				inputButtonsPressed = false;
			}
		} else {

			if (menuInputHandler->DPadLeftDown() && menuInputHandler->XButtonDown() && !inputButtonsPressed)
			{
				menuopened = !menuopened;
				inputButtonsPressed = true;
			}
			else if (!menuInputHandler->DPadLeftDown() && !menuInputHandler->XButtonDown())
			{
				inputButtonsPressed = false;
			}
		}

        if (menuopened && inputButtonsPressed)
		{
            if (submenuLevel <= 0)
			{
                submenu = Main_Menu;
                submenuLevel = 0;
                currentOption = 1;
            } else {

                submenu = lastSubmenu[submenuLevel];
                if (lastOption[submenuLevel] != 0)
				{
                    currentOption = lastOption[submenuLevel];
                } else { currentOption = 1; }
            }
            playSound("YES");
        }
    } else {

        menuInputHandler->UpdateInput();
		if (MenuOpenClose == 0)
		{
			if (menuInputHandler->DPadRightDown() && menuInputHandler->XButtonDown() && !inputButtonsPressed)
			{
				menuopened = !menuopened;
				inputButtonsPressed = true;
			}
			else if (!menuInputHandler->DPadRightDown() && !menuInputHandler->XButtonDown())
				inputButtonsPressed = false;
		} else {

			if (menuInputHandler->DPadLeftDown() && menuInputHandler->XButtonDown() && !inputButtonsPressed)
			{
				menuopened = !menuopened;
				inputButtonsPressed = true;
			}
			else if (!menuInputHandler->DPadLeftDown() && !menuInputHandler->XButtonDown())
				inputButtonsPressed = false;
		}
 
        if (!menuopened && inputButtonsPressed)
        {
			hasBeenUsed = true;
            lastSubmenu[submenuLevel] = submenu;
            lastOption[submenuLevel] = currentOption;
            submenu = Closed;
        }

        if (menuInputHandler->BButtonDown() && !bButtonPressed)
		{
			hasBeenUsed = true;
            submenu = lastSubmenu[submenuLevel - 1];
            currentOption = lastOption[submenuLevel - 1];
            submenuLevel--;
            playSound("Back");
            bButtonPressed = true;
        } else if (!menuInputHandler->BButtonDown())
            bButtonPressed = false;
 
        if (menuInputHandler->AButtonDown() && !aButtonPressed)
		{
			hasBeenUsed = true;
            optionPress = true;
            AUDIO::PLAY_SOUND_FRONTEND(-1, "Pin_Good", "DLC_HEIST_BIOLAB_PREP_HACKING_SOUNDS");
            aButtonPressed = true;
        } else if (!menuInputHandler->AButtonDown())
            aButtonPressed = false;

        if (menuInputHandler->DpadUp())
        {
            resetFastScrollUp = false;
            controlPressedTimeout++;
            if (controlPressedTimeout > 5)
            {
                currentOption = currentOption - 1;
                if (currentOption < 1)
                {
                    currentOption = optionCount;
					hasBeenUsed = true;
                }
                playSound("NAV_UP_DOWN");
            }
        } else resetFastScrollUp = true;

        if (menuInputHandler->DpadDown())
        {
            resetFastScrollDown = false;
            controlPressedTimeout++;
            if (controlPressedTimeout > 5)
            {
                currentOption = currentOption + 1;
                if (currentOption > optionCount)
                {
                    currentOption = 1;
					hasBeenUsed = true;
                }
                playSound("NAV_UP_DOWN");
            }
        } else resetFastScrollDown = true;

        if (menuInputHandler->DPadRightDown() && !dpadRightPressed)
        {
			hasBeenUsed = true;
            rightPress = true;
            dpadRightPressed = true;
        } else if (!menuInputHandler->DPadRightDown())
            dpadRightPressed = false;

        if (menuInputHandler->DPadLeftDown() && !dpadLeftPressed)
        {
			hasBeenUsed = true;
            leftPress = true;
            dpadLeftPressed = true;
        } else if (!menuInputHandler->DPadLeftDown())
            dpadLeftPressed = false;

        if (menuInputHandler->DPadRightDown())
        {
			hasBeenUsed = true;
            fastRightPress = true;
        }

        if (menuInputHandler->DPadLeftDown())
        {
			hasBeenUsed = true;
            fastLeftPress = true;
        }

        if (menuInputHandler->XButtonDown() && !xButtonPressed)
        {
			hasBeenUsed = true;
            squarePress = true;
            xButtonPressed = true;
        } else if (!menuInputHandler->XButtonDown())
            xButtonPressed = false;
 
        if (resetFastScrollUp && resetFastScrollDown)
            controlPressedTimeout = 0;
 
        if (menuInputHandler->DpadUp() && !DupButtonPressed)
		{
            currentOption--;
            if (currentOption < 1)
            {
                currentOption = optionCount;
				hasBeenUsed = true;
            }
            playSound("NAV_UP_DOWN");
            DupButtonPressed = true;
        } else if (!menuInputHandler->DpadUp())
            DupButtonPressed = false;
 
        if (menuInputHandler->DpadDown() && !DdownButtonPressed)
		{
            currentOption++;
            if (currentOption > optionCount)
            {
                currentOption = 1;
				hasBeenUsed = true;
            }
            playSound("NAV_UP_DOWN");
            DdownButtonPressed = true;
        } else if (!menuInputHandler->DpadDown())
            DdownButtonPressed = false;
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
	squareInstruction2 = false;
	squareInstruction3 = false;
	squareInstruction4 = false;
	xInstruction = false;
	lrInstruction = false;
}