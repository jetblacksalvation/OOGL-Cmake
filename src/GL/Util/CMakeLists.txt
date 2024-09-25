FILE(GLOB OOGL_UTIL_SOURCE *.cpp)

target_sources(OOGL_EXE PUBLIC 
	${OOGL_UTIL_SOURCE}
)
target_sources(OOGL_LIB PUBLIC 
	${OOGL_UTIL_SOURCE}
)

add_subdirectory("libjpeg")
add_subdirectory("libpng")
add_subdirectory("zlib")

target_include_directories(OOGL_EXE PUBLIC "libpnng" "libjpeg" "zlib") 
target_include_directories(OOGL_LIB PUBLIC "libpnng" "libjpeg" "zlib") 
