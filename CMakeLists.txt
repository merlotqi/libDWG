cmake_minimum_required(VERSION 3.10)
project(libDWG LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 17)

find_package(Iconv REQUIRED)
find_package(fmt REQUIRED)

add_library(dwg SHARED)

add_subdirectory(include)
add_subdirectory(src)

if(WIN32)
    target_compile_definitions(dwg PRIVATE LIBDWG_EXPORTS)    
    target_compile_definitions(dwg PUBLIC _USE_MATH_DEFINES)
endif()
target_link_libraries(dwg PRIVATE Iconv::Iconv fmt::fmt)
add_subdirectory(examples)