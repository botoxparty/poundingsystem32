/**
 ******************************************************************************
 * File Name		: wm8731.h
 * Author			: Adam Hammad
 * Date				: 13 December 2020
 * Description		: Drivers for Wolfson WM8731
 ******************************************************************************
 */

#define W8731_ADDR_0 0x1A
#define W8731_ADDR_1 0x1B
#define W8731_NUM_REGS 10

#define CODEC_ADDRESS           (W8731_ADDR_0<<1)


/* Maximum Timeout values for flags and events waiting loops. These timeouts are
   not based on accurate values, they just guarantee that the application will
   not remain stuck if the I2C communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */
#define CODEC_FLAG_TIMEOUT             ((uint32_t)0x1000)
#define CODEC_LONG_TIMEOUT             ((uint32_t)(300 * CODEC_FLAG_TIMEOUT))

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>
#include "main.h"

/* Exported functions ------------------------------------------------------- */
void    WM8731_Init(void);
uint32_t WM8731_WriteRegister(uint8_t RegisterAddr, uint16_t RegisterValue);