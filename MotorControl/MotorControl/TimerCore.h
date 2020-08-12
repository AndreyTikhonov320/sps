#pragma once
#include "STM32.h"
#include "UserTimer.h"

#define ASSERT(cond) typedef int foo[(cond) ? 1 : -1]
class IUserTimer;
class TimerCore : public MCU::TIM::ServiceHandler
{
public:
	TimerCore() = delete;
	TimerCore(const char* name);
	virtual ~TimerCore();
	//return False if the timer can't be added to the list
	bool register_timer(IUserTimer* timer);

	virtual void OnCallback();

private:
	#define					__MAX_TIMER_AMOUNT__ 8
	static const uint32_t	MAX_TIMER_AMOUNT = __MAX_TIMER_AMOUNT__;
	IUserTimer*				m_timer_list[MAX_TIMER_AMOUNT];
	std::string				m_module_name;
	uint8_t					m_registered_timers_amount;

	ASSERT(__MAX_TIMER_AMOUNT__ < 256);  //"The paramter value could not be more 255"
};

