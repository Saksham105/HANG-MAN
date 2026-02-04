# TIC-TAC-TOE

This is a simple C++ implementation of the classic game Tic-Tac-Toe. The program allows two players to play the game on a 3x3 grid, taking turns to mark their symbol ('X' or 'O') in empty cells. It checks for valid input, detects wins (horizontal, vertical, and diagonal matches), and identifies a tie if the board fills without a winner. The code provides a clear game board display after each move, and announces the result at the end. This implementation is suitable for beginners looking to understand basic game logic, control flow, user input, and array manipulation in C++.

# COMMAND TO RUN

>g++ -c Test\Figure\Figure.cpp Test\Figure\HangmanFigure.cpp Test\Game\Challenge.cpp Test\Level\Level.cpp Test\Manager\GameManager.cpp Test\Player\Player.cpp Main\Hangman_Application.cpp

>g++ Figure.o HangmanFigure.o Challenge.o Level.o GameManager.o Player.o Hangman_Application.o -o runGameApp

>runGameApp.exe

# corrections

1. on winning, have to display full word. instead of only displaying congratulation msg.
2. after loosing, on restarting the level, have to clear user_guess (string) guessed letters.
3. allow guest signup
