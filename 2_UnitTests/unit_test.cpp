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

    auto TestAllCombinations = [SingleTest](
        std::string const& millions_text,
        std::string const& thousands_text,
        std::string const& units_text,
        std::size_t word_index,
        int millions_value,
        int thousands_value,
        int units_value
        )
    {
        std::vector<bool> bool_vec{true, false};

        for (bool add_million : bool_vec)
        {
            for (bool add_thousand : bool_vec)
            {
                for (bool add_units : bool_vec)
                {
                    std::string text;
                    int value = 0;
                    if (add_million)
                    {
                        text += millions_text + " million ";
                        value += millions_value * 1000000;
                    }

                    if (add_thousand)
                    {
                        text += thousands_text + " thousand ";
                        value += thousands_value * 1000;
                    }

                    if (add_units)
                    {
                        text += units_text + " ";
                        value += units_value;
                    }

                    if (!text.empty())
                        text.pop_back();

                    if (value != 0)
                        SingleTest(text, word_index, value);
                }
            }
        }
    };

    SingleTest("I am one test", /*word_index*/ 2, /*number*/ 1);
    TestAllCombinations("six hundred thirty-one", "one hundred and sixty-eight", "eight hundred and forty-two", /*word_index*/ 0, /*millions_value*/ 631, /*thousands_value*/ 168, /*units_value*/ 842);
    TestAllCombinations("three", "sixty-four", "nineteen", /*word_index*/ 0, /*millions_value*/ 3, /*thousands_value*/ 64, /*units_value*/ 19);
}

BOOST_AUTO_TEST_CASE(TestParagraphs)
{
    auto SingleTest = [](std::string const& text, std::string const& expected_result)
    {
        NumberParser parser(text);
        BOOST_CHECK_EQUAL(parser.GetModifiedText(), expected_result);
    };

    SingleTest("", "");

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
    SingleTest(
        "two thousand one thousand",
        "2001 thousand"
    );
    SingleTest(
        "one hundred thousand",
        "100000"
    );
    SingleTest(
        "one hundred and thousand",
        "100 and thousand"
    );
    SingleTest(
        "and one and two hundred and three",
        "and 1 and 203"
    );
    SingleTest(
        "and twenty-three",
        "and 23"
    );
}