#pragma once

#include "STM32.h"
#include "UserTimer.h"
#include "TimerCore.h"

class ConfigLinker
{
public:
	ConfigLinker();
	virtual ~ConfigLinker();
	TimerCore* get_timer(const char* module_name);

private:
	//MCU resources
	MCU::STM32_TIM1 tim1;

	//Application resources
	static const uint8_t TIM_CORE_MAX_AMOUNT = 4;
	TimerCore* TimerCoreList[TIM_CORE_MAX_AMOUNT];
public:
	static ConfigLinker* instance();
};

