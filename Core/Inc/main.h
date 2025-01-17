/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define MQ2D_Pin GPIO_PIN_5
#define MQ2D_GPIO_Port GPIOA
#define MQ2A_Pin GPIO_PIN_6
#define MQ2A_GPIO_Port GPIOA
#define TRIG_Pin GPIO_PIN_7
#define TRIG_GPIO_Port GPIOA
#define buzzer_Pin GPIO_PIN_1
#define buzzer_GPIO_Port GPIOB
#define DHT11_Pin GPIO_PIN_10
#define DHT11_GPIO_Port GPIOB
#define AN1_Pin GPIO_PIN_11
#define AN1_GPIO_Port GPIOB
#define AN2_Pin GPIO_PIN_12
#define AN2_GPIO_Port GPIOB
#define BN1_Pin GPIO_PIN_13
#define BN1_GPIO_Port GPIOB
#define BN2_Pin GPIO_PIN_14
#define BN2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define COM_CONFIG
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
