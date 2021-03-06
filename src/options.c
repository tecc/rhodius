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

    out->argc = 0;
    out->argv = NULL;
    out->argv_noOptions = 0;
    out->argv_noOptions = NULL;
}

enum RhOptionsParserState {
    Rh_Waiting,
    Rh_MainBuildFile,
    Rh_WorkingDirectory,
    Rh_OnlyPositionals
};

int RhOptions_Parse(struct RhOptions* out, int argc, char** argv) {
    enum RhOptionsParserState state = Rh_Waiting;

    char** positionals = malloc(1);
    char** firstNonoptPositional = malloc(1);
    int positionalCount = 0;
    int nonoptPositionalCount = 0;

    void* temp;

    int tempi;

    for (int i = 1; i < argc; i++) {

        char* arg = argv[i];
        size_t argl = strlen(arg);

        switch (state) {
            case Rh_OnlyPositionals:
                goto RhAddOnlyPositional;
            RhAddPositional:
                if (argl >= 1 && arg[0] != '-' && firstNonoptPositional == NULL) {
                    tempi = nonoptPositionalCount;
                    nonoptPositionalCount++;
                    firstNonoptPositional = realloc(firstNonoptPositional, nonoptPositionalCount * sizeof(char*));
                    firstNonoptPositional[tempi] = arg;
                } else {
                RhAddOnlyPositional:
                    tempi = positionalCount;
                    positionalCount++;
                    positionals = realloc(positionals, sizeof(char*) * positionalCount);
                    positionals[tempi] = arg;
                }

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
                    continue;
                }
            }
        }

        goto RhAddPositional;
    }

    out->argv = positionals;
    out->argc = positionalCount;
    out->argv_noOptions = firstNonoptPositional;
    out->argc_noOptions = positionalCount;

    return 0;
}
const struct RhOptions* RhOptions_Get() {
    return RhOptions_Instance;
}
void RhOptions_Set(const struct RhOptions* options) {
    RhOptions_Instance = options;
}
