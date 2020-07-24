#pragma once
#include <iostream>


class UserTimer
{
public:
	UserTimer(const char* module_name);
	virtual ~UserTimer();

	virtual void OnTime() = 0;
private:
	UserTimer();
};

