#include "com_os.h"
#include "string.h"

com_thread::com_thread(const char *name, uint32_t priority)
	: Priority(priority)
{
	memcpy(Name, name, 10);
}

uint8_t com_thread::operator =  (com_thread &thread)
{
	if(this == &thread)
	{
		return COM_ERROR;
	}
	Priority = thread.Priority;
	memcpy(Name, thread.Name, 10);
	return COM_OK;
}


com_os::com_os()
{
	thread_count = 0;
	thread_ptr = &thread[0];
}

com_thread &com_os::new_thread(char *name, uint32_t priority)
{
	com_thread thread(name, priority);
	*thread_ptr = thread;
	if(++thread_count <= COM_OS_MAX_THREAD)
	{
		thread_ptr++;
		thread_count++;
		return *thread_ptr;
	}
	return default_thread;
}

void com_os::Start_Scheduler()
{

}
