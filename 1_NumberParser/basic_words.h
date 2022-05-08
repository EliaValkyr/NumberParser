#pragma once

#include <string>
#include <vector>

/// Returns the words for the units, together with their value.
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

/// Returns the words for the teens, together with their value.
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
        {"nineteen", 19}
    };
    return values;
}

/// Returns the words for the tenths, together with their value.
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

/// Returns the keyword for and.
inline std::string GetAnd() { return "and"; }

/// Returns the keyword for hundred.
inline std::string GetHundred() { return "hundred"; }

/// Returns the keyword for thousand.
inline std::string GetThousand() { return "thousand"; }

/// Returns the keyword for million.
inline std::string GetMillion() { return "million"; }