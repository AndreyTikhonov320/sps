#pragma once
#include "ControlBase.h"

class AccelLoop :
	public IControlBase
{
public:
	AccelLoop() = delete;
	AccelLoop(IConfigLinker* linker);
	virtual ~AccelLoop();

	virtual void set_reference(InputParameter ref);
	virtual void set_feedback(InputParameter fb);

	virtual void OnTime();

private:
	InputParameter m_reference;
	InputParameter m_feedback;
};

