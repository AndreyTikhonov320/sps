#include "STM32_CONFIG.h"

namespace MCU {

	STM32_CONFIG::STM32_CONFIG()
	{
	}


	STM32_CONFIG::~STM32_CONFIG()
	{
	}


	STM32_CONFIG* STM32_CONFIG::instance()
	{
		static STM32_CONFIG __instance;
		return &__instance;
	}

};