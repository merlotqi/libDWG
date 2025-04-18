add_executable(dwgreader dwgreader.cpp)
target_link_libraries(dwgreader dwg)

add_executable(dwgwriter dwgwriter.cpp)
target_link_libraries(dwgwriter dwg)