#pragma once

#include <stdio.h>
#include <iostream>
#include <map>
#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "Modules/FS.h"

using namespace rapidjson;

namespace SystemParameters {
	class SPSParamterDescriptor;
	class SPSParameterValue;

	//The sigletone object of this class is contains configuration of the system
	class SPSParameters {
	public:
		enum ReturnCode { eOkReturnCode = 0, eErrorReturnCode = 1 };
		SPSParameters() = delete;
		SPSParameters(FS::IFS* _ptr, const char* config_name);
		virtual ~SPSParameters();
		virtual ReturnCode register_parameter(SPSParamterDescriptor* descriptor);
		virtual bool isParamter(const char* short_name);
		virtual SPSParameterValue get_parameter(const char* short_name);
		virtual void update_parameter(const char* short_name, SPSParameterValue& value);
		virtual void reset_all();
	private:
		
		void update_settings();
		void read_settings();

	private:
		std::map< std::string, SPSParamterDescriptor* > m_list_by_name;
		std::map< uint32_t, SPSParamterDescriptor* > m_list_by_address;
		FS::IFS* m_fs_ptr;
		std::string m_file_name;
		static const uint16_t	JASON_SIZE = 1024;
		char					m_json[JASON_SIZE];
		Document				m_document;  // Default template parameter uses UTF8 and MemoryPoolAllocator.
											 // Indicates the state of the linker
		bool m_error;
	};

	class ParameterRange {
	public:
		ParameterRange() = delete;
		ParameterRange(int32_t min, int32_t max) : m_min(min), m_max(max) {}
		~ParameterRange() {}
		int32_t apply_range(int32_t value) {
			if (value > m_max) return m_max;
			if (value < m_min) return m_min;
			return value;
		}
	private:
		int32_t m_min;
		int32_t m_max;

	};

	//SPSParameters initializes the object of this class but owner can change the value after
	class SPSParameterValue
	{
	public:
		
		SPSParameterValue() :m_value(0) {}
		SPSParameterValue(int32_t v) : m_value(v) {}
		~SPSParameterValue() {}
		int32_t get_value() const { return m_value; }
		const char* get_string() { 			
			snprintf(m_str, sizeof(m_str), "%d", m_value);
			return m_str; 
		};
		int32_t operator=(int32_t v) { m_value = v; return m_value; }
		bool	operator==(SPSParameterValue& v) { return (m_value == v.m_value); }
	private:
		int32_t m_value;
		char m_str[11];
	};


	//The interface must be supported by owner of the paramter
	class IParameters
	{
	public:
		~IParameters() {}
		//callback methods for change notification only
		virtual void on_read_param_value(uint32_t address) = 0;
		virtual bool on_write_param_value(uint32_t address, const SPSParameterValue& v) = 0;
	};

	//The parameter owner must create and initialize the object of this class 
	class SPSParamterDescriptor
	{
	public:
		enum PARAMETER_TYPE { STATIC_PARAMETER_TYPE = 0, DYNAMIC_PARAMETER_TYPE = 1 };
		SPSParamterDescriptor() = delete;
		SPSParamterDescriptor(	SPSParameters* config,
								IParameters* owner, 
								const char* short_name, 
								uint32_t addr, 								
								uint32_t default_value=0, 
								PARAMETER_TYPE is_static= DYNAMIC_PARAMETER_TYPE,
								ParameterRange range = ParameterRange(0,0) )
			: m_config(config), m_owner(owner), m_short_name(short_name), m_addr(addr), m_range(range), m_default_value(default_value), m_is_static(is_static)
		{
			m_config->register_parameter(this);
		}
		~SPSParamterDescriptor() {}

		SPSParameterValue& get_value() { return m_value; }
		void set_value(const SPSParameterValue& v) 
		{ 
			m_value = m_range.apply_range(v.get_value());
			m_owner->on_write_param_value(m_addr, m_value);
		}

	private:
		friend class SPSParameters;

		SPSParameters*		m_config;
		IParameters*		m_owner;
		std::string			m_short_name;
		uint32_t			m_addr;
		ParameterRange		m_range;
		uint32_t			m_default_value;
		PARAMETER_TYPE		m_is_static;
		SPSParameterValue	m_value;
	};
};