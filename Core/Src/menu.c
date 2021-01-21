#include "main.h"

int currentMenu = 0;
int menuCount = 3;

int activeItem = 0;
int activeItemCount = 3;

extern uint8_t WM8978_SPK_Volume;

/**
  * @brief Main Menu
  */
void MainMenu(void)
{
	LCD_drawHLine(0, 8, 83);
	LCD_refreshScr();
	if (activeItem == 0)
	{
		LCD_invertText(true);
		LCD_print("SINE", 0, 0);
		LCD_invertText(false);
	}
	else
	{
		LCD_print("SINE", 0, 0);
	}
	//  LCD_goXY(0,20);
	LCD_print("Freq       440", 0, 1);
	LCD_print("Mod        100", 0, 2);
	LCD_print("Rate      1200", 0, 3);
	LCD_print("- - - -       ", 0, 4);

	if (activeItem == 1)
	{
		LCD_print("         MIXER", 0, 5);
		LCD_invertText(true);
		LCD_print("<  >", 0, 5);
		LCD_invertText(false);
	}
	else if (activeItem == 2)
	{
		LCD_print("<  >", 0, 5);
		LCD_invertText(true);
		LCD_print("MIXER", 54, 5);
		LCD_invertText(false);
	}
	else
	{
		LCD_print("<  >     MIXER", 0, 5);
	}
}

void MenuSelect(void) {
	switch(currentMenu) {
	case 0:
		switch(activeItem) {
		case 0:
			SoundMenu();
			break;
		case 1:
			break;
		case 2:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}


void SoundMenu(void) {
	currentMenu = 0;
	activeItem = 0;
}

/**
  * @brief Main Menu
  */
void MixerMenu(void)
{
	char *spk[4];

	sprintf(spk, "%d", WM8978_SPK_Volume);
	spk[4] = '\0';

	LCD_drawHLine(0, 8, 83);
	LCD_refreshScr();
	LCD_print("MIXER        X", 0, 0);
	//  LCD_goXY(0,20);
	LCD_print(spk, 0, 1);
	LCD_print("Headphones 100", 0, 2);
	LCD_print("LineIn      --", 0, 3);
	LCD_print("Microphone  --", 0, 4);
	LCD_print("<  >     MIXER", 0, 5);
}

/**
  * @brief Main Menu
  */
void DelayMenu(void)
{
	LCD_drawHLine(0, 8, 83);
	LCD_refreshScr();
	LCD_print("DELAY         ", 0, 0);
	//  LCD_goXY(0,20);
	LCD_print("Speed       90", 0, 1);
	LCD_print("Feedback   100", 0, 2);
	LCD_print("Filter      --", 0, 3);
	LCD_print("            --", 0, 4);
	LCD_print("<  >     MIXER", 0, 5);
}

/**
  * @brief Main Menu
  */
void BlankPage(void)
{
	LCD_drawHLine(0, 8, 83);
	LCD_refreshScr();
	LCD_print("BLANK      MIX", 0, 0);
	//  LCD_goXY(0,20);
	//   LCD_print("Speed       90", 0, 1);
	//   LCD_print("Feedback   100", 0, 2);
	//   LCD_print("Filter      --", 0, 3);
	//   LCD_print("            --", 0, 4);
	LCD_print("<  >     MIXER", 0, 5);
}

/**
  * @brief Go to next/prev menu page.
  */
void TriggerENC1(bool direction)
{

	if (direction)
	{
		activeItem++;
		if (activeItem > activeItemCount)
		{
			activeItem = 0;
		}
	}
	else
	{
		activeItem--;
		if (activeItem < 0)
		{
			activeItem = activeItemCount - 1;
		}
	}

	switch (currentMenu)
	{
	case 0:
		MainMenu();
		break;
	case 1:
		MixerMenu();
		break;
	case 2:
		DelayMenu();
		break;
	default:
		BlankPage();
		break;
	}
}
