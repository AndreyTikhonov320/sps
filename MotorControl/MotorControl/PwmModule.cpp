#include "PwmModule.h"

PwmModule::PwmModule(IConfigLinker* linker)
	: IControlBase(linker, __FUNCTION__)
	, m_reference(0)
	, m_max_output(2048)
{
}

PwmModule::~PwmModule()
{
}

void PwmModule::set_input(uint32_t pin_number, InputParameter ref)
{
	
	switch (pin_number)
	{
	case IControlBase::REFERENCE_PIN_NUMBER:
		m_reference = ref;
		//restrict the output
		int32_t pwm = ref.get_restricted_value(m_max_output);
		//set_pwm(pwm);//not implemented yet
		break;
	}
}

void PwmModule::OnTime()
{
}
