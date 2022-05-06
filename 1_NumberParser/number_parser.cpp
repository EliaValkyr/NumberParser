#include "number_parser.h"

#include <algorithm>
#include <iterator>
#include <sstream>

#include "basic_words.h"

namespace {

std::optional<int> TryMatch(std::string const& current_word, std::vector<std::pair<std::string, int>> const& possible_values)
{
    auto it = std::find_if(possible_values.begin(), possible_values.end(), [&current_word](std::pair<std::string, int> const& kv) { return kv.first == current_word; });
    return it == possible_values.end() ? std::nullopt : std::optional<int>(it->second);
}

std::optional<int> ParseUnit(std::string const& current_word)
{
    std::vector<std::pair<std::string, int>> units = GetUnits();
    return TryMatch(current_word, units);
}

}

NumberParser::NumberParser(std::string const& text)
    : m_original_text(text)
{
    std::istringstream iss(m_original_text);
    m_original_split_text = std::vector<std::string>((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

    std::size_t word_index = 0;
    while (word_index < m_original_split_text.size())
    {
        std::string current_word = GetWordAtIndex(word_index);
        std::optional<int> current_value = ParseBelow1000(word_index);
        if (current_value)
            m_modified_split_text.emplace_back(std::to_string(*current_value));
        else
            m_modified_split_text.emplace_back(current_word);
    }

    std::ostringstream imploded_ss;
    std::copy(m_modified_split_text.begin(), m_modified_split_text.end(), std::ostream_iterator<std::string>(imploded_ss, " "));
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
    ++current_word_index;

    std::size_t hyphen_index = current_word.find('-');
    if (hyphen_index != std::string::npos)
    {
        std::string tenth_text = current_word.substr(0, hyphen_index);
        std::string unit_text = current_word.substr(hyphen_index + 1);
        std::optional<int> try_tenth = TryMatch(tenth_text, GetTenths());
        std::optional<int> try_unit = TryMatch(unit_text, GetUnits());
        if (try_tenth && try_unit)
            return *try_tenth + *try_unit;
    }

    std::optional<int> try_unit = TryMatch(current_word, GetUnits());
    if (try_unit)
        return try_unit;

    std::optional<int> try_tenth = TryMatch(current_word, GetTenths());
    if (try_tenth)
        return try_tenth;

    std::optional<int> try_teen = TryMatch(current_word, GetTeens());
    if (try_teen)
        return try_teen;

    return std::nullopt;
}

std::optional<int> NumberParser::ParseBelow1000(std::size_t& current_word_index) const
{
    int result = 0;
    std::size_t temp_word_index = current_word_index;

    std::optional<int> unit_hundred = ParseUnit(GetLowercaseWordAtIndex(temp_word_index));
    if (unit_hundred && GetLowercaseWordAtIndex(temp_word_index + 1) == GetHundred())
    {
        result = *unit_hundred * 100;
        temp_word_index += 2;

        bool exists_and = GetLowercaseWordAtIndex(temp_word_index) == "and";

        std::size_t tenths_index = exists_and ? temp_word_index + 1 : temp_word_index;

        std::optional<int> tenths = ParseBelow100(tenths_index);
        if (tenths)
        {
            result += *tenths;
            temp_word_index = tenths_index;
        }
    }
    else
    {
        std::optional<int> tenths = ParseBelow100(temp_word_index);
        if (tenths)
            result += *tenths;
    }

    current_word_index = temp_word_index;

    return result == 0 ? std::nullopt : std::optional<int>(result);
}

std::optional<int> NumberParser::GetNumberAtWordIndex(std::size_t word_index) const
{
    if (word_index >= m_original_split_text.size())
        return std::nullopt;

    return ParseBelow1000(word_index);
}