cmake_minimum_required (VERSION 3.7.2)

project (cellular_automata)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++14")
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -ggdb")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")

set (CURSES_NEED_NCURSES TRUE)
find_package (Curses REQUIRED)
include_directories (${CURSES_INCLUDE_DIRS})
include_directories(src/)


set (AUTOMATA_SOURCES
    src/automata/life.cpp
    src/automata/life_like.cpp
    src/automata/predator_and_prey.cpp
    )
set (AUTOMATA_HEADERS
    src/automata/life.h
    src/automata/life_like.h
    src/automata/predator_and_prey.h
    )

set (SCREEN_SOURCES
    src/curses/screen.cpp
    )
set (SCREEN_HEADERS
    src/curses/screen.h
    )

set (GRID_HEADERS
    src/grid/grid.h
    src/grid/toroidal_grid.h
    )

set (TEST_SOURCES
    src/automata_test/life.cpp
    src/automata_test/life_like.cpp
    src/automata_test/predator_and_prey.cpp
    )


add_library (automata_lib
    ${AUTOMATA_SOURCES}
    ${AUTOMATA_HEADERS}
    ${SCREEN_HEADERS}
    ${GRID_HEADERS}
    )

add_library (screen_lib
    ${SCREEN_SOURCES}
    ${SCREEN_HEADERS}
    ${GRID_HEADERS}
    )


foreach (test_source ${TEST_SOURCES})
    get_filename_component (test_exec ${test_source} NAME_WE)
    add_executable (${test_exec} ${test_source})
    target_link_libraries (${test_exec} ${CURSES_LIBRARIES} automata_lib screen_lib)
endforeach (test_source ${TEST_SOURCES})
