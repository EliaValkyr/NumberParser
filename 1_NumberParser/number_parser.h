#pragma once

#include <optional>
#include <string>
#include <vector>

/// Class that receives a text and is able to replace all the numbers in word form to numerical form.
/// Ex: "I am fifty-eight years old" would become "I am 58 years old".
class NumberParser
{
public:
    explicit NumberParser(std::string const& text);

    /// Tries to parse the number starting at the given word index.
    std::optional<int> GetNumberAtWordIndex(std::size_t word_index) const;

    /// Returns the modified text, with all the numbers converted to numerical form.
    std::string GetModifiedText() const { return m_modified_text; }

private:
    /// Tries to parse a number below 100 starting at the indicated word index.
    /// If successful, advances the index until the first word after the number, and returns the number value.
    std::optional<int> ParseBelow100(std::size_t& current_word_index) const;

    /// Tries to parse a number below 1000 starting at the indicated word index.
    /// If successful, advances the index until the first word after the number, and returns the number value.
    std::optional<int> ParseBelow1000(std::size_t& current_word_index) const;

    /// Tries to parse a number below 1000 followed by a keyword (such as 'thousand' or 'million' starting at the indicated word index.
    /// If successful, advances the index until the first word after the number, and returns the number value.
    std::optional<int> ParseBelow1000WithKeyword(std::size_t& current_word_index, std::string const& keyword_at_end) const;

    /// Tries to parse a number up to 1e9.
    /// If successful, advances the index until the first word after the number, and returns the number value.
    std::optional<int> ParseGenericNumber(std::size_t& current_word_index) const;

    /// Tries to parse a four digit number in pairs of two (ex: twenty-two hundred and fifty).
    /// If successful, advances the index until the first word after the number, and returns the number value.
    std::optional<int> ParseFourDigitNumberInPairs(std::size_t& current_word_index) const;

    /// Tries to parse any positive number in any format at the indicated word index.
    /// If successful, advances the index until the first word after the number, and returns the number value.
    std::optional<int> ParseAnyNumber(std::size_t& current_word_index) const;

    /// Returns the word at the given index.
    std::string GetWordAtIndex(std::size_t index) const;

    /// Returns the word at the given index in all lowercase.
    std::string GetLowercaseWordAtIndex(std::size_t index) const;

    /// Stores the original text split by words.
    std::vector<std::string> m_original_split_text;

    /// Stores a string with all the numbers replaced by their numeric form.
    std::string m_modified_text;
};