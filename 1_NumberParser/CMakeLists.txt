cmake_minimum_required(VERSION 3.17)
project(NumberParser)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        basic_words.h
        number_parser.cpp
        number_parser.h
        )

# Define the library
add_library(NumberParser STATIC ${SOURCES})