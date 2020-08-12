#include "BasicReferance.h"


BasicReference::BasicReference(IConfigLinker* linker)
	: IControlBase(linker, __FUNCTION__)
{
}


BasicReference::~BasicReference()
{
}


void BasicReference::temp_input(uint32_t input)
{
	set_output(m_output_pin_number, InputParameter(input));
}
