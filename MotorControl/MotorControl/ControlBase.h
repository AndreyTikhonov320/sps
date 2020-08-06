#pragma once

#include "ConfigLinker.h"
#include "UserTimer.h"
class InputParameter {
public:
	InputParameter(int32_t in) : m_parameter(in) {}
	virtual ~InputParameter() {}
	InputParameter operator-(const InputParameter& p) const { return m_parameter - p.m_parameter; }
	InputParameter operator*(const InputParameter& p) const { return m_parameter * p.m_parameter; }
	InputParameter operator*(const int& p) const { return m_parameter * p; }
	int32_t get_restricted_value(int32_t saturation) const { 
		if( static_cast<int32_t>(saturation) < m_parameter) return saturation;
		else if (-static_cast<int32_t>(saturation) > m_parameter) return -static_cast<int32_t>(saturation);
		else return m_parameter;
	}
private:
	InputParameter() {}
private:
	int32_t m_parameter;
};

class IConfigLinker;
class IUserTimer;

class IControlBase :
	public IUserTimer
{
public:
	IControlBase() = delete;
	IControlBase(IConfigLinker* linker, const char* module_name);
	virtual ~IControlBase();

	// It's the control input of the module. It could be: Reference, Feedback or Feedforward
	virtual void set_input(uint32_t pin_number, InputParameter ref) = 0;

	// Connect the module to imput of the following module in the chain
	bool set_output_link(IControlBase* module_ptr, uint32_t pin_number);

protected:
	void set_output(uint32_t pin_number, InputParameter ref);

private:
	IConfigLinker*	m_linker;
	IControlBase*	m_output;
	std::string		m_module_name;
protected:
	enum { REFERENCE_PIN_NUMBER = 0, FEEDBACK_PIN_NUMBER = 1, FEEDFORWARD_PIN_NUMBER = 2 };
	uint32_t		m_output_pin_number;
public:

};


