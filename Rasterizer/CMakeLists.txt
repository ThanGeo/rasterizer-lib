cmake_minimum_required(VERSION 3.5.0)
project(Rasterizer VERSION 1.0.0)

set(ProjectType STATIC) # make STATIC or SHARED

set(SrcFiles
    src/def.cpp
    src/generate.cpp
    src/rasterization.cpp
    src/intervalization.cpp
    src/utils.cpp
)

# find boost
find_package(Boost 1.50 REQUIRED COMPONENTS)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    #   add_executable(foo foo.cc)
endif()

include_directories(include)
add_library(${PROJECT_NAME} ${ProjectType} ${SrcFiles})