#include <malloc.h>
#include <rhodius/_plugins.h>
#include <rhodius/api/plugins.h>
#include <rhodius/log.h>
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
const struct RhLinkedList* RhPlugins_GetList() {
    return &RhPlugins_Instance->pluginList;
}

void RhAPI_Plugin_Create(struct RhAPI_Plugin* out, const char* name, void* data, RhAPI_Plugin_ScriptingFeatureFinder featureFinder, RhAPI_Plugin_Destroyer destroyer) {
    out->name = name;
    out->data = data;
    out->scriptingFeatureFinder = featureFinder;
    out->destroyer = destroyer;
}

void RhAPI_Plugin_Register(struct RhAPI_Plugin* plugin) {
    struct RhLinkedListNode* node = malloc(sizeof(struct RhLinkedListNode));
    node->value = plugin;
    RhList_Append(&RhPlugins_Instance->pluginList, node);
}
bool RhAPI_Plugin_FindScriptingFeature(struct RhAPI_Plugin* plugin, lua_State* state, const char* featureName) {
    return plugin->scriptingFeatureFinder(plugin, state, featureName);
}

#define RhAPI_LOGF_IMPL(level)                                                                 \
    void RhAPI_Plugin_Log##level(const struct RhAPI_Plugin* plugin, const char* format, ...) { \
        va_list argp;                                                                          \
        char* buffer = NULL;                                                                   \
        va_start(argp, format);                                                                \
        int requiredSize = 0;                                                                  \
        requiredSize = vsnprintf(buffer, requiredSize, format, argp);                          \
        va_end(argp);                                                                          \
                                                                                               \
        const char* message;                                                                   \
        if (requiredSize < 1) {                                                                \
            message = "";                                                                      \
        } else {                                                                               \
            buffer = malloc(requiredSize * sizeof(char));                                      \
            vsprintf(buffer, format, argp);                                                    \
            buffer[requiredSize] = '\0';                                                       \
            message = buffer;                                                                  \
        }                                                                                      \
                                                                                               \
        RhLog_##level("[%s] %s", plugin->name, message);                                       \
        free(buffer);                                                                          \
    }

RhAPI_LOGF_IMPL(Trace);
RhAPI_LOGF_IMPL(Debug);
RhAPI_LOGF_IMPL(Info);
RhAPI_LOGF_IMPL(Warn);
RhAPI_LOGF_IMPL(Error);