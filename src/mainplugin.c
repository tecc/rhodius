#include <malloc.h>
#include <rhodius/generators/template.h>
#include <rhodius/mainplugin.h>
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

}

void RhMainPlugin_Create(struct RhAPI_Plugin* out) {
    RhAPI_Plugin_Create(out, "rhodius", NULL, RhMainPlugin_FindFeature, RhMainPlugin_Destroy);
}

void RhMainPlugin_Register() {
    RhMainPlugin_Instance = malloc(sizeof(struct RhAPI_Plugin));
    RhMainPlugin_Create(RhMainPlugin_Instance);

    RhAPI_Plugin_Register(RhMainPlugin_Instance);
}