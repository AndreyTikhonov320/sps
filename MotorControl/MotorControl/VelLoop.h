#pragma once
#include "ControlBase.h"
class VelLoop :
	public ControlBase
{
public:
	VelLoop();
	virtual ~VelLoop();

	virtual void set_reference(InputParameter ref);
	virtual void set_feedback(InputParameter fb);

	virtual void OnTime();

private:
	InputParameter reference;
	InputParameter feedback;
};

