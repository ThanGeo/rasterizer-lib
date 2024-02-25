cmake_minimum_required(VERSION 3.1.0)
project(Rasterizer VERSION 1.0.0)

set(ProjectType STATIC) # make STATIC or SHARED

set(SrcFiles
    src/def.cpp
    src/generate.cpp
    src/rasterization.cpp
    src/intervalization.cpp
    src/utils.cpp
)

include_directories(include)
add_library(${PROJECT_NAME} ${ProjectType} ${SrcFiles})