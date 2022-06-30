--[[
    Rhodius: Lua definitions

    This file contains definitions for the Rhodius Lua API.
    It also contains definitions for the Rhodius Main Plugin
]]--

-- Core definitions

---
--- Require plugins.
---
function require_plugins(...) end

---
--- Use certain features not active by default.
--- Features are provided
---
--- @vararg string
function use_features(...) end

---
---
function project(name) end

---
--- Get a path relative to the current script directory.
---
--- For example, if the current script is "/path/to/script.lua",
--- and this function is called with the argument "example/example.txt",
--- the function will return "/path/to/example/example.txt".
---
--- @param name string
function path(name) end


-- Main plugin definitions
--- Adds a template.
--- It is recommended to use the path function for the source_path parameter.
--- @param name string
--- @param source_path string
function add_template(name, source_path) end