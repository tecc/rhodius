#include <malloc.h>
#include <rhodius/_plugins.h>
#include <rhodius/api/plugins.h>
#include <rhodius/plugins.h>

static struct RhPlugins_Instance* RhPlugins_Instance = NULL;

enum RhAPI_Error RhPlugins_Initialise() {
    RhPlugins_Instance = malloc(sizeof(RhPlugins_Instance));

    if (RhPlugins_Instance == NULL) {
        return RhAPI_Error_AllocationFailed;
    }

    RhList_Create(&RhPlugins_Instance->pluginList);

    return RhAPI_Error_Ok;
}
const struct RhList* RhPlugins_GetList() {
    return &RhPlugins_Instance->pluginList;
}

void RhAPI_Plugin_Create(struct RhAPI_Plugin* out, const char* name, void* data, RhAPI_Plugin_ScriptingFeatureFinder featureFinder, RhAPI_Plugin_Destroyer destroyer) {
    out->name = name;
    out->data = data;
    out->scriptingFeatureFinder = featureFinder;
    out->destroyer = destroyer;
}

void RhAPI_Plugin_Register(struct RhAPI_Plugin* plugin) {
    struct RhListNode* node = malloc(sizeof (struct RhListNode));
    node->value = plugin;
    RhList_Append(&RhPlugins_Instance->pluginList, node);
}
bool RhAPI_Plugin_FindScriptingFeature(struct RhAPI_Plugin* plugin, lua_State* state, const char* featureName) {
    return plugin->scriptingFeatureFinder(plugin, state, featureName);
}
