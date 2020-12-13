/*
 * PS_interface.c
 *
 *  First created on: 13 dec. 2020
 *      Author: Adam Hammad
 */

/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "PS_interface.h"
#include "adsr.h"

/* Private define ------------------------------------------------------------*/

int8_t currentNote;
int8_t velocity;
uint8_t notes_On[128] = {0};
int8_t notesCount = 0; // number of notes on (keys pressed)
bool triggered = false;
bool hold = false;
extern ADSR_t adsr;
extern bool sequencerIsOn;
static unsigned short bpm_led_state = 0;
uint16_t adcValArray[4];
extern ADC_HandleTypeDef hadc1;

/*-----------------------------------------------------------------------------*/
/**
 * @brief  Start PS interface in main.c
 * @param  None
 * @retval none
 */
void PS_Interface_Init(void)
{

}

/*-----------------------------------------------------------------------------*/
/**
 * @brief  Trigger the sound on
 * @param  None
 * @retval none
 */
void Trigger(void)
{
	if(triggered) {
		velocity = 0;
		ADSR_keyOff(&adsr);
	} else {
		velocity = 127;
		ADSR_keyOn(&adsr);
	}

	triggered = !triggered;
	HAL_GPIO_WritePin(PS_TRIG_LED_GPIO, PS_TRIG_LED, triggered);
}

/**
 * @brief  Starts reading the pots
 * @param  None
 * @retval none
 */
void PS_StartPots(void)
{
  HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adcValArray, 4);
}

int map(int in, int inMin, int inMax, int outMin, int outMax) {
  // check it's within the range
  if (inMin<inMax) { 
    if (in <= inMin) 
      return outMin;
    if (in >= inMax)
      return outMax;
  } else {  // cope with input range being backwards.
    if (in >= inMin) 
      return outMin;
    if (in <= inMax)
      return outMax;
  }
  // calculate how far into the range we are
  float scale = (in-inMin)/(inMax-inMin);
  // calculate the output.
  return outMin + scale*(outMax-outMin);
}

/*-----------------------------------------------------------------------------*/
/**
 * @brief  ADC data receive callback.
 * @param  hadc: ADC handle
 * @retval None
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	uint16_t read = &adcValArray;
	int16_t note = (short) &adcValArray[1];
	// Conversion Complete & DMA Transfer Complete As Well
	currentNote = (int) &adcValArray[0] / 8;
}

/*-----------------------------------------------------------------------------*/
void Reset_notes_On(void)
{
	notesCount = 0;
	for (uint8_t i = 0; i < 128; i++)
		notes_On[i] = 0;
}

/*-----------------------------------------------------------------------------*/