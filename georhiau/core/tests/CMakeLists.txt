add_executable(point_test point_test.cpp)
target_link_libraries(point_test
                      gtest_main
)

add_test(NAME point_test COMMAND point_test)
