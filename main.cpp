#include <algorithm>
#include <iostream>
#include <iterator>
#include <optional>
#include <sstream>
#include <vector>

#include "1_NumberParser/number_parser.h"

int main()
{
    std::string text = "I have one hundred apples and I will eat ninety-nine";
    NumberParser parser(text);

    std::cout << parser.GetModifiedText() << std::endl;
}
