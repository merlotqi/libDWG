project(libDWG LANGUAGES CXX C)

add_library(dwg SHARED)

add_subdirectory(include)
add_subdirectory(src)

if(WIN32)
    target_compile_definitions(dwg PRIVATE DWG_EXPORTS)
endif()