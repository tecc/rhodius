cmake_minimum_required(VERSION 3.20)
project(rhodius LANGUAGES C VERSION 0.1.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH};${CMAKE_CURRENT_LIST_DIR}/cmake)

include(TargetSystem)

target_system(TARGET_SYSTEM)
add_executable(rhodius
    src/main.c src/options.c src/io_${TARGET_SYSTEM}.c src/util.c src/log.c
    src/scripting/script.c src/scripting/api.c src/scripting/runner.c

    src/generators/template.c
    src/ext/lua.c
    )

find_package(Lua REQUIRED)
add_subdirectory(ext/cwalk)

target_link_libraries(rhodius ${LUA_LIBRARIES} cwalk)
target_include_directories(rhodius PRIVATE include ${LUA_INCLUDE_DIR})
target_compile_definitions(rhodius PRIVATE RHODIUS_BUILD_$<UPPER_CASE:${CMAKE_BUILD_TYPE}> RHODIUS_VERSION="${CMAKE_PROJECT_VERSION}")