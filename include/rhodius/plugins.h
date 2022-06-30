#ifndef RHODIUS_PLUGINS_H
#define RHODIUS_PLUGINS_H

#include <rhodius/api/errors.h>
#include <rhodius/api/plugins.h>
#include <rhodius/util/linkedlist.h>

enum RhAPI_Error RhPlugins_Initialise();
const struct RhLinkedList* RhPlugins_GetList();

#endif
