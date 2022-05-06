#include <iostream>

#define BOOST_TEST_MODULE MainUnitTest
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(FirstTestCase)
{
    std::cout << "Hello test" << std::endl;
    int x = 42;
    BOOST_CHECK_EQUAL(x, 42);
    BOOST_CHECK_EQUAL(x, 43);
}