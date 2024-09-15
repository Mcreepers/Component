#include "OLED.h"
#include "cmsis_os2.h"

#include "math.h"
#include "string.h"
#include "Message.h"
#include "SmartHome.h"

extern I2C_HandleTypeDef hi2c1;
extern uint8_t Light_Status;

OLED_Task OLED;

void OLED_task(void *argument)
{
	osDelay(1000);

	OLED.OLED_Begin();
	while(1)
	{
		OLED.Statistic_Update(osKernelGetTickCount());
		OLED.Update();
		// OLED.Test();
		OLED.Display();
	}
}

OLED_Task::OLED_Task()
	:com_oled(&hi2c1)
{}

void OLED_Task::Update()
{

}

void OLED_Task::Display()
{
	static uint32_t time = osKernelGetTickCount();
	OLED_Clear();
	if(osKernelGetTickCount() - time < 5000)
	{
		Show.String(0, 24, "Hello World!", OLED_8X16);
	}
	else
	{
		uint8_t Height = 0;
		char uart_buf[62] = { 0 };
		memcpy(uart_buf, Message.Get_Uart_Data(), Message.Get_Uart_Len());
		Show.Printf(0, Height, OLED_6X8, "Uart:%s", uart_buf);
		char jdy_buf[62] = { 0 };
		Height += 8;
		memcpy(jdy_buf, Message.JDY_uart.Get_Uart_Data(), Message.JDY_uart.Get_Uart_Len());
		Show.Printf(0, Height, OLED_6X8, "JDY:%s", jdy_buf);
		if(Message.Flags.Music_Play)
		{
			Show.String(128 - Get_Count() / 2 % 180, 56, "Always with me", OLED_6X8);
			Show.String(0, 56, "Music:", OLED_6X8);
		}
		Height += 8;
		if(Message.Flags.DHT11)
		{
			Height += 8;
//			Show.String(0, 16, "DHT11:", OLED_6X8);
			Show.Printf(0, Height, OLED_6X8, "T:%.1fC H:%.0f", SmartHome.Get_Temperature(), SmartHome.Get_Humidity());
			Show.Char(72, Height, '%', OLED_6X8);
		}
		if(Message.Flags.SR04)
		{
			Height += 8;
			Show.String(0, Height, "SR04:", OLED_6X8);
			Show.Printf(30, Height, OLED_6X8, "%.1fm", SmartHome.Get_SR04_Distance());
		}
		if(Message.Flags.MQ2)
		{
			Height += 8;
			Show.String(0, Height, "MQ2:", OLED_6X8);
			if(Message.Flags.MQ2_Give == 0)
			{
				if(Message.Data.MQ2_ADC != 0 && Message.Data.MQ2_ADC != 0xfff)
				{
					Show.Printf(24, Height, OLED_6X8, "%.3f", (Message.Data.MQ2_ADC / 3.3f * 100));
					//if(Message.Flags.MQ2) Show.Printf(48, Height, OLED_6X8, "GG");
				}
			}
			else
			{
				Show.Printf(24, Height, OLED_6X8, "%.d", (Message.Data.MQ2_Gas));
				//if(Message.Flags.MQ2) Show.Printf(48, Height, OLED_6X8, "Gas");
			}
			Show.Char(36, Height, '%', OLED_6X8);
			Show.Printf(42, Height, OLED_6X8, "         ");
		}
		if(Message.Flags.Motor)
		{
			Height += 8;
			Show.Printf(0, Height, OLED_6X8, "Motor:%d", Message.Data.Motor_Speed);
		}
		if(Light_Status == 1)
		{
			Height += 8;
			Show.String(0, Height, "Light On", OLED_6X8);
		}
		else if(Light_Status == 0)
		{
			Height += 8;
			Show.String(0, Height, "Light Off", OLED_6X8);
		}
		if(Message.Flags.Detect_Human)
		{
			Show.String(0, 0, "Welcome Home", OLED_8X16);
		}
		if(Message.Flags.MQ2_Warn)
		{
			Show.String(0, 0, "GAS WARNING", OLED_8X16);
		}
	}
	Show.Line(115, 54, 128, 54, 1);
	Show.Line(115, 54, 115, 63, 1);
	Show.Num(116, 56, round(Get_FPS_Count()), 2, OLED_6X8);
	OLED.Show.Line(127, 0, 127, Get_Count() % 54, 1);
	OLED_Update();
}

void OLED_Task::Test()
{
	static uint32_t i = 0;
#if 0
	OLED_Clear();
	Show.String(0, 0, "Hello World!", OLED_8X16);
	Show.String(0, 16, "Hello World!", OLED_6X8);
	OLED_Update();
	Statistic_Update(osKernelGetTickCount());

	OLED_Clear();
	Show.Line(0, 0, 127, 63, 1);
	Show.Line(0, 63, 127, 0, 1);
	Show.Line(0, 31, 127, 31, 1);
	Show.Line(63, 0, 63, 63, 1);
	OLED_Update();
	Statistic_Update(osKernelGetTickCount());

	OLED_Clear();
	Show.Rectangle(2, 2, 125, 61, 1, 1);
	Show.Rectangle(0, 0, 127, 63, 0, 1);
	OLED_Update();
	Statistic_Update(osKernelGetTickCount());

	OLED_Clear();
	Show.Arc(64, 32, 30, 0, 10, 1, 1);
	OLED_Update();
#endif

#if 0
	OLED.Show.Printf(0, 0, OLED_6X8, "FPS:%f", OLED.Get_FPS_Count());
	OLED.Show.Point(i % 127, i % 64, 1);
	OLED.Show.Point((i - 1) % 127, (i - 1) % 64, 0);
	OLED.OLED_Update();
#endif

#if 0
	OLED_Clear();
	Show.Arc(64, 32, 30, i % 360, (i % 360) * 2, 0, 1);
	OLED_Update();
#endif


	i++;
}
