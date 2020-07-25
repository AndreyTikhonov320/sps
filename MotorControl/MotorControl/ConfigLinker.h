#pragma once

#include "STM32.h"
#include "UserTimer.h"
#include "TimerCore.h"
#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON

using namespace rapidjson;

class ConfigLinker
{
public:
	ConfigLinker();
	virtual ~ConfigLinker();
	TimerCore* get_timer(const char* module_name);
	enum ConfigureLinkerErrorCode {NotInited=0, Ok, Wrong_configure_file_structure} ;
private:
	//Application resources
	static const uint8_t TIM_CORE_MAX_AMOUNT = 4;
	TimerCore* TimerCoreList[TIM_CORE_MAX_AMOUNT];
	static const uint16_t JASON_SIZE = 1024;
	char json[JASON_SIZE];
	Document document;  // Default template parameter uses UTF8 and MemoryPoolAllocator.
public:
	static ConfigLinker* instance();
private:
	bool parse_configuration();
	// Indicates the state of the linker
	
	ConfigureLinkerErrorCode error;
	bool restrict_module_name(std::string* name);
	// Initializa TimerCore timers
	bool init_timercore();
};

