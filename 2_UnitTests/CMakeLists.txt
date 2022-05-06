project(UnitTest)

set(SOURCES
        unit_test.cpp
        )


if(Boost_FOUND)
    add_executable(UnitTest ${SOURCES})
    target_link_libraries(UnitTest PUBLIC NumberParser ${Boost_LIBRARIES})
endif()