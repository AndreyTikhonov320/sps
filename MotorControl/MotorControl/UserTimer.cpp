#include "stdafx.h"
#include "UserTimer.h"
#include "ConfigLinker.h"

UserTimer::UserTimer()
{
}

UserTimer::UserTimer(const char* module_name)
{
	TimerCore* timer_core_ptr = ConfigLinker::instance()->get_timer(module_name);
	timer_core_ptr->register_timer(this);
}


UserTimer::~UserTimer()
{
}