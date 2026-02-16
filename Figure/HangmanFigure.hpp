#ifndef HANGMAN_FIGURE_HPP
#define HANGMAN_FIGURE_HPP

#include "Figure.hpp"

/*
    class HangmanFigure: inherits from Figure class
    Gives implementation to the function drawFigure()
*/
class HangmanFigure : public Figure {
public:
    HangmanFigure(); // default constructor
    
    /**
     * @brief implements the pure virtual function of base class, draws the specific figure on cmd
     * @param tries number of failed attempts made by user
     */
    void drawFigure(int tries) override ;

    /**
     * @brief Draws the figure when user guess it correct and won the game.
     */
    virtual void winFigure() override ;

    /**
     * @brief returns the current class name as string
     * @return name of the Figure
     */
    std::string getFigureClassName() override ;

    ~HangmanFigure() override;
};

#endif