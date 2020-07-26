#pragma once
#include "ControlBase.h"
class BasicReference :
	public ControlBase
{
public:
	BasicReference();
	virtual ~BasicReference();

	virtual void set_reference(InputParameter ref) {}
	virtual void set_feedback(InputParameter fb) {}

	virtual void OnTime() {}
	void temp_input(uint32_t input);
};

