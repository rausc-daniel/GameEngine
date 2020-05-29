cmake_minimum_required(VERSION 3.5)

project(Fps)

add_executable(Fps FpsGame.h FpsGame.cpp Fps.cpp)

include_directories(${CMAKE_SOURCE_DIR}/CppGameEngine)
target_link_libraries(Fps CppGameEngine)

install(TARGETS Fps RUNTIME DESTINATION bin)
