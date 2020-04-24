# we want these packages from plotting
find_package(glfw3 3.0 REQUIRED) 
find_package(OpenGL REQUIRED)

add_executable(giftwrap_test giftwrap_test.cpp)
target_link_libraries(giftwrap_test gtest_main)
target_link_libraries(giftwrap_test glfw)
target_link_libraries(giftwrap_test OpenGL::GL)

add_executable(mate_test mate_test.cpp)
target_link_libraries(mate_test gtest_main)

add_executable(delaunay_test delaunay_test.cpp)
target_link_libraries(delaunay_test gtest_main)

add_executable(ear_clip_test ear_clip_test.cpp)
target_link_libraries(ear_clip_test gtest_main)

add_executable(rng_test rng_test.cpp)
target_link_libraries(rng_test gtest_main)

add_test(NAME giftwrap_test COMMAND giftwrap_test)
add_test(NAME mate_test COMMAND mate_test)
add_test(NAME delaunay_test COMMAND delaunay_test)
add_test(NAME ear_clip_test COMMAND ear_clip_test)
add_test(NAME rng_test COMMAND rng_test)
