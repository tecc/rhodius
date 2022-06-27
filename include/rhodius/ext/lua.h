#ifndef RHODIUS_LUA_H
#define RHODIUS_LUA_H

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <stdbool.h>

lua_Integer RhExt_Lua_GetInteger(lua_State* L, void* key);
void        RhExt_Lua_SetInteger(lua_State* L, void* key, lua_Integer integer);
const char* RhExt_Lua_GetString(lua_State* L, void* key);
void        RhExt_Lua_SetString(lua_State* L, void* key, const char* value);

#define RhLua_RegisterFunction(state, name) \
    lua_pushcfunction(state, (lua_CFunction) L##name); \
    lua_setglobal(state, #name)

#endif
