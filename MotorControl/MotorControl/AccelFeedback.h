#pragma once
#include "ControlBase.h"
class AccelFeedback :
	public IControlBase
{
public:
	AccelFeedback() = delete;
	AccelFeedback(IConfigLinker* linker);
	virtual ~AccelFeedback();

	virtual void set_input(uint32_t pin_number, InputParameter ref) {}

	virtual void OnTime();
private:
	InputParameter m_output_value;
};

