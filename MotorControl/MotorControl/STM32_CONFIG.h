#pragma once
#include "MCU.h"
namespace MCU
{

	class STM32_CONFIG : public MCU_CONFIG
	{
	public:
		virtual ~STM32_CONFIG();

		virtual uint32_t TIM1_time();
		virtual uint32_t TIM1_interrupt_priority_group();
		virtual uint32_t TIM1_interrupt_order_group_in_group();

		static MCU_CONFIG* instance();

	protected:
		STM32_CONFIG();
	};

};