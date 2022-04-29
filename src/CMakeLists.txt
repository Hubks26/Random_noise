cmake_minimum_required(VERSION 3.0)

set (PROJECT_NAME noise)
project(${PROJECT_NAME})

set (SOURCES
    Game.cpp
    Grid.cpp
    main.cpp
)

set (HEADERS
    Game.h 
    Grid.h 
)

set(SFML_LIB_DIR /usr/lib/x86_64-linux-gnu/)
set(SFML_INCLUDE_DIR usr/include)
include_directories(${SFML_INCLUDE_DIR})
link_directories(${PROJECT_NAME} ${SFML_LIB_DIR})

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS})

target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system
)