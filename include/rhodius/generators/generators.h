#ifndef RHODIUS_GENERATORS_H
#define RHODIUS_GENERATORS_H

struct RhGenerator;

typedef int(RhGenerator_Generate)(struct RhGenerator*, struct RhTarget*);
typedef void(RhGenerator_Destroy)(struct RhGenerator*);
struct RhGenerator {
    const char* name;
    void* data;
    RhGenerator_Generate* generate_f;
    RhGenerator_Destroy* destroy_f;
};

#endif
