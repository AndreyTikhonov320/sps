

#include <cstdio>
#include "Modules/FS.h"
#include "ConfigLinkerJson.h"

using namespace std;


ConfigLinkerJson::ConfigLinkerJson(FS::IFS* _ptr, const char* config_name)
	: m_fs_ptr(_ptr)
	, m_config_file_name(config_name)
{
	parse_configuration();
	init_timercore();
}

ConfigLinkerJson::~ConfigLinkerJson()
{
	for (int i = 0; i < TIM_CORE_MAX_AMOUNT; i++) if (NULL == m_timer_core_list[i]) delete m_timer_core_list[i];
}

bool ConfigLinkerJson::register_control_base(const char* module_name, IControlBase* module_ptr)
{
	//register module
	std::string name(module_name);
	restrict_module_name(&name);
	m_app_modules[name] = module_ptr;
	return true;
}

bool ConfigLinkerJson::connect_control_base_to(const char* module_name, IControlBase* module_ptr)
{
	//find the link for the module in configure
	std::string query_output_module("Links.");
	query_output_module += module_name;
	restrict_module_name(&query_output_module);
	std::string query_output_pin(query_output_module);
	query_output_module += ".output.module";
	query_output_pin += ".output.pin";

	if (!m_document.HasMember(query_output_module.c_str())) return false;
	if (!m_document.HasMember(query_output_pin.c_str())) return false;
	const char* output_module_name = m_document[query_output_module.c_str()].GetString();
	const char* output_pin_name = m_document[query_output_pin.c_str()].GetString();

	//find the module ptr and connect to
	std::map<std::string, IControlBase*>::iterator iter;
	iter = m_app_modules.find(output_module_name);
	module_ptr->set_output_link(iter->second);

	return true;
}

TimerCore* ConfigLinkerJson::get_timer(const char* module_name)
{
	std::string query_timer_type("Resources.");
	query_timer_type += module_name;
	restrict_module_name(&query_timer_type);
	std::string query_timer_number(query_timer_type);
	query_timer_type += ".timer_type";
	query_timer_number += ".timer_number";

	if (!m_document.HasMember(query_timer_type.c_str())) return NULL;
	if (!m_document.HasMember(query_timer_number.c_str())) return NULL;
	if (strcmp(m_document[query_timer_type.c_str()].GetString(), "TimerCore") == 0) {
		int index = m_document[query_timer_number.c_str()].GetInt();
		if (index < TIM_CORE_MAX_AMOUNT) return m_timer_core_list[index];
	}

	return NULL;
}

bool ConfigLinkerJson::parse_configuration()
{
	// 1. Parse a JSON text string to a document.
	if (NULL == m_fs_ptr) return false;
	m_fs_ptr->read_text_file(m_config_file_name.c_str(), m_json, sizeof(m_json));
	printf("Original JSON:\n %s\n", m_json);

	//#if 0
							// "normal" parsing, decode strings to new buffers. Can use other input stream via ParseStream().
	if (m_document.Parse(m_json).HasParseError())
		return 1;
	//#else
	//						// In-situ parsing, decode strings directly in the source string. Source must be string.
	//	char buffer[sizeof(m_json)];
	//	memcpy(buffer, m_json, sizeof(m_json));
	//	if (m_document.ParseInsitu(buffer).HasParseError())
	//		return 1;
	//#endif
		// Document is a JSON value represents the root of DOM. Root can be either an object or array.
	if (!m_document.IsObject()) return false;

	return true;
}


bool ConfigLinkerJson::restrict_module_name(std::string* name)
{
	unsigned int index = name->find_first_of("::");
	if(index < name->length())
		name->erase(index);
	return true;
}


// Initialize TimerCore timers
bool ConfigLinkerJson::init_timercore()
{
	for (int i = 0; i < TIM_CORE_MAX_AMOUNT; i++) m_timer_core_list[i] = NULL;

	std::string query_timer_number;
	char s[3];
	for (int i = 0; i < TIM_CORE_MAX_AMOUNT; i++) {
		query_timer_number = "Resources.TimerCore";
		snprintf(s, sizeof(s), "%d", i);
		query_timer_number += s;
		query_timer_number += ".hal_timer_number";
		if (!m_document.HasMember(query_timer_number.c_str())) return true;
		int index = m_document[query_timer_number.c_str()].GetInt();
		query_timer_number = "TimerCore";
		query_timer_number += s;
		m_timer_core_list[i] = new TimerCore(query_timer_number.c_str());
		//Link MCU resources and application modules
		if (NULL != m_timer_core_list[i]) {
			if (NULL != MCU::STM32::reference()->tim(index))
				MCU::STM32::reference()->tim(index)->SetServiceHandler(m_timer_core_list[i]);
		}
	}
	return true;
}
