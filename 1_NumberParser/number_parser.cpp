#include "number_parser.h"

#include <algorithm>
#include <iterator>
#include <sstream>

#include "../basic_words.h"

namespace {

std::optional<int> TryMatch(std::string const& current_word, std::vector<std::pair<std::string, int>> const& possible_values)
{
    auto it = std::find_if(possible_values.begin(), possible_values.end(), [&current_word](std::pair<std::string, int> const& kv) { return kv.first == current_word; });
    return it == possible_values.end() ? std::nullopt : std::optional<int>(it->second);
}

//std::optional<int> ParseUnit(std::string const& current_word)
//{
//    std::vector<std::pair<std::string, int>> units = GetUnits();
//    return TryMatch(current_word, units);
//}

std::optional<int> ParseDU(std::string const& current_word)
{
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

}

NumberParser::NumberParser(std::string const& text)
    : m_original_text(text)
{
    std::istringstream iss(m_original_text);
    m_original_split_text = std::vector<std::string>((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

    for (std::string const& og_word : m_original_split_text)
    {
        std::optional<int> word_value = ParseDU(og_word);
        if (word_value)
            m_modified_split_text.emplace_back(std::to_string(*word_value));
        else
            m_modified_split_text.emplace_back(og_word);
    }

    std::ostringstream imploded_ss;
    std::copy(m_modified_split_text.begin(), m_modified_split_text.end(), std::ostream_iterator<std::string>(imploded_ss, " "));
    m_modified_text = imploded_ss.str();
}

std::optional<int> NumberParser::GetNumberAtWordIndex(std::size_t word_index) const
{
    if (word_index >= m_original_split_text.size())
        return std::nullopt;

    return ParseDU(m_original_split_text[word_index]);
}