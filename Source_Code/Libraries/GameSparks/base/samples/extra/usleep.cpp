
#if defined(WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#if WINAPI_FAMILY_DESKTOP_APP == WINAPI_FAMILY

void usleep(__int64 usec)
{
	HANDLE timer;
	LARGE_INTEGER ft;
	
	ft.QuadPart = -(10 * usec); // Convert to 100 nanosecond interval, negative value indicates relative time
	
	timer = CreateWaitableTimer(NULL, TRUE, NULL);
	SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
	WaitForSingleObject(timer, INFINITE);
	CloseHandle(timer);
}

#else

void usleep(__int64 usec)
{
	// Not implemented
}

extern "C" char* getenv(const char* name)
{
	return 0;
}

#endif

#endif
