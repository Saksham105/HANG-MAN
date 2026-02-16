#include <iostream> // for cout and cin
#include <fstream> // for file handling
#include <string> // for dealing with string
#include <cstdlib> // for exit() function
#include <thread> // for sleep_for() function
#include <chrono> // for delay time units

#include "../Manager/GameManager.hpp"



#define LEVEL_FILE "Data/level_file.txt"
#define PLAYER_FILE "Data/player_file.txt"

/*
    the GCC specific compiler extension which mark a function to execute before main()
    i.e. as soon as the shared library loaded, then this function executes.
*/
__attribute__((constructor))
void showBanner() {
    /* cmd color changes (cyan: light blue) */
    std::cout << BOLD << GREEN;

    /* Opens the banner text file in read mode */
    std::string fileName = "Data/title_page.txt";
    std::ifstream file(fileName);
    if(!file.is_open()) {
        std::cerr << BOLD << RED << "\tunable to open banner [" << fileName << "]." << std::endl << RESET;
        return;
    }

    std::string line;

    /* reads untill EOF reaches */
    while(std::getline(file, line)) {
        Sleep(250);
        std::cout << line << std::endl;
    }

    file.close();
    std::cout << RESET << WHITE;

}

/* menu functions */
int adminMenu() {
    int choice;

    std::cout << BOLD << BLUE << "\n\t= = = = =\tA D M I N - M E N U\t\t= = = = =" << std::endl << RESET;
    std::cout << YELLOW << "\n\t1. " << WHITE << "Add new level" << std::endl << RESET;
    std::cout << YELLOW << "\t2. " << WHITE << "Remove level" << std::endl << RESET;
    std::cout << YELLOW << "\t3. " << WHITE << "Get level count" << std::endl << RESET;
    std::cout << YELLOW << "\t4. " << WHITE << "Change keyword by level id" << std::endl << RESET;
    std::cout << YELLOW << "\t5. " << WHITE << "Change word by level id" << std::endl << RESET;
    std::cout << YELLOW << "\t6. " << WHITE << "Change hint by level id" << std::endl << RESET;
    std::cout << YELLOW << "\t7. " << WHITE << "Change figure by level id" << std::endl << RESET;
    std::cout << YELLOW << "\t8. " << WHITE << "Remove player by name and email" << std::endl << RESET;
    std::cout << YELLOW << "\t9. " << WHITE << "Remove all guest player" << std::endl << RESET;
    std::cout << YELLOW << "\t10. " << WHITE << "Get all player's details" << std::endl << RESET;
    std::cout << YELLOW << "\t11. " << WHITE << "Get player by name and email" << std::endl << RESET;
    std::cout << YELLOW << "\t12. " << WHITE << "Generate report" << std::endl << RESET;
    std::cout << YELLOW << "\t0. " << RED << "BACK TO MAIN MENU" << std::endl << RESET;

    std::cout << BOLD << MAGENTA << "\n\tEnter your choice: " << RESET;
    std::cin >> choice;
    std::cin.ignore();

    return choice;
}

int playerMenu() {
    int choice;

    std::cout << BOLD << BLUE << "\n\t= = = = =\tP L A Y E R - M E N U\t\t= = = = =" << std::endl << RESET;
    std::cout << YELLOW << "\n\t1. " << WHITE << "Sign-up (create account)" << std::endl << RESET;
    std::cout << YELLOW << "\t2. " << WHITE << "Login" << std::endl << RESET;
    std::cout << YELLOW << "\t3. " << WHITE << "Show profile" << std::endl << RESET;
    std::cout << YELLOW << "\t4. " << WHITE << "Delete account" << std::endl << RESET;
    std::cout << YELLOW << "\t5. " << WHITE << "Change name" << std::endl << RESET;
    std::cout << YELLOW << "\t6. " << WHITE << "Change email" << std::endl << RESET;
    std::cout << YELLOW << "\t7. " << WHITE << "Reset game" << std::endl << RESET;
    std::cout << YELLOW << "\t8. " << WHITE << "Get current score" << std::endl << RESET;
    std::cout << YELLOW << "\t9. " << WHITE << "Play (start game)" << std::endl << RESET;
    std::cout << YELLOW << "\t10. " << WHITE << "Logout" << std::endl << RESET;
    std::cout << YELLOW << "\t0. " << RED << "BACK TO MAIN MENU" << std::endl << RESET;

    std::cout << BOLD << MAGENTA << "\n\tEnter your choice: " << RESET;
    std::cin >> choice;
    std::cin.ignore();

    return choice;
}

