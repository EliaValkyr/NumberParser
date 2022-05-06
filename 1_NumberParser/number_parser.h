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
    std::string m_original_text;
    std::vector<std::string> m_original_split_text;
    std::vector<std::string> m_modified_split_text;
    std::string m_modified_text;
};