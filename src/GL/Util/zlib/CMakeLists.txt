FILE(GLOB ZLIB_SOURCE *.c)

target_sources(OOGL_EXE PUBLIC 
	${ZLIB_SOURCE}
)
target_link_libraries(OOGL_LIB ${ZLIB_SOURCE})