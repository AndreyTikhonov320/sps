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

//callback methods for change notification only
void AccelLoop::on_read_param_value(uint32_t address)
{
	if (PARAMETER_ADDRESS__Kp == address) {
	}
	else if (PARAMETER_ADDRESS__Ki == address) {
	}
}

//callback methods for change notification only
bool AccelLoop::on_write_param_value(uint32_t address, const SystemParameters::SPSParameterValue& v)
{
	if (PARAMETER_ADDRESS__Kp == address) {
		return true;
	}
	else if (PARAMETER_ADDRESS__Ki == address) {
		return true;
	}
	return false;
}
