#pragma once
#include <map>
#include <string>
#include "STM32.h"
#include "UserTimer.h"
#include "TimerCore.h"
#include "ControlBase.h"
#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON

using namespace rapidjson;

class ConfigLinker
{
public:
	static void set_config_file(const char* config_name);
	virtual ~ConfigLinker();
	static ConfigLinker* instance();

	bool register_control_base(const char* module_name, ControlBase* module_ptr);
	TimerCore* get_timer(const char* module_name);
	enum ConfigureLinkerErrorCode {NotInited=0, Ok, Wrong_configure_file_structure} ;

private:
	ConfigLinker();
	bool parse_configuration();
	bool restrict_module_name(std::string* name);
	// Initializa TimerCore timers
	bool init_timercore(); 

private:
	static std::string config_file_name;
	//Application resources
	std::map<std::string, ControlBase*> m_app_modules;

	static const uint8_t	TIM_CORE_MAX_AMOUNT = 4;
	TimerCore*				m_timer_core_list[TIM_CORE_MAX_AMOUNT];

	static const uint16_t	JASON_SIZE = 1024;
	char					m_json[JASON_SIZE];

	Document				m_document;  // Default template parameter uses UTF8 and MemoryPoolAllocator.
										 // Indicates the state of the linker


	ConfigureLinkerErrorCode error;
};

