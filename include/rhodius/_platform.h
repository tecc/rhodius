#ifndef RHODIUS__PLATFORM_H
#define RHODIUS__PLATFORM_H

#include <stdbool.h>
#include <stddef.h>

bool RhPlatform_FileExists(const char* filename);
void RhPlatform_GetWorkingDirectory(char* out, size_t maxLength);

bool RhPlatform_TerminalSupportsColour();

#endif
