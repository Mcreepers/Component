#include "Message.h"
#include "cmsis_os2.h"

#include "string"

#include "SmartHome.h"

Message_Task Message;

uint8_t Light_Status = 2;

uint8_t Uart1_Tx_Fun(uint8_t *buf, uint16_t len);
uint8_t Uart2_Tx_Fun(uint8_t *buf, uint16_t len);

void Message_task(void *argument)
{
	osDelay(1000);

	HAL_UARTEx_ReceiveToIdle_IT(&huart1, Message.Get_Uart_Data(), 128);
	HAL_UARTEx_ReceiveToIdle_IT(&huart2, Message.JDY_uart.Get_Uart_Data(), 128);

	while(1)
	{
		Message.Statistic_Update(osKernelGetTickCount());
		Message.Receive();
		Message.Send();
		osDelay(1);
	}
}

Message_Task::Message_Task()
	:com_uart(&huart1, RX_IDLE), JDY_uart(&huart2, RX_IDLE)
{
	Output_ptr = Uart1_Tx_Fun;
	JDY_printf.Output_ptr = Uart2_Tx_Fun;
}

void Message_Task::Hook(Message_id id)
{
	switch(id)
	{
	case dLight:
	Flags.Light = !Flags.Light;
	break;
	case dOLED:
	Flags.OLED = !Flags.OLED;
	break;
	case dUART:
	JDY_printf.printf_add(Get_Uart_Data(), Get_Uart_Len());
	printf_add("JDY_SEND:");
	printf_add(Get_Uart_Data(), Get_Uart_Len());
	printf_add("\n");
	Flags.UART = 1;
	break;
	case dJDY:
	AT_Read_Cmd(JDY_uart.Get_Uart_Data(), JDY_uart.Get_Uart_Len());
	printf_add("JDY_GET:");
	printf_add(JDY_uart.Get_Uart_Data(), JDY_uart.Get_Uart_Len());
	printf_add("\n");
	Flags.JDY = 1;
	break;
	default:
	break;
	}
}

void Message_Task::Receive()
{
	// if(SmartHome.Flags.Detect_Human == true) Flags.Detect_Human = 1;
	// else Flags.Detect_Human = 0;
	// if(SmartHome.Flags.DHT11) Flags.DHT11 = 1;
	// else Flags.DHT11 = 0;
	// if(SmartHome.Flags.SR04) Flags.SR04 = 1;
	// else Flags.SR04 = 0;
	// if(SmartHome.Flags.Music_Play || Flags.Music_Play) Flags.Music_Play = 1;
	// else Flags.Music_Play = 0;


	if(Flags.Light)
	{
		Flags.Light = 0;
		printf_add("Light\n");
	}
	if(Flags.OLED)
	{
		Flags.OLED = 0;
		printf_add("OLED\n");
	}
	if(Flags.UART || Flags.JDY)
	{
		uint8_t Buf[64] = { 0 }, len = 0;
		if(Flags.UART)
		{
			Flags.UART = 0;
			memcpy(Buf, Get_Uart_Data(), Get_Uart_Len());
		}
		else if(Flags.JDY)
		{
			Flags.JDY = 0;
			memcpy(Buf, JDY_uart.Get_Uart_Data(), JDY_uart.Get_Uart_Len());
		}
		if(memcmp(Buf, "MUSIC", 5) == 0 || memcmp(Buf, "Music", 5) == 0 || memcmp(Buf, "music", 5) == 0)
		{
			Flags.Music_Play = !Flags.Music_Play;
		}
		if(memcmp(Buf, "RESET", 5) == 0 || memcmp(Buf, "Reset", 5) == 0 || memcmp(Buf, "reset", 5) == 0)
		{
			HAL_NVIC_SystemReset();
		}
		if(memcmp(Buf, "MOTOR", 5) == 0 || memcmp(Buf, "Motor", 5) == 0 || memcmp(Buf, "motor", 5) == 0)
		{
			Flags.Motor = !Flags.Motor;
			Data.Motor_Speed = atoi((char *)&(Buf[5]));
			if(Data.Motor_Speed != 0)
			{
				Flags.Motor = 1;
			}
		}
		if(memcmp(Buf, "MQ2", 3) == 0 || memcmp(Buf, "Mq2", 3) == 0 || memcmp(Buf, "mq2", 3) == 0)
		{
			Flags.MQ2_Give = 1;
			Flags.MQ2 = 1;
			Data.MQ2_Gas = atoi((char *)&(Buf[3]));
			if(Data.MQ2_Gas > 70)
			{
				Flags.MQ2_Warn = 1;
			}
			else if(Data.MQ2_Gas < 70)
			{
				Flags.MQ2_Warn = 0;
			}
		}
		if(memcmp(Buf, "light", 5) == 0 || memcmp(Buf, "Light", 5) == 0 || memcmp(Buf, "LIGHT", 5) == 0)
		{
			Light_Status = !Light_Status;
		}
	}
}

void Message_Task::Send()
{
	uint8_t ptr[64] = { 0 };
	uint16_t len = 0;

//	if(Rate_Do_Execute(5000))
//	{
//		printf_add("Count:%d\n", Get_Count());
//		printf_add("FPS:%.2f\n", Get_FPS_Count());
//	}
	if(AT_Get_Status() == COM_JDY_AT_NONE && Rate_Do_Execute(1000))
	{
		AT_Get_Cmd(COM_JDY_AT_READY, ptr, len);
		JDY_printf.printf_add(ptr, len);
		printf_add("JDY_SEND:");
		printf_add(ptr, len);
	}
	if(Rate_Do_Execute(10000) && Flags.Music_Play)
	{
		printf_add("Playing Music\n");
		JDY_printf.printf_add("Playing Music\n");
	}
	if(Rate_Do_Execute(10001) && Flags.DHT11)
	{
		printf_add("T:%.1fC H:%0.f\n", SmartHome.Get_Temperature(), SmartHome.Get_Humidity());
		JDY_printf.printf_add("T:%.1fC H:%0.f\n", SmartHome.Get_Temperature(), SmartHome.Get_Humidity());
	}
	if(Rate_Do_Execute(3001) && Flags.Detect_Human)
	{
		printf_add("Welcome Home\n");
		JDY_printf.printf_add("Welcome Home\n");
	}
	if(Rate_Do_Execute(1002) && Flags.MQ2_Warn)
	{
		printf_add("GAS WARNING");
		JDY_printf.printf_add("GAS WARNING");
	}

	printf_out();
	JDY_printf.printf_out();
}


uint8_t Uart1_Tx_Fun(uint8_t *buf, uint16_t len)
{
	return Message.Uart_Tx_Fun(buf, len);
}

uint8_t Uart2_Tx_Fun(uint8_t *buf, uint16_t len)
{
	return Message.JDY_uart.Uart_Tx_Fun(buf, len);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart1)
	{
		Message.Uart_RxRXNE_Fun(1);
	}
	else if(huart == &huart2)
	{
		Message.JDY_uart.Uart_RxRXNE_Fun(1);
	}
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if(huart == &huart1)
	{
		Message.Uart_RxIDLE_Fun(Size);
		Message.Hook(dUART);
	}
	else if(huart == &huart2)
	{
		Message.JDY_uart.Uart_RxIDLE_Fun(Size);
		Message.Hook(dJDY);
	}
}
