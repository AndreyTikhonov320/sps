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

void AccelLoop::set_input(uint32_t pin_number, InputParameter ref)
{
	switch (pin_number)
	{
	case IControlBase::REFERENCE_PIN_NUMBER:
		m_reference = ref;
		break;
	case IControlBase::FEEDBACK_PIN_NUMBER:
		m_feedback = ref;
		break;
	}
}

void AccelLoop::OnTime()
{
	//the simplest internal structure of a control module is retranslation of the input to output
	//InputParameter out = reference;
	InputParameter out = (m_reference - m_feedback) * 10;
	set_output(m_output_pin_number, out);
}
