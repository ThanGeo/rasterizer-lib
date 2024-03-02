cmake_minimum_required(VERSION 3.5.0)
project(example VERSION 1.0.0)

if(MSVC)
    add_compile_options(/std::c++latest)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
endif()

include_directories(Rasterizer)
if(NOT TARGET Rasterizer)
    add_subdirectory(Rasterizer)
endif()

# build examples
set(Executables
    example
    example_april
)

set(SrcFiles
    example.cpp
    example_april.cpp
)

# find boost
find_package(Boost 1.50 REQUIRED COMPONENTS)

list(LENGTH Executables cnt)
math(EXPR len "${cnt} - 1")
foreach(idx RANGE ${len})
    list(GET Executables ${idx} exec)
    list(GET SrcFiles ${idx} src)
    # link boost
    if(Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
        #   add_executable(foo foo.cc)
    endif()
    add_executable(${exec} ${src})
    target_link_libraries(${exec} Rasterizer)
endforeach()
