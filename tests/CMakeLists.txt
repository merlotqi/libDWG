find_package(GTest REQUIRED)

file(GLOB_RECURSE _testfiles ${CMAKE_CURRENT_LIST_DIR}/*Test.cpp CONFIGURE_DEPEND)

add_executable(dwg_unit_test ${_testfiles})
target_link_libraries(dwg_unit_test PRIVATE DWG::dwg GTest::GTest GTest::Main)
enable_testing()

foreach(_testfile ${_testfiles})
    get_filename_component(_testname ${_testfile} NAME_WE)
    string(REPLACE "Test" "" _suite_name ${_testname})
    add_test(
        NAME DWG_TEST_${_suite_name}
        COMMAND dwg_unit_test --gtest_filter=${_suite_name}.*
    )
endforeach()

unset(_testfiles)