cmake_minimum_required(VERSION 3.5)

file (GLOB_RECURSE SOURCES "*.c")
file (GLOB_RECURSE HEADERS "../include/game/*.h")

SET(GCC_COVERAGE_COMPILE_FLAGS "-g -Wall -Wpedantic")

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

add_executable(game ${SOURCES} ${HEADERS})
target_link_libraries(game ${OPENGL_LIBRARY} ${GLEW_LIBRARIES} ${X11_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})