#include "pch.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <iostream>
#include "OS.h"
#include "Modules/FS.h"
#include "Modules/Parameters/SPSParameters.h"

using namespace std;

namespace FS {
	class MockFS : public IFS
	{
	public:
		MockFS() = delete;
		MockFS(const char* json) : m_json(json) {}
		virtual ~MockFS() {}
		virtual bool read_text_file(const char* name, char* value, unsigned int max_size)
		{
			if (max_size < strlen(m_json)) return false;
			memcpy(value, m_json, strlen(m_json) + 1);
			return true;
		}
		virtual bool write_text_file(const char* name, const char* value)
		{
			m_json_for_write_operation = value;
			m_json = m_json_for_write_operation.c_str();
			return true;
		}

		const char* get_json_after_write_operation() { return m_json_for_write_operation.c_str(); }

	private:
		const char* m_json;
		std::string m_json_for_write_operation;
	};
};

#include "ControlBase.h"

class TestModule : public SystemParameters::IParameters
{
private:
	SystemParameters::SPSParamterDescriptor m_TEST;

private:
	#define PARAMETER_SHORT_PATH__TEST		"Static/TestGroup"
	#define PARAMETER_SHORT_NAME__TEST		"ts001"
	#define PARAMETER_ADDRESS__TEST			(1)
	#define PARAMETER_DEFAULT__TEST			(2048)

public:
	TestModule() = delete;
	TestModule(SystemParameters::SPSParameters* config)
		:m_TEST(config,
			this,
			PARAMETER_SHORT_NAME__TEST,
			PARAMETER_ADDRESS__TEST,
			PARAMETER_DEFAULT__TEST,
			SystemParameters::SPSParamterDescriptor::STATIC_PARAMETER_TYPE,
			SystemParameters::ParameterRange(1024, 1024 * 100))
	{
	}
	virtual ~TestModule() {	}

	//callback methods for change notification only
	virtual void on_read_param_value(uint32_t address) {}
	virtual bool on_write_param_value(uint32_t address, const SystemParameters::SPSParameterValue& v) {
		return true;
	}
};


TEST(SPSParametersTest, parameter_is_valid_when_it_is_in_json_and_when_added_to_pool) {

	std::string json_file = "{\
		\"ts001\" : 2048,\
		\"pw001\" : 4096\
	}";


	FS::MockFS fs(json_file.c_str());
	SystemParameters::SPSParameters parameters_pool(&fs, "C:\test_param.json");
	TestModule test_module(&parameters_pool);

	//EXPECT_EQ(1, 1);
	EXPECT_TRUE(parameters_pool.isParamter("ts001"));
	EXPECT_TRUE(!parameters_pool.isParamter("pw001"));
	EXPECT_EQ(parameters_pool.get_parameter("ts001").get_value(), 2048);
}

TEST(SPSParametersTest, json_updated_after_set_new_value_of_parameter) {

	std::string json_file = "{\
		\"ts001\" : 2048,\
		\"pw001\" : 4096\
	}";


	FS::MockFS fs(json_file.c_str());
	SystemParameters::SPSParameters parameters_pool(&fs, "C:\test_param.json");
	TestModule test_module(&parameters_pool);

	//EXPECT_EQ(1, 1);
	EXPECT_TRUE(parameters_pool.isParamter("ts001"));
	EXPECT_EQ(parameters_pool.get_parameter("ts001").get_value(), 2048);
	parameters_pool.update_parameter("ts001", SystemParameters::SPSParameterValue(4096));
	EXPECT_EQ(parameters_pool.get_parameter("ts001").get_value(), 4096);
}

TEST(SPSParametersTest, range_is_applied_to_parameter_when_user_tries_to_set_new_value) {

	std::string json_file = "{\
		\"ts001\" : 2048,\
		\"pw001\" : 4096\
	}";


	FS::MockFS fs(json_file.c_str());
	SystemParameters::SPSParameters parameters_pool(&fs, "C:\test_param.json");
	TestModule test_module(&parameters_pool);

	//EXPECT_EQ(1, 1);
	EXPECT_TRUE(parameters_pool.isParamter("ts001"));
	EXPECT_EQ(parameters_pool.get_parameter("ts001").get_value(), 2048);
	parameters_pool.update_parameter("ts001", SystemParameters::SPSParameterValue(512));
	//The range of the parameter is [1024, 1024 * 100]. So, it will be narrowed to 1024
	EXPECT_EQ(parameters_pool.get_parameter("ts001").get_value(), 1024);
}

TEST(SPSParametersTest, parameter_value_is_equalt_to_default_value_after_reset) {

	std::string json_file = "{\
		\"ts001\" : 5000,\
		\"pw001\" : 4096\
	}";


	FS::MockFS fs(json_file.c_str());
	SystemParameters::SPSParameters parameters_pool(&fs, "C:\test_param.json");
	TestModule test_module(&parameters_pool);

	//EXPECT_EQ(1, 1);
	EXPECT_TRUE(parameters_pool.isParamter("ts001"));
	EXPECT_EQ(parameters_pool.get_parameter("ts001").get_value(), 5000);
	parameters_pool.reset_all();
	//The default value is 2048. So, it will be 2048 after reset
	EXPECT_EQ(parameters_pool.get_parameter("ts001").get_value(), 2048);
}

TEST(SPSParametersTest, paramters_core_stores_new_value_to_file) {

	std::string json_file = "{\
		\"ts001\" : 5000\
	}";
	std::string json_file_after_updating = "{\n    \"ts001\" : 4096\n}\n";



	FS::MockFS fs(json_file.c_str());
	SystemParameters::SPSParameters parameters_pool(&fs, "C:\test_param.json");
	TestModule test_module(&parameters_pool);

	//EXPECT_EQ(1, 1);
	EXPECT_TRUE(parameters_pool.isParamter("ts001"));
	EXPECT_EQ(parameters_pool.get_parameter("ts001").get_value(), 5000);
	parameters_pool.update_parameter("ts001", SystemParameters::SPSParameterValue(4096));

	std::string json = fs.get_json_after_write_operation();
	EXPECT_EQ(json, json_file_after_updating);
}