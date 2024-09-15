#ifndef __MUSIC_H
#define __MUSIC_H

#include "component.h"
#ifdef __cplusplus
extern "C" {
#endif

	void Music_task(void *argument);

#ifdef __cplusplus
}
#endif


class Music_Task :public com_statistic, public com_buzzer
{
private:
	/* data */
public:
	Music_Task();
};



#endif // __MUSIC_H