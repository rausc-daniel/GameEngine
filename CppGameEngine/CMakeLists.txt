cmake_minimum_required(VERSION 3.5)

project(CppGameEngine)

include_directories(CppGameEngine /usr/local/inclue/GLFW)
include_directories(CppGameEngine /usr/include/GL)
include_directories(CppGameEngine /usr/local/include/libpng16)

set(OpenGL_GL_PREFERENCE GLVND)

add_library(CppGameEngine Game.h Game.cpp Matrix.h Matrix.cpp Shader.h Shader.cpp Sprite.h Sprite.cpp Texture.h Texture.cpp Vector3.h Vector3.cpp VertexPositionUV.h)

install(TARGETS CppGameEngine
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

find_package(ZLIB REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(PNG REQUIRED)

target_link_libraries(CppGameEngine glfw OpenGL::GL ${ZLIB_LIBRARIES} ${GLEW_LIBRARIES} ${PNG_LIBRARIES})
