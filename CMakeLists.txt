cmake_minimum_required(VERSION 3.0.0)
project(Main VERSION 1.0.0)

if(MSVC)
    add_compile_options(/std::c++latest)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
endif()

include_directories(Rasterizer)
if(NOT TARGET Rasterizer)
    add_subdirectory(Rasterizer)
endif()

add_executable(${PROJECT_NAME} example.cpp)
target_link_libraries(${PROJECT_NAME} Rasterizer)