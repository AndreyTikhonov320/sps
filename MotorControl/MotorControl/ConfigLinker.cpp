#include "stdafx.h"
#include "ConfigLinker.h"


ConfigLinker::ConfigLinker()
{
	for (int i = 0; i < TIM_CORE_MAX_AMOUNT; i++) TimerCoreList[i] = NULL;
	//Refactor on base of parsing of configure in JSON file
	TimerCoreList[0] = new TimerCore("TimerCore1");
	//Link MCU resources and application modules
	if(NULL != TimerCoreList[0]) tim1.SetServiceHandler(TimerCoreList[0]);
}


ConfigLinker::~ConfigLinker()
{
	for (int i = 0; i < TIM_CORE_MAX_AMOUNT; i++) if(NULL == TimerCoreList[i]) delete TimerCoreList[i];
}

TimerCore* ConfigLinker::get_timer(const char* module_name)
{
	if(module_name == "accel_loop_module")
		return TimerCoreList[0];
	return TimerCoreList[0];
}

ConfigLinker* ConfigLinker::instance()
{
	static ConfigLinker __instance;
	return &__instance;
}
