#include <malloc.h>
#include <rhodius-mainplugin/generators/template.h>
#define RHODIUS_MAINPLUGIN_IS_MAIN_C
#include <rhodius-mainplugin/main.h>
#include <string.h>

static struct RhAPI_Plugin* RhMainPlugin_Instance;

bool RhMainPlugin_FindFeature(struct RhAPI_Plugin* plugin, lua_State* L, const char* featureName) {
    if (strcmp(featureName, "generator:template") == 0) {
        RhTemplateGenerator_InitLua(L);
        return true;
    }

    return false;
}

void RhMainPlugin_Destroy(struct RhAPI_Plugin* plugin) {
    // Since the main plugin doesn't really do anything, just leave it
}

void RhMainPlugin_Create(struct RhAPI_Plugin* out) {
    RhAPI_Plugin_Create(out, "rhodius", NULL, RhMainPlugin_FindFeature, RhMainPlugin_Destroy);
}

void RhPlugin_Register() {
    RhMainPlugin_Instance = malloc(sizeof(struct RhAPI_Plugin));
    RhMainPlugin_Create(RhMainPlugin_Instance);

    RhAPI_Plugin_Register(RhMainPlugin_Instance);

    RhAPI_Plugin_LogDebug(RhMainPlugin_Instance, "Instance created (at %p) and registered", RhMainPlugin_Instance);
}