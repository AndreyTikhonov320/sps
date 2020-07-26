#include "TimerCore.h"

TimerCore::TimerCore(const char* name)
	: m_module_name(name)
	, m_registered_timers_amount(0)
{
	for (int i = 0; i < MAX_TIMER_AMOUNT; i++)
	{
		m_timer_list[i] = NULL;
	}
}



TimerCore::~TimerCore()
{
}


//return False if the timer can't be added to the list
bool TimerCore::register_timer(UserTimer* timer)
{
	if (m_registered_timers_amount < MAX_TIMER_AMOUNT)
	{
		m_timer_list[m_registered_timers_amount] = timer;
		m_registered_timers_amount++;
		return true;
	}
	return false;
}


void TimerCore::OnCallback()
{
	for (int i = 0; i < m_registered_timers_amount; i++)
	{
		if (NULL != m_timer_list[i]) {
			m_timer_list[i]->OnTime();
		}
	}
}
