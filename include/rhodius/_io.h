#ifndef RHODIUS__IO_H
#define RHODIUS__IO_H

#include <stdbool.h>
#include <stddef.h>

bool RhIO_FileExists(const char* filename);
void RhIO_GetWorkingDirectory(char* out, size_t maxLength);

#endif
