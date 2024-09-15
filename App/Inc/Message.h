/*
 * @Author: Mcreeper 1507907006@qq.com
 * @Date: 2024-04-09 16:11:51
 * @LastEditors: Mcreeper 1507907006@qq.com
 * @LastEditTime: 2024-04-17 17:34:59
 * @FilePath: \SmartHome\App\inc\Message.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
	void Message_task(void *argument);

#ifdef __cplusplus
}
#endif

#include "component.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

struct Message_Flags
{
	bool Music_Play;
	bool Light;
	bool OLED;
	bool UART;
	bool JDY;
	bool DHT11;
	bool SR04;
	bool MQ2;
	bool MQ2_Warn;
	bool MQ2_Give;
	bool Detect_Human;
	bool Motor;
};

enum Message_id
{
	dMusic = 0,
	dLight,
	dOLED,
	dUART,
	dJDY,
	Message_id_count
};

struct Message_Data
{
	int16_t Motor_Speed;
	int16_t MQ2_ADC;
	int16_t MQ2_Gas;
};

class Message_Task :public com_statistic, public com_uart, public com_printf, public com_jdy_at
{
public:
	Message_Task();
	void Send();
	void Receive();
	void Hook(Message_id id);
	void Set_Flag(Message_id id);

	com_printf JDY_printf;
	com_uart JDY_uart;
	Message_Flags Flags;
	Message_Data Data;
};

extern Message_Task Message;

#endif // __MESSAGE_H__