#include <malloc.h>
#include <rhodius/_util.h>
#include <rhodius/options.h>
#include <rhodius/platform.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


static const struct RhOptions* RhOptions_Instance;

void RhOptions_SetDefault(struct RhOptions* out) {
    out->mainBuildFile = "build.rhodius.lua";

    char* buffer = malloc(RhPATH_MAX);
    RhPlatform_GetWorkingDirectory(buffer, RhPATH_MAX);
    out->workingDirectory = buffer;
    out->verbosity = 0;

    buffer = malloc(RhPATH_MAX);
    RhPlatform_GetUserHomeDirectory(buffer, RhPATH_MAX);
    out->rhodiusDataDirectory = RhUtil_ResolvePath(2, buffer, ".rhodius"); // ~/.rhodius
    free(buffer);                                                          // Avoiding memory leaks since 2022
    if (!RhPlatform_FileExists(out->rhodiusDataDirectory)) {
        RhPlatform_MakeDirectoryRecursive(out->rhodiusDataDirectory);
    }

    struct RhPlatform_TerminalCapabilities termCap;
    RhPlatform_GetTerminalCapabilities(&termCap);
    out->enableTerminalColours = termCap.colours;
}

enum RhOptionsParserState {
    Rh_Waiting,
    Rh_MainBuildFile,
    Rh_WorkingDirectory,
    Rh_OnlyPositionals
};

int RhOptions_Parse(struct RhOptions* out, int argc, char** argv) {
    enum RhOptionsParserState state = Rh_Waiting;

    char** others = malloc(16 * sizeof(char*));
    int positionals = 0;

    void* temp;

    for (int i = 1; i < argc; i++) {

        char* arg = argv[i];
        size_t argl = strlen(arg);

        switch (state) {
            case Rh_OnlyPositionals:
            RhAddPositional:
                others[positionals++] = arg;
                continue;
            case Rh_MainBuildFile:
                temp = malloc(argl * sizeof(char));
                strcpy(temp, arg);
                out->mainBuildFile = temp;
                state = Rh_Waiting;
                continue;
            default:
                break;
        }

        if (argl < 1) {
            continue;
        }


        if (argl < 2) {
            continue;
        }
        if (arg[0] == '-') {
            if (arg[1] == '-') {
                if (argl == 2) {
                    state = Rh_OnlyPositionals;
                    continue;
                }

                if (strcmp(arg + 2, "main-build-file") == 0) {
                    state = Rh_MainBuildFile;
                    continue;
                }
                if (strcmp(arg + 2, "colours") == 0) {
                    out->enableTerminalColours = true;
                    continue;
                }
                if (strcmp(arg + 2, "no-colours") == 0) {
                    out->enableTerminalColours = false;
                    continue;
                }
            } else {
                // SHORT FORM
                if (strcmp(arg + 1, "m") == 0) {
                    state = Rh_MainBuildFile;
                    continue;
                }
                if (strcmp(arg + 1, "c") == 0) {
                    state = Rh_WorkingDirectory;
                    continue;
                }
                if (arg[1] == 's' || arg[1] == 'v') {
                    // silent
                    int16_t value = 0;
                    for (int j = 1; j < argl; j++) {
                        switch (arg[j]) {
                            case 's':
                                value--;
                                continue;
                            case 'v':
                                value++;
                                continue;
                        }
                    }
                    out->verbosity += value;
                }
            }
        }

        goto RhAddPositional;
    }

    return 0;
}
const struct RhOptions* RhOptions_Get() {
    return RhOptions_Instance;
}
void RhOptions_Set(const struct RhOptions* options) {
    RhOptions_Instance = options;
}
