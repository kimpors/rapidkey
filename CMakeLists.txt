cmake_minimum_required(VERSION 3.20.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(rapidkey VERSION 1.0.0 LANGUAGES C)
set(C_STANDART 23)

add_subdirectory(cmdio)
include_directories(${CMAKE_SOURCE_DIR}/cmdio)
add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} cmdio)
