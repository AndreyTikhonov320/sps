#include "VelLoop.h"


VelLoop::VelLoop()
	: ControlBase(__FUNCTION__)
	, reference(0)
	, feedback(0)
{
}


VelLoop::~VelLoop()
{
}

void VelLoop::set_reference(InputParameter ref)
{
	reference = ref;
}

void VelLoop::set_feedback(InputParameter fb)
{
	feedback = fb;
}

void VelLoop::OnTime()
{
	//the simplest internal structure of a control module is retranslation of the input to output
	//InputParameter out = reference;
	InputParameter out = (reference - feedback) * 10;
	set_output(out);
}
