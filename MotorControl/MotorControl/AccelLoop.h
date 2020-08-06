#pragma once
#include "ControlBase.h"

class AccelLoop :
	public IControlBase
{
public:
	AccelLoop() = delete;
	AccelLoop(IConfigLinker* linker);
	virtual ~AccelLoop();

	virtual void set_input(uint32_t pin_number, InputParameter ref);

	virtual void OnTime();

private:
	InputParameter m_reference;
	InputParameter m_feedback;
};

