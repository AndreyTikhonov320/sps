#pragma once
#include "ControlBase.h"
class VelLoop :
	public IControlBase
{
public:
	VelLoop() = delete;
	VelLoop(IConfigLinker* linker);
	virtual ~VelLoop();

	virtual void set_reference(InputParameter ref);
	virtual void set_feedback(InputParameter fb);

	virtual void OnTime();

private:
	InputParameter m_reference;
	InputParameter m_feedback;
};

