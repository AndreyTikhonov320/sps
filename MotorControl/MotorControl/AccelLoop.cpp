#include "Parameters/SPSParameters.h"
#include "AccelLoop.h"


AccelLoop::AccelLoop(IConfigLinker* linker, SystemParameters::SPSParameters* config)
	: IControlBase(linker, __FUNCTION__)
	, m_reference(0)
	, m_feedback(0)
	, m_Kp(config,
		this,
		PARAMETER_SHORT_NAME__Kp,
		PARAMETER_ADDRESS__Kp,
		PARAMETER_DEFAULT__Kp,
		SystemParameters::SPSParamterDescriptor::STATIC_PARAMETER_TYPE,
		SystemParameters::ParameterRange(1024, 1024*100))
	, m_Ki(config,
		this,
		PARAMETER_SHORT_NAME__Ki,
		PARAMETER_ADDRESS__Ki,
		PARAMETER_DEFAULT__Ki,
		SystemParameters::SPSParamterDescriptor::STATIC_PARAMETER_TYPE,
		SystemParameters::ParameterRange(1024, 1024 * 100))
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

SystemParameters::SPSParameterValue AccelLoop::read_param_value(const char* short_name)
{
	if (PARAMETER_SHORT_NAME__Kp == short_name) {
		return m_Kp.get_value();
	}
	else if (PARAMETER_SHORT_NAME__Ki == short_name) {
		return m_Ki.get_value();
	}
	return m_Kp.get_value();
}

SystemParameters::SPSParameterValue AccelLoop::read_param_value(uint32_t address)
{
	if (PARAMETER_ADDRESS__Kp == address) {
		return m_Kp.get_value();
	}
	else if (PARAMETER_ADDRESS__Ki == address) {
		return m_Ki.get_value();
	}
	return m_Kp.get_value();
}

bool AccelLoop::write_param_value(const char* short_name, const SystemParameters::SPSParameterValue& v)
{
	if (PARAMETER_SHORT_NAME__Kp == short_name) {
		m_Kp.set_value(v);
		return true;
	}
	else if (PARAMETER_SHORT_NAME__Ki == short_name) {
		m_Ki.set_value(v);
		return true;
	}
	return false;
}

bool AccelLoop::write_param_value(uint32_t address, const SystemParameters::SPSParameterValue& v)
{
	if (PARAMETER_ADDRESS__Kp == address) {
		m_Kp.set_value(v);
		return true;
	}
	else if (PARAMETER_ADDRESS__Ki == address) {
		m_Ki.set_value(v);
		return true;
	}
	return false;
}
