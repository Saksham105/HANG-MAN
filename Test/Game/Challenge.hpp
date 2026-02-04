#ifndef CHALLENGE_HPP
#define CHALLENGE_HPP
#include <iostream>
#include <string>

/*
    Class will represent the actual game to be played
    Class will contain:
        the word to be guessed by the player
        the keyword on which the player will guess the word
        one hint which helps the user to guess the word
        track of failed attempts done by the user
*/
class Challenge {
private:
    std::string keyword; // specifies user to guess in a perticular direction
    std::string word; // actual word to be guessed by user
    std::string hint; // helps user for guessing

public:
    Challenge(); // default constructor

    /**
     * @brief initiates the @a keyword, actual @a word and @a hint for the word
     * @param keyword only word will display on screen for guess
     * @param word actual word which supposed to guess
     * @param hint description about word which help user to guess
     */
    Challenge(const std::string &keyword, const std::string &word, const std::string &hint);
    
    /* Setter for keyword */
    void setKeyword(const std::string &keyword);

    /* Getter for keyword */
    std::string getKeyword() const ;

    /* Setter for word */
    void setWord(const std::string &word);

    /* Getter for word */
    std::string getWord() const ;

    /* Setter for hint */
    void setHint(const std::string &hint);

    /* Getter for hint */
    std::string getHint() const ;

    /**
     * @brief shows the game challenge data (only required)
     * @param out outstream reference
     * @param c Challenge reference
     */
    friend std::ostream& operator<<(std::ostream& out, const Challenge& c);
};

#endif