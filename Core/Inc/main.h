/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "CONSTANTS.h"
#include "audio_conf.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/* Local includes ------------------------------------------------------------------*/
// #include "stm32f4xx_hal.h"
// #include "stm32f4_discovery.h"
// #include "stm32f4_discovery_audio.h"
// #include "stm32f4_discovery_accelerometer.h"
// #include <stdio.h>
// #include "stm32f4xx_it.h"
// #include "lis302dl.h"

// #include "usbh_MIDI.h"
#include "wm8731.h"
#include "PS_application.h"
#include "timers.h"
#include "soundGen.h"
#include "delay.h"
#include "chorusFD.h"
#include "random.h"
// #include "CONSTANTS.h"
#include "drifter.h"
#include "resonantFilter.h"
#include "adsr.h"
#include "sequencer.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
