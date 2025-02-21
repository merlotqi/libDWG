file(GLOB_RECURSE _headers ${CMAKE_CURRENT_LIST_DIR}/*.h  CONFIGURE_DEPEND)
file(GLOB_RECURSE _private_headers ${CMAKE_CURRENT_LIST_DIR}/*_p.h CONFIGURE_DEPEND)
list(REMOVE_ITEM _headers ${_private_headers})

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/dwg/dwg_version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/dwg/dwg_version.h
)

generate_export_header(
	dwg
	EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/dwg/exports.h
	EXPORT_MACRO_NAME LIBDWG_API
)
set(_headers ${_headers} 
	${CMAKE_CURRENT_BINARY_DIR}/dwg/exports.h
	${CMAKE_CURRENT_BINARY_DIR}/dwg/dwg_version.h
)

target_sources(dwg PUBLIC ${_headers})
target_sources(dwg PRIVATE ${_private_headers})
unset(_headers)
unset(_private_headers)

target_include_directories(dwg
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include/dwg>)