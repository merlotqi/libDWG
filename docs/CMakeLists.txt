set(DOXYGEN_INPUT ${CMAKE_SOURCE_DIR}/include
                   ${CMAKE_SOURCE_DIR}/src
                   ${CMAKE_SOURCE_DIR}/README.md)

set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/docs)
set(DOXYGEN_PROJECT_NAME "libDWG")
set(DOXYGEN_PROJECT_NUMBER "${LIBDWG_VERSION_STRING}")
set(DOXYGEN_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
                 ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

add_custom_target(docs ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM)

set_target_properties(docs PROPERTIES FOLDER "Documentation")
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs/html
          DESTINATION share/doc/libDWG)
