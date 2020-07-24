#include "stdafx.h"
#include "TimerCore.h"

TimerCore::TimerCore(const char* name)
	: module_name(name)
{
	for (int i = 0; i < MAX_TIMER_AMOUNT; i++)
	{
		timer_list[i] = NULL;
	}
}



TimerCore::~TimerCore()
{
}


//return False if the timer can't be added to the list
bool TimerCore::register_timer(UserTimer* timer)
{
	for (int i = 0; i < MAX_TIMER_AMOUNT; i++)
	{
		if (NULL == timer_list[i]) {
			timer_list[i] = timer;
			return true;
		}
	}
	return false;
}


void TimerCore::OnCallback()
{
	for (int i = 0; i < MAX_TIMER_AMOUNT; i++)
	{
		if (NULL != timer_list[i]) {
			timer_list[i]->OnTime();
		}
	}
}
