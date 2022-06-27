#ifndef RHODIUSAPI_PLUGINS_H
#define RHODIUSAPI_PLUGINS_H

#include <stdbool.h>
#include <stddef.h>

#ifndef RHODIUS_VERSION
#define RHODIUS_API extern
#else
#define RHODIUS_API
#endif

#include <lua.h>

struct RhAPI_Plugin;

typedef bool(*RhAPI_Plugin_ScriptingFeatureFinder)(struct RhAPI_Plugin*, lua_State* luaState, const char* featureName);
typedef void(*RhAPI_Plugin_Destroyer)(struct RhAPI_Plugin*);

struct RhAPI_Plugin {
    const char* name;
    void* data;
    const size_t id;

    RhAPI_Plugin_ScriptingFeatureFinder scriptingFeatureFinder;
    RhAPI_Plugin_Destroyer destroyer;
};

RHODIUS_API void RhAPI_Plugin_Create(struct RhAPI_Plugin* out, const char* name, void* data, RhAPI_Plugin_ScriptingFeatureFinder featureFinder, RhAPI_Plugin_Destroyer destroyer);
RHODIUS_API void RhAPI_Plugin_Register(struct RhAPI_Plugin* plugin);
RHODIUS_API bool RhAPI_Plugin_FindScriptingFeature(struct RhAPI_Plugin* plugin, lua_State* state, const char* featureName);

#endif
