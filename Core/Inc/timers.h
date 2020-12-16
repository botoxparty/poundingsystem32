/**
 ******************************************************************************
 * File Name		: timers.h
 * Author			: Xavier Halgand
 * Date				:
 * Description		:
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIMERS_H
#define __TIMERS_H

/* Includes ------------------------------------------------------------------*/
#include <audio_conf.h>
#include <stdint.h>
#include <stdbool.h>
#include "CONSTANTS.h"
//#include "stm32f4_discovery_audio.h"
//#include "stm32f4_discovery.h"
#include "soundGen.h"

/* Exported functions ------------------------------------------------------- */
void 		TimingDelay_Decrement(void);
void 		setSysTick(void);
uint32_t 	getTime(void);
void 		setTime(uint32_t val);
void 		PS_StartBPMLED();
void 		update_temporized_LED();
void 		DebounceFireButton(void);
void        DebounceHoldSwitch(void);
/*************************************************************************************/
#endif /* __TIMERS_H */
