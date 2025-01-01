cmake_minimum_required(VERSION 3.8)
project(OOGL LANGUAGES CXX C)

function(get_all_targets _result _dir)
    get_property(_subdirs DIRECTORY "${_dir}" PROPERTY SUBDIRECTORIES)
    foreach(_subdir IN LISTS _subdirs)
        get_all_targets(${_result} "${_subdir}")
    endforeach()

    get_directory_property(_sub_targets DIRECTORY "${_dir}" BUILDSYSTEM_TARGETS)
    set(${_result} ${${_result}} ${_sub_targets} PARENT_SCOPE)
endfunction()

# Set C++17 standard
set(CMAKE_CXX_STANDARD 23)
add_definitions(-DSCRIPTS="${CMAKE_SOURCE_DIR}/glsl_scripts")

add_executable(OOGL_EXE "null.cpp" )  # Make sure to replace "main.cpp" with the actual source file for your executable

# Add a simple source file and create the library
add_library(OOGL_LIB STATIC "null.cpp")
target_include_directories(OOGL_LIB PUBLIC "include")
target_include_directories(OOGL_LIB PUBLIC "src/GL")
#DEPEND
include(FetchContent)
include(FindOpenGL)
add_subdirectory("src/GL")

find_package(OpenGL REQUIRED)
target_link_libraries(OOGL_LIB OpenGL::GL) 


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


find_package(OpenGL REQUIRED)
target_link_libraries(OOGL_LIB OpenGL::GL)

#OOOGL EXE SECTION

# Add include directories for the executable as well (if needed)
target_include_directories(OOGL_EXE PRIVATE "include")

# Link the executable with the library
target_link_libraries(OOGL_EXE OOGL_LIB)

# Optionally, link OpenGL to the executable if needed
target_link_libraries(OOGL_EXE OpenGL::GL)



