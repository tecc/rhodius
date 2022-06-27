#define RHODIUS_LOG_COLOURS
#include <rhodius/log.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void RhLog_PrintColour_2(FILE* file, enum RhLogColour background, enum RhLogColour foreground) {
    fprintf(file, RhCOLOUR_FORMAT RhCOLOUR_FORMAT, background + 10, foreground);
}
void RhLog_PrintColour(FILE* file, enum RhLogColour colour, bool isBackground) {
    fprintf(file, RhCOLOUR_FORMAT, colour + (isBackground == true ? 10 : 0));
}

#define RhLog_Generic(out, prefixbg, prefixfg, prefix, msgbg, msgfg, va_list) \
    RhLog_PrintColour_2(out, prefixbg, prefixfg);                             \
    fprintf(out, prefix);                                                     \
    RhLog_PrintColour(out, RhLogColour_Reset, false);                         \
    fprintf(out, " ");                                                        \
    RhLog_PrintColour_2(out, msgbg, msgfg);                                   \
    vfprintf(out, format, va_list)

#define RhLog_CanLog_(level)                 \
    if (!RhLog_CanLog(RhLogLevel_##level)) { \
        return;                              \
    } else
#define RhLog_InitVa() \
    va_list va_list;   \
    va_start(va_list, format)
#define RhLog_Trace_() RhLog_Generic(stdout, RhLogColour_Reset, RhLogColour_Grey, "Trace", RhLogColour_Reset, RhLogColour_White, va_list)
#define RhLog_Debug_() RhLog_Generic(stdout, RhLogColour_Reset, RhLogColour_BrightBlue, "Debug", RhLogColour_Reset, RhLogColour_Reset, va_list)
#define RhLog_Info_() RhLog_Generic(stdout, RhLogColour_Reset, RhLogColour_BrightWhite, "Info", RhLogColour_Reset, RhLogColour_Reset, va_list)
#define RhLog_Warn_() RhLog_Generic(stderr, RhLogColour_Yellow, RhLogColour_BrightWhite, " Warn ", RhLogColour_Reset, RhLogColour_Yellow, va_list)
#define RhLog_Error_() RhLog_Generic(stderr, RhLogColour_BrightRed, RhLogColour_BrightWhite, " Error ", RhLogColour_Reset, RhLogColour_BrightRed, va_list)

void RhLog_Log(enum RhLogLevel level, const char* format, ...) {
    RhLog_InitVa();
    if (!RhLog_CanLog(level)) {
        return;
    }
    switch (level) {
        case RhLogLevel_Trace:
            RhLog_Trace_();
            break;
        case RhLogLevel_Debug:
            RhLog_Debug_();
            break;
        case RhLogLevel_Info:
            RhLog_Info_();
            break;
        case RhLogLevel_Warn:
            RhLog_Warn_();
            break;
        case RhLogLevel_Error:
            RhLog_Error_();
            break;
    }
    va_end(va_list);
}
void RhLog_Trace(const char* format, ...) {
    RhLog_CanLog_(Trace);
    RhLog_InitVa();
    RhLog_Trace_();
    va_end(va_list);
}
void RhLog_Debug(const char* format, ...) {
    RhLog_CanLog_(Debug);
    RhLog_InitVa();
    RhLog_Debug_();
    va_end(va_list);
}
void RhLog_Info(const char* format, ...) {
    RhLog_CanLog_(Info);
    RhLog_InitVa();
    RhLog_Info_();
    va_end(va_list);
}
void RhLog_Warn(const char* format, ...) {
    RhLog_CanLog_(Warn);
    RhLog_InitVa();
    RhLog_Warn_();
    va_end(va_list);
}
void RhLog_Error(const char* format, ...) {
    RhLog_CanLog_(Error);
    RhLog_InitVa();
    RhLog_Error_();
    va_end(va_list);
}

#ifndef RhLog_DEFAULT_LEVEL
#ifdef RHODIUS_BUILD_DEBUG
#define RhLog_DEFAULT_LEVEL RhLogLevel_Debug
#else
#define RhLog_DEFAULT_LEVEL RhLogLevel_Info
#endif
#endif
static enum RhLogLevel RhLog_LogLevel = RhLog_DEFAULT_LEVEL;
bool RhLog_CanLog(enum RhLogLevel level) {
    return level <= RhLog_LogLevel;
}
void RhLog_SetLogLevel(enum RhLogLevel level) {
    RhLog_LogLevel = level;
}

inline enum RhLogLevel RhLog_GetLevelFromInt(int16_t value) {
    if (value <= RhLogLevel_Error) {
        return RhLogLevel_Error;
    }
    if (value >= RhLogLevel_Trace) {
        return RhLogLevel_Trace;
    }
    return (enum RhLogLevel) value;
}
