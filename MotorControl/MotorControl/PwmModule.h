#pragma once
#include "ControlBase.h"

class PwmModule :
	public IControlBase, public SystemParameters::IParameters
{
public:
	PwmModule() = delete;
	PwmModule(IConfigLinker* linker, SystemParameters::SPSParameters* config);
	virtual ~PwmModule();

	virtual void set_input(uint32_t pin_number, InputParameter ref);

	virtual void OnTime();

	//callback methods for change notification only
	virtual void on_read_param_value(uint32_t address);
	virtual bool on_write_param_value(uint32_t address, const SystemParameters::SPSParameterValue& v);

private:
	InputParameter m_reference;
	uint32_t m_max_output;
	SystemParameters::SPSParamterDescriptor m_MAX_PWM;

private:
	#define PARAMETER_SHORT_PATH__MAX_PWM		"Static/Accelerate"
	#define PARAMETER_SHORT_NAME__MAX_PWM		"pw001"
	#define PARAMETER_ADDRESS__MAX_PWM			(1)
	#define PARAMETER_DEFAULT__MAX_PWM			(2048)
};

