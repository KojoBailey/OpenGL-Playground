cmake_minimum_required(VERSION 3.10)
project(OpenGL)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(external/glad/include)
include_directories(external/glfw/include)

set(SOURCES
	src/main.cpp
	external/glad/src/glad.c
)

add_executable(${PROJECT_NAME} ${SOURCES})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/lib-mingw-w64/libglfw3.a")
target_link_libraries(${PROJECT_NAME} gdi32 opengl32)
