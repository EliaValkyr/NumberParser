#pragma once

#include <string>
#include <vector>

inline std::vector<std::pair<std::string, int>> GetUnits()
{
    static std::vector<std::pair<std::string, int>> values = {
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9}
    };
    return values;
}

inline std::vector<std::pair<std::string, int>> GetTeens()
{
    static std::vector<std::pair<std::string, int>> values = {
        {"eleven", 11},
        {"twelve", 12},
        {"thirteen", 13},
        {"fourteen", 14},
        {"fifteen", 15},
        {"sixteen", 16},
        {"seventeen", 17},
        {"eighteen", 18},
        {"nineteen", 10}
    };
    return values;
}

inline std::vector<std::pair<std::string, int>> GetTenths()
{
    static std::vector<std::pair<std::string, int>> values = {
        {"ten", 10},
        {"twenty", 20},
        {"thirty", 30},
        {"forty", 40},
        {"fifty", 50},
        {"sixty", 60},
        {"seventy", 70},
        {"eighty", 80},
        {"ninety", 90}
    };
    return values;
}
