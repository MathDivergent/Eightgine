cmake_minimum_required(VERSION 3.15)
project(Lua C)

add_compile_definitions(LUA_COMPAT_5_3)

add_subdirectory(src)
