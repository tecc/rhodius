#ifndef RHODIUS_PLUGINS_H
#define RHODIUS_PLUGINS_H

#include <rhodius/api/plugins.h>
#include <rhodius/util/linkedlist.h>
#include <rhodius/api/errors.h>

enum RhAPI_Error RhPlugins_Initialise();
const struct RhList* RhPlugins_GetList();


#endif
