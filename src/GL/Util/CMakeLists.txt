set(OOGL_UTIL_ROOT_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/")
target_sources(OOGL_EXE PUBLIC 
	${OOGL_UTIL_ROOT_SOURCE}Image.cpp  ${OOGL_UTIL_ROOT_SOURCE}Mesh.cpp 
)

add_subdirectory("libjpeg")
add_subdirectory("libpng")
add_subdirectory("zlib")

target_include_directories(OOGL_EXE PUBLIC include "libpnng" "libjpeg" "zlib") 