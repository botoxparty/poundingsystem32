/*
 * PS_application.c
 *
 *  First created on: 13 dec. 2020
 *      Author: Adam Hammad
 */

/* Includes ------------------------------------------------------------------*/

//#include "main.h"
#include "PS_application.h"
#include "adsr.h"

/* Private define ------------------------------------------------------------*/

int8_t currentNote;
int8_t velocity;
uint8_t notes_On[128] = {0};
int8_t notesCount = 0; // number of notes on (keys pressed)
bool triggered = false;
extern ADSR_t adsr;
extern bool sequencerIsOn;
static unsigned short bpm_led_state = 0;
uint16_t adcValArray[4];
extern uint16_t audiobuff[BUFF_LEN]; // THE audio buffer
extern ADC_HandleTypeDef hadc1;

/*-----------------------------------------------------------------------------*/
/**
 * @brief  Main routine for application, looped in main.c
 * @param  None
 * @retval none
 */
void PS_Application(void)
{
	bpm_led_state = !bpm_led_state;
	HAL_GPIO_WritePin(PS_BPM_LED_GPIO, PS_BPM_LED, bpm_led_state);
	int delay = map((int)adcValArray[0], 0, 4096, 200, 1000);
	HAL_Delay(delay);
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
void MagicFX(uint8_t val) /* random effects parameters */
{
	if (val == MIDI_MAXi)
	{
		Delay_switch(MIDI_MAXi);
		Delay_time_set(MIDIrandVal());
		DelayWet_set(MIDIrandVal());
		DelayFeedback_set(MIDIrandVal());

		Chorus_switch(MIDI_MAXi);
		ChorusRate_set(MIDIrandVal());
		ChorusSecondRate_set(MIDIrandVal());
		ChorusDelay_set(MIDIrandVal());
		ChorusSweep_set(MIDIrandVal());
		ChorusFeedback_set(MIDIrandVal());
		ChorusMode_switch(MIDIrandVal());
		ChorusFDBsign_switch(MIDIrandVal());

		Phaser_switch(MIDI_MAXi);
		Phaser_Rate_set(MIDIrandVal());
		Phaser_Feedback_set(MIDIrandVal());
		Phaser_Wet_set(MIDIrandVal());
	}
}
/*-----------------------------------------------------------------------------*/
void MagicPatch(uint8_t val) /* random sound parameters */
{
	if (val == MIDI_MAXi)
	{
		seq_tempo_set(MIDIrandVal());
		seq_freqMax_set(MIDIrandVal());
		seq_scale_set(MIDIrandVal());
		seq_switchMovingSeq(MIDIrandVal());
		seq_switchMute(MIDIrandVal());
		seq_gateTime_set(MIDIrandVal());
		autoSound_set(rand() % 3);
		Sound_set(MIDIrandVal());
		uint8_t snd = soundNumber_get();

		if (snd == FM2)
		{
			FM_OP1_freq_set(MIDIrandVal());
			FM_OP1_modInd_set(MIDIrandVal());
			FM_OP2_freq_set(MIDIrandVal());
			FM_OP2_modInd_set(MIDIrandVal());
			FM_OP3_freq_set(MIDIrandVal());
			FM_OP3_modInd_set(MIDIrandVal());
			FM_OP4_freq_set(MIDIrandVal());
			FM_OP4_modInd_set(MIDIrandVal());
		}
		else if (snd == DRIFTERS)
		{
			//STM_EVAL_LEDOn(LED_Green);
			Drifter_amp_set(MIDIrandVal());
			Drifter_minFreq_set(MIDIrandVal());
			Drifter_maxFreq_set(MIDIrandVal());
			Drifter_centralFreq_set(MIDIrandVal());
		}

		Filter1Freq_set(MIDIrandVal());
		Filter1Res_set(MIDIrandVal());
		Filter1Drive_set(MIDIrandVal());
		Filter1Type_set(MIDIrandVal());
		Filt1LFO_amp_set(MIDIrandVal());
		Filt1LFO_freq_set(MIDIrandVal());

		Filter2Freq_set(MIDIrandVal());
		Filter2Res_set(MIDIrandVal());
		Filter2Drive_set(MIDIrandVal());
		Filter2Type_set(MIDIrandVal());
		Filt2LFO_amp_set(MIDIrandVal());
		Filt2LFO_freq_set(MIDIrandVal());

		Filter_Random_switch(MIDIrandVal());

		AttTime_set((uint8_t)lrintf(frand_a_b(0, MIDI_MAX / 10)));
		DecTime_set(MIDIrandVal());
		SustLevel_set(MIDIrandVal());
		RelTime_set(MIDIrandVal());

		VibratoAmp_set(MIDIrandVal());
		VibratoFreq_set(MIDIrandVal());

		AmpLFO_amp_set(MIDIrandVal());
		AmpLFO_freq_set(MIDIrandVal());
	}
}

/*-----------------------------------------------------------------------------*/
void Reset_notes_On(void)
{
	notesCount = 0;
	for (uint8_t i = 0; i < 128; i++)
		notes_On[i] = 0;
}

/*-----------------------------------------------------------------------------*/

/**
  * @brief  Tx Transfer completed callbacks.
  * @param  hi2s: I2S handle
  * @retval None
  */
void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
{
  if(hi2s->Instance == SPI2)
  {
    /* Call the user function which will manage directly transfer complete */
	  make_sound((uint16_t *)(audiobuff + BUFF_LEN_DIV2), BUFF_LEN_DIV4);
  }
}

/**
  * @brief  Tx Half Transfer completed callbacks.
  * @param  hi2s: I2S handle
  * @retval None
  */
void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
  if(hi2s->Instance == SPI2)
  {
    /* Manage the remaining file size and new address offset: This function should
       be coded by user (its prototype is already declared in stm32f4_discovery_audio.h) */  
  	make_sound((uint16_t *)audiobuff, BUFF_LEN_DIV4);
  }
}
