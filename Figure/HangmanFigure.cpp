#include <iostream>
#include "HangmanFigure.hpp"

/* No such implementation required */
HangmanFigure::HangmanFigure() {}

HangmanFigure::~HangmanFigure() {}


/* takes the wrong tries by user and display according "hang-man" figure */
void HangmanFigure::drawFigure(int tries) {

    // by default header lines
    if(tries < 6) {
        std::cout <<RED << "\t+-------+" << std::endl;
        std::cout << "\t||\t|" << std::endl;
    
        // head line
        std::cout << "\t||\t"; std::cout << ((tries >= 1) ? YELLOW "O" : "") << RED << std::endl;
    
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

        std::cout << "\t||" << std::endl;
        std::cout << "\t||" << std::endl;
        std::cout << "===============================" << std::endl;
        std::cout << "you have " << GREEN << (6 - tries) << RED << " chances left." << RESET << std::endl;

    }else {

        /* falling effect */
        std::cout << RED << "\t+-------+" << std::endl;
        std::cout << "\t||\t|" << std::endl;
        std::cout << "\t||\t" << YELLOW << "0" << RED;
        std::cout << "\r\t||           \r" << std::endl;

        std::cout << "\t||\tX";
        std::cout << "\r\t||           \r";


        Sleep(200);
        std::cout << "\t||    *****";
        Sleep(200);
        std::cout << "\r\t||           \r";

        
        Sleep(200);
        std::cout << "\t||" << std::endl;
        std::cout << "\t||    *****";
        Sleep(200);
        std::cout << "\r\t||             \r";

        
        Sleep(200);
        std::cout << "\t||" << std::endl;
        std::cout << "\t||    *****";
        Sleep(200);
        std::cout << "\r\t||             \r";

        
        Sleep(200);
        std::cout << "\t||     <^> " << std::endl;
        std::cout << "\t||   ___|___" << std::endl;
        std::cout << "\t||  |       |" << std::endl;
        std::cout << "\t||  | (RIP) |" << std::endl;
        std::cout << "\t||  |       |" << std::endl;
        std::cout << "============^=======^===============" << RESET << std::endl;
        return;
    }
}

void HangmanFigure::winFigure() {
    std::cout << BOLD << GREEN << "\t+--------+" << std::endl;
    std::cout << "\t||\t |" << std::endl;
    std::cout << "\t||" RED "\t X" GREEN << std::endl;
    std::cout << "\t||" << std::endl;
    std::cout << "\t||" << std::endl;
    std::cout << "\t||\t 0 --> |THANKS|" << std::endl;
    std::cout << "\t||\t/|\\" << std::endl;
    std::cout << "\t||\t/ \\" << std::endl;
    std::cout << "===============================" << RESET << std::endl;
}

std::string HangmanFigure::getFigureClassName() {
    return "HangmanFigure";
}