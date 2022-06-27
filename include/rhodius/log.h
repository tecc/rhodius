#ifndef RHODIUS_LOG_H
#define RHODIUS_LOG_H

#include <stdbool.h>
#include <stdint.h>
#ifdef RHODIUS_LOG_COLOURS
#include <stdio.h>

enum RhLogColour {
    RhLogColour_Reset = 0,
    RhLogColour_Black = 30,
    RhLogColour_Red = 31,
    RhLogColour_Green = 32,
    RhLogColour_Yellow = 33,
    RhLogColour_Blue = 34,
    RhLogColour_Magenta = 35,
    RhLogColour_Cyan = 36,
    RhLogColour_White = 37,
    RhLogColour_Grey = 90,
    RhLogColour_BrightRed = 91,
    RhLogColour_BrightGreen = 92,
    RhLogColour_BrightYellow = 93,
    RhLogColour_BrightBlue = 94,
    RhLogColour_BrightMagenta = 95,
    RhLogColour_BrightCyan = 96,
    RhLogColour_BrightWhite = 97,
};

void RhLog_PrintColour(FILE* file, enum RhLogColour colour, bool isBackground);
void RhLog_PrintColour_2(FILE* file, enum RhLogColour background, enum RhLogColour foreground);

#define RhCOLOUR_FORMAT "\x1b[%im"
#endif

enum RhLogLevel { // The values correspond to how verbose they are; Trace is the most verbose whilst Error is the least verbose
    RhLogLevel_Trace = 2,
    RhLogLevel_Debug = 1,
    RhLogLevel_Info = 0,
    RhLogLevel_Warn = -1,
    RhLogLevel_Error = -2,
};

bool RhLog_CanLog(enum RhLogLevel level);
void RhLog_SetLogLevel(enum RhLogLevel level);
void RhLog_Log(enum RhLogLevel level, const char* format, ...);
void RhLog_Trace(const char* format, ...);
void RhLog_Debug(const char* format, ...);
void RhLog_Info(const char* format, ...);
void RhLog_Warn(const char* format, ...);
void RhLog_Error(const char* format, ...);
enum RhLogLevel RhLog_GetLevelFromInt(int16_t value);

#endif
