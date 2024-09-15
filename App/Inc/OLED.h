#ifndef __OLED_H
#define __OLED_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
	void OLED_task(void *argument);
#ifdef __cplusplus
}
#endif

#include "component.h"

class OLED_Task :public com_statistic, public com_oled
{
public:
	OLED_Task();
	void Update();
	void Test();
	void Display();
private:
};

#endif