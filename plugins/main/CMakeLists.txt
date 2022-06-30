project(rhodius-mainplugin C)

add_library(rhodius-mainplugin SHARED
    src/main.c
    src/generators/template.c
    )
target_link_libraries(rhodius-mainplugin rhodius-api)
target_include_directories(rhodius-mainplugin PRIVATE include)