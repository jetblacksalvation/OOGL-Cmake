cmake_policy(SET CMP0072 NEW)
include(FetchContent)
include(FindOpenGL)
cmake_minimum_required(VERSION 3.18)
project(OOGL LANGUAGES CXX C)
add_library(OOGL_LIB "null.cpp")
add_executable(OOGL_EXE "null.cpp")

include_directories("include")



add_subdirectory("src/GL")


find_package(OpenGL REQUIRED)
target_link_libraries(OOGL_EXE OpenGL::GL) 


set_target_properties(OOGL_LIB PROPERTIES 
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/OOGL_ELIB"
)
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    #install and link x11 
    message(STATUS "Configuring for Linux platform")
    set(OOGL_PLATFORM_LINUX ON)
    # Find X11
    find_package(X11 REQUIRED)

    # Link X11 to your target
    target_link_libraries(OOGL_LIB PRIVATE X11::X11)

endif()