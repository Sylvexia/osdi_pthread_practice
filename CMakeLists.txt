cmake_minimum_required(VERSION 3.0)
set(PROJECT_NAME pthread_os)

project(${PROJECT_NAME})

add_executable(pi_approach pi_approach.c)

target_link_libraries(pi_approach PRIVATE m)