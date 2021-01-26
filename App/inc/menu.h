
#ifndef _PS_MENU_
#define _PS_MENU_

#include "lcd.h"
#include "synth.h"

#ifdef __cplusplus

enum PSMenus
{
    MAIN_MENU,
    MIXER_MENU,
    SOUND_MENU,
    DELAY_MENU
};

extern Synth *synth;

class MenuSystem
{
public:
    MenuSystem(LCD *hlcd);

    void SetMenu(PSMenus menu);
    void TriggerEncoder(bool direction);
    void TriggerPushEncoder();

    void MenuSelect();
    void RefreshMenu();

    void MainMenu();
    void MixerMenu();
    void SoundMenu();
    void DelayMenu();

private:
    LCD *lcd;
};
#endif
#endif