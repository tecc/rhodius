#ifndef RHODIUSAPI_PLUGINS_H
#define RHODIUSAPI_PLUGINS_H

#include <stdbool.h>
#include <stddef.h>

#include <rhodius/api/def.h>
#include <rhodius/api/lua.h>

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

RHODIUS_API void RhAPI_LoadPluginFile(const char* filename, struct RhAPI_Plugin* out); // Loads and registers
RHODIUS_API void RhAPI_Plugin_Create(struct RhAPI_Plugin* out, const char* name, void* data, RhAPI_Plugin_ScriptingFeatureFinder featureFinder, RhAPI_Plugin_Destroyer destroyer);
RHODIUS_API void RhAPI_Plugin_Register(struct RhAPI_Plugin* plugin);
RHODIUS_API bool RhAPI_Plugin_FindScriptingFeature(struct RhAPI_Plugin* plugin, lua_State* state, const char* featureName);

RHODIUS_API void RhAPI_Plugin_LogTrace(const struct RhAPI_Plugin* plugin, const char* format, ...);
RHODIUS_API void RhAPI_Plugin_LogDebug(const struct RhAPI_Plugin* plugin, const char* format, ...);
RHODIUS_API void RhAPI_Plugin_LogInfo(const struct RhAPI_Plugin* plugin, const char* format, ...);
RHODIUS_API void RhAPI_Plugin_LogWarn(const struct RhAPI_Plugin* plugin, const char* format, ...);
RHODIUS_API void RhAPI_Plugin_LogError(const struct RhAPI_Plugin* plugin, const char* format, ...);

RHODIUS_PLUGIN_DEF void RhPlugin_Register(); // Implemented by plugin

#endif
