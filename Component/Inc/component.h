/*
 * @Author: Mcreeper 1507907006@qq.com
 * @Date: 2024-04-07 17:20:37
 * @LastEditors: Mcreeper 1507907006@qq.com
 * @LastEditTime: 2024-04-21 16:13:04
 * @FilePath:\Component\Inc\component.h
 */
#ifndef __COMPONENT_H
#define __COMPONENT_H

/**
 * @file component.h
 * @author Mcreeper
 * @date 2024-4
 * @brief  Component
 * @note This enumeration is used to provide a common use of the kinds of components
 * @note How to use it
 * first, you need to include this file in the header in your project file
 * than,add components files you need in the Inc folder
 * another way is define COM_CONFIG in main.h,and use the com_config.h to configure the components you need
 * last,you can inherit or instantiate all the components you need
 * @attention all files base on UTF-8,but most notes write in English,so GB2312 or GBK can use it
 * @attention all the components are based on the HAL library
*/

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "com_types.h"

#ifdef __cplusplus
}
#endif

//#include "cmsis_os2.h"

typedef enum
{
	COM_OK = 0,
	COM_ERROR = 1,
	COM_BUSY = 2,
	COM_TIMEOUT = 3
}COM_StatusTypeDef;//component status

#ifdef COM_CONFIG
#include "com_config.h"
#endif

// #include "com_printf.h"
// #include "com_statistic.h"
// #include "com_jdy_at.h"
// #include "com_buzzer.h"
// #include "com_dht11.h"
// #include "com_oled.h"
// #include "com_key.h"
// #include "com_buzzer.h"
// #include "com_tb6612.h"
// #include "com_sr04.h"
// #include "com_steer.h"
// #include "com_mpu6050.h"
// #include "com_oled.h"
// #include "com_mq2.h"
// #include "com_uart.h"
// #include "com_time.h"

#endif // __COMPONENT_H