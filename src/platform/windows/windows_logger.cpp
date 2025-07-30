#ifdef MINT_PLATFORM_WINDOWS

#include <windows.h>

#include "mint/core/logger.hpp"

namespace mnt
{
    void logger::console_write(log_level level, const char* msg)
    {
        HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);

        static u8 levels[6] = {64, 4, 6, 2, 1, 15};

        SetConsoleTextAttribute(console_handle, levels[level]);

        OutputDebugStringA(msg);

        u64 length = strlen(msg);

        LPDWORD number_written = 0;

        WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), msg, (DWORD)length, number_written, 0);
    }
} // namespace mnt
#endif
