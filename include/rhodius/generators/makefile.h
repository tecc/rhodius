#ifndef RHODIUS_MAKEFILE_H
#define RHODIUS_MAKEFILE_H

enum RhMakefileGeneratorMode {
    RhMakefileGeneratorMode_GNU
};

struct RhMakefileGenerator {
    enum RhMakefileGeneratorMode mode;
};

#endif
