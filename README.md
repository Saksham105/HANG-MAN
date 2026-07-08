# HANG-MAN
Game in C++

# COMMAND TO RUN

>g++ -c Figure\Figure.cpp Figure\HangmanFigure.cpp Game\Challenge.cpp Level\Level.cpp Manager\GameManager.cpp Player\Player.cpp Main\Hangman_Application.cpp

>g++ Figure.o HangmanFigure.o Challenge.o Level.o GameManager.o Player.o Hangman_Application.o -o runGameApp

>runGameApp.exe

# Description
HANG-MAN is a classic word-guessing game implemented in C++. Players attempt to guess a hidden word one letter at a time, with a limited number of incorrect guesses allowed before the hangman figure is completed. This project showcases object-oriented programming principles, modular code structure, and custom-designed game logic, making it an ideal demonstration of both C++ proficiency and software design skills.

Features include multiple levels of difficulty, player management, and a dynamic ASCII-art hangman figure that updates with every incorrect guess. Designed with clear code separation across classes such as Figure, Challenge, Level, GameManager, and Player, this game is a great example of maintainable and extensible code architecture.