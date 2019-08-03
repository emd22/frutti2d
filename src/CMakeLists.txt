cmake_minimum_required(VERSION 3.5)

project(frutti2d C)

file (GLOB_RECURSE SOURCES "*.c")
file (GLOB_RECURSE HEADERS "../include/f2d/*.h")

set(GCC_COVERAGE_COMPILE_FLAGS "-g -Wall -Wpedantic")
set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(X11)
find_package(Threads REQUIRED)

include_directories(
  ${CMAKE_CURRENT_LIST_DIR}/../include
  ${GLEW_INCLUDE_DIRS}
  ${X11_INCLUDE_DIRS}
  ${THREADS_INCLUDE_DIRS}
)
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
add_library(frutti2d SHARED ${SOURCES})
#install(TARGETS frutti2d DESTINATION frutti2d/frutti2d)
install(FILES ${HEADERS} DESTINATION include/frutti2d)
# add_executable(game ${SOURCES} ${HEADERS})
target_link_libraries(frutti2d ${OPENGL_LIBRARY} ${GLEW_LIBRARIES} ${X11_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} m)
