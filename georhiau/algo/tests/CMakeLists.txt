add_executable(giftwrap_test giftwrap_test.cpp)
target_link_libraries(giftwrap_test
                      gtest_main
)

add_test(NAME giftwrap_test COMMAND giftwrap_test)
