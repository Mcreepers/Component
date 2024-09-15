#include "SmartHome.h"
#include "Message.h"
#include "cmsis_os2.h"
#include "tim.h"
#include "adc.h"

SmartHome_Task SmartHome;
extern uint32_t TimOverflowCount;
extern uint8_t Light_Status;
void SmartHome_task(void *argument)
{
	osDelay(1000);
	while(1)
	{
		SmartHome.FeedBack();
		SmartHome.Calc();
		SmartHome.Output();
		osDelay(1);
	}
}

SmartHome_Task::SmartHome_Task()
	:com_dht11(GPIOB, GPIO_PIN_10)
	, com_sr04(GPIOA, GPIO_PIN_7, &htim15, TIM_CHANNEL_2, &TimOverflowCount)
	, com_mq2(&hadc2, GPIOA, GPIO_PIN_5)
	, com_tb6612(&htim4, TIM_CHANNEL_1, GPIOB, GPIO_PIN_11, GPIO_PIN_12)
{}

void SmartHome_Task::FeedBack()
{
	Statistic_Update(osKernelGetTickCount());
	if(Rate_Do_Execute(2000))
	{
		if(DHT11_Read() == COM_OK)
		{
			Message.Flags.DHT11 = 1;
		}
		else
		{
			Message.Flags.DHT11 = 0;
		}
	}
	if(Rate_Do_Execute(200))
	{
		SR04_Start();
	}
	if(Get_SR04_Run_Flag())
	{
		Message.Flags.SR04 = 1;
		if(Get_SR04_Distance() < 50)
		{
			Message.Flags.Detect_Human = 1;
		}
		else
		{
			Message.Flags.Detect_Human = 0;
		}
	}
	if(Rate_Do_Execute(2000) && Message.Flags.MQ2_Give == 0)
	{
		if(Get_MQ2_Status() == 0)
		{
			Message.Flags.MQ2 = 1;
		}
		else
		{
			Message.Flags.MQ2 = 0;
		}
		Message.Data.MQ2_ADC = Get_MQ2_ADC();
		if(Message.Data.MQ2_ADC == 0xfff)
		{
			Message.Flags.MQ2 = 0;
		}
	}

	// if( == 1)
	// {
	// 	Message.Flags.Music_Play = 1;
	// }
	// else
	// {
	// 	Message.Flags.Music_Play = 0;
	// }
	static uint32_t Motor_Time = 0;
	static uint8_t Motor_Detect_Flag = 0;

	if(Message.Flags.Detect_Human == 1 && Motor_Detect_Flag == 0)
	{
		Message.Data.Motor_Speed = 400;
		Message.Flags.Motor = 1;
		Motor_Time = osKernelGetTickCount();
		Motor_Detect_Flag = 1;
		Light_Status = 1;
	}
	if(Motor_Detect_Flag == 1 && (osKernelGetTickCount() - Motor_Time) > 10000)
	{
		Message.Flags.Motor = 0;
		Motor_Detect_Flag = 2;
	}
}

void SmartHome_Task::Calc()
{}

void SmartHome_Task::Output()
{
	if(Message.Flags.Detect_Human == true && Get_Count() > 5000)
	{
//		Message.Flags.Music_Play = true;
	}
	else
	{
//		Message.Flags.Music_Play = false;
	}
	if(Message.Flags.Motor)
	{
		Set_Motor_Speed(Message.Data.Motor_Speed);
	}
	else
	{
		Stop_Motor();
	}
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
//	if(htim == SmartHome.GET_SR04_Tim() && htim->Channel == SmartHome.GET_SR04_Tim_Channel())
	{
		SmartHome.SR04_Tim_IC_Isr();
	}
}

