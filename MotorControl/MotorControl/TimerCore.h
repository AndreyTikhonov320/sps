#pragma once
#include "STM32.h"
#include "UserTimer.h"


class TimerCore : public MCU::TIM::ServiceHandler
{
public:
	TimerCore() = delete;
	TimerCore(const char* name);
	virtual ~TimerCore();
	//return False if the timer can't be added to the list
	bool register_timer(UserTimer* timer);

	virtual void OnCallback();

private:
	static const uint32_t MAX_TIMER_AMOUNT = 8;
	UserTimer* timer_list[MAX_TIMER_AMOUNT];
	std::string module_name;
};

