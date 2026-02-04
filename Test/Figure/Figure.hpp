#ifndef FIGURE_HPP
#define FIGURE_HPP
#include <string>

/*
    Figure: abstract base class for figure in the hangman game
    contains a pure virtual function drawFigure()
*/
class Figure {
public:
    Figure(); // default constructor 

    /**
     * @brief Draws the figure according to how many wrong guess are made by user
     * @param tries number of failed attempts made by user
     */
    virtual void drawFigure(int tries) =0;

    /**
     * @brief returns the current class name as string
     * @return name of the Figure
     */
    virtual std::string getFigureClassName() =0;

    /* invokes all the derived class destructors first, then executes itself */
    virtual ~Figure();
};

#endif