#include "Parameters/SPSParameters.h"
#include "PwmModule.h"

PwmModule::PwmModule(IConfigLinker* linker, SystemParameters::SPSParameters* config)
	: IControlBase(linker, __FUNCTION__)
	, m_reference(0)
	, m_max_output(2048)
	, m_MAX_PWM(	config,
				this, 
				PARAMETER_SHORT_NAME__MAX_PWM, 
				PARAMETER_ADDRESS__MAX_PWM,
				PARAMETER_DEFAULT__MAX_PWM,
				SystemParameters::SPSParamterDescriptor::STATIC_PARAMETER_TYPE,
				SystemParameters::ParameterRange(1024, 2048))
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

//callback methods for change notification only
void PwmModule::on_read_param_value(uint32_t address)
{
	if (PARAMETER_ADDRESS__MAX_PWM == address) 
	{
		
	}
}

//callback methods for change notification only
bool PwmModule::on_write_param_value(uint32_t address, const SystemParameters::SPSParameterValue& v)
{
	if (PARAMETER_ADDRESS__MAX_PWM == address) 
	{
		return true;
	}
	return false;
}
