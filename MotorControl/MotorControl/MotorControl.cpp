// MotorControl.cpp: определяет точку входа для консольного приложения.
//

#include <stdio.h>
#include <iostream>
#include "Configure.h"
#include "STM32.h"
#include "OS.h"
#include "Modules/WinFS.h"
#include "ConfigLinkerJson.h"
#include "TimerCore.h"
#include "AccelLoop.h"
#include "VelLoop.h"
#include "BasicReferance.h"

using namespace std;


int main()
{
	FS::WinFS fs;
	ConfigLinkerJson config_linker(&fs, CONFIG_LINKER_FILE);

	static AccelLoop accel_loop(&config_linker);
	static VelLoop vel_loop(&config_linker);
	static BasicReference referance(&config_linker);

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

