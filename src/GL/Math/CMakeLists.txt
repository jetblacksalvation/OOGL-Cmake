FILE(GLOB OOGL_MATH_SOURCE *.cpp)

target_sources(OOGL_EXE PUBLIC 
	${OOGL_MATH_SOURCE}
)
target_link_libraries(OOGL_LIB  ${OOGL_MATH_SOURCE})
