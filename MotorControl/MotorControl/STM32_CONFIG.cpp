#include "stdafx.h"
#include "STM32_CONFIG.h"

namespace MCU {

	STM32_CONFIG::STM32_CONFIG()
	{
	}


	STM32_CONFIG::~STM32_CONFIG()
	{
	}

	uint32_t STM32_CONFIG::TIM1_time()
	{
		return 1024;
	}
	uint32_t STM32_CONFIG::TIM1_interrupt_priority_group()
	{
		return 1;
	}
	uint32_t STM32_CONFIG::TIM1_interrupt_order_group_in_group()
	{
		return 1;
	}

	MCU_CONFIG* STM32_CONFIG::instance()
	{
		static STM32_CONFIG __instance;
		return &__instance;
	}

};