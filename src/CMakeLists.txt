enable_testing()

set(MATRIX_SOURCES
  Errors.h
  Matrix.h
)

set(TEST_SOURCES
  ${MATRIX_SOURCES}
  test_main.cpp
)

add_executable(test_matrix ${TEST_SOURCES})
target_link_libraries(test_matrix GTest::Main)

include(GoogleTest)
gtest_discover_tests(test_matrix)
