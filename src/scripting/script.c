#include <malloc.h>
#include <rhodius/log.h>
#include <rhodius/platform.h>
#include <rhodius/scripting/_script.h>
#include <rhodius/scripting/script.h>
#include <stdlib.h>
#include <string.h>

const static struct RhScript empty = EMPTY_SCRIPT;

void RhScript_Init(struct RhScript* out) {
    struct RhScript_Data* data = malloc(sizeof(struct RhScript_Data));
    data->state = luaL_newstate();
    luaL_openlibs(data->state);

    data->freeFilename = false;

    out->data = data;
    RhScript_Init_RegisterAPI(out);
}

void RhScript_Load(struct RhScript* out, const char* filename) {
    out->filename = realpath(filename, NULL);
    RhScript_Init(out);
    out->data->freeFilename = true;

    if (RhPlatform_FileExists(filename) == false) {
        RhScript_Destroy(out);
        RhLog_Error("%s is not a file", filename);
        exit(1);
    }

    int status = luaL_loadfile(out->data->state, out->filename);
    if (status) {
        RhLog_Error("Couldn't load file %s:\n%s\n", out->filename, lua_tostring(out->data->state, -1));
        exit(1);
    }

    status = lua_pcall(out->data->state, 0, LUA_MULTRET, 0);
    if (status) {
        RhLog_Error("Evaluating file %s failed:\n%s\n", out->filename, lua_tostring(out->data->state, -1));
        exit(1);
    }

    return;
    /*FILE* file = fopen(filename, "r");

    char buf[BUFSIZ];
    int error;
    bool firstError = false;
    while (fgets(buf, sizeof(buf), file) != NULL) {
        error = luaL_loadbufferx(out->data->state, buf, strlen(buf), "line") || lua_pcall(out->data->state, 0, 0, 0);
        if (error) {
            if (!firstError) {
                fprintf(stderr, "Errors found whilst parsing file %s:\n", out->filename);
                firstError = true;
            }
            fprintf(stderr, "%s\n", lua_tostring(out->data->state, -1));
            lua_pop(out->data->state, 1);
        }
    }*/
}
void RhScript_Destroy(struct RhScript* out) {
    if (out->data->freeFilename) {
        free((void*) out->filename);
    }
    if (out->data) {
        lua_close(out->data->state);
        free(out->data);
    }

    struct RhScript emptyScript = EMPTY_SCRIPT;
    memcpy(out, &emptyScript, sizeof(struct RhScript));
}
struct RhScript* RhScript_CreateEmpty() {
    struct RhScript* ptr = malloc(sizeof(struct RhScript));
    memcpy(ptr, &empty, sizeof(struct RhScript));
    return ptr;
}
