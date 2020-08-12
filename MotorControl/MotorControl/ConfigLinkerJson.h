#pragma once
#include <map>
#include <string>
#include "ConfigLinker.h"
#include "STM32.h"
#include "UserTimer.h"
#include "TimerCore.h"
#include "ControlBase.h"
#include "Modules/FS.h"
#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON

using namespace rapidjson;

class ConfigLinkerJson :
	public IConfigLinker
{
public:
	ConfigLinkerJson() = delete;
	ConfigLinkerJson(FS::IFS* _ptr, const char* config_name);
	virtual ~ConfigLinkerJson();

	virtual bool register_control_base(const char* module_name, IControlBase* module_ptr);
	virtual bool connect_control_base_to(const char* module_name, IControlBase* module_ptr);
	virtual TimerCore* get_timer(const char* module_name);

private:
	bool parse_configuration();
	bool restrict_module_name(std::string* name);
	// Initializa TimerCore timers
	bool init_timercore();

private:
	FS::IFS* m_fs_ptr;
	std::string m_config_file_name;

	//Application resources
	std::map<std::string, IControlBase*> m_app_modules;

	static const uint8_t	TIM_CORE_MAX_AMOUNT = 4;
	TimerCore*				m_timer_core_list[TIM_CORE_MAX_AMOUNT];

	static const uint16_t	JASON_SIZE = 1024;
	char					m_json[JASON_SIZE];

	Document				m_document;  // Default template parameter uses UTF8 and MemoryPoolAllocator.
										 // Indicates the state of the linker
};