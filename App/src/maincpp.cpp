#include "maincpp.h"

// class class_that_needs_i2c{
//     //ctor
//     class_that_needs_i2c(i2c_enc& i2c){
//         i2c.DR
//     }
// };

int maincpp(PS_Communication_Interface* comms, PS_Encoder_Timers* enc, LCD_GPIO* lcdGpio)
{
    LCD lcd (lcdGpio);

    MenuSystem menu(&lcd);
    menu.MainMenu();

    // make use of i2c struct
    while(1)
    {

    }
    return 0;
}
