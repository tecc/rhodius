#include <cwalk.h>
#include <malloc.h>
#include <rhodius/_util.h>
#include <rhodius/options.h>
#include <rhodius/platform.h>
#include <stdarg.h>
#include <string.h>

char* RhUtil_CopyString(const char* string) {
    size_t length = strlen(string);
    char* data = malloc((length + 1) * sizeof(char));
    memcpy(data, string, length * sizeof(char));
    data[length] = '\0';
    return data;
}
char* RhUtil_ResolvePath(size_t count, ...) {
    if (count < 1) {
        return NULL; // Just in case, the all-time developer classic
    }

    va_list argp;
    va_start(argp, count);
    char buf[PATH_MAX]; // Just a temporary buffer so previous isn't being read and written at the same time
    char* previous = malloc(PATH_MAX * sizeof(char));
    strcpy(previous, RhUtil_GetWorkingDirectory());
    for (int i = 0; i < count; i++) {
        char* next = va_arg(argp, char*);
        cwk_path_get_absolute(previous, next, buf, PATH_MAX);
        strcpy(previous, buf);
    }
    return previous;
}
const char* RhUtil_GetWorkingDirectory() {
    return RhOptions_Get()->workingDirectory;
}
