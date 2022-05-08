#include "number_parser.h"

#include <algorithm>
#include <iterator>
#include <sstream>

#include "basic_words.h"

namespace {

/// Tries to match the given word with any of the words in possible_values.
/// If found, returns the integer associated to it.
std::optional<int> TryMatch(std::string const& current_word, std::vector<std::pair<std::string, int>> const& possible_values)
{
    auto it = std::find_if(possible_values.begin(), possible_values.end(), [&current_word](std::pair<std::string, int> const& kv) { return kv.first == current_word; });
    return it == possible_values.end() ? std::nullopt : std::optional<int>(it->second);
}

/// Tries to find a u
std::optional<int> ParseUnit(std::string const& current_word)
{
    std::vector<std::pair<std::string, int>> units = GetUnits();
    return TryMatch(current_word, units);
}

}

NumberParser::NumberParser(std::string const& text)
{
    // Split the original text by spaces, to have the vector of words.
    std::istringstream iss(text);
    m_original_split_text = std::vector<std::string>((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

    // Iterate through all the words, and try to parse each one of them as a number.
    std::vector<std::string> modified_split_text;
    std::size_t word_index = 0;
    while (word_index < m_original_split_text.size())
    {
        std::string current_word = GetWordAtIndex(word_index);
        std::optional<int> current_value = ParseAnyNumber(word_index);
        if (current_value)
        {
            // If the current word (plus the following ones) can be parsed as a number, add the number to the text in numerical form.
            // The index will already be properly advanced in this case, so we don't need to do that here.
            modified_split_text.emplace_back(std::to_string(*current_value));
        }
        else
        {
            // If the current word does not represent a number, simply add it unchanged. Then, increment the index.
            modified_split_text.emplace_back(current_word);
            ++word_index;
        }
    }

    // Finally, implode the vector of modified strings into a single string separated by spaces.
    std::ostringstream imploded_ss;
    std::copy(modified_split_text.begin(), modified_split_text.end(), std::ostream_iterator<std::string>(imploded_ss, " "));
    m_modified_text = imploded_ss.str();
    if (!m_modified_text.empty())
        m_modified_text.pop_back();
}

std::string NumberParser::GetWordAtIndex(std::size_t index) const
{
    return index >= m_original_split_text.size() ? "" : m_original_split_text[index];
}

std::string NumberParser::GetLowercaseWordAtIndex(std::size_t index) const
{
    std::string word = GetWordAtIndex(index);
    std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c){ return std::tolower(c); });
    return word;
}

std::optional<int> NumberParser::ParseBelow100(std::size_t& current_word_index) const
{
    std::string current_word = GetLowercaseWordAtIndex(current_word_index);

    // Try to parse the number in the 'tenth-unit' format. Ex: sixty-four.
    std::size_t hyphen_index = current_word.find('-');
    if (hyphen_index != std::string::npos)
    {
        std::string tenth_text = current_word.substr(0, hyphen_index);
        std::string unit_text = current_word.substr(hyphen_index + 1);
        std::optional<int> try_tenth = TryMatch(tenth_text, GetTenths());
        std::optional<int> try_unit = TryMatch(unit_text, GetUnits());
        if (try_tenth && try_unit)
        {
            ++current_word_index;
            return *try_tenth + *try_unit;
        }
    }

    // Try to parse the number as a single unit (i.e < 10).
    std::optional<int> try_unit = TryMatch(current_word, GetUnits());
    if (try_unit)
    {
        ++current_word_index;
        return try_unit;
    }

    // Try to parse the number as a tenth (i.e 10, 20, ..., 90).
    std::optional<int> try_tenth = TryMatch(current_word, GetTenths());
    if (try_tenth)
    {
        ++current_word_index;
        return try_tenth;
    }

    // Try to parse the number as a teen (i.e 11 - 19).
    std::optional<int> try_teen = TryMatch(current_word, GetTeens());
    if (try_teen)
    {
        ++current_word_index;
        return try_teen;
    }

    return std::nullopt;
}

