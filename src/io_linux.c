#include <rhodius/_io.h>
#include <unistd.h>
#include <stdlib.h>

inline bool RhIO_FileExists(const char* filename) {
    return access(filename, F_OK) == 0;
}
void RhIO_GetWorkingDirectory(char* out, size_t outSize) {
    getcwd(out, outSize);
}
