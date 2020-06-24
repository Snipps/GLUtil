cmake_minimum_required(VERSION 3.6)
project(GLUtil)

file(GLOB_RECURSE GLUtil_SRC "GLUtil/src/*.cpp" "GLUtil/src/*.c" "GLUtil/inlcude/*.h")\

add_library(GLUtil STATIC ${GLUtil_SRC})
target_include_directories(GLUtil PUBLIC "GLUtil/include")
set_target_properties(GLUtil PROPERTIES CXX_STANDARD 14 C_STANDARD 99)