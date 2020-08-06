#pragma once
#include "ControlBase.h"
class VelLoop :
	public IControlBase
{
public:
	VelLoop() = delete;
	VelLoop(IConfigLinker* linker);
	virtual ~VelLoop();

	virtual void set_input(uint32_t , InputParameter ref);

	virtual void OnTime();

private:
	InputParameter m_reference;
	InputParameter m_feedback;
};

