
#include "ControlBase.h"
#include "ConfigLinker.h"

ControlBase::ControlBase(const char* module_name)
	: UserTimer(module_name)
	, m_output(NULL)
	, m_module_name(module_name)
{
	ConfigLinker::instance()->register_control_base(module_name, this);
}


ControlBase::~ControlBase()
{
}

void ControlBase::set_output(InputParameter ref)
{
	if (NULL != m_output) {
		this->m_output->set_reference(InputParameter(ref));
	}
}

// Connect the module to imput of the following module in the chain
bool ControlBase::set_output_link(ControlBase* input_module_ptr)
{
	m_output = input_module_ptr;
	return true;
}