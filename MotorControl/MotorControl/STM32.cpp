#include "stdafx.h"
#include "STM32.h"

namespace MCU {
	STM32_TIM1* STM32::tim1_instance = NULL;

	STM32::STM32()
	{
	}


	STM32::~STM32()
	{
	}


	TIM* STM32::tim()
	{
		if (NULL == STM32::tim1_instance) {
			STM32::tim1_instance = new STM32_TIM1();
		}
		return tim1_instance;
	}

	STM32* STM32::reference()
	{
		static STM32 _reference;
		return &_reference;
	}

};