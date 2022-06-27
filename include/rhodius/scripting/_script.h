#ifndef RHDOIUS__SCRIPT_H
#define RHODIUS__SCRIPT_H

#include "script.h"

#include <rhodius/ext/lua.h>

struct RhScript_Data {
    lua_State* state;

    bool freeFilename : 1;
};

void RhScript_Init_RegisterAPI(const struct RhScript* script);

#endif