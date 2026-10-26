find_package(GTest CONFIG REQUIRED)

add_executable(
  unit_tests
  test-find-peaks.cpp
)

target_compile_definitions(unit_tests PRIVATE
      DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data")

target_link_libraries(unit_tests
  PRIVATE
    peak-finding
    GTest::gtest
    GTest::gtest_main
)

add_test(NAME unit_tests COMMAND unit_tests)

set_tests_properties(unit_tests PROPERTIES
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)
