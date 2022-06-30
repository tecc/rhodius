#include <rhodius-mainplugin/generators/template.h>
#include <rhodius-mainplugin/main.h>

static int Ladd_template(lua_State* L) {
    const char* name = luaL_checkstring(L, 1);
    const char* path = luaL_checkstring(L, 2);

    RhAPI_Plugin_LogTrace(RhMainPlugin_Instance, "Template %s (file: %s) was added", name, path);
    return 0;
}

static int Lgenerate_template_result(lua_State* L) {
    RhAPI_Plugin_LogWarn(RhMainPlugin_Instance, "generate_template_result is not yet implemented");
}

void RhTemplateGenerator_InitLua(lua_State* L) {
    RhLua_RegisterFunction(L, add_template);
    RhLua_RegisterFunction(L, generate_template_result);
}
