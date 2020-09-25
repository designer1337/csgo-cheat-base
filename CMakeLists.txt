cmake_minimum_required(VERSION 3.0.0)
project(csgo-cheeto VERSION 0.1.0)

add_library(csgo-cheeto SHARED 
core/main.cpp
core/menu/framework.cpp
core/menu/menu.cpp core/hooks/hooks.cpp
core/features/misc/misc.cpp
core/features/misc/engine_prediction.cpp

dependencies/math/math.cpp
dependencies/interfaces/interfaces.cpp
dependencies/utilities/utilities.cpp
dependencies/utilities/csgo.cpp
dependencies/utilities/netvars/netvars.cpp
dependencies/utilities/renderer/renderer.cpp

source-sdk/math/vector3d.cpp
source-sdk/math/view_matrix.cpp

dependencies/minhook/hook.c
dependencies/minhook/buffer.c
dependencies/minhook/trampoline.c
dependencies/minhook/hde/hde32.c
dependencies/minhook/hde/hde64.c
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_STANDARD 17)

set_property(TARGET csgo-cheeto PROPERTY CXX_STANDARD 17)

add_definitions("-Wno-everything")