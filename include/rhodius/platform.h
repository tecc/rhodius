#ifndef RHODIUS_PLATFORM_H
#define RHODIUS_PLATFORM_H

#include <stdbool.h>
#include <stddef.h>

#include <rhodius/api/errors.h>

#define RhPlatform_SMALL_BUFFER_SIZE 512
#define RhPlatform_BUFFER_SIZE       8192

struct RhPlatform_FileState {
    bool isDirectory : 1;
    bool exists : 1;
    bool accessible : 1;
};

bool RhPlatform_FileExists(const char* filename);
enum RhAPI_Error RhPlatform_GetFileState(const char* filename, struct RhPlatform_FileState* out);

enum RhAPI_Error RhPlatform_MakeDirectoryRecursive(const char* directory);

void RhPlatform_GetWorkingDirectory(char* out, size_t maxLength);

struct RhPlatform_TerminalCapabilities {
    bool colours : 1;
};

void RhPlatform_GetTerminalCapabilities(struct RhPlatform_TerminalCapabilities* out);
enum RhAPI_Error RhPlatform_GetUserHomeDirectory(char* out, size_t maxLength);

#define RhPlatform_SYSNAME_LINUX   "linux"
#define RhPlatform_SYSNAME_WINDOWS "windows"
#define RhPlatform_SYSNAME_MACOS   "macos"
const char* RhPlatform_GetSystemName();

#endif
