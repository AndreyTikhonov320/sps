// MotorControl.cpp: определяет точку входа для консольного приложения.
//

#include <stdio.h>
#include <iostream>
#include "TimerCore.h"
#include "STM32.h"
#include "AccelLoop.h"
#include "VelLoop.h"
#include "BasicReferance.h"
#include "OS.h"
#include "ConfigLinker.h"
#include "Configure.h"

using namespace std;


int main()
{
	ConfigLinker::set_config_file(CONFIG_LINKER_FILE);
	static AccelLoop accel_loop;
	static VelLoop vel_loop;
	static BasicReference referance;

	//testing
	MCU::STM32* stm32 = MCU::STM32::reference();
	OS::WindowsOS* win = OS::WindowsOS::instance();

	//system emoulation
	referance.temp_input(1024);
	while (true)
	{
		win->sleep(100);
		stm32->tim(1)->OnTime();//lower pri timer
		stm32->tim(0)->OnTime();//higher pri timer
	}
	char str[80];
	cin >> str;
    return 0;
}

