/*
 * PS_application.h
 *
 *  First created on: 13 dec. 2020
 *      Author: Adam Hammad
 */

#ifndef PS_Application_H_
#define PS_Application_H_

/* Includes ------------------------------------------------------------------*/

#include "stdio.h"

#include <math.h>
#include <stdint.h>
#include <stdbool.h>

#include "PS_interface.h"
#include "CONSTANTS.h"
#include "delay.h"
#include "random.h"
#include "drifter.h"
#include "sinetable.h"
#include "notesTables.h"
#include "drifter.h"
#include "soundGen.h"
#include "audio_conf.h"

/*------------------------------------------------------------------------------*/

extern int8_t currentNote;
extern int8_t velocity;

/* Exported functions ------------------------------------------------------- */

void MagicFX(uint8_t val);
void MagicPatch(uint8_t val);
void PS_Application(void);

/*------------------------------------------------------------------------------*/
#endif /* PS_Application_H_ */
