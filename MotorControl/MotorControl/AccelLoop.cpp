#include "AccelLoop.h"


AccelLoop::AccelLoop(IConfigLinker* linker)
	: IControlBase(linker, __FUNCTION__)
	, m_reference(0)
	, m_feedback(0)
{
}


AccelLoop::~AccelLoop()
{
}

void AccelLoop::set_reference(InputParameter ref)
{
	m_reference = ref;
}

void AccelLoop::set_feedback(InputParameter fb)
{
	m_feedback = fb;
}

void AccelLoop::OnTime()
{
	//the simplest internal structure of a control module is retranslation of the input to output
	//InputParameter out = reference;
	InputParameter out = (m_reference - m_feedback) * 10;
	set_output(out);
}
