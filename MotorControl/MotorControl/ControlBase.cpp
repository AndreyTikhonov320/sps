#include "ConfigLinker.h"
#include "ControlBase.h"


IControlBase::IControlBase(IConfigLinker* linker, const char* module_name)
	: IUserTimer(linker, module_name)
	, m_linker(linker)
	, m_output(NULL)
	, m_module_name(module_name)
{
	m_linker->register_control_base(module_name, this);
	m_linker->connect_control_base_to(module_name, this);
}


IControlBase::~IControlBase()
{
}

void IControlBase::set_output(InputParameter ref)
{
	if (NULL != m_output) {
		this->m_output->set_reference(InputParameter(ref));
	}
}

// Connect the module to imput of the following module in the chain
bool IControlBase::set_output_link(IControlBase* input_module_ptr)
{
	m_output = input_module_ptr;
	return true;
}