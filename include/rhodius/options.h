#ifndef RHODIUS_OPTIONS_H
#define RHODIUS_OPTIONS_H

struct RhOptions {
    const char* mainBuildFile; // -m, --main-build-file
    const char* workingDirectory; // -c, -cwd, --current-working-directory
    int verbosity;
};

void RhOptions_SetDefault(struct RhOptions* out);
int RhOptions_Parse(struct RhOptions* out, int argc, char** argv);

const struct RhOptions* RhOptions_Get();
void RhOptions_Set(const struct RhOptions* options);

#endif
