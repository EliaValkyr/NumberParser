#define BOOST_TEST_MODULE MainUnitTest
#include <boost/test/included/unit_test.hpp>

#include "../1_NumberParser/number_parser.h"

BOOST_AUTO_TEST_CASE(TestNumberParsing)
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

BOOST_AUTO_TEST_CASE(TestParagraphs)
{
    auto SingleTest = [](std::string const& text, std::string const& expected_result)
    {
        NumberParser parser(text);
        BOOST_CHECK_EQUAL(parser.GetModifiedText(), expected_result);
    };

    SingleTest("I am one test", "I am 1 test");
    SingleTest(
        "I have one hundred apples and I will eat ninety-nine apples",
        "I have 100 apples and I will eat 99 apples"
    );
    SingleTest(
        "I have three hundred and fifty-eight pears but I only want three hundred fifty-seven",
        "I have 358 pears but I only want 357"
    );
    SingleTest(
        "Twenty children",
        "20 children"
    );
    SingleTest(
        "I see tables, there are one hundred and of those, sixty are yellow",
        "I see tables, there are 100 and of those, 60 are yellow"
    );
}