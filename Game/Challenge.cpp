#include "Challenge.hpp"
#include <cctype>

Challenge::Challenge() {}

Challenge::Challenge(
    const std::string &keyword,
    const std::string &word,
    const std::string &hint
) : keyword(keyword), hint(hint)
{
    for(char letter : word) {
        this->word += std::toupper(letter);
    }
}

void Challenge::setKeyword(const std::string &keyword) {
    this->keyword = keyword;
}

std::string Challenge::getKeyword() const  {
    return keyword;
}

void Challenge::setWord(const std::string &word) {
    this->word = word;
}

std::string Challenge::getWord() const  {
    return word;
}

void Challenge::setHint(const std::string &hint) {
    this->hint = hint;
}

std::string Challenge::getHint() const  {
    return hint;
}

std::ostream& operator<<(std::ostream& out, const Challenge& c) {
    out << "\tKeyword:\t\t"          << c.keyword        << std::endl
        << "\tHint:\t\t\t"             << c.hint           << std::endl;
        // << "\tWord:\t\t\t"             << c.word           << std::endl
        // << "\tFailed attempts:\t"  << c.failedAttempts << std::endl;

    return out;
}


// int main() {
//     Challenge c("fruit", "mango", "king of all fruits");

//     std::cout << "Keyword: " << c.getKeyword() << std::endl;
//     std::cout << "Word: " << c.getword() << std::endl;
//     std::cout << "Hint: " << c.getHint() << std::endl;
//     std::cout << "Failed Attempts: " << c.getFailedAttempts() << std::endl;

//     c.setKeyword("person");
//     c.setWord("bhagat singh");
//     c.setHint("died in his 23");
//     ++c;

//     std::cout << c << std::endl;

//     return 0;
// }