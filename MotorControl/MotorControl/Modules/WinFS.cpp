
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "WinFS.h"

using namespace std;

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
		fclose(file);
		return true;
	}

	bool WinFS::write_text_file(const char* name, const char* value)
	{
		ofstream f;
		f.open(name, std::ofstream::trunc);
		if (!f.is_open()) return false;
		f << value;
		f.flush();
		f.close();
		return true;
	}
};