#include <iostream>
#include <algorithm>
#include <cctype>
#include "Level.hpp"

Level::Level() : figure(nullptr) {}

Level::Level(const Challenge &game, Figure *figure)
    : game(game), win(false), figure(figure) {}

Level::Level(const Level &level) {
    this->game = level.game;
    this->win = level.win;
    this->figure = new HangmanFigure();
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

    std::cout << "\t" << CYAN << keyboard << std::endl << RESET;
}

bool Level::play() {

    /* Reset previously guessed characters */
    user_guess = "";

    /* Get the actual word to be guessed (already in uppercase) */
    std::string dummy_word = game.getWord();

    /* Sort characters so that duplicates can be removed easily */
    std::sort(dummy_word.begin(), dummy_word.end());

    /* Move unique characters to the front */
    std::string::iterator last = std::unique(dummy_word.begin(), dummy_word.end());

    /* Erase duplicate characters from the end */
    dummy_word.erase(last, dummy_word.end());

    /* Counter to track wrong guesses */
    int failed_user_try = 0;

    

    /* Main game loop: runs until max failed tries */
    while (failed_user_try <= 5) {
        /* Display keyword/category once at the start */
        std::cout << MAGENTA << "\n\tYou have to guess a:" << YELLOW << "\n\tKEYWORD: " <<CYAN << game.getKeyword() << std::endl << RESET;

        /* Display hint */
        std::cout << YELLOW << "\tHINT:\t " << CYAN << game.getHint() << std::endl << RESET;
        

        /* Reference to the actual word */
        const std::string& actual_word = game.getWord();

        /* Display the current guessed state of the word */
        std::cout << YELLOW <<  "\n\tWord: ";
        std::cout << BG_GREEN;
        for (char c : actual_word) {
            if (user_guess.find(c) != std::string::npos)
                std::cout << BLACK << c << ' ';   // already guessed
            else
                std::cout << BLUE << "_ ";      // not guessed yet
        }
        std::cout << RESET << std::endl;

        /* Display available alphabets (keyboard view) */
        showAlphabets();

        /* ===== WORD GUESS INPUT (NEW LOGIC) ===== */

        std::string guessed_word;
        std::cout << YELLOW << "\tGuess a word: " << BG_WHITE << BLACK << " \b" << RESET;
        std::cin >> guessed_word;

        /* Validate that the guessed word contains only alphabets */
        bool valid = true;
        for (char &c : guessed_word) {
            if (!std::isalpha(c)) {
                valid = false;
                break;
            }
            c = std::toupper(c);  // normalize to uppercase
        }

        /* If invalid input, ask again */
        if (!valid) {
            std::cout << BOLD << RED << "\tPlease enter alphabets only!\n" << RESET;
            continue;
        }

        /* ===== SUBSTRING CHECK ===== */
        bool is_substring = false;
        if(guessed_word.length() < actual_word.length()) {
            /* iterate over the actual string till (word.length - guess.length) */
            for(int i=0; i<=actual_word.length()-guessed_word.length(); i++) {
                /* take a substring of length equal to guess_word */
                std::string sub_str = actual_word.substr(i, guessed_word.length());

                /* if any of the substrings matches to the guess_word, accept it */
                if(guessed_word == sub_str) {
                    is_substring = true;
                    break;
                }
            }
        } else if(guessed_word.length() == actual_word.length()){
            is_substring = (actual_word == guessed_word);
        }

        /* If guessed word is NOT a substring of actual word */
        if (!is_substring) {
            std::cout << BOLD << RED << "\tOops! Wrong guess.\n" << RESET;

            /* Increase failed try count and draw figure */
            if (figure) {
                figure->drawFigure(++failed_user_try);
            } else {
                ++failed_user_try;
            }
        }
        else {
            /* ===== (GUESS LOGIC) ===== */

            /* Add newly guessed characters to user_guess */
            for (char c : guessed_word) {
                if (user_guess.find(c) == std::string::npos) {
                    user_guess.push_back(c);
                }
            }

            /* If all unique characters are guessed, player wins */
            if (user_guess.size() == dummy_word.size()) {

                /* Display full word on success */
                std::cout << CYAN;
                std::cout << "\n\tWord: ";
                for (char c : actual_word)
                    std::cout << c << ' ';
                std::cout << std::endl << RESET;

                figure->winFigure();

                return this->win = true;
            }
            /* Repeat category prompt for next iteration */
            // std::cout << MAGENTA << "\n\tYou have to guess" << YELLOW << "\n\tKEYWORD: " <<CYAN << game.getKeyword() << std::endl << RESET;
        }

        
    }

    /* If maximum failed tries reached, player loses */
    return this->win = false;
}
