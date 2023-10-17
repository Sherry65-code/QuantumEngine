cmake_minimum_required(VERSION 3.07.0)

set(PROJECT_NAME QuantumEngine)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS OFF)

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)
find_library(glfw3 opengl32)

if (WIN32)
    link_libraries(opengl32 glfw3)
else()
    link_libraries(glfw)
endif()

set(COMPILE_FLAGS "${COMPILE_FLAGS} -static")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(QuantumEngineTest ${CMAKE_SOURCE_DIR}/src/Binary.cpp ${CMAKE_SOURCE_DIR}/src/Engine.cpp ${CMAKE_SOURCE_DIR}/src/external/glad.c)
