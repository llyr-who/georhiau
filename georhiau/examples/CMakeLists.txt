find_package(glfw3 3.0 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(circle circle.cpp)

add_executable(ear_vs_delaunay ear_vs_delaunay.cpp)
target_link_libraries(ear_vs_delaunay glfw)
target_link_libraries(ear_vs_delaunay OpenGL::GL)
