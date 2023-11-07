cmake_minimum_required(VERSION 3.0)
set(PROJECT_NAME pthread_os)
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=thread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -ffast-math -fopenmp")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")

project(${PROJECT_NAME})

add_executable(no_thread no_thread.c)
add_executable(naive_thread naive_thread.c)
add_executable(openmp openmp.c)

target_link_libraries(no_thread PRIVATE m)
target_link_libraries(naive_thread PRIVATE m)
target_link_libraries(openmp PRIVATE m)