#pragma once
class OscillatorChannel
{
public:
	OscillatorChannel();
	virtual ~OscillatorChannel();
	static int register_parameter(const char* name);
};

