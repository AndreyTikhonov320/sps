#pragma once
class RestApiEmulator
{
public:
	RestApiEmulator() = delete;
	RestApiEmulator(SystemParameters::SPSParameters *config);
	virtual ~RestApiEmulator();

	void print_json();
	int32_t get_parameter_value(const char* short_name);
	bool set_parameter_value(const char* short_name, int32_t value);
	bool set_all_to_default();

private:
	SystemParameters::SPSParameters *m_config;
	char m_json[512];
};

