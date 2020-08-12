#pragma once
#include "ControlBase.h"
class BasicReference :
	public IControlBase
{
public:
	BasicReference() = delete;
	BasicReference(IConfigLinker* linker);
	virtual ~BasicReference();

	virtual void set_input(uint32_t, InputParameter ref) {}

	virtual void OnTime() {}
	void temp_input(uint32_t input);
};

