#pragma once
#include "ControlBase.h"
class AccelLoop :
	public ControlBase
{
public:
	AccelLoop();
	virtual ~AccelLoop();

	virtual void set_reference(InputParameter ref);
	virtual void set_feedback(InputParameter fb);

	virtual void OnTime();

private:
	InputParameter reference;
	InputParameter feedback;
};

