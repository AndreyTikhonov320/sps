#pragma once
#include "MCU.h"
namespace MCU
{

	class STM32_CONFIG
	{
	public:
		virtual ~STM32_CONFIG();

		static STM32_CONFIG* instance();

	protected:
		STM32_CONFIG();

//Incude auto generated header file contains all settings for MCU level
#include "Configurations/MCUConfiguration/stm32_configuration_gen.h"
	};

};