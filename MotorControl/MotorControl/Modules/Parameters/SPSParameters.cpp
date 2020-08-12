
#include <cstdio>
#include "Parameters/SPSParameters.h"

using namespace std;

namespace SystemParameters 
{
	SPSParameters::SPSParameters(FS::IFS* _ptr, const char* config_name)
		: m_fs_ptr(_ptr)
		, m_file_name(config_name)
		, m_error(false)
	{
		read_settings();
		if (m_error)
		{
			m_error = false;
			reset_all();
		}
		
		if (m_error) assert("SPSParameters::SPSParameters: Can't initialize storage");
	}

	SPSParameters::~SPSParameters()
	{
	}

	SPSParameters::ReturnCode SPSParameters::register_parameter(SPSParamterDescriptor* descriptor)
	{
		//register the paramter in  maps
		m_list_by_name[descriptor->m_short_name] = descriptor;
		m_list_by_address[descriptor->m_addr] = descriptor;

		//initialize the paramter value
		if (SPSParamterDescriptor::STATIC_PARAMETER_TYPE == descriptor->m_is_static) {
			//read from setting file
			std::string query(descriptor->m_short_name);
			if (m_document.HasMember(query.c_str()))
			{
				descriptor->m_value = m_document[query.c_str()].GetInt();
			}
			else
			{
				//if there is no file or the file is currepted then set the default value
				descriptor->m_value = descriptor->m_default_value;
				//rewrite the settings file
				update_settings();
			}
		}
		else {
			descriptor->m_value = descriptor->m_default_value;
		}
		return eOkReturnCode;
	}

	bool SPSParameters::isParamter(const char* short_name)
	{
		auto search = m_list_by_name.find(short_name);
		if (search == m_list_by_name.end()) {
			//the param has not been found
			return false;
		}
		return true;
	}

	SPSParameterValue SPSParameters::get_parameter(const char* short_name)
	{
		auto search = m_list_by_name.find(short_name);
		if (search != m_list_by_name.end()) {
			//the param has been found
			return search->second->get_value();
		}		
		return NULL;
	}

	void SPSParameters::update_parameter(const char* short_name, SPSParameterValue& value)
	{
		auto search = m_list_by_name.find(short_name);
		if (search != m_list_by_name.end()) {
			//the param has been found, let's update it
			bool need_to_update = !(search->second->get_value() == value);
			search->second->set_value(value);
			if(need_to_update && (search->second->m_is_static == SPSParamterDescriptor::STATIC_PARAMETER_TYPE) )
				update_settings();
		}
	}
	void SPSParameters::reset_all()
	{
		for (auto iter = m_list_by_name.begin(); iter != m_list_by_name.end(); iter++)
		{
			if(iter->second->m_is_static == SPSParamterDescriptor::STATIC_PARAMETER_TYPE)
				iter->second->set_value( SPSParameterValue(iter->second->m_default_value) );
		}
		update_settings();
	}

	void SPSParameters::update_settings()
	{
		string str;
		str = "{\n";
		for (auto iter = m_list_by_name.begin(); iter != m_list_by_name.end(); iter++)
		{
			if (iter->second->m_is_static == SPSParamterDescriptor::STATIC_PARAMETER_TYPE)
			{
				str += "    \"";
				str += iter->second->m_short_name.c_str();
				str += "\" : ";
				str += iter->second->m_value.get_string();
			}
			auto next_iter = iter;
			next_iter++;
			if (next_iter != m_list_by_name.end()) {
				str += ",";
			}
			str += "\n";
		}
		str += "}\n";
		m_fs_ptr->write_text_file(m_file_name.c_str(), str.c_str());

		read_settings();//read json again
	}

	void SPSParameters::read_settings()
	{
		// 1. Parse a JSON text string to a document.
		m_fs_ptr->read_text_file(m_file_name.c_str(), m_json, sizeof(m_json));

		if (m_document.Parse(m_json).HasParseError()) m_error = true;
		else
		{
			// Document is a JSON value represents the root of DOM. Root can be either an object or array.
			if (!m_document.IsObject()) m_error = true;
		}
	}
}