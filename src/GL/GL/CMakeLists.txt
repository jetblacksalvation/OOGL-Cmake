set(OOGL_GL_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/")
message(STATUS "TEST TESTTETTESTFDFFDSLKF")
target_sources(OOGL_EXE PUBLIC 
	"${OOGL_GL_SOURCE}Context_X11.cpp"  ${OOGL_GL_SOURCE}Program.cpp       ${OOGL_GL_SOURCE}Texture.cpp
	${OOGL_GL_SOURCE}Context.cpp        ${OOGL_GL_SOURCE}Extensions.cpp   ${OOGL_GL_SOURCE}Renderbuffer.cpp  ${OOGL_GL_SOURCE}VertexArray.cpp
${OOGL_GL_SOURCE}Context_Win32.cpp  ${OOGL_GL_SOURCE}Framebuffer.cpp  ${OOGL_GL_SOURCE}Shader.cpp        ${OOGL_GL_SOURCE}VertexBuffer.cpp

)