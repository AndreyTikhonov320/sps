#pragma once
#include <string.h>

namespace FS{
	class IFS
	{
	public:
		virtual ~IFS() {}
		virtual bool read_text_file(const char* name, char* value, unsigned int max_size) = 0;
	};
};
