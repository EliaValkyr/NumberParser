#define BOOST_TEST_MODULE MainUnitTest
#include <boost/test/included/unit_test.hpp>

#include "../1_NumberParser/number_parser.h"

BOOST_AUTO_TEST_CASE(TestNumberParsing)
{
    // Given a text and a word index, checks that the number at the given word index is the expected one.
    auto SingleTest = [](std::string const& text, std::size_t word_index, int number)
    {
        NumberParser parser(text);
        std::optional<int> opt_value = parser.GetNumberAtWordIndex(word_index);
        BOOST_CHECK(opt_value.has_value());
        BOOST_CHECK_EQUAL(*opt_value, number);
    };

    // Given three numbers below 1000, tests all possible combinations for them appearing or not in the millions, thousands and unis position, respectively.
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
    SingleTest("There are nine hundred pencils but only six are blue", /*word_index*/ 7, /*number*/ 6);
    SingleTest("I have one hundred and sixty-eight coins", /*word_index*/ 2, /*number*/ 168);

    // Test all powers of ten.
    SingleTest("One", /*word_index*/ 0, /*number*/ 1);
    SingleTest("Ten", /*word_index*/ 0, /*number*/ 10);
    SingleTest("One hundred", /*word_index*/ 0, /*number*/ 100);
    SingleTest("One thousand", /*word_index*/ 0, /*number*/ 1000);
    SingleTest("Ten thousand", /*word_index*/ 0, /*number*/ 10000);
    SingleTest("One hundred thousand", /*word_index*/ 0, /*number*/ 100000);
    SingleTest("One million", /*word_index*/ 0, /*number*/ 1000000);
    SingleTest("Ten million", /*word_index*/ 0, /*number*/ 10000000);
    SingleTest("One hundred million", /*word_index*/ 0, /*number*/ 100000000);

    // Test all the combinations for a bunch of random big numbers. Make sure to test some "x hundred y" and "x hundred *and* y".
    TestAllCombinations("six hundred thirty-one", "one hundred and sixty-eight", "eight hundred and forty-two", /*word_index*/ 0, /*millions_value*/ 631, /*thousands_value*/ 168, /*units_value*/ 842);
    TestAllCombinations("three", "sixty-four", "nineteen", /*word_index*/ 0, /*millions_value*/ 3, /*thousands_value*/ 64, /*units_value*/ 19);
    TestAllCombinations("two hundred eighty-five", "seven hundred and three", "fourteen", /*word_index*/ 0, /*millions_value*/ 285, /*thousands_value*/ 703, /*units_value*/ 14);
}

BOOST_AUTO_TEST_CASE(TestParagraphs)
{
    auto SingleTest = [](std::string const& text, std::string const& expected_result)
    {
        NumberParser parser(text);
        BOOST_CHECK_EQUAL(parser.GetModifiedText(), expected_result);
    };

    // Make sure the empty string does not crash.
    SingleTest("", "");

    // Add some basic tests.
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
        "I see tables, there are one hundred and of those, sixty are yellow",
        "I see tables, there are 100 and of those, 60 are yellow"
    );

    // Test that it works in a greedy fashion, always trying to fit as many words as possible into each number before going to the next.
    SingleTest(
        "One million twenty two hundred thousand sixty eight",
        "1000020 200060 8"
    );
    SingleTest(
        "two thousand one thousand",
        "2001 thousand"
    );

    // Test some four digit numbers.
    SingleTest(
        "There are thirteen hundred five screws",
        "There are 1305 screws"
    );
    SingleTest(
        "My car weighs thirty-six hundred pounds",
        "My car weighs 3600 pounds"
    );
    SingleTest(
        "I can count up to eighty-seven hundred and sixty-three",
        "I can count up to 8763"
    );

    // Test that it does not parse as four digit numbers if the 'hundred' value is a tenth.
    SingleTest(
        "Parsing twenty hundred as a single number makes no sense because it actually is two thousand",
        "Parsing 20 hundred as a single number makes no sense because it actually is 2000"
    );

    // Test that adding "and" in some random places does not accidentally create a number that should not be created.
    SingleTest(
        "one hundred and thousand",
        "100 and thousand"
    );
    SingleTest(
        "and one and two hundred and three",
        "and 1 and 203"
    );
    SingleTest(
        "and twenty-three and five",
        "and 23 and 5"
    );

    // Test that it does not allow to put thousand before million.
    SingleTest(
        "one thousand two million sixty-five",
        "1002 million 65"
    );
    SingleTest(
        "eighteen thousand one hundred and thirty million",
        "18130 million"
    );

    // Test case sensitivity.
    SingleTest(
        "ElEVeN thOUsAnD fOrtY-FIve",
        "11045"
    );

    // Test that it does not parse numbers that are not in the accepted format.
    SingleTest(
        "twenty five",
        "20 5"
    );
    SingleTest(
        "twentyfive",
        "twentyfive"
    );
    SingleTest(
        "one-hundred",
        "one-hundred"
    );
    SingleTest(
        "one-thousand",
        "one-thousand"
    );
    SingleTest(
        "one-million",
        "one-million"
    );
    SingleTest(
        "a hundred",
        "a hundred"
    );
    SingleTest(
        "a thousand",
        "a thousand"
    );
    SingleTest(
        "a million",
        "a million"
    );

    // Check that it does not accept "zero" anywhere.
    SingleTest(
        "zero",
        "zero"
    );
    SingleTest(
        "twenty-zero",
        "twenty-zero"
    );
    SingleTest(
        "zero hundred",
        "zero hundred"
    );
    SingleTest(
        "zero thousand",
        "zero thousand"
    );
    SingleTest(
        "zero million",
        "zero million"
    );
}