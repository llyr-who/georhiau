find_package(glfw3 3.0 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(circle circle.cpp)
target_link_libraries(circle glfw)
target_link_libraries(circle OpenGL::GL)

add_executable(random_triangulation random_triangulation.cpp)
target_link_libraries(random_triangulation glfw)
target_link_libraries(random_triangulation OpenGL::GL)

add_executable(random_rng random_rng.cpp)
target_link_libraries(random_rng glfw)
target_link_libraries(random_rng OpenGL::GL)

add_executable(basic_vs_del_blog1 basic_vs_del_blog1.cpp)
target_link_libraries(basic_vs_del_blog1 glfw)
target_link_libraries(basic_vs_del_blog1 OpenGL::GL)
