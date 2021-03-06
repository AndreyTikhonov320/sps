// MotorControl.cpp: определяет точку входа для консольного приложения.
//
#include <stdio.h>
#include <iostream>
#include "Configure.h"
#include "STM32.h"
#include "OS.h"
#include "Modules/WinFS.h"
#include "ConfigLinkerJson.h"
#include "Parameters/SPSParameters.h"
#include "TimerCore.h"
#include "AccelLoop.h"
#include "VelLoop.h"
#include "BasicReferance.h"
#include "AccelFeedback.h"
#include"PwmModule.h"
#include "Parameters/RestApiEmulator.h"

using namespace std;


int main()
{
	FS::WinFS fs;
	ConfigLinkerJson config_linker(&fs, CONFIG_LINKER_FILE);
	SystemParameters::SPSParameters parameters_pool(&fs, PARAMETERS_POOL_FILE);//SystemParameters::SPSParameters* parameters_pool = SystemParameters::SPSParameters::instance();

	//Initialized rules: 
	// 1. Every feedback must be initilized before the loop
	// 2. Make sure the feedback has the same timer as the loop. Check it in Linker.json
	// 3. Make sure the feedback is properly connected to feedback pin of the following loop. Check it in Linker.json

	static PwmModule pwm_module(&config_linker, &parameters_pool);
	static AccelLoop accel_loop(&config_linker, &parameters_pool);
	static AccelFeedback accel_feedback(&config_linker);
	static VelLoop vel_loop(&config_linker);
	static BasicReference referance(&config_linker);

	RestApiEmulator rest_api_emulator(&parameters_pool);

	//testing
	MCU::STM32* stm32 = MCU::STM32::reference();
	OS::WindowsOS* win = OS::WindowsOS::instance();

	//system emoulation
	std::string command;
	printf("\nUse one of the following commands to run different scenarious of emulation: \n");
	printf("  api - to emulate the work of RESTfull API interface in command-line mode\n");
	printf("  control - to emulate the work of control modules\n");
	printf("  oscil - to emulate the work of control modules and run oscillograph\n");
	printf("Input a command > ");

	cin >> command;
	
	
	if (command == "api")
	{
		printf("RESTful API interface emulation mode\n");
		printf("\nThe requests list:\n");
		printf("  print: RESTful API interface\n");
		printf("  get: returns the value of the parameter\n");
		printf("  put: set new the value of the parameter\n");
		printf("  reset: set all the parameters to default state\n");
		printf("  exit: terminate the program\n\n");		
		std::string request;
		while (true)
		{
			printf("Insert the request > ");
			cin >> request;
			if (request == "print") {
				rest_api_emulator.print_json();
			}
			else if (request == "get") {
				printf("Insert short name of the parameter > ");
				std::string short_name;
				cin >> short_name;
				cout << short_name << " = " << rest_api_emulator.get_parameter_value(short_name.c_str()) << endl;
			}
			else if (request == "put") {				
				printf("Insert short name of the parameter > ");
				std::string short_name;
				cin >> short_name;
				printf("Insert the value of the parameter > ");
				std::string value_str;
				cin >> value_str;
				rest_api_emulator.set_parameter_value(short_name.c_str(), atoi(value_str.c_str()));
			}
			else if (request == "reset") {
				rest_api_emulator.set_all_to_default();
			}
			else if (request == "exit") {
				break;
			}
		}
	}
	if (command == "control")
	{
		printf("Control mode\n");
		referance.temp_input(1024);
		while (true)
		{
			win->sleep(100);
			stm32->tim(1)->OnTime();//lower pri timer
			stm32->tim(0)->OnTime();//higher pri timer
		}
	}

    return 0;
}

