#pragma once
#include <string.h>
#include "FS.h"

namespace FS{
	class WinFS : public IFS
	{
	public:
		WinFS();
		virtual ~WinFS();
		virtual bool read_text_file(const char* name, char* value, unsigned int max_size);
		virtual bool write_text_file(const char* name, const char* value);
	};
};
