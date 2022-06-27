#define RHODIUS_LOG_COLOURS
#include <rhodius/log.h>
#include <rhodius/options.h>
#include <rhodius/scripting/script.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct RhScript* mainScript;

void onexit() {
    RhScript_Destroy(mainScript);
}

char* generatePadding(size_t target, size_t base) {
    size_t paddingLength = (target - base) >> 1;
    char* padding = malloc(paddingLength + 1);
    padding[paddingLength] = '\0';
    for (int i = 0; i < paddingLength; i++) {
        padding[i] = ' ';
    }
    return padding;
}
#define GENERIC_TARGET 40
void printHeader() {
    const char version[] = RHODIUS_VERSION;
    const char line1[] = "Copyright (c) tecc.me 2022.";
    const char line2[] = "Licensed under the MIT licence.";
    const char* lines[] = {line1, line2, NULL};
    char* headerPadding = generatePadding(GENERIC_TARGET, strlen(version) + 20);

    RhLog_PrintColour_2(stdout, RhLogColour_Reset, RhLogColour_BrightGreen);
    fprintf(stdout, "%sRhodius Build Tool ", headerPadding); // NOTE: Don't forget to update restLength!
    RhLog_PrintColour(stdout, RhLogColour_BrightYellow, false);
    fprintf(stdout, "v%s%s\n", version, headerPadding);
    RhLog_PrintColour(stdout, RhLogColour_Reset, false);

    free(headerPadding);

    int i = 0;
    while (lines[i] != NULL) {
        const char* line = lines[i];
        char* padding = generatePadding(GENERIC_TARGET, strlen(line));
        RhLog_PrintColour(stdout, RhLogColour_White, false);

        fprintf(stdout, "%s%s%s\n", padding, line, padding);
        free(padding);
        i++;
    }

    fprintf(stdout, "\n");
    RhLog_PrintColour(stdout, RhLogColour_Reset, false);
}
int main(int argc, char** argv) {
    atexit(onexit);

    struct RhOptions* options = malloc(sizeof(struct RhOptions));
    printHeader();


    RhOptions_Set(options);
    RhOptions_SetDefault(options);
    RhOptions_Parse(options, argc, argv);

    mainScript = RhScript_CreateEmpty();
    RhLog_Debug("Configuring %s...\n", options->mainBuildFile);
    RhScript_Load(mainScript, options->mainBuildFile);

}