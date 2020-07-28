
#include <stdio.h>
#include <iostream>
#include "WinFS.h"

namespace FS {
	WinFS::WinFS()
	{
	}


	WinFS::~WinFS()
	{
	}

	bool WinFS::read_text_file(const char* name, char* value, unsigned int max_size)
	{
		FILE* file;
		errno_t error = fopen_s(&file, name, "r");
		if ((error != 0) || (file == NULL)) return false;
		//if (filelength(file)
		fread(value, sizeof(char), max_size, file);
		return true;
	}
};