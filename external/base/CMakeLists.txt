add_library(dwg_base STATIC)

target_sources(dwg_base
    PRIVATE
    Coordinate.cpp
    DateTime.cpp
    Encoding.cpp
    EndianConverter.cpp
    Timespan.cpp
    Timestamp.cpp
)

target_include_directories(dwg_base
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(dwg_base PUBLIC Iconv::Iconv)