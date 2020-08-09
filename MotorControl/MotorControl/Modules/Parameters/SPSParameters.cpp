#include "Parameters/SPSParameters.h"

namespace SystemParameters {

	SPSParameters::SPSParameters()
	{
	}

	SPSParameters::~SPSParameters()
	{
	}

	SPSParameters* SPSParameters::instance()
	{
		static SPSParameters singletone;
		return &singletone;
	}

	SPSParameters::ReturnCode SPSParameters::register_parameter(SPSParamterDescriptor* descriptor)
	{
		//register the paramter in  maps
		m_list_by_name[descriptor->m_short_name] = descriptor;
		m_list_by_address[descriptor->m_addr] = descriptor;

		//initialize the paramter value
		if (SPSParamterDescriptor::STATIC_PARAMETER_TYPE == descriptor->m_is_static) {
			//read from setting file
			//...
			//if there is no file or the file is currepted then set the default value
			descriptor->m_value = descriptor->m_default_value;

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

	SPSParamterDescriptor* SPSParameters::get_paramter(const char* short_name)
	{
		auto search = m_list_by_name.find(short_name);
		if (search == m_list_by_name.end()) {
			//the param has not been found
			return NULL;
		}		
		return search->second;
	}

	void SPSParameters::update_parameter(const char* short_name, SPSParamterDescriptor* descriptor)
	{
		auto search = m_list_by_name.find(short_name);
		if (search != m_list_by_name.end()) {
			//the param has been found, let's update it
			//...
		}
	}

}