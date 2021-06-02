set(SOURCES
  Matrix.h
  main.cpp
  )

add_executable(test_matrix ${SOURCES})
target_link_libraries(test_matrix GTest::GTest)
