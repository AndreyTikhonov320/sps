#include "STM32.h"

namespace MCU {
	STM32_TIM1* STM32::tim1_instance = NULL;
	STM32_TIM2* STM32::tim2_instance = NULL;

	STM32::STM32()
	{
	}


	STM32::~STM32()
	{
	}


	TIM* STM32::tim(int index)
	{
		if (0 == index)
		{		
			if (NULL == STM32::tim1_instance) {
				STM32::tim1_instance = new STM32_TIM1();				
			}
			return STM32::tim1_instance;
		}
		if (1 == index)
		{
			if (NULL == STM32::tim2_instance) {
				STM32::tim2_instance = new STM32_TIM2();
			}
			return STM32::tim2_instance;
		}
		return NULL;
	}

	STM32* STM32::reference()
	{
		static STM32 _reference;
		return &_reference;
	}

};