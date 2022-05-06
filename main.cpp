#include <iostream>

#include "1_NumberParser/number_parser.h"

int main()
{
    std::string text = "six hundred thirty-one million one hundred and sixty-eight thousand eight hundred and forty-two";

    std::cout << "Original text: " << text << std::endl;
    NumberParser parser(text);

    std::cout << "Modified text: " << parser.GetModifiedText() << std::endl;
}
