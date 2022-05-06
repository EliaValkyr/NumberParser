project(UnitTest)

# Find boost library, required for unit tests.
set(Boost_USE_STATIC_LIBS ON)
if(EXISTS "/usr/local/boost_1_68_g++_8.1.0/")
    set(BOOST_ROOT "/usr/local/boost_1_68_g++_8.1.0/")
    message("Found Boost")
else()
    message(FATAL_ERROR "Boost not found")
endif()

# Add boost modules
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

set(SOURCES
        unit_test.cpp
        )

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(UnitTest ${SOURCES})
    target_link_libraries(UnitTest PUBLIC NumberParser ${Boost_LIBRARIES})
endif()