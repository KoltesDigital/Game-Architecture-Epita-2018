#include <platform/SetWorkingDirectory.hpp>

#include <unistd.h>

namespace platform
{
	bool SetWorkingDirectory(const char *path)
	{
		auto ret = chdir(path);
		return ret == 0;
	}
}
