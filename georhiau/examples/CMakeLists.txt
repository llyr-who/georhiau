find_package(glfw3 3.0 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(circle circle.cpp)
target_link_libraries(circle glfw)
target_link_libraries(circle OpenGL::GL)

add_executable(random random.cpp)
target_link_libraries(random glfw)
target_link_libraries(random OpenGL::GL)
