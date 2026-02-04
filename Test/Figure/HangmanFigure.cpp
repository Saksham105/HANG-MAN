#include <iostream>
#include "HangmanFigure.hpp"

/* No such implementation required */
HangmanFigure::HangmanFigure() {}

HangmanFigure::~HangmanFigure() {}


/* takes the wrong tries by user and display according "hang-man" figure */
void HangmanFigure::drawFigure(int tries) {

    // by default header lines
    std::cout << "\t+-------+" << std::endl;
    std::cout << "\t||\t|" << std::endl;

    // head line
    std::cout << "\t||\t"; std::cout << ((tries >= 1) ? "O" : "") << std::endl;

    // arm line
    if(tries == 2) {
        std::cout << "\t||      |" << std::endl;
    } else if(tries == 3) {
        std::cout << "\t||     /|" << std::endl;
    } else if(tries >= 4) {
        std::cout << "\t||     /|\\" << std::endl;
    }

    // leg line
    if(tries == 5)
        std::cout << "\t||     /" << std::endl;
    else if(tries >= 6)
        std::cout << "\t||     / \\" << std::endl;

    // by default footer lines
    std::cout << "\t||" << std::endl;
    std::cout << "\t||" << std::endl;
    std::cout << "===============================" << std::endl;
    int chances = (tries <= 6) ? (6 - tries) : 0;
    std::cout << "you have " << chances << " chances left." << std::endl;
}

std::string HangmanFigure::getFigureClassName() {
    return "HangmanFigure";
}

// int main() {
//     Figure *f = new HangmanFigure();
//     f->drawFigure(1);
//     std::cout << std::endl;

//     f->drawFigure(2);
//     std::cout << std::endl;

//     f->drawFigure(3);
//     std::cout << std::endl;

//     f->drawFigure(4);
//     std::cout << std::endl;

//     f->drawFigure(5);
//     std::cout << std::endl;

//     f->drawFigure(6);
//     std::cout << std::endl;

//     delete f;

//     return 0;
// }