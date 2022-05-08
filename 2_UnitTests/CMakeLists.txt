project(UnitTest)

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