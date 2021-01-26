#include "main.h"
#include "lcd.h"
#include "menu.h"
#include "audiocodec.h"
#include <vector>
#include <string>
/**
 *
 * Menus:
 * 0 main menu
 * 1 mixer menu
 * 2 sound menu
 * 3 delay menu
 *
 *
 */

PSMenus currentMenu = MAIN_MENU;
int menuCount = 3;
int activeItem = 0;
int activeItemCount = 3;
bool scrollMode = false;

extern uint8_t WM8978_SPK_Volume;
extern AudioCodec *audio;

MenuSystem::MenuSystem(LCD *hlcd)
{
    lcd = hlcd;
}

/**
  * @brief Load the current state onto the display
  */
void MenuSystem::RefreshMenu(void)
{
    lcd->clrScr();
    switch (currentMenu)
    {
    case MAIN_MENU:
        MainMenu();
        break;
    case MIXER_MENU:
        MixerMenu();
        break;
    case SOUND_MENU:
        SoundMenu();
        break;
    case DELAY_MENU:
        DelayMenu();
    default:
        break;
    }

    if (scrollMode)
    {
        lcd->invertText(true);
        lcd->print("<            >", 0, 5);
        lcd->invertText(false);
    }
}

/**
  * @brief Load the current state onto the display
  */
void MenuSystem::SetMenu(PSMenus menu)
{
    currentMenu = menu;
    RefreshMenu();
}

void MenuSystem::MenuSelect(void)
{
    if (scrollMode)
    {
        scrollMode = false;
        RefreshMenu();
        return;
    }
    switch (currentMenu)
    {
    case MIXER_MENU:
        activeItem = 1;
        SetMenu(MAIN_MENU);
        return;
        break;
    case MAIN_MENU:
        if (activeItem == 2)
        {
            SetMenu(SOUND_MENU);
            return;
        }
    case SOUND_MENU:
        activeItem = 2;
        SetMenu(MAIN_MENU);
    default:
        break;
    }
    switch (activeItem)
    {
    case 0:
        // set to scroll thru pages
        scrollMode = true;
        RefreshMenu();
        break;
    case 1:
        // set previous menu to current menu
        // show mixer menu
        SetMenu(MIXER_MENU);
        break;
    default:
        // switch (currentMenu)
        // {
        // case MAIN_MENU:
        //     break;
        // case MIXER_MENU:
        //     break;
        // default:
        //     break;
        // }
        break;
    }
}

/**
  * @brief Go to next/prev menu page.
  */
void MenuSystem::TriggerEncoder(bool direction)
{

    if (scrollMode)
    {
        int newmenu = (int)currentMenu;

        if (direction)
        {
            newmenu--;
            if (newmenu > 3)
            {
                newmenu = 3;
            }
        }
        else
        {
            newmenu++;
            if (newmenu > 3)
            {
                newmenu = 0;
            }
        }

        SetMenu((PSMenus)newmenu);
        return;
    }

    if (direction)
    {
        activeItem++;
        if (activeItem > activeItemCount - 1)
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
    RefreshMenu();
}

void MenuSystem::TriggerPushEncoder()
{
    MenuSelect();
}

/**
  * @brief Main Menu
  */
void MenuSystem::MainMenu()
{
    currentMenu = MAIN_MENU;
    switch (activeItem)
    {
    case 0:
        lcd->print("SINE", 0, 0);
        lcd->print("Freq       440", 0, 1);
        lcd->print("Mod        100", 0, 2);
        lcd->print("Rate      1200", 0, 3);
        lcd->print("- - - -       ", 0, 4);
        lcd->print("         MIXER", 0, 5);
        lcd->invertText(true);
        lcd->print("<  >", 0, 5);
        lcd->invertText(false);
        break;
    case 1:
        lcd->print("SINE", 0, 0);
        lcd->print("Freq       440", 0, 1);
        lcd->print("Mod        100", 0, 2);
        lcd->print("Rate      1200", 0, 3);
        lcd->print("- - - -       ", 0, 4);
        lcd->print("<  >", 0, 5);
        lcd->invertText(true);
        lcd->print("MIXER", 54, 5);
        lcd->invertText(false);
        break;
    case 2:
        lcd->invertText(true);
        lcd->print("SINE", 0, 0);
        lcd->invertText(false);
        lcd->print("Freq       440", 0, 1);
        lcd->print("Mod        100", 0, 2);
        lcd->print("Rate      1200", 0, 3);
        lcd->print("- - - -       ", 0, 4);
        lcd->print("<  >     MIXER", 0, 5);
        break;
    default:
        break;
    }
}

/**
  * @brief Mixer
  */
void MenuSystem::MixerMenu()
{
    currentMenu = MIXER_MENU;

    char hp[4];
    sprintf(hp, "%d", audio->HP_Volume);
    hp[4] = '\0';
    char spk[4];
    sprintf(spk, "%d", audio->SPK_Volume);
    spk[4] = '\0';

    lcd->drawHLine(0, 9, 83);
    lcd->refreshScr();

    lcd->invertText(true);
    lcd->print("             X", 0, 0);
    lcd->invertText(false);
    lcd->print("MIXER        ", 0, 0);
    lcd->print("Headphones   ", 0, 2);
    lcd->print(hp, 60, 1);
    lcd->print("LineOut      ", 0, 3);
    lcd->print(spk, 60, 2);
    lcd->print("LineIn      --", 0, 4);
    lcd->print("Mic         --", 0, 5);
}
/**
  * @brief Sound select Menu
  */
void MenuSystem::SoundMenu()
{
    currentMenu = SOUND_MENU;
    char colour[4][10] = {"Blue", "Red", "Orange",
                          "Yellow"};
    lcd->drawHLine(0, 8, 83);
    lcd->refreshScr();
    lcd->print("SOUND        X", 0, 0);

    for (int i = 0; i < 3; i++)
    {
        lcd->print(colour[i], 0, i + 1);
    }
}

/**
  * @brief Delay Menu
  */
void MenuSystem::DelayMenu()
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
