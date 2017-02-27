#pragma once

#if defined(_WIN32) || defined(_WIN64)
void usleep(__int64 usec);
#elif defined(__APPLE__) || defined(ANDROID)
#	include <unistd.h>
#endif /* _WIN32 || _WIN64 */
