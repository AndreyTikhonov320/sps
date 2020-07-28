#include "ConfigLinker.h"
#include "UserTimer.h"


IUserTimer::IUserTimer()
{
}

IUserTimer::IUserTimer(IConfigLinker* linker, const char* module_name)
	: m_linker(linker)
{
	TimerCore* timer_core_ptr = m_linker->get_timer(module_name);
	if(NULL != timer_core_ptr)
		timer_core_ptr->register_timer(this);
}


IUserTimer::~IUserTimer()
{
}
