#ifndef FIGURE_HPP
#define FIGURE_HPP
#include <string>

/* if already define in system, then only... */
#ifdef _WIN32
#include <windows.h> // for cmd color manipulation
#endif

#define  RESET           "\033[0m"
#define  BOLD            "\033[1m"
#define  DIM             "\033[2m"
#define  ITALIC          "\033[3m"
#define  UNDERLINE       "\033[4m"
#define  BLINK           "\033[5m"
#define  INVERT          "\033[7m"

// Foreground (Text) Colors
#define  RED             "\033[31m"
#define  GREEN           "\033[32m"
#define  YELLOW          "\033[33m"
#define  BLUE            "\033[34m"
#define  MAGENTA         "\033[35m"
#define  CYAN            "\033[36m"
#define  WHITE           "\033[37m"
#define  BLACK           "\033[30m"
#define  BRIGHT_GREEN    "\033[92m"

// Background Colors
#define  BG_RED          "\033[41m"
#define  BG_GREEN        "\033[42m"
#define  BG_BLUE         "\033[44m"
#define  BG_WHITE        "\033[107m"

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
     * @brief Draws the figure when user guess it correct and won the game.
     */
    virtual void winFigure() =0;

    /**
     * @brief returns the current class name as string
     * @return name of the Figure
     */
    virtual std::string getFigureClassName() =0;

    /* invokes all the derived class destructors first, then executes itself */
    virtual ~Figure();
};

#endif