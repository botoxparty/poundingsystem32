#include "main.h"
#include "LCD.h"
#include "menu.h"

int currentMenu = 0;
int menuCount = 3;

int activeItem = 0;
int activeItemCount = 3;

extern uint8_t WM8978_SPK_Volume;

MenuSystem::MenuSystem(LCD *hlcd)
{
    lcd = hlcd;
}
/**
  * @brief Main Menu
  */
void MenuSystem::MainMenu()
{
    lcd->drawHLine(0, 8, 83);
    lcd->refreshScr();
    if (activeItem == 0)
    {
        lcd->invertText(true);
        lcd->print("SINE", 0, 0);
        lcd->invertText(false);
    }
    else
    {
        lcd->print("SINE", 0, 0);
    }
    //  lcd->goXY(0,20);
    lcd->print("Freq       440", 0, 1);
    lcd->print("Mod        100", 0, 2);
    lcd->print("Rate      1200", 0, 3);
    lcd->print("- - - -       ", 0, 4);

    if (activeItem == 1)
    {
        lcd->print("         MIXER", 0, 5);
        lcd->invertText(true);
        lcd->print("<  >", 0, 5);
        lcd->invertText(false);
    }
    else if (activeItem == 2)
    {
        lcd->print("<  >", 0, 5);
        lcd->invertText(true);
        lcd->print("MIXER", 54, 5);
        lcd->invertText(false);
    }
    else
    {
        lcd->print("<  >     MIXER", 0, 5);
    }
}

void MenuSelect(void)
{
    switch (currentMenu)
    {
    case 0:
        switch (activeItem)
        {
        case 0:
            // SoundMenu();
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

void SoundMenu(void)
{
    currentMenu = 0;
    activeItem = 0;
}

/**
  * @brief Main Menu
  */
void MixerMenu(LCD *lcd)
{
    // char spk[4];

    // sprintf(spk, "%d", WM8978_SPK_Volume);
    // spk[4] = '\0';

    lcd->drawHLine(0, 8, 83);
    lcd->refreshScr();
    lcd->print("MIXER        X", 0, 0);
    //  lcd->goXY(0,20);
    // lcd->print(spk, 0, 1);
    lcd->print("Headphones 100", 0, 2);
    lcd->print("LineIn      --", 0, 3);
    lcd->print("Microphone  --", 0, 4);
    lcd->print("<  >     MIXER", 0, 5);
}

/**
  * @brief Main Menu
  */
void DelayMenu(LCD *lcd)
{
    lcd->drawHLine(0, 8, 83);
    lcd->refreshScr();
    lcd->print("DELAY         ", 0, 0);
    //  lcd->goXY(0,20);
    lcd->print("Speed       90", 0, 1);
    lcd->print("Feedback   100", 0, 2);
    lcd->print("Filter      --", 0, 3);
    lcd->print("            --", 0, 4);
    lcd->print("<  >     MIXER", 0, 5);
}

/**
  * @brief Main Menu
  */
void BlankPage(LCD *lcd)
{
    lcd->drawHLine(0, 8, 83);
    lcd->refreshScr();
    lcd->print("BLANK      MIX", 0, 0);
    //  lcd->goXY(0,20);
    //   lcd->print("Speed       90", 0, 1);
    //   lcd->print("Feedback   100", 0, 2);
    //   lcd->print("Filter      --", 0, 3);
    //   lcd->print("            --", 0, 4);
    lcd->print("<  >     MIXER", 0, 5);
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
        // MainMenu();
        break;
    case 1:
        // MixerMenu();
        break;
    case 2:
        // DelayMenu();
        break;
    default:
        // BlankPage();
        break;
    }
}
