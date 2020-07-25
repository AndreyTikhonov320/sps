
#include <stdio.h>
#include <iostream>
#include "FS.h"

FS::FS()
{
}


FS::~FS()
{
}
FS* FS::instance()
{
	static FS __instance;
	return &__instance;
}

 bool FS::read_text_file(const char* name, char* value, int max_size)
{
	FILE* file;
	errno_t error = fopen_s(&file, name, "r");
	if ((error != 0)||(file == NULL)) return false;
	//if (filelength(file)
	fread(value, sizeof(char), max_size, file);
	return true;
}