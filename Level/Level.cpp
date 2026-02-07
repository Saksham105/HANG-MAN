#include <iostream>
#include <algorithm>
#include <cctype>
#include "Level.hpp"

Level::Level() : figure(nullptr) {}

Level::Level(const Challenge &game, Figure *figure)
    : game(game), win(false), figure(figure) {}

Level::Level(const Level &level) : figure(nullptr) {
    this->game = level.game;
    this->win = level.win;
}

Level::~Level() {
    // figure is non-owning; lifetime is managed elsewhere
}

void Level::setWinner() {
    this->win = true;
}

bool Level::isWinner() const  {
    return win;
}

void Level::setChallenge(const Challenge &game) {
    this->game = game;
}

Challenge Level::getChallenge() const  {
    return game;
}

void Level::setFigure(Figure *figure) {
    // update non-owning pointer; do not delete existing figure
    this->figure = figure;
}

Figure* Level::getFigure() const  {
    return figure;
}

std::ostream& operator<<(std::ostream &out, const Level &level) {
    out << "\n\tGame:\n" << level.game
        << "\tClear? " << (level.win ? "YES" : "NO") << std::endl;

    return out;
}

void Level::showAlphabets() {
    std::string keyboard =
        "\n\tQ   W   E   R   T   Y   U   I   O   P\n"
        "\t  A   S   D   F   G   H   J   K   L\n"
        "\t      Z   X   C   V   B   N   M\n";

    for (char guessed : user_guess) {
        std::size_t pos = keyboard.find(guessed);
        if (pos != std::string::npos) {
            keyboard[pos] = '_';
        }
    }

    std::cout << "\t" << keyboard << std::endl;
}

bool Level::play() {
    /**
     * while storing in Challenge object: convert the word in game to uppercase. (done)
     * while playing: remove all duplicate letters from the word.
     * ask user to guess letters one by one.
     * compare it in actual word.
     * if size matches, declare won.
     * if failed tries reaches, declare failed.
     */

    /* reset the user guess */
    user_guess = "";

    std::string dummy_word = game.getWord();

    /* sort the character sequence */
    std::sort(dummy_word.begin(), dummy_word.end());

    /* move all unique letters to the front of sequence */
    std::string::iterator last = std::unique(dummy_word.begin(), dummy_word.end());

    /* remove the duplicate occurances at the last of the string */
    dummy_word.erase(last, dummy_word.end());

    int failed_user_try = 0;

    // ask once if player wants to see the hint during the game
    bool showHint = true; // always show hint.
    // bool showHint = false; // always show hint.
    char hintChoice;

    std::cout << "\n\tYou have to guess a: " << game.getKeyword() << std::endl;

    // std::cout << "\tDo you want to see hint while playing? (y/n): ";
    // std::cin >> hintChoice;
    // if (hintChoice == 'y' || hintChoice == 'Y') {
    //     showHint = true;
    // }

    while (failed_user_try <= 5) {

        if (showHint) {
            std::cout << "\tHINT: " << game.getHint() << std::endl;
        }

        const std::string& actual_word = game.getWord();
        if(user_guess == actual_word){
            return this->win = true;
        }
        std::cout << "\n\tWord: ";
        for (char c : actual_word) {
            if (user_guess.find(c) != std::string::npos)
                std::cout << c << ' ';
            else
                std::cout << "_ ";
        }
        std::cout << std::endl;

        showAlphabets();

        char guess_letter;
        std::cout << "\tGuess a letter: ";
        std::cin >> guess_letter;

        if (!std::isalpha(guess_letter)) {
            std::cout << "\tPlease enter a valid letter!\n";
            continue;
        }

        guess_letter = std::toupper(guess_letter);

        if (user_guess.find(guess_letter) != std::string::npos) {
            std::cout << "\tYou already guessed it!\n";
            continue;
        }

        if (dummy_word.find(guess_letter) == std::string::npos) {
            std::cout << "\tOops! Wrong guess.\n";
            if (figure) {
                figure->drawFigure(++failed_user_try);
            } else {
                ++failed_user_try;
            }
        } else {
            user_guess.push_back(guess_letter);
            if (user_guess.size() == dummy_word.size()) {
                /* displaying the complete guessed word */
                std::cout << "\n\tWord: ";
                for(char c : actual_word)
                    std::cout << c << ' ';
                std::cout << std::endl;

                return this->win = true;
            }
        }

        std::cout << "\n\tYou have to guess a: " << game.getKeyword() << std::endl;
    }

    return this->win = false;
}
