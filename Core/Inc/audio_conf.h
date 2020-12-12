/**
 ******************************************************************************
 * File Name          : audio_conf.h
 * Author				: Xavier Halgand
 * Date               :
 * Description        :
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AUDIO_CONF_H
#define __AUDIO_CONF_H

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


#define DMA_MAX_SZE                     0xFFFF

/** @defgroup STM32F4_DISCOVERY_AUDIO_Exported_Macros AUDIO_Exported_Macros
  * @{
  */
#define DMA_MAX(_X_)                (((_X_) <= DMA_MAX_SZE)? (_X_):DMA_MAX_SZE)


/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>
#include "CONSTANTS.h"
#include "soundGen.h"
#include "main.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  BUFFER_OFFSET_NONE = 0,
  BUFFER_OFFSET_HALF,
  BUFFER_OFFSET_FULL,
}BUFFER_StateTypeDef;

/* Exported functions ------------------------------------------------------- */
void audio_init(void);
void toggleSound(void);
void incVol(void);
void decVol(void);
void Volume_set(uint8_t val);



#endif /* __AUDIO_H */
