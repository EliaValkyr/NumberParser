#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <optional>
#include <algorithm>

int main()
{
    std::string text = "I have one hundred apples and I will eat ninety-nine";
    std::istringstream iss(text);
    std::vector<std::string> words((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

    for (std::size_t i = 0; i < words.size(); ++i)
    {
        std::cout << words[i] << std::endl;
    }
}