/* helper functions */

int main() {

    GameManager hangman;
    Player registeredPlayer;
    Figure *figure = nullptr;

    std::string admin_password;
    std::string keyword;
    std::string word;
    std::string hint;
    std::string figureName;
    std::string player_name;
    std::string player_email;
    std::string report;
    int level_id;

    bool is_admin = false;
    bool is_login = false;
    int choice;
    int admin_choice;
    int player_choice;

    hangman.downloadLevels(LEVEL_FILE);
    hangman.downloadPlayers(PLAYER_FILE);

    do {
        std::cout << BOLD << BLUE << "\n\t= = = = =\tM E N U\t\t= = = = =" << std::endl << RESET;
        std::cout << YELLOW << "\t1. " << WHITE << "I am an Admin" << std::endl << RESET;
        std::cout << YELLOW << "\t2. " << WHITE << "I am a Player" << std::endl << RESET;
        std::cout << YELLOW << "\t0. " << RED << "EXIT" << std::endl << RESET;

        std::cout << BOLD << MAGENTA << "\n\tEnter your choice: " << RESET;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
            {
                std::cout << CYAN <<  "\n\tEnter admin password: " << MAGENTA;
                getline(std::cin, admin_password);

                is_admin = hangman.verifyAdmin(admin_password);

                if(!is_admin) {
                    std::cerr << BOLD << RED << "\n\tIncorrect passwod.!" << std::endl << RESET;
                    break;
                }

                std::cout << BRIGHT_GREEN << "\n\tCorrect password.!\n\tlogin successful" << std::endl << RESET;
                std::cout << BOLD << GREEN << "\n\tLoading admin panel ... " << RESET;
                for(int i=0; i<5; i++) {
                    std::cout << BOLD << GREEN << " " << (i*20) << " %";
                    Sleep(500);
                    std::cout << "\b\b\b\b    \b\b\b\b";
                    Sleep(500);
                }
                std::cout << "100 %" << std::endl;
                std::cout  << RESET << std::endl;

                do {
                    admin_choice = adminMenu();

                    switch (admin_choice) {
                        case 1:
                        {
                            std::cout << YELLOW << "\n\tEnter keyword: " << CYAN;
                            getline(std::cin, keyword);

                            std::cout << YELLOW << "\tEnter word: " << CYAN;
                            getline(std::cin, word);

                            std::cout << YELLOW << "\tEnter hint description: " << CYAN;
                            getline(std::cin, hint);

                            // std::cout << YELLOW << "\tEnter figure name: " << CYAN;
                            // getline(std::cin, figureName);

                            Challenge game(keyword, word, hint);
                            figure = new HangmanFigure();

                            Level level(game, figure);
                            hangman.addNewLevel(level);
                            std::cout << BRIGHT_GREEN << "\n\tSUCCESSFULLY ADDED NEW LEVEL." << std::endl << RESET;

                            break;
                        }

                        case 2:
                            try {
                                std::cout << YELLOW << "\n\tEnter level number: " << CYAN;
                                std::cin >> level_id;
                                std::cin.ignore();
    
                                hangman.removeLevel(level_id);
                                std::cout << BRIGHT_GREEN << "\n\tSUCCESSFULLY REMOVED LEVEL: " << level_id << std::endl << RESET;

                            } catch (std::runtime_error &e) {
                                std::cerr << "\n\t" << BOLD << RED << e.what() << std::endl << RESET;
                            }

                            break;

                        case 3:
                            std::cout << YELLOW << "\n\tTotal levels available: " << CYAN << hangman.getLevelCount() << std::endl << RESET;

                            break;

                        case 4:
                            try {
                                std::cout << YELLOW << "\n\tEnter level number: " << CYAN;
                                std::cin >> level_id;
                                std::cin.ignore();
    
                                std::cout << YELLOW << "\tEnter new keyword: " << CYAN;
                                getline(std::cin, keyword);
    
                                hangman.changeKeyword(level_id, keyword);
                                std::cout << BRIGHT_GREEN << "\n\tSUCCESSFULLY UPDATED THE KEYWORD." << std::endl << RESET;

                            } catch (std::runtime_error &e) {
                                std::cerr << "\n\t" << BOLD << RED << e.what() << std::endl << RESET;
                            }

                            break;

                        case 5:
                            try {
                                std::cout << YELLOW << "\n\tEnter level number: " << CYAN;
                                std::cin >> level_id;
                                std::cin.ignore();
    
                                std::cout << YELLOW << "\tEnter new word: " << CYAN;
                                getline(std::cin, word);
    
                                hangman.changeWord(level_id, word);
                                std::cout << BRIGHT_GREEN << "\n\tSUCCESSFULLY UPDATED THE WORD." << std::endl << RESET;

                            } catch (std::runtime_error &e) {
                                std::cerr << "\n\t" << BOLD << RED << e.what() << std::endl << RESET;
                            }

                            break;

                        case 6:
                            try {
                                std::cout << YELLOW << "\n\tEnter level number: " << CYAN;
                                std::cin >> level_id;
                                std::cin.ignore();
    
                                std::cout << YELLOW << "\tEnter new hint description: " << CYAN;
                                getline(std::cin, hint);
    
                                hangman.changeHint(level_id, hint);
                                std::cout << BRIGHT_GREEN << "\n\tSUCCESSFULLY UPDATED THE HINT." << std::endl << RESET;

                            } catch (std::runtime_error &e) {
                                std::cerr << "\n\t" << BOLD << RED << e.what() << std::endl << RESET;
                            }

                            break;

                        case 7:
                            std::cout << BOLD << RED << "\n\tSERVICE UNAVAILABLE .!" << std::endl << RESET;
                            break;

                        case 8:
                            try {
                                std::cout << YELLOW << "\n\tEnter player name: " << CYAN;
                                getline(std::cin, player_name);
                                
                                std::cout << YELLOW << "\tEnter player email: " << CYAN;
                                getline(std::cin, player_email);
    
                                hangman.removePlayer(hangman.getPlayerByNameEmail(player_name, player_email));
    
                                std::cout << BRIGHT_GREEN << "\n\tPLAYER REMOVED SUCCESSFULLY" << std::endl << RESET;

                            } catch (std::runtime_error &e) {
                                std::cerr << "\n\t" << BOLD << RED << e.what() << std::endl << RESET;
                            }

                            break;

                        case 9:
                            hangman.removeAllGuestPlayers();
                            std::cout << BRIGHT_GREEN << "\n\tGUEST PLAYERS REMOVED SUCCESSFULLY" << std::endl << RESET;

                            break;

                        case 10:
                        {
                            std::cout << YELLOW << "\n\tPlayer's details: " << std::endl << RESET;
                            std::vector<Player> players = hangman.getAllPlayers();
                            for(Player player : players) {
                                std::cout << CYAN << player << RESET << std::endl;
                            }

                            break;
                        }

                        case 11:
                        {
                            std::cout << YELLOW << "\n\tEnter player name: " << CYAN;
                            getline(std::cin, player_name);

                            std::cout << YELLOW << "\tEnter player email: " << CYAN;
                            getline(std::cin, player_email);
                            Player player = hangman.getPlayerByNameEmail(player_name, player_email);

                            if(player.isGuest()) {
                                std::cerr << BOLD << RED << "player not found.!" << std::endl << RESET;
                            } else {
                                std::cout <<std::endl << MAGENTA << player << std::endl;
                            }

                            break;
                        }

                        case 12:
                            report = hangman.generateReport();

                            break;

                        case 0:
                            break;

                        default:
                            std::cerr << BOLD << RED <<"\n\tINVALID CHOICE..!" << std::endl << RESET;
                    }

                } while (admin_choice != 0);
                break;
            }

            case 2:
            {
                do {
                    player_choice = playerMenu();

                    if(player_choice != 1 && player_choice != 2 && player_choice != 0) {
                        if(!is_login) {
                            std::cerr << BOLD << RED << "\n\tYou have to login first." << std::endl << RESET;
                            continue;
                        }
                    }

                    switch(player_choice) {
                        case 1:
                        {
                            try {
                                std::cout << YELLOW << "\n\tEnter player name: " << CYAN;
                                getline(std::cin, player_name);
    
                                std::cout << YELLOW << "\tEnter player email: " << CYAN;
                                getline(std::cin, player_email);
    
                                hangman.signup(player_name, player_email);
                                std::cout << BRIGHT_GREEN << "\n\tPLAYER REGISTERED SUCCESSFULLY." << std::endl << RESET;

                            } catch (const std::runtime_error &e) {
                                std::cerr << "\n\t" << BOLD << RED << e.what() << std::endl << RESET;
                            }

                            break;
                        }

                        case 2:
                        {
                            /* want guess user? */
                            std::string ans = "";
                            std::cout << BLUE << "\n\tWant guest login (y/n)? " << CYAN;
                            std::cin >> ans;
                            std::cin.ignore();

                            if(ans[0] == 'Y' || ans[0] == 'y') {
                                registeredPlayer = Player();
                                is_login = true;
                                break;
                            }

                            /* login using credentials */
                            std::cout << YELLOW << "\n\tEnter player name: " << CYAN;
                            getline(std::cin, player_name);

                            std::cout << YELLOW << "\tEnter player email: " << CYAN;
                            getline(std::cin, player_email);

                            registeredPlayer = hangman.login(player_name, player_email);

                            if(registeredPlayer.isGuest()) {
                                std::cerr << BOLD << RED << "\n\tIncorrect name and email.!" << std::endl << RESET;
                            } else {
                                is_login = true;
                                std::cout << BRIGHT_GREEN << "\n\tPLAYER LOGIN SUCCESSFULLY." << std::endl << RESET;
                            }

                            break;
                        }

                        case 3:
                        {
                            std::cout << YELLOW "\n\tProfile:" CYAN << registeredPlayer << std::endl;
                            break;
                        }

                        case 4:
                        {
                            hangman.deleteAccount(registeredPlayer);
                            registeredPlayer = Player();
                            std::cout << BRIGHT_GREEN << "\n\tPLAYER DELETED SUCCESSFULLY." << std::endl << RESET;
                            is_login = false;

                            break;
                        }

                        case 5:
                        {
                            std::cout << YELLOW << "\n\tEnter new name: " << CYAN;
                            getline(std::cin, player_name);

                            if(hangman.changeName(registeredPlayer, player_name)) {
                                std::cout << BRIGHT_GREEN << "\n\tPLAYER NAME CHANGED SUCCESSFULLY." << std::endl << RESET;
                            } else {
                                std::cerr << BOLD << RED << "\n\tUNABLE TO CHANGE PLAYER NAME." << std::endl << RESET;
                            }

                            break;
                        }

                        case 6:
                        {
                            std::cout << YELLOW << "\n\tEnter new email: " << CYAN;
                            getline(std::cin, player_email);

                            if(hangman.changeEmail(registeredPlayer, player_email)) {
                                std::cout << BRIGHT_GREEN << "\n\tPLAYER EMAIL CHANGED SUCCESSFULLY." << std::endl << RESET;
                            } else {
                                std::cerr << BOLD << RED << "\n\tUNABLE TO CHANGE PLAYER EMAIL." << std::endl << RESET;
                            }

                            break;
                        }

                        case 7:
                        {
                            if(hangman.resetGame(registeredPlayer)) {
                                std::cout << BRIGHT_GREEN << "\n\tGAME RESET SUCCESSFULLY." << std::endl << RESET;
                            } else {
                                std::cerr << BOLD << RED << "\n\tUNABLE TO RESET GAME." << std::endl << RESET;
                            }

                            break;
                        }

                        case 8:
                        {
                            std::cout << GREEN << "\n\tScore: " << hangman.getPoints(registeredPlayer) << std::endl << RESET;

                            break;
                        }

                        case 9:
                        {
                            hangman.startGame(registeredPlayer);

                            break;
                        }

                        case 10:
                        {
                            if(!is_login) {
                                std::cerr << BOLD << RED << "\n\tno account is login.!" << std::endl << RESET;
                            } else {
                                registeredPlayer = Player();
                                is_login = false;
                                std::cout << BRIGHT_GREEN << "\n\tPLAYER LOGOUT SUCCESSFULLY." << std::endl << RESET;
                            }

                            break;
                        }

                        case 0:
                            break;

                        default:
                            std::cerr << BOLD << RED << "\n\tINVALID CHOICE.!" << std::endl << RESET;
                    }

                } while (player_choice != 0);
            }
        }

    } while (choice != 0);

    hangman.uploadLevels(LEVEL_FILE);
    hangman.uploadPlayers(PLAYER_FILE);
    
    /* reset color to default */
    std::cout << "\033[0m";
    return 0;
}
