#ifndef RHODIUS_OPTIONS_H
#define RHODIUS_OPTIONS_H
#include <rhodius/util/linkedlist.h>
#include <stdbool.h>
#include <stdint.h>

struct RhOptions {
    const char* mainBuildFile;    // -m, --main-build-file
    const char* workingDirectory; // -c, -cwd, --current-working-directory
    const char* rhodiusDataDirectory;
    int16_t verbosity;
    bool enableTerminalColours : 1;
};

void RhOptions_SetDefault(struct RhOptions* out);
int RhOptions_Parse(struct RhOptions* out, int argc, char** argv);

const struct RhOptions* RhOptions_Get();
void RhOptions_Set(const struct RhOptions* options);

#endif
