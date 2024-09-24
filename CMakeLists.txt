include(FetchContent)
include(FindOpenGL)
cmake_minimum_required(VERSION 3.18)
project(OOGL LANGUAGES CXX C)

include_directories("include")

add_executable(OOGL_EXE "null.cpp")
add_subdirectory("src/GL")


find_package(OpenGL REQUIRED)
target_link_libraries(OOGL_EXE OpenGL::GL) 
message("DONE")