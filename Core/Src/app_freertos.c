/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern uint8_t Light_Status;

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
uint32_t defaultTaskBuffer[ 128 ];
osStaticThreadDef_t defaultTaskControlBlock;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_mem = &defaultTaskBuffer[0],
  .stack_size = sizeof(defaultTaskBuffer),
  .cb_mem = &defaultTaskControlBlock,
  .cb_size = sizeof(defaultTaskControlBlock),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Message_Task */
osThreadId_t Message_TaskHandle;
uint32_t Message_TaskBuffer[ 256 ];
osStaticThreadDef_t Message_TaskControlBlock;
const osThreadAttr_t Message_Task_attributes = {
  .name = "Message_Task",
  .stack_mem = &Message_TaskBuffer[0],
  .stack_size = sizeof(Message_TaskBuffer),
  .cb_mem = &Message_TaskControlBlock,
  .cb_size = sizeof(Message_TaskControlBlock),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for SmartHome_Task */
osThreadId_t SmartHome_TaskHandle;
uint32_t SmartHome_TaskBuffer[ 128 ];
osStaticThreadDef_t SmartHome_TaskControlBlock;
const osThreadAttr_t SmartHome_Task_attributes = {
  .name = "SmartHome_Task",
  .stack_mem = &SmartHome_TaskBuffer[0],
  .stack_size = sizeof(SmartHome_TaskBuffer),
  .cb_mem = &SmartHome_TaskControlBlock,
  .cb_size = sizeof(SmartHome_TaskControlBlock),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for OLED_Task */
osThreadId_t OLED_TaskHandle;
uint32_t OLED_TaskBuffer[ 384 ];
osStaticThreadDef_t OLED_TaskControlBlock;
const osThreadAttr_t OLED_Task_attributes = {
  .name = "OLED_Task",
  .stack_mem = &OLED_TaskBuffer[0],
  .stack_size = sizeof(OLED_TaskBuffer),
  .cb_mem = &OLED_TaskControlBlock,
  .cb_size = sizeof(OLED_TaskControlBlock),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Music_Task */
osThreadId_t Music_TaskHandle;
uint32_t Music_TaskBuffer[ 128 ];
osStaticThreadDef_t Music_TaskControlBlock;
const osThreadAttr_t Music_Task_attributes = {
  .name = "Music_Task",
  .stack_mem = &Music_TaskBuffer[0],
  .stack_size = sizeof(Music_TaskBuffer),
  .cb_mem = &Music_TaskControlBlock,
  .cb_size = sizeof(Music_TaskControlBlock),
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
extern void Message_task(void *argument);
extern void SmartHome_task(void *argument);
extern void OLED_task(void *argument);
extern void Music_task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
/* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
/* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
/* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of Message_Task */
  Message_TaskHandle = osThreadNew(Message_task, NULL, &Message_Task_attributes);

  /* creation of SmartHome_Task */
  SmartHome_TaskHandle = osThreadNew(SmartHome_task, NULL, &SmartHome_Task_attributes);

  /* creation of OLED_Task */
  OLED_TaskHandle = osThreadNew(OLED_task, NULL, &OLED_Task_attributes);

  /* creation of Music_Task */
  Music_TaskHandle = osThreadNew(Music_task, NULL, &Music_Task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
	for(;;)
	{
		if(Light_Status == 1)
		{
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
			osDelay(1);
		}
		else if(Light_Status == 0)
		{
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
			osDelay(1);
		}
		else
		{
			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
			osDelay(500);
		}
	}
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

