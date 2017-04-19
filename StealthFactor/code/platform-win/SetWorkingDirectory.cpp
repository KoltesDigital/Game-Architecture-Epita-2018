#include <platform/SetWorkingDirectory.hpp>

#include <windows.h>

namespace platform
{
	bool SetWorkingDirectory(const char *path)
	{
		wchar_t wPath[4096];
		MultiByteToWideChar(CP_ACP, 0, path, -1, wPath, 4096);
		auto ret = SetCurrentDirectory(wPath);
		return ret != 0;
	}
}
