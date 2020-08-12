#include "AccelFeedback.h"

AccelFeedback::AccelFeedback(IConfigLinker* linker)
	: IControlBase(linker, __FUNCTION__)
	, m_output_value(0)
{
}

AccelFeedback::~AccelFeedback()
{
}

void AccelFeedback::OnTime()
{
	//Just read the Feadback from ADC
	//...
	//For test purpose just setup some value
	InputParameter m_output_value = 10;
	set_output(m_output_pin_number, m_output_value);
}
