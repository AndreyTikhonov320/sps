#include "Parameters/SPSParameters.h"
#include "PwmModule.h"

PwmModule::PwmModule(IConfigLinker* linker, SystemParameters::SPSParameters* config)
	: IControlBase(linker, __FUNCTION__)
	, m_reference(0)
	, m_max_output(2048)
	, m_MAX(	config,
				this, 
				PARAMETER_SHORT_NAME__MAX.c_str(), 
				PARAMETER_ADDRESS__MAX, 
				PARAMETER_DEFAULT__MAX,
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

SystemParameters::SPSParameterValue PwmModule::read_param_value(const char* short_name)
{
	if (PARAMETER_SHORT_NAME__MAX == short_name) {
		return m_MAX.get_value();
	}
	return m_MAX.get_value();
}

SystemParameters::SPSParameterValue PwmModule::read_param_value(uint32_t address)
{
	if (PARAMETER_ADDRESS__MAX == address) {
		return m_MAX.get_value();
	}
	return m_MAX.get_value();
}

bool PwmModule::write_param_value(const char* short_name, const SystemParameters::SPSParameterValue& v)
{
	if (PARAMETER_SHORT_NAME__MAX == short_name) {
		m_MAX.set_value(v);
		return true;
	}
	return false;
}

bool PwmModule::write_param_value(uint32_t address, const SystemParameters::SPSParameterValue& v)
{
	if (PARAMETER_ADDRESS__MAX == address) {
		m_MAX.set_value(v);
		return true;
	}
	return false;
}
