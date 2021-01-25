
#ifndef _PS_MENU_
#define _PS_MENU_

#include "lcd.h"



#ifdef __cplusplus
class MenuSystem
{
public:
    MenuSystem(LCD *hlcd);
    void MainMenu();
    void NextMenu();
    void MixerMenu();
    void MenuSelect();
    void TriggerEncoder(bool direction);
    void TriggerPushEncoder();
    LCD *lcd;
};
#endif
#endif