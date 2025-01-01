cmake_policy(SET CMP0072 NEW)
include(FetchContent)
include(FindOpenGL)
set(CMAKE_CXX_STANDARD 17) # Set to C++17



cmake_minimum_required(VERSION 3.18)
project(OOGL LANGUAGES CXX C)
add_library(OOGL_LIB "null.cpp")
include_directories("include")

add_executable(OOGL_EXE "null.cpp")
include_directories("include")

add_definitions(-DSCRIPTS="${CMAKE_SOURCE_DIR}/glsl_scripts")



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

# Set the output directory for the library
set_target_properties(OOGL_LIB PROPERTIES 
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/OOGL_ELIB"
)
find_package(OpenGL REQUIRED)
target_link_libraries(OOGL_LIB OpenGL::GL)

# Set the output directory for the library
set_target_properties(OOGL_LIB PROPERTIES 
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/OOGL_ELIB"
)
message(STATUS "Library output directory: ${CMAKE_BINARY_DIR}/OOGL_ELIB")

#OOOGL EXE SECTION

# Add include directories for the executable as well (if needed)
target_include_directories(OOGL_EXE PRIVATE "include")

# Link the executable with the library
target_link_libraries(OOGL_EXE OOGL_LIB)

# Optionally, link OpenGL to the executable if needed
target_link_libraries(OOGL_EXE OpenGL::GL)

# Set the output directory for the executable
set_target_properties(OOGL_EXE PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/OOGL_EXE"
)

