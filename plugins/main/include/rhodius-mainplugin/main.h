#ifndef RHODIUS_MAINPLUGIN_MAIN_H
#define RHODIUS_MAINPLUGIN_MAIN_H

#include <rhodius/api/plugins.h>

#ifndef RHODIUS_MAINPLUGIN_IS_MAIN_C
extern struct RhAPI_Plugin* RhMainPlugin_Instance;
#endif

void RhMainPlugin_Create(struct RhAPI_Plugin* out);

void RhPlugin_Register();

#endif
