cmake_minimum_required(VERSION 3.17)
project(Test)

# Find boost library, required for unit tests.
set(Boost_USE_STATIC_LIBS ON)
if(EXISTS "/usr/local/boost_1_68_g++_8.1.0/")
    set(BOOST_ROOT "/usr/local/boost_1_68_g++_8.1.0/")
    message("Found Boost")
else()
    message(FATAL_ERROR "Boost not found")
endif()

find_package(Boost REQUIRED COMPONENTS system filesystem serialization iostreams thread date_time program_options unit_test_framework chrono regex)

set(CMAKE_CXX_STANDARD 17)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(Test main.cpp)
    target_link_libraries(Test ${Boost_LIBRARIES})
endif()


add_subdirectory(UnitTests)