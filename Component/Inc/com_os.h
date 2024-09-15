#ifndef __COM_OS_H__
#define __COM_OS_H__

#include "component.h"
#include "com_time.h"

//#include ""

#define COM_OS_MAX_THREAD 10
#define COM_OS_MAX_STACK_SIZE 1024

class com_thread
{
public:
	com_thread();
	com_thread(const char *name, uint32_t priority);
	uint8_t operator = (com_thread &thread);
private:
	char *Name[10];
	uint32_t Priority;
	uint32_t Top_Stack[16];
};

class com_os
{
public:
	com_os();
	com_thread &new_thread(char *name, uint32_t priority);
	uint8_t delete_thread(com_thread &thread);
	void Start_Scheduler();
private:
	com_thread default_thread;
	com_thread *thread_ptr;
	com_thread *threads_ptr[10];
	com_thread threads[COM_OS_MAX_THREAD];
	uint8_t Stack[COM_OS_MAX_STACK_SIZE];
};

#endif