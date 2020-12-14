/*
 * PS_interface.h
 *
 *  First created on: 13 dec. 2020
 *      Author: Adam Hammad
 */

#ifndef PS_Interface_H_
#define PS_Interface_H_

#include "stm32f4xx_hal.h"


#define PS_BPM_LED                      GPIO_PIN_2
#define PS_TRIG_LED                     GPIO_PIN_4
#define PS_BPM_LED_GPIO                 GPIOA
#define PS_TRIG_LED_GPIO                GPIOA

/*------------------------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void PS_Interface_Init(void);
void PS_Interface_Loop(void);

void Trigger(void);
void Toggle_Hold(GPIO_PinState val);
void Reset_notes_On(void);

#endif /* PS_Interface_H_ */
