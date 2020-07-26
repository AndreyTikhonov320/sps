#include "VelLoop.h"


VelLoop::VelLoop()
	: ControlBase(__FUNCTION__)
	, m_reference(0)
	, m_feedback(0)
{
}


VelLoop::~VelLoop()
{
}

void VelLoop::set_reference(InputParameter ref)
{
	m_reference = ref;
}

void VelLoop::set_feedback(InputParameter fb)
{
	m_feedback = fb;
}

void VelLoop::OnTime()
{
	//the simplest internal structure of a control module is retranslation of the input to output
	//InputParameter out = reference;
	InputParameter out = (m_reference - m_feedback) * 10;
	set_output(out);
}
