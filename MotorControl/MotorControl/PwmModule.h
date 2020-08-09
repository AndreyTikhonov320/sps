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

	virtual SystemParameters::SPSParameterValue read_param_value(const char* short_name);
	virtual SystemParameters::SPSParameterValue read_param_value(uint32_t address);
	virtual bool write_param_value(const char* short_name, const SystemParameters::SPSParameterValue& v);
	virtual bool write_param_value(uint32_t address, const SystemParameters::SPSParameterValue& v);

private:
	InputParameter m_reference;
	uint32_t m_max_output;
	SystemParameters::SPSParamterDescriptor m_MAX;

private:
	const std::string PARAMETER_SHORT_NAME__MAX = "pwm_max";
	const uint32_t PARAMETER_ADDRESS__MAX = 0x00000001;
	const uint32_t PARAMETER_DEFAULT__MAX = 2048;
};

