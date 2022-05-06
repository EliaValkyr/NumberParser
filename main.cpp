#include <algorithm>
#include <iostream>
#include <iterator>
#include <optional>
#include <sstream>
#include <vector>

#include "1_NumberParser/number_parser.h"

int main()
{
    // begin of text
    // end of text
    // punctuation
    // case sensitive

    std::string text = "I have one hundred apples and I will eat ninety-nine apples. I have three hundred and fifty-eight pears but I only want three hundred fifty-seven as I am not hungry";

    std::cout << "Original text: " << text << std::endl;
    NumberParser parser(text);

    std::cout << "Modified text: " << parser.GetModifiedText() << std::endl;
}
