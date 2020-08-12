#include "pch.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <iostream>
#include "OS.h"
#include "Modules/FS.h"
#include "ConfigLinkerJson.h"

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
		memcpy(value, m_json, strlen(m_json)+1);
		return true;
	}
	virtual bool write_text_file(const char* name, const char* value)
	{
		m_json_for_write_operation = value;
		return true;
	}

	const char* get_json_after_write_operation() { return m_json_for_write_operation.c_str(); }

private:
	const char* m_json;
	std::string m_json_for_write_operation;
};
};

TEST(ConfigLinkerTest, get_timercore_when_configure_is_valid) {

	std::string json_file = "{\
			\"Resources.TimerCore0.hal_timer_number\":0,\
			\"Resources.TimerCore1.hal_timer_number\" : 1,\
			\
			\"Resources.AccelLoop.timer_type\" : \"TimerCore\",\
			\"Resources.AccelLoop.timer_number\" : 0,\
			\
			\"Resources.VelLoop.timer_type\" : \"TimerCore\",\
			\"Resources.VelLoop.timer_number\" : 1,\
			\
			\"Links.VelLoop.output.module\" : \"AccelLoop\",\
			\"Links.VelLoop.output.pin\" : \"reference\",\
			\
			\"Links.BasicReference.output.module\" : \"VelLoop\",\
			\"Links.BasicReference.output.pin\" : \"reference\",\
			\
			\"Resources\" : {\
			\"AccelLoop\" : {\
				\"timer_type\":\"TimerCore\",\
					\"timer_number\" : 0\
			}\
		},\
			\"Links\": {\
			\"BasicReferance\" : {\
				\"output\": {\
					\"module\":\"AccelLoop\",\
						\"pin\" : \"reference\"\
				}\
			}\
		}\
	}";


	FS::MockFS fs(json_file.c_str());
	TimerCore* timer_ptr = NULL;
	ConfigLinkerJson config(&fs, "C:\test_config.json");
	timer_ptr = config.get_timer("AccelLoop");

	//EXPECT_EQ(1, 1);
	EXPECT_TRUE(timer_ptr != NULL);
}