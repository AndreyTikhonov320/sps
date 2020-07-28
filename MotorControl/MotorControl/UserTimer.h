#pragma once
#include <iostream>
#include "ConfigLinker.h"
class IConfigLinker;
class IControlBase;

class IUserTimer
{
public:
	IUserTimer(IConfigLinker* linker, const char* module_name);
	virtual ~IUserTimer();

	virtual void OnTime() = 0;
private:
	IUserTimer();
	IConfigLinker* m_linker;
};

