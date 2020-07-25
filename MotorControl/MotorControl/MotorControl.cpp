// MotorControl.cpp: определяет точку входа для консольного приложения.
//

#include <stdio.h>
#include <iostream>
#include "TimerCore.h"
#include "STM32.h"
#include "AccelLoop.h"
#include "VelLoop.h"
#include "OS.h"

using namespace std;


int main()
{
	static AccelLoop accel_loop;
	static VelLoop vel_loop;

	//testing
	MCU::STM32* stm32 = MCU::STM32::reference();
	OS::WindowsOS* win = OS::WindowsOS::instance();
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

