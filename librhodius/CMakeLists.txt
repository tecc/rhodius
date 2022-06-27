project(rhodius-api)

add_library(rhodius-api STATIC src/headers.c)

find_package(Lua REQUIRED)

target_include_directories(rhodius-api PUBLIC include ${LUA_INCLUDE_DIR})