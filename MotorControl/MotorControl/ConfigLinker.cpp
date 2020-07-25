
#include "ConfigLinker.h"

#include <cstdio>
#include "Modules/FS.h"

using namespace std;



ConfigLinker::ConfigLinker()
	: error(NotInited)
{
	if (!parse_configuration()) error = Wrong_configure_file_structure;
	else {
		error = Ok;
		init_timercore();
	}
}


ConfigLinker::~ConfigLinker()
{
	for (int i = 0; i < TIM_CORE_MAX_AMOUNT; i++) if(NULL == TimerCoreList[i]) delete TimerCoreList[i];
}

TimerCore* ConfigLinker::get_timer(const char* module_name)
{
	std::string query_timer_type("Resources.");
	query_timer_type += module_name;
	restrict_module_name(&query_timer_type);
	std::string query_timer_number(query_timer_type);
	query_timer_type += ".timer_type";
	query_timer_number += ".timer_number";

	if (!document.HasMember(query_timer_type.c_str())) return NULL;
	if (!document.HasMember(query_timer_number.c_str())) return NULL;
	if (strcmp(document[query_timer_type.c_str()].GetString(), "TimerCore") == 0) {
		int index = document[query_timer_number.c_str()].GetInt();
		if(index < TIM_CORE_MAX_AMOUNT) return TimerCoreList[index];
	}
		
	return NULL;
}

ConfigLinker* ConfigLinker::instance()
{
	static ConfigLinker __instance;
	return &__instance;
}


bool ConfigLinker::parse_configuration()
{
	// 1. Parse a JSON text string to a document.
	FS::instance()->read_text_file("C:/Tikhonov/progs/education/sps/MotorControl/MotorControl/Configurations/Linker.json", json, sizeof(json));
	printf("Original JSON:\n %s\n", json);

//#if 0
						// "normal" parsing, decode strings to new buffers. Can use other input stream via ParseStream().
	if (document.Parse(json).HasParseError())
		return 1;
//#else
						// In-situ parsing, decode strings directly in the source string. Source must be string.
//	char buffer[sizeof(json)];
//	memcpy(buffer, json, sizeof(json));
//	if (document.ParseInsitu(buffer).HasParseError())
//		return 1;
//#endif
	// Document is a JSON value represents the root of DOM. Root can be either an object or array.
	if (!document.IsObject()) return false;

	return true;
}


bool ConfigLinker::restrict_module_name(std::string* name)
{
	name->erase(name->find_first_of("::"));
	return true;
}


// Initializa TimerCore timers
bool ConfigLinker::init_timercore()
{
	for (int i = 0; i < TIM_CORE_MAX_AMOUNT; i++) TimerCoreList[i] = NULL;

	std::string query_timer_number;		
	char s[3];
	for (int i = 0; i < TIM_CORE_MAX_AMOUNT; i++) {
		query_timer_number = "Resources.TimerCore";
		snprintf(s, sizeof(s), "%d", i);
		query_timer_number += s;
		query_timer_number += ".hal_timer_number";
		if (!document.HasMember(query_timer_number.c_str())) return true;
		int index = document[query_timer_number.c_str()].GetInt();
		query_timer_number = "TimerCore";
		query_timer_number += s;
		TimerCoreList[i] = new TimerCore(query_timer_number.c_str());
		//Link MCU resources and application modules
		if (NULL != TimerCoreList[i]) {
			if (NULL != MCU::STM32::reference()->tim(index))
				MCU::STM32::reference()->tim(index)->SetServiceHandler(TimerCoreList[i]);
		}
	}
	return true;
}
