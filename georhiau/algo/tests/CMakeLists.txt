add_executable(giftwrap_test giftwrap_test.cpp)
target_link_libraries(giftwrap_test
                      gtest_main
)

add_executable(mate_test mate_test.cpp)
target_link_libraries(mate_test
                      gtest_main
)

add_executable(delaunay_test delaunay_test.cpp)
target_link_libraries(delaunay_test
                      gtest_main
)

add_test(NAME giftwrap_test COMMAND giftwrap_test)
add_test(NAME mate_test COMMAND mate_test)
add_test(NAME delaunay_test COMMAND delaunay_test)
