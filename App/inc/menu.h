
#ifndef _PS_MENU_
#define _PS_MENU_

#include "lcd.h"
#ifdef __cplusplus
class MenuSystem
{
public:
    MenuSystem(LCD *hlcd);
    void MainMenu();
    LCD *lcd;
};
#endif
#endif