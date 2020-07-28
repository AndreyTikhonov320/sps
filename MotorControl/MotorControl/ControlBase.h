#pragma once

#include "ConfigLinker.h"
#include "UserTimer.h"
class InputParameter {
public:
	InputParameter(uint32_t in) : m_parameter(in) {}
	virtual ~InputParameter() {}
	InputParameter operator-(const InputParameter& p) const { return m_parameter - p.m_parameter; }
	InputParameter operator*(const InputParameter& p) const { return m_parameter * p.m_parameter; }
	InputParameter operator*(const int& p) const { return m_parameter * p; }
private:
	InputParameter() {}
private:
	uint32_t m_parameter;
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
	// It's the control input of the module
	virtual void set_reference(InputParameter ref) = 0;
	// It's the feadback for the module
	virtual void set_feedback(InputParameter fb) = 0;

protected:
	void set_output(InputParameter ref);

private:
	IConfigLinker*	m_linker;
	IControlBase*	m_output;
	std::string		m_module_name;
public:

	// Connect the module to imput of the following module in the chain
	bool set_output_link(IControlBase* input_module_ptr);
};


