#include <rhodius/ext/lua.h>

#define RhExt_Lua_Get(state, key)      \
    lua_pushlightuserdata(state, key); \
    lua_gettable(state, LUA_REGISTRYINDEX)
#define RhExt_Lua_Set(state, key, value, type) \
    lua_pushlightuserdata(state, (void*) key); \
    lua_push##type(state, value);              \
    lua_settable(L, LUA_REGISTRYINDEX)

inline lua_Integer RhExt_Lua_GetInteger(lua_State* L, void* key) {
    RhExt_Lua_Get(L, key);
    return luaL_checkinteger(L, -1);
}
inline void RhExt_Lua_SetInteger(lua_State* L, void* key, lua_Integer integer) {
    RhExt_Lua_Set(L, key, integer, integer);
}
inline const char* RhExt_Lua_GetString(lua_State* L, void* key) {
    RhExt_Lua_Get(L, key);
    return luaL_checkstring(L, -1);
}
inline void RhExt_Lua_SetString(lua_State* L, void* key, const char* value) {
    RhExt_Lua_Set(L, key, value, string);
}
