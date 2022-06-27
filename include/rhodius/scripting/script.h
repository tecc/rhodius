#ifndef RHODIUS_SCRIPT_H
#define RHODIUS_SCRIPT_H

#include <rhodius/project.h>

struct RhScript {
    const char* filename;

    struct RhScript* parent;

    struct RhScript_Data* data;

    struct RhProject* project;
};
#define EMPTY_SCRIPT {data: NULL, parent: NULL, filename: NULL}

struct RhScript* RhScript_CreateEmpty();

void RhScript_Load(struct RhScript* out, const char* filename);

int RhScript_Run(struct RhScript* script);

void RhScript_Destroy(struct RhScript* out);

#endif
