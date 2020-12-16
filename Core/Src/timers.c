/**
 ******************************************************************************
 * File Name		: timers.c
 * Date				:
 * Author			: Xavier Halgand
 * Description		:
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include "timers.h"

#define CHECK_MSEC 		4 // Read hardware every x msec
#define PRESS_MSEC 		40 // Stable time before registering pressed
#define RELEASE_MSEC 	40 // Stable time before registering released


static uint32_t TimingDelay = 0;
static uint32_t TimingDelay1 = 0;
uint32_t 		LED_counter[4]; // time counter for blue LED

static uint8_t	FireCount = RELEASE_MSEC / CHECK_MSEC;
static uint8_t	HoldCount = RELEASE_MSEC / CHECK_MSEC;
static bool 	DebouncedKeyPress = false; // This holds the debounced state of the key.
static bool 	DebouncedSwitchState = false; // This holds the debounced state of the key.
static bool 	Key_changed = false;
static bool 	Key_pressed = false;
static bool 	Switch_changed = false;
static bool 	Switch_pressed = false;

extern uint32_t shift;

/*----------------------------------------------------------------------------------------------*/

/**
 * @brief  Decrements the TimingDelays variables.
 * 			Called by SysTick_Handler() in stm32f4xx_it.c
 * @param  None
 * @retval None
 */
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0)
	{
		TimingDelay--;
	}
	if (TimingDelay1 != 0)
	{
		TimingDelay1--;
	}
}
/***********************************************************************************/
/**
 * @brief  Turns selected LED On for  a given duration.
 * @param  Led: Specifies the Led to be set on.
 *   This parameter can be one of following parameters:
 *     @arg LED4
 *     @arg LED3
 *     @arg LED5
 *     @arg LED6
 * @retval None
 */
void PS_StartBPMLED()
{
	PS_LED_On();
	LED_counter[0] = shift / 10;
}
/*------------------------------------------------------------------------------------*/
/* Function called by SysTick_Handler()  */
void update_temporized_LED()
{
	LED_counter[0]--;
	if (LED_counter[0] == 0) {
		PS_LED_Toggle();
		LED_counter[0] = shift / 10;
	}
}


/***************************************************************************************************************************/
// Service routines called every CHECK_MSEC to
// debounce both edges

void DebounceFireButton(void) // Called by SysTick_Handler() in file stm32f4xx_it.c
{
	bool RawState;

	RawState = (bool) HAL_GPIO_ReadPin(FIRE_BTN_GPIO_Port, FIRE_BTN_Pin);

	if (RawState == DebouncedKeyPress) {
		// Set the timer which allows a change from current state.
		if (DebouncedKeyPress) FireCount = RELEASE_MSEC / CHECK_MSEC;
		else FireCount = PRESS_MSEC / CHECK_MSEC;

	} else {
		// Key has changed - wait for new state to become stable.
		if (--FireCount == 0) {
			// Timer expired - accept the change.
			DebouncedKeyPress = RawState;
			Key_changed = true;
			Key_pressed = DebouncedKeyPress;
			// And reset the timer.
			if (DebouncedKeyPress) // rising edge
			{
				FireCount = RELEASE_MSEC / CHECK_MSEC;
				// ButtonPressed_action();
				Trigger();
			}
			else // falling edge
			{
				FireCount = PRESS_MSEC / CHECK_MSEC;
				// ButtonReleased_action();
				Trigger();
			}
		}
	}
}


void DebounceHoldSwitch(void) // Called by SysTick_Handler() in file stm32f4xx_it.c
{
	bool RawState;

	RawState = (bool) HAL_GPIO_ReadPin(HOLD_SW_GPIO_Port, HOLD_SW_Pin);

	if (RawState == DebouncedSwitchState) {
		// Set the timer which allows a change from current state.
		if (DebouncedSwitchState) HoldCount = RELEASE_MSEC / CHECK_MSEC;
		else HoldCount = PRESS_MSEC / CHECK_MSEC;

	} else {
		// Key has changed - wait for new state to become stable.
		if (--HoldCount == 0) {
			// Timer expired - accept the change.
			DebouncedSwitchState = RawState;
			Switch_changed = true;
			Switch_pressed = DebouncedSwitchState;
			// And reset the timer.
			if (DebouncedSwitchState) // rising edge
			{
				HoldCount = RELEASE_MSEC / CHECK_MSEC;
				// ButtonPressed_action();
				Trigger();
			}
			else // falling edge
			{
				HoldCount = PRESS_MSEC / CHECK_MSEC;
				// ButtonReleased_action();
				Trigger();
			}
		}
	}
}
