add_executable(vertex_test vertex_test.cpp)
target_link_libraries(vertex_test
                      gtest_main
)

add_executable(edge_test edge_test.cpp)
target_link_libraries(edge_test
                      gtest_main
)

add_executable(polygon_test polygon_test.cpp)
target_link_libraries(polygon_test
                      gtest_main
)

add_test(NAME vertex_test COMMAND vertex_test)
add_test(NAME edge_test COMMAND edge_test)
add_test(NAME polygon_test COMMAND polygon_test)
