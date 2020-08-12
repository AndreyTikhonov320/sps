#pragma once
#include "ControlBase.h"

class AccelLoop :
	public IControlBase, public SystemParameters::IParameters
{
public:
	AccelLoop() = delete;
	AccelLoop(IConfigLinker* linker, SystemParameters::SPSParameters* config);
	virtual ~AccelLoop();

	virtual void set_input(uint32_t pin_number, InputParameter ref);

	virtual void OnTime();

	//callback methods for change notification only
	virtual void on_read_param_value(uint32_t address);
	virtual bool on_write_param_value(uint32_t address, const SystemParameters::SPSParameterValue& v);

private:
	InputParameter m_reference;
	InputParameter m_feedback;
	SystemParameters::SPSParamterDescriptor m_Kp;
	SystemParameters::SPSParamterDescriptor m_Ki;

private:
	#define PARAMETER_SHORT_PATH__Kp		"Static/Accelerate"
	#define PARAMETER_SHORT_NAME__Kp		"ac001"
	#define PARAMETER_ADDRESS__Kp			(2)
	#define PARAMETER_DEFAULT__Kp			(2048)

	#define PARAMETER_SHORT_PATH__Ki		"Static/Accelerate"
	#define PARAMETER_SHORT_NAME__Ki		"ac002"
	#define PARAMETER_ADDRESS__Ki			(3)
	#define PARAMETER_DEFAULT__Ki			(2048)
};

