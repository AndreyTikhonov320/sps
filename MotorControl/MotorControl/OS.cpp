#include <stdio.h>
#include <iostream>
#include "Windows.h"
#include "OS.h"

namespace OS 
{
WindowsOS::WindowsOS()
{
}


WindowsOS::~WindowsOS()
{
}

WindowsOS* WindowsOS::instance()
{
	static WindowsOS __instance;
	return &__instance;
}

void WindowsOS::sleep(uint32_t ms)
{
	Sleep(100);
}
};

void OS::WindowsOS::enter_critical_section()
{
}


void OS::WindowsOS::leave_critical_section()
{
}
