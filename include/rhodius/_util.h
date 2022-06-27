#ifndef RHODIUS__UTIL_H
#define RHODIUS__UTIL_H

#ifdef __linux__
#include <linux/limits.h>
#define RhPATH_MAX PATH_MAX
#endif

#include <stddef.h>
char* RhUtil_CopyString(const char* string);
char* RhUtil_ResolvePath(size_t count, ...);
const char* RhUtil_GetWorkingDirectory();

#endif
