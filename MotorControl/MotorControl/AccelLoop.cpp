#include "stdafx.h"
#include "AccelLoop.h"


AccelLoop::AccelLoop()
	: ControlBase(__FUNCTION__)
	, reference(0)
	, feedback(0)
{
}


AccelLoop::~AccelLoop()
{
}

void AccelLoop::set_reference(InputParameter ref)
{
	reference = ref;
}

void AccelLoop::set_feedback(InputParameter fb)
{
	feedback = fb;
}

void AccelLoop::OnTime()
{
	//the simplest internal structure of a control module is retranslation of the input to output
	//InputParameter out = reference;
	InputParameter out = (reference - feedback) * 10;
	set_output(out);
}