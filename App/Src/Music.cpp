#include "Music.h"
#include "Message.h"

Music_Task Music;

extern TIM_HandleTypeDef htim3;

void Music_task(void *argument)
{
	com_delay_ms_os(1000);
	while(1)
	{
		Music.Statistic_Update(com_get_tick_os());
		if(Message.Flags.Music_Play || Message.Flags.MQ2_Warn)
		{
			if(Music.Play_Music_Once(Always_with_me) == HAL_BUSY)
			{
				Message.Flags.Music_Play = false;
				Music.Close_PWM();
			}
		}
		else
		{
			com_delay_ms_os(1);
			Music.Close_PWM();
		}
	}
}

Music_Task::Music_Task()
	:com_buzzer(&htim3, TIM_CHANNEL_4)
{}
