#ifndef RHODIUSAPI_LUA_H
#define RHODIUSAPI_LUA_H

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <rhodius/api/def.h>
#include <stdbool.h>

lua_Integer RhLua_GetInteger(lua_State* L, void* key);
void RhLua_SetInteger(lua_State* L, void* key, lua_Integer integer);
const char* RhLua_GetString(lua_State* L, void* key);
void RhLua_SetString(lua_State* L, void* key, const char* value);

#define RhLua_RegisterFunction(state, name)            \
    lua_pushcfunction(state, (lua_CFunction) L##name); \
    lua_setglobal(state, #name)

#endif
