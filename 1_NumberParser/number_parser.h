#pragma once

#include <optional>
#include <string>
#include <vector>

class NumberParser
{
public:
    explicit NumberParser(std::string const& text);

    std::optional<int> GetNumberAtWordIndex(std::size_t word_index) const;

    std::string GetModifiedText() const { return m_modified_text; }

private:
    std::optional<int> ParseBelow100(std::size_t& current_word_index) const;
    std::optional<int> ParseBelow1000(std::size_t& current_word_index) const;
    std::string GetWordAtIndex(std::size_t index) const;
    std::string GetLowercaseWordAtIndex(std::size_t index) const;

    std::string m_original_text;
    std::vector<std::string> m_original_split_text;
    std::vector<std::string> m_modified_split_text;
    std::string m_modified_text;
};