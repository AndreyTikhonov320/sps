#pragma once
#include "ControlBase.h"
class PwmModule :
	public IControlBase
{
public:
	PwmModule() = delete;
	PwmModule(IConfigLinker* linker);
	virtual ~PwmModule();

	virtual void set_input(uint32_t pin_number, InputParameter ref);

	virtual void OnTime();

private:
	InputParameter m_reference;
	uint32_t m_max_output;
};

