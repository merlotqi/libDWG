cmake_minimum_required(VERSION 3.10)
project(libDWG LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_LIBDWG_TESTS "Build libdwg tests" OFF)
option(BUILD_LIBDWG_EXAMPLES "Build libdwg examples" OFF)

set(LIBDWG_VERSION_MAJOR 1)
set(LIBDWG_VERSION_MINOR 0)
set(LIBDWG_VERSION_PATCH 1)
set(LIBDWG_VERSION_STRING "${LIBDWG_VERSION_MAJOR}.${LIBDWG_VERSION_MINOR}.${LIBDWG_VERSION_PATCH}")

find_package(Iconv REQUIRED)
find_package(fmt REQUIRED)
find_package(double-conversion REQUIRED)
find_package(magic_enum REQUIRED)

include(GenerateExportHeader)

add_subdirectory(thirdparty)
add_library(dwg SHARED)

add_subdirectory(include)
add_subdirectory(src)

if(MSVC)
    target_compile_definitions(dwg PRIVATE _USE_MATH_DEFINES)
    target_compile_options(dwg PRIVATE 
        /wd4251  # class 'X' needs to have dll-interface
        /wd4275  # non-dll-interface class 'std::exception' used as base
        /wd4661  # no suitable definition provided for explicit template instantiation request
        /bigobj  # MSVC-specific: Allows more sections in COFF object files
    )
endif()
target_link_libraries(dwg Iconv::Iconv fmt::fmt double-conversion::double-conversion magic_enum::magic_enum RTTR::Core_Lib)

add_library(DWG::dwg ALIAS dwg)

if(BUILD_LIBDWG_EXAMPLES)
    add_subdirectory(examples)
endif()

if(BUILD_LIBDWG_TESTS)
    include(CTest)
    add_subdirectory(tests)
endif()