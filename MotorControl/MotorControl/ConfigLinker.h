#pragma once
#include "Modules/FS.h"
#include "UserTimer.h"
#include "TimerCore.h"
#include "ControlBase.h"

class IControlBase;
class IUserTimer;

class IConfigLinker
{
public:
	IConfigLinker();
	virtual ~IConfigLinker();

	virtual bool register_control_base(const char* module_name, IControlBase* module_ptr) = 0;
	virtual bool connect_control_base_to(const char* module_name, IControlBase* module_ptr) = 0;
	virtual TimerCore* get_timer(const char* module_name) = 0;
	enum ConfigureLinkerErrorCode {NotInited=0, Ok, Wrong_configure_file_structure} ;

protected:
	ConfigureLinkerErrorCode m_error;
};

