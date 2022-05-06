cmake_minimum_required(VERSION 3.17)
project(Main)

set(CMAKE_CXX_STANDARD 17)

# Treat all warnings as errors
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wuninitialized -Winit-self -Wno-unknown-pragmas -Wno-deprecated-declarations")

# Find boost library, required for unit tests.
set(Boost_USE_STATIC_LIBS ON)
if(EXISTS "/usr/local/boost_1_68_g++_8.1.0/")
    set(BOOST_ROOT "/usr/local/boost_1_68_g++_8.1.0/")
    message("Found Boost")
else()
    message(FATAL_ERROR "Boost not found")
endif()

# Add boost modules
find_package(Boost REQUIRED COMPONENTS system filesystem serialization iostreams thread date_time program_options unit_test_framework chrono regex)

set(SOURCES
        main.cpp
)

# Define the executable
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(Main ${SOURCES})
    target_link_libraries(Main NumberParser ${Boost_LIBRARIES})
endif()


add_subdirectory(1_NumberParser)
add_subdirectory(2_UnitTests)