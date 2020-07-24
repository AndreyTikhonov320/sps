// MotorControl.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include "TimerCore.h"
#include "STM32.h"
#include "AccelLoop.h"


using namespace std;


int main()
{
	char str[80];
	string name = __FUNCTION__;
	static TimerCore test_timer(name.c_str());

	printf("Test %s, %s %d", __FILE__, __FUNCTION__, __LINE__);

	static AccelLoop accel_loop;

	//testing
	MCU::STM32* stm32 = MCU::STM32::reference();
	stm32->tim()->OnTime();

	cin >> str;
    return 0;
}

