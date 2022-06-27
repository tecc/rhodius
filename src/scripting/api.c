#include "rhodius/_util.h"
#include <errno.h>
#include <libgen.h>
#include <rhodius/generators/template.h>
#include <rhodius/log.h>
#include <rhodius/scripting/_script.h>
#include <stdlib.h>
#include <string.h>

static const char* keyScriptPointer = "script_pointer";

static int Lpath(lua_State* L) {
    struct RhScript* script = (struct RhScript*) RhExt_Lua_GetInteger(L, (void*) keyScriptPointer);
    const char* relativePath = luaL_checkstring(L, 1);
    size_t relativePathLen = strlen(relativePath);

    char* copy = RhUtil_CopyString(script->filename);
    const char* directory = dirname(copy);

    char* path = RhUtil_ResolvePath(2, directory, relativePath);
    if (path == NULL) {
        int error = errno;
        luaL_error(L, "Path is null: %s", strerror(error));
        return 0;
    }

    lua_pushstring(L, path);

    free(copy);
    return 1;
}

static int Luse_features(lua_State* L) {
    int count = lua_gettop(L);
    for (int i = 1; i <= count; i++) {
        const char* featureName = luaL_checkstring(L, i);

        bool found = false;
        // now to check manually
        // TODO(tecc): replace CMake with Rhodius and generate this file
        if (strcmp(featureName, "generator:template") == 0) {
            RhTemplateGenerator_InitLua(L);
            found = true;
        }


        if (found == true) {
            RhLog_Trace("Feature %s enabled\n", featureName);
        }
    }
}

void RhScript_Init_RegisterAPI(const struct RhScript* script) {
    RhExt_Lua_SetInteger(script->data->state, (void*) keyScriptPointer, (lua_Integer) script);
    RhLua_RegisterFunction(script->data->state, path);
    RhLua_RegisterFunction(script->data->state, use_features);
}