#pragma once
#include <string.h>
class FS
{
public:
	FS();
	virtual ~FS();
	bool read_text_file(const char* name, char* value, int max_size);
	static FS* instance();
};

