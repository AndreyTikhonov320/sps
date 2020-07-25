#pragma once
#include "MCU.h"
#include "STM32_CONFIG.h"
namespace MCU
{

	class STM32_TIM1 : public TIM {
	public:
		friend class STM32;
		virtual ~STM32_TIM1() {}

		virtual void enable() {}
		virtual void disable() {}
	private:
		STM32_TIM1()			
		{
			uint32_t time = STM32_CONFIG::instance()->TIM1_time();
			uint32_t pri_group = STM32_CONFIG::instance()->TIM1_interrupt_priority_group();
			uint32_t pri = STM32_CONFIG::instance()->TIM1_interrupt_order_group_in_group();
			
			//initialize TIM registers amd setup interrup control scheme for this timer
			//...

		};

		virtual void SetServiceHandler(ServiceHandler* h) { handler = h; }

		virtual void OnTime() {
			if (handler != NULL) handler->OnCallback();
		}

	};

	class STM32_TIM2 : public TIM {
	public:
		friend class STM32;
		virtual ~STM32_TIM2() {}

		virtual void enable() {}
		virtual void disable() {}
	private:
		STM32_TIM2()
		{
			uint32_t time = STM32_CONFIG::instance()->TIM2_time();
			uint32_t pri_group = STM32_CONFIG::instance()->TIM2_interrupt_priority_group();
			uint32_t pri = STM32_CONFIG::instance()->TIM2_interrupt_order_group_in_group();

			//initialize TIM registers amd setup interrup control scheme for this timer
			//...

		};

		virtual void SetServiceHandler(ServiceHandler* h) { handler = h; }

		virtual void OnTime() {
			if (handler != NULL) handler->OnCallback();
		}
	};

	class STM32 : public MCU
	{
	public:
		STM32();
		virtual ~STM32();
		virtual TIM* tim(int index);
		static STM32* reference();
	private:
		static STM32_TIM1* tim1_instance;
		static STM32_TIM2* tim2_instance;
	};

};