#include "ConfigLinker.h"
#include "ControlBase.h"


IControlBase::IControlBase(IConfigLinker* linker, const char* module_name)
	: IUserTimer(linker, module_name)
	, m_linker(linker)
	, m_output(NULL)
	, m_module_name(module_name)
	, m_output_pin_number(0)
{
	m_linker->register_control_base(module_name, this);
	m_linker->connect_control_base_to(module_name, this);
}


IControlBase::~IControlBase()
{
}

void IControlBase::set_output(uint32_t pin_number, InputParameter ref)
{
	if (NULL != m_output) {
		this->m_output->set_input(pin_number,  InputParameter(ref));
	}
}

// Connect the module to input of the following module in the chain
bool IControlBase::set_output_link(IControlBase* module_ptr, uint32_t pin_number)
{
	m_output = module_ptr;
	m_output_pin_number = pin_number;
	return true;
}