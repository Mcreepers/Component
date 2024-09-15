#ifndef __SMARTHOME_H__
#define __SMARTHOME_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
	void SmartHome_task(void *argument);

#ifdef __cplusplus
}
#endif

#include "component.h"

struct SmartHome_Flags
{
	bool Music_Play;
	bool Light;
	bool OLED;
	bool DHT11;
	bool SR04;
	bool MQ2;
	bool Detect_Human;
};

class SmartHome_Task :public com_statistic, public com_dht11, public com_sr04, public com_mq2, public com_tb6612
{
public:
	SmartHome_Task();
	void FeedBack();
	void Calc();
	void Output();

	SmartHome_Flags Flags;
};

extern SmartHome_Task SmartHome;

#endif // __SMARTHOME_H__