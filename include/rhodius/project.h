#ifndef RHODIUS_PROJECT_H
#define RHODIUS_PROJECT_H

struct RhProject {
    char* name;
    char* rootPath;

    struct RhTarget** targets;
};


struct RhTarget {
    char* name;

    struct RhProject* project;
};

#endif
