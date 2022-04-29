cmake_minimum_required(VERSION 3.0)

set (PROJECT_NAME Random)
project(${PROJECT_NAME})

add_subdirectory(src)

install(FILES src/noise DESTINATION ./)