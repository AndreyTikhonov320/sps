#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Parameters/SPSParameters.h"
#include "RestApiEmulator.h"

using namespace std;

RestApiEmulator::RestApiEmulator(SystemParameters::SPSParameters *config)
	: m_config(config)
	, m_json("")
{

}

RestApiEmulator::~RestApiEmulator()
{
}

void RestApiEmulator::print_json()
{
	ifstream myfile("./Modules/Parameters/sps_paramters.json");
	char line[100];
	if (myfile.is_open())
	{
		for (myfile >> line; !myfile.eof(); myfile >> line)
			cout << line << endl;
		cout << endl;
		myfile.close();
	}
}

int32_t RestApiEmulator::get_parameter_value(const char* short_name)
{
	SystemParameters::SPSParameterValue ret = m_config->get_parameter(short_name);
	return ret.get_value();
}

bool RestApiEmulator::set_parameter_value(const char* short_name, int32_t value)
{
	SystemParameters::SPSParameterValue v(value);
	m_config->update_parameter(short_name, v);
	return true;
}

bool RestApiEmulator::set_all_to_default()
{
	m_config->reset_all();
	return true;
}

