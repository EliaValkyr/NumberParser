project(UnitTest)

# Add all files from this folder automatically to the sources.
file(GLOB_RECURSE SOURCES *.cpp *.h *.ipp)

if(Boost_FOUND)
    add_executable(UnitTest unit_test.cpp ../basic_words.h)
    target_link_libraries(UnitTest PUBLIC NumberParser ${Boost_LIBRARIES})
endif()