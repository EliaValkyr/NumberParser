#define BOOST_TEST_MODULE MainUnitTest
#include <boost/test/included/unit_test.hpp>

#include "../NumberParser/number_parser.h"

BOOST_AUTO_TEST_CASE(FirstTestCase)
{
    auto SingleTest = [](std::string const& text, std::size_t word_index, int number)
    {
        NumberParser parser(text);
        std::optional<int> opt_value = parser.GetNumberAtWordIndex(word_index);
        BOOST_CHECK(opt_value.has_value());
        BOOST_CHECK_EQUAL(*opt_value, number);
    };

    SingleTest("I am one test", /*word_index*/ 2, /*number*/ 1);
}