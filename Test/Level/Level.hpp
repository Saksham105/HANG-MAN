#ifndef LEVEL_HPP
#define LEVEL_HPP
#include "../Game/Challenge.hpp"
#include "../Figure/Figure.hpp"
#include "../Figure/HangmanFigure.hpp"
#include <string>

/*
    This class Represents one level of the game
    It contains:
        one Challenge object to access actual guessing challenge
        a flag to indicate player won or not.
        a Figure object to display hang-man
        a string to accept the user guess
*/
class Level {
private:
    Challenge game; // Challenge object to store one challenge
    bool win; // flag to identify level cleared or not
    Figure *figure; // pointer to the figure to be displayed while playing (non-owning)
    std::string user_guess; // store user guess.

    /* Function to display alphabets from which player must select letters */
    void showAlphabets();

    
public:
    /* Copy constructor - copies challenge and win flag, but not ownership of figure */
    Level(const Level &level);
    Level(); // default constructor

    /**
     * @brief initialize one Level for game
     * @param game challenge the level contain
     * @param figure hangman figure dsiplays while playing
     */
    Level(const Challenge &game, Figure *figure);

    /* destructor to release object instance*/
    ~Level();

    /* Setter for keyword */
    void setWinner();

    /* Gtter for keyword */
    bool isWinner() const ;

    /* Setter for keyword */
    void setChallenge(const Challenge &game);

    /* Gtter for keyword */
    Challenge getChallenge() const ;

    /* Setter for keyword */
    void setFigure(Figure *figure);

    /* Gtter for keyword */
    Figure* getFigure() const ;

    /**
     * @brief shows the level data
     * @param out outstream reference
     * @param c Challenge reference
     * 
     * Displays the game challenge data and is the level is win or not.
     */
    friend std::ostream& operator<< (std::ostream &out, const Level &level);

    /* main logic to play one level challenge */
    bool play();
};

#endif