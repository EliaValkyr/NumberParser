cmake_minimum_required(VERSION 3.17)
project(NumberParser)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        basic_words.h
        number_parser.cpp
        number_parser.h
        )

# Define the executable
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_library(NumberParser STATIC ${SOURCES})
    target_link_libraries(NumberParser ${Boost_LIBRARIES})
endif()