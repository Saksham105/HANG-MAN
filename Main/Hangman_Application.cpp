#include <iostream> // for cout and cin
#include <fstream> // for file handling
#include <string> // for dealing with string
#include <cstdlib> // for exit() function

#include "../Manager/GameManager.hpp"

/* if already define in system, then only... */
#ifdef _WIN32
#include <windows.h> // for cmd color manipulation
#endif

#define ORANGE "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define PINC "\033[1;35m"
#define CYAN "\033[1;36m"
#define DEFAULT "\033[0m"

#define LEVEL_FILE "level_file.txt"
#define PLAYER_FILE "player_file.txt"

/*
    the GCC specific compiler extension which mark a function to execute before main()
    i.e. as soon as the shared library loaded, then this function executes.
*/
__attribute__((constructor))
void showBanner() {
    /* cmd color changes (cyan: light blue) */
    std::cout << GREEN;

    /* Opens the banner text file in read mode */
    std::string fileName = "Main/title_page.txt";
    std::ifstream file(fileName);
    if(!file.is_open()) {
        std::cerr << "\tunable to open banner [" << fileName << "]." << std::endl;
        return;
    }

    std::string line;

    /* reads untill EOF reaches */
    while(std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();

}

/* menu functions */
int adminMenu() {
    int choice;

    std::cout << "\n\t= = = = =\tA D M I N - M E N U\t\t= = = = =" << std::endl;
    std::cout << "\n\t1. Add new level" << std::endl;
    std::cout << "\t2. Remove level" << std::endl;
    std::cout << "\t3. Get level count" << std::endl;
    std::cout << "\t4. Change keyword by level id" << std::endl;
    std::cout << "\t5. Change word by level id" << std::endl;
    std::cout << "\t6. Change hint by level id" << std::endl;
    std::cout << "\t7. Change figure by level id" << std::endl; // later implementation
    std::cout << "\t8. Remove player by name and email" << std::endl;
    std::cout << "\t9. Remove all guest player" << std::endl;
    std::cout << "\t10. Get total players count" << std::endl;
    std::cout << "\t11. Get player by name and email" << std::endl;
    std::cout << "\t12. Generate report" << std::endl;
    std::cout << "\t0. BACK TO MAIN MENU" << std::endl;

    std::cout << "\n\tEnter your choice: ";
    std::cin >> choice;
    std::cin.ignore();

    return choice;
}

int playerMenu() {
    int choice;

    std::cout << "\n\t= = = = =\tP L A Y E R - M E N U\t\t= = = = =" << std::endl;
    std::cout << "\n\t1. Sign-up (create account)" << std::endl;
    std::cout << "\t2. Login" << std::endl;
    std::cout << "\t3. Delete account" << std::endl;
    std::cout << "\t4. Change name" << std::endl;
    std::cout << "\t5. Change email" << std::endl;
    std::cout << "\t6. Reset game" << std::endl;
    std::cout << "\t7. Get current score" << std::endl;
    std::cout << "\t8. Play (start game)" << std::endl;
    std::cout << "\t9. Logout" << std::endl;
    std::cout << "\t0. BACK TO MAIN MENU" << std::endl;

    std::cout << "\n\tEnter your choice: ";
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
    std::string player_name;
    std::string player_email;
    int level_id;

    bool is_admin = false;
    bool is_login = false;
    int choice;
    int admin_choice;
    int player_choice;

    hangman.downloadLevels(LEVEL_FILE);
    hangman.downloadPlayers(PLAYER_FILE);

    do {
        std::cout << "\n\t= = = = =\tM E N U\t\t= = = = =" << std::endl;
        std::cout << "\n\t1. I am an Admin" << std::endl;
        std::cout << "\t2. I am a Player" << std::endl;
        std::cout << "\t0. EXIT" << std::endl;

        std::cout << "\n\tEnter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
            {
                std::cout << "\n\tEnter admin password: ";
                getline(std::cin, admin_password);

                is_admin = hangman.verifyAdmin(admin_password);

                if(!is_admin) {
                    std::cerr << "\n\tIncorrect passwod.!" << std::endl;
                    break;
                }

                std::cout << "\n\tCorrect password.!\n\tlogin successful" << std::endl;
                do {
                    admin_choice = adminMenu();

                    switch (admin_choice) {
                        case 1:
                        {
                            std::cout << "\n\tEnter keyword: ";
                            getline(std::cin, keyword);

                            std::cout << "\tEnter word: ";
                            getline(std::cin, word);

                            std::cout << "\tEnter hint description: ";
                            getline(std::cin, hint);

                            Challenge game(keyword, word, hint);
                            figure = new HangmanFigure();

                            Level level(game, figure);
                            hangman.addNewLevel(level);
                            std::cout << "\n\tSUCCESSFULLY ADDED NEW LEVEL." << std::endl;

                            break;
                        }

                        case 2:
                            std::cout << "\n\tEnter level number: ";
                            std::cin >> level_id;
                            std::cin.ignore();

                            hangman.removeLevel(level_id);
                            std::cout << "\n\tSUCCESSFULLY REMOVED LEVEL: " << level_id << std::endl;

                            break;

                        case 3:
                            std::cout << "\n\tTotal levels available: " << hangman.getLevelCount() << std::endl;

                            break;

                        case 4:
                            std::cout << "\n\tEnter level number: ";
                            std::cin >> level_id;
                            std::cin.ignore();

                            std::cout << "\tEnter new keyword: ";
                            getline(std::cin, keyword);

                            hangman.changeKeyword(level_id, keyword);
                            std::cout << "\n\tSUCCESSFULLY UPDATED THE KEYWORD." << std::endl;

                            break;

                        case 5:
                            std::cout << "\n\tEnter level number: ";
                            std::cin >> level_id;
                            std::cin.ignore();

                            std::cout << "\tEnter new word: ";
                            getline(std::cin, word);

                            hangman.changeWord(level_id, word);
                            std::cout << "\n\tSUCCESSFULLY UPDATED THE WORD." << std::endl;

                            break;

                        case 6:
                            std::cout << "\n\tEnter level number: ";
                            std::cin >> level_id;
                            std::cin.ignore();

                            std::cout << "\tEnter new hint description: ";
                            getline(std::cin, hint);

                            hangman.changeHint(level_id, hint);
                            std::cout << "\n\tSUCCESSFULLY UPDATED THE HINT." << std::endl;

                            break;

                        case 7:
                            std::cout << "\n\tSERVICE UNAVAILABLE .!" << std::endl;
                            break;

                        case 8:
                            std::cout << "\n\tEnter player name: ";
                            getline(std::cin, player_name);

                            std::cout << "\tEnter player email: ";
                            getline(std::cin, player_email);

                            hangman.removePlayer(hangman.getPlayerByNameEmail(player_name, player_email));

                            std::cout << "\n\tPLAYER REMOVED SUCCESSFULLY" << std::endl;

                            break;

                        case 9:
                            hangman.removeAllGuestPlayers();
                            std::cout << "\n\tGUEST PLAYERS REMOVED SUCCESSFULLY" << std::endl;

                            break;

                        case 10:
                            std::cout << "\n\tTotal players registered: " << hangman.getPlayerCount() << std::endl;

                            break;

                        case 11:
                        {
                            std::cout << "\n\tEnter player name: ";
                            getline(std::cin, player_name);

                            std::cout << "\tEnter player email: ";
                            getline(std::cin, player_email);
                            Player player = hangman.getPlayerByNameEmail(player_name, player_email);

                            std::cout << player << std::endl;

                            break;
                        }

                        case 12:
                            hangman.generateReport();

                            break;

                        case 0:
                            break;

                        default:
                            std::cerr << "\n\tINVALID CHOICE..!" << std::endl;
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
                            std::cerr << "\n\tYou have to login first." << std::endl;
                            continue;
                        }
                    }

                    switch(player_choice) {
                        case 1:
                        {
                            std::cout << "\n\tEnter player name: ";
                            getline(std::cin, player_name);

                            std::cout << "\tEnter player email: ";
                            getline(std::cin, player_email);

                            hangman.signup(player_name, player_email);
                            std::cout << "\n\tPLAYER REGISTERED SUCCESSFULLY." << std::endl;

                            break;
                        }

                        case 2:
                        {
                            /* want guess user? */
                            char ans;
                            std::cout << "\n\tWant guest login (y/n)? ";
                            std::cin >> ans;
                            std::cin.ignore();
                            if(ans == 'Y' || ans == 'y') {
                                registeredPlayer = Player();
                                is_login = true;
                                break;
                            }

                            /* login using credentials */
                            std::cout << "\n\tEnter player name: ";
                            getline(std::cin, player_name);

                            std::cout << "\tEnter player email: ";
                            getline(std::cin, player_email);

                            registeredPlayer = hangman.login(player_name, player_email);
                            if(registeredPlayer.isGuest()) {
                                std::cerr << "\n\tIncorrect name and email.!" << std::endl;
                            } else {
                                is_login = true;
                                std::cout << "\n\tPLAYER LOGIN SUCCESSFULLY." << std::endl;
                            }

                            break;
                        }

                        case 3:
                        {
                            hangman.deleteAccount(registeredPlayer);
                            registeredPlayer = Player();
                            std::cout << "\n\tPLAYER DELETED SUCCESSFULLY." << std::endl;

                            break;
                        }

                        case 4:
                        {
                            std::cout << "\n\tEnter player name: ";
                            getline(std::cin, player_name);

                            if(hangman.changeName(registeredPlayer, player_name)) {
                                std::cout << "\n\tPLAYER NAME CHANGED SUCCESSFULLY." << std::endl;
                            } else {
                                std::cerr << "\n\tUNABLE TO CHANGE PLAYER NAME." << std::endl;
                            }

                            break;
                        }

                        case 5:
                        {
                            std::cout << "\n\tEnter player email: ";
                            getline(std::cin, player_email);

                            if(hangman.changeEmail(registeredPlayer, player_email)) {
                                std::cout << "\n\tPLAYER EMAIL CHANGED SUCCESSFULLY." << std::endl;
                            } else {
                                std::cerr << "\n\tUNABLE TO CHANGE PLAYER EMAIL." << std::endl;
                            }

                            break;
                        }

                        case 6:
                        {
                            if(hangman.resetGame(registeredPlayer)) {
                                std::cout << "\n\tGAME RESET SUCCESSFULLY." << std::endl;
                            } else {
                                std::cerr << "\n\tUNABLE TO RESET GAME." << std::endl;
                            }

                            break;
                        }

                        case 7:
                        {
                            std::cout << "\n\tScore: " << hangman.getPoints(registeredPlayer) << std::endl;

                            break;
                        }

                        case 8:
                        {
                            hangman.startGame(registeredPlayer);

                            break;
                        }

                        case 9:
                        {
                            registeredPlayer = Player();
                            is_login = false;
                            std::cout << "\n\tPLAYER LOGOUT SUCCESSFULLY." << std::endl;

                            break;
                        }

                        case 0:
                            break;

                        default:
                            std::cerr << "\n\tINVALID CHOICE.!" << std::endl;
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
