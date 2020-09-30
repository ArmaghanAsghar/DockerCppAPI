cmake_minimum_required(VERSION 3.12)
project(TestProject)


find_package(CURL REQUIRED)

set(CMAKE_CXX_STANDARD 17)
add_executable(TestProject main.cpp  DockerAPI.cpp DockerAPI.h)
target_link_libraries(TestProject  -lcurl )
