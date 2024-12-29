cmake_minimum_required(VERSION 3.10)
project(libDWG LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 17)

find_package(Iconv REQUIRED)

add_subdirectory(external)

add_library(dwg SHARED)

add_subdirectory(include)
add_subdirectory(src)

if(WIN32)
    target_compile_definitions(dwg PRIVATE LIBDWG_EXPORTS)
endif()
target_link_libraries(dwg PUBLIC Iconv::Iconv)

add_subdirectory(examples)