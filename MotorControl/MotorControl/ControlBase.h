#pragma once
#include "UserTimer.h"

class InputParameter {
public:
	InputParameter(uint32_t in) : parameter(in) {}
	virtual ~InputParameter() {}
	InputParameter operator-(const InputParameter& p) const { return parameter - p.parameter; }
	InputParameter operator*(const InputParameter& p) const { return parameter * p.parameter; }
	InputParameter operator*(const int& p) const { return parameter * p; }
private:
	InputParameter() {}
private:
	uint32_t parameter;
};

class ControlBase :
	public UserTimer
{
public:
	ControlBase() = delete;
	ControlBase(const char* module_name);
	virtual ~ControlBase();
	// It's the control input of the module
	virtual void set_reference(InputParameter ref) = 0;
	// It's the feadback for the module
	virtual void set_feedback(InputParameter fb) = 0;

protected:
	void set_output(InputParameter ref);

private:
	ControlBase* output;
};