std::optional<int> NumberParser::ParseBelow1000(std::size_t& current_word_index) const
{
    int result = 0;

    // There are two possibilities here:
    //      (1) The number is of the form "X hundred [and] Y".
    //      (2) The number is smaller than 100.

    // Try to parse the hundreds.
    std::optional<int> unit_hundred = ParseUnit(GetLowercaseWordAtIndex(current_word_index));
    if (unit_hundred && GetLowercaseWordAtIndex(current_word_index + 1) == GetHundred())
    {
        // If found, add the value to the result and increment the index by 2, as we have read two words.
        result = *unit_hundred * 100;
        current_word_index += 2;

        // Check for the optional "and" to allow parsing of "two hundred and three".
        bool exists_and = GetLowercaseWordAtIndex(current_word_index) == GetAnd();

        // Try to find a number smaller than 100 after that. Advance the word index if successful.
        std::size_t tenths_index = exists_and ? current_word_index + 1 : current_word_index;
        std::optional<int> tenths = ParseBelow100(tenths_index);
        if (tenths)
        {
            result += *tenths;
            current_word_index = tenths_index;
        }
    }
    else
    {
        // Try to find a number smaller than 100 after that. Advance the word index if successful.
        std::optional<int> tenths = ParseBelow100(current_word_index);
        if (tenths)
            result += *tenths;
    }

    return result == 0 ? std::nullopt : std::optional<int>(result);
}

std::optional<int> NumberParser::ParseBelow1000WithKeyword(std::size_t& current_word_index, std::string const& keyword_at_end) const
{
    // Parse a number below 1000.
    std::size_t temp_word_index = current_word_index;
    std::optional<int> value = ParseBelow1000(temp_word_index);

    // Then check if the word immediately after is the desired keyword.
    if (value && GetLowercaseWordAtIndex(temp_word_index) == keyword_at_end)
    {
        current_word_index = temp_word_index + 1;
        return value;
    }

    return std::nullopt;
}

std::optional<int> NumberParser::ParseGenericNumber(std::size_t& current_word_index) const
{
    int result = 0;

    // Parse the millions part of the number. If it exists, add it to the result.
    std::optional<int> millions_amount = ParseBelow1000WithKeyword(current_word_index, GetMillion());
    if (millions_amount)
        result += *millions_amount * 1000000;

    // Parse the thousands part of the number. If it exists, add it to the result.
    std::optional<int> thousands_amount = ParseBelow1000WithKeyword(current_word_index, GetThousand());
    if (thousands_amount)
        result += *thousands_amount * 1000;

    // Try to find an "and" before the last units, if we have seen a million or a thousand.
    bool exists_and = result > 0
        ? GetLowercaseWordAtIndex(current_word_index) == GetAnd()
        : false;

    // Parse the units part of the number. If it exists, add it to the result.
    std::size_t unit_word_index = exists_and ? current_word_index + 1 : current_word_index;
    std::optional<int> units_amount = ParseBelow1000(unit_word_index);
    if (units_amount)
    {
        result += *units_amount;
        current_word_index = unit_word_index;
    }

    return result == 0 ? std::nullopt : std::optional<int>(result);
}

std::optional<int> NumberParser::ParseFourDigitNumberInPairs(std::size_t& current_word_index) const
{
    int result = 0;

    // Parse the hundreds value. To be accepted, it needs to be larger than 10 and it can't be a tenth.
    std::size_t hundreds_index = current_word_index;
    std::optional<int> hundreds = ParseBelow100(hundreds_index);
    bool valid_value = hundreds && *hundreds > 10 && *hundreds % 10 != 0;
    if (valid_value && GetLowercaseWordAtIndex(hundreds_index) == GetHundred())
    {
        // If found, add the value to the result and update the current index.
        result += *hundreds * 100;
        current_word_index = hundreds_index + 1;

        // Check for the optional and.
        bool exists_and = GetLowercaseWordAtIndex(current_word_index) == GetAnd();
        std::size_t units_index = exists_and ? current_word_index + 1 : current_word_index;

        // Optionally, parse the units value.
        std::optional<int> units = ParseBelow100(units_index);
        if (units)
        {
            // If successful, add them to the result and update the index.
            result += *units;
            current_word_index = units_index;
        }
    }
    return result == 0 ? std::nullopt : std::optional<int>(result);
}

std::optional<int> NumberParser::ParseAnyNumber(std::size_t& current_word_index) const
{
    // First, try parsing a four digit number as pairs of two numbers.
    std::optional<int> four_digit_number = ParseFourDigitNumberInPairs(current_word_index);
    if (four_digit_number)
        return four_digit_number;

    // Then, try parsing a number in the generic form.
    return ParseGenericNumber(current_word_index);
}

std::optional<int> NumberParser::GetNumberAtWordIndex(std::size_t word_index) const
{
    if (word_index >= m_original_split_text.size())
        return std::nullopt;

    return ParseAnyNumber(word_index);
}