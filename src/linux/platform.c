#include <rhodius/_platform.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

inline bool RhPlatform_FileExists(const char* filename) {
    return access(filename, F_OK) == 0;
}
void RhPlatform_GetWorkingDirectory(char* out, size_t maxLength) {
    getcwd(out, maxLength);
}