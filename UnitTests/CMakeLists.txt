project(UnitTest)

file(GLOB_RECURSE SOURCES *.cpp *.h *.ipp)
add_executable(UnitTest unit_test.cpp)
target_link_libraries(UnitTest PUBLIC ${Boost_LIBRARIES})

message("${Boost_LIBRARIES}")