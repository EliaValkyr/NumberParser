#include <iostream>

#include "1_NumberParser/number_parser.h"

namespace {

void PrintUsage()
{
    std::cout << "Usage: ./Main \"text to convert to numerical form\"" << std::endl;
}

}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        PrintUsage();
        return -1;
    }

    std::string text = argv[1];
    std::cout << "Original text:" << std::endl << text << std::endl << std::endl;
    NumberParser parser(text);
    std::cout << "Modified text:" << std::endl << parser.GetModifiedText() << std::endl;
}
