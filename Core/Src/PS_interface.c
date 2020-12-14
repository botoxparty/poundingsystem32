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
int16_t currentFreq;
int8_t velocity;
uint8_t notes_On[128] = {0};
int8_t notesCount = 0; // number of notes on (keys pressed)
bool triggered = false;
GPIO_PinState hold = 0;
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

    PS_StartPots();
    // DelayFeedback_set(80);
}

/*-----------------------------------------------------------------------------*/
/**
 * @brief  Start PS interface in main.c
 * @param  None
 * @retval none
 */
void PS_Interface_Loop(void)
{
//    bool hold = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);
//    if (hold)
//    {
//        velocity = 127;
//        triggered = 1;
//    } else {
//        velocity = 0;
//        triggered = 0;
//    }

    // HAL_GPIO_WritePin(PS_TRIG_LED_GPIO, PS_TRIG_LED, triggered);
}

void Toggle_Hold(GPIO_PinState val)
{
//	if(val) {
//		triggered = 1;
//	} else {
//		triggered = 0;
//	}
//	hold = val;
}


/*-----------------------------------------------------------------------------*/
/**
 * @brief  Trigger the sound on
 * @param  None
 * @retval none
 */
void Trigger(void)
{

         if (triggered)
         {
             velocity = 0;
             ADSR_keyOff(&adsr);
         }
         else
         {
             velocity = 127;
             ADSR_keyOn(&adsr);
            //  MagicPatch(MIDI_MAXi);
         }

         triggered = !triggered;

     HAL_GPIO_WritePin(PS_TRIG_LED_GPIO, PS_TRIG_LED, triggered);
}

void ButtonPressed_action(void)
{ // User butter toggles sequencer
    Toggle_Hold(true);
}

void ButtonReleased_action(void)
{ // User butter toggles sequencer
    Toggle_Hold(false);
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

float map(float val, float I_Min, float I_Max, float O_Min, float O_Max)
	{
		return O_Max - (((val-I_Min)*((O_Max-O_Min)/(I_Max-I_Min)))+O_Min);
}
/*-----------------------------------------------------------------------------*/
/**
 * @brief  ADC data receive callback.
 * @param  hadc: ADC handle
 * @retval None
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	// set frequency
    currentFreq = map(adcValArray[1], 0, 4096, 20, 12600);
    currentNote = map(adcValArray[1],  0, 4096, 0, 107);

    VibratoFreq_set(map(adcValArray[2],  0, 4096, 0, 107));
    VibratoAmp_set(MIDI_MAX);
    // VibratoFreq_set(map(adcValArray[0],  0, 4096, 0, MIDI_MAX));
    // seq_tempo_set(map(adcValArray[3],  0, 4096, 0, MIDI_MAX));
    FM_OP1_modInd_set(map(adcValArray[2],  0, 4096, 0, 107));
    // FM_OP1_freq_set(map(adcValArray[0],  0, 4096, 0, MIDI_MAX));
    // Delay_time_set(map(adcValArray[3],  0, 4096, 0, MIDI_MAX));
}

/*-----------------------------------------------------------------------------*/
void Reset_notes_On(void)
{
    notesCount = 0;
    for (uint8_t i = 0; i < 128; i++)
        notes_On[i] = 0;
}

/*-----------------------------------------------------------------------------*/
