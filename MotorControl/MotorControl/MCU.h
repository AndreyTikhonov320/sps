#pragma once
#include <cstdint>

namespace MCU
{


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

