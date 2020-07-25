#pragma once
#include <cstdint>

namespace MCU
{
	
class MCU_CONFIG{
public:
	virtual ~MCU_CONFIG() {}

	virtual uint32_t TIM1_time() = 0;
	virtual uint32_t TIM1_interrupt_priority_group() = 0;
	virtual uint32_t TIM1_interrupt_order_group_in_group() = 0;
	virtual uint32_t TIM2_time() = 0;
	virtual uint32_t TIM2_interrupt_priority_group() = 0;
	virtual uint32_t TIM2_interrupt_order_group_in_group() = 0;

};

class TIM
{
public:
	class ServiceHandler {
	public:
		virtual void OnCallback() = 0;
	};
	TIM() : handler(NULL) {}

	virtual ~TIM() {}
	virtual void enable() = 0;
	virtual void disable() = 0;
	virtual void OnTime()=0;

	void SetServiceHandler(ServiceHandler* h) { handler = h; }

protected:
	ServiceHandler * handler;
};

class MCU
{
public:
	virtual ~MCU() {}
	virtual TIM* tim(int index) = 0;
};

};

