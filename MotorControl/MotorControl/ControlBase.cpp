
#include "ControlBase.h"


ControlBase::ControlBase(const char* module_name)
	: UserTimer(module_name)
	, output(NULL)
{
}


ControlBase::~ControlBase()
{
}

void ControlBase::set_output(InputParameter ref)
{
	if (NULL != output) {
		this->output->set_reference(InputParameter(ref));
	}
}