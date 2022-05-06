cmake_minimum_required(VERSION 3.17)
project(Main)

set(CMAKE_CXX_STANDARD 17)

# Treat all warnings as errors
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wuninitialized -Winit-self -Wno-unknown-pragmas -Wno-deprecated-declarations")

set(SOURCES
        main.cpp
)

# Define the executable
add_executable(Main ${SOURCES})
target_link_libraries(Main NumberParser)

add_subdirectory(1_NumberParser)
add_subdirectory(2_UnitTests)