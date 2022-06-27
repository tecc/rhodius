#include <rhodius/generators/template.h>
#include <rhodius/log.h>

static int Ladd_template(lua_State* L) {
    const char* name = luaL_checkstring(L, 1);
    const char* path = luaL_checkstring(L, 2);

    RhLog_Trace("Template %s (file: %s) was added\n", name, path);
    return 0;
}

static int Lgenerate_template_result(lua_State* L) {

}

void RhTemplateGenerator_InitLua(lua_State* L) {
    RhLua_RegisterFunction(L, add_template);
    RhLua_RegisterFunction(L, generate_template_result);
}
