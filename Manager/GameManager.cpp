#include "GameManager.hpp"
#include <fstream>
#include <iostream>
#include <cstring>
#include <limits>

bool GameManager::verifyAdmin(const std::string password) {
    return this->admin_password == password;
}

bool GameManager::setAdminPassword(const std::string newPassword) {
    std::string check;
    std::cout << "\tEnter admin password for verification: ";
    getline(std::cin, check);

    /* change admin password after verification */
    if(verifyAdmin(check)) {
        this->admin_password = newPassword;
        return true;
    } else {
        std::cerr << "\tInvalid password.!" << std::endl;
        return false;
    }
}

GameManager::GameManager() {}

std::vector<Player> GameManager::getAllPlayers() const {
    return players;
}

std::map<int, Level> GameManager::getAllLevels() const {
    return levels;
}

void GameManager::addNewLevel(Level &level) {
    int id = levels.size()+1;
    levels[id] = level;
}

void GameManager::removeLevel(int id) {
    levels.erase(id);
}

std::size_t GameManager::getLevelCount() {
    return levels.size();
}

void GameManager::changeKeyword(int id, const std::string &keyword) {
    Level &l = levels[id];

    /* checking if the level already exists */
    if(l.getFigure()) {
        Challenge ch = l.getChallenge();
        ch.setKeyword(keyword);
        l.setChallenge(ch);
    }
}

void GameManager::changeWord(int id, const std::string &word) {
    Level &l = levels[id];

    /* checking if the level already exists */
    if(l.getFigure()) {
        Challenge ch = l.getChallenge();
        ch.setWord(word);
        l.setChallenge(ch);
    }
}

void GameManager::changeHint(int id, const std::string &hint) {
    Level &l = levels[id];

    /* checking if the level already exists */
    if(l.getFigure()) {
        Challenge ch = l.getChallenge();
        ch.setHint(hint);
        l.setChallenge(ch);
    }
}

void GameManager::changeFigure(int id, Figure *newFigure) {
    Level &l = levels[id];

    /* checking if the level already exists */
    if(l.getFigure()) {
        l.setFigure(newFigure);
    }
}

void GameManager::addNewPlayer(const Player &player) {
    players.push_back(player);
}

void GameManager::removePlayer(const Player &player) {
    auto it = std::find_if(players.begin(), players.end(),
                           [&](const Player &p) {
                               return p.getName() == player.getName() &&
                                      p.getEmail() == player.getEmail();
                           });
    if(it != players.end()){
        players.erase(it);
    }
}

void GameManager::removeAllGuestPlayers() {
    players.erase(
        std::remove_if(players.begin(), players.end(),
                       [](const Player &p) { return p.getEmail().empty(); }),
        players.end()
    );
}

std::size_t GameManager::getPlayerCount() {
    return players.size();
}

const Player GameManager::getPlayerByNameEmail(const std::string &name, const std::string &email) {
    for (const Player& p : players) {
        if (p.getName() == name && p.getEmail() == email) {
            return p;
        }
    }
    // If not found, return a default Player or handle as needed
    return Player();
}

std::string GameManager::generateReport() {
    std::string level_report = "\n\tTotal level count: " + std::to_string(levels.size());
    std::string player_report = "\n\tTotal registered players count: " + std::to_string(Player::getTotalPlayerCount());

    std::cout << level_report << player_report << std::endl;
    return level_report + player_report;
}

void GameManager::uploadLevels(const char *filename) {
    std::ofstream fout(filename);
    if(!fout.is_open()) {
        std::cerr << "\tError in opening file: [" << filename << "].!" << std::endl;
        return;
    }

    std::map<int, Level>::iterator it = levels.begin();
    while(it != levels.end()) {
        // key for map
        fout << (*it).first << std::endl;

        // game (challenge) details
        fout << (*it).second.getChallenge().getKeyword() << std::endl;
        fout << (*it).second.getChallenge().getWord() << std::endl;
        fout << (*it).second.getChallenge().getHint() << std::endl;

        // figure details (handle possible null figure safely)
        Figure *fig = (*it).second.getFigure();
        fout << (fig ? fig->getFigureClassName() : "NONE") << std::endl;

        it++;
    }

    fout.close();
}

void GameManager::downloadLevels(const char *filename) {
    std::ifstream fin(filename);
    if(!fin.is_open()) {
        std::cerr << "\tError in opening file: [" << filename << "].!" << std::endl;
        return;
    }

    if(fin.peek() == std::ifstream::traits_type::eof())
        return; // no need to notify, if file is empty, data will be filled from scratch

    int id;
    std::string keyword, word, hint;
    std::string figureName;

    while(fin >> id) {
        fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // read game data
        if(!getline(fin, keyword)) break;
        if(!getline(fin, word)) break;
        if(!getline(fin, hint)) break;

        // read figure data
        if(!getline(fin, figureName)) break;

        // create objects of game, figure and then level
        Challenge game(keyword, word, hint);

        Figure *figure = nullptr;
        if(figureName == "HangmanFigure")
            figure = new HangmanFigure();
        
        Level level(game, figure);

        // insert it in level map
        levels[id] = level;
    }

    fin.close();
}

void GameManager::uploadPlayers(const char *filename) {
    std::ofstream fout(filename);
    if(!fout.is_open()) {
        std::cerr << "\tError in opening file: [" << filename << "].!" << std::endl;
        return;
    }

    for(const Player &player : players) {
        fout << player.getName() << std::endl;
        fout << player.getEmail() << std::endl;
        fout << player.getCompletedLevelCount() << std::endl;
    }

    fout.close();
}

void GameManager::downloadPlayers(const char *filename) {
    std::ifstream fin(filename);
    if(!fin.is_open()) {
        std::cerr << "\tError in opening file: [" << filename << "].!" << std::endl;
        return;
    }

    if(fin.peek() == std::ifstream::traits_type::eof())
        return; // no need to notify, if file is empty, data will be filled from scratch

    std::string name, email;
    int level_count;

    while(getline(fin, name)) {
        if(!getline(fin, email)) break;
        fin >> level_count;
        fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // create player object
        Player player(name, email);
        player.setCompletedLevelCount(level_count);

        // insert in players list
        players.push_back(player);
    }
}











void GameManager::signup(const std::string &name, const std::string &email) {
    Player player(name, email);
    auto it = std::find_if(players.begin(), players.end(),
                           [&](const Player &p) {
                               return p.getName() == player.getName() &&
                                      p.getEmail() == player.getEmail();
                           });
    if(it == players.end()) {
        this->addNewPlayer(player);
    }
}

void GameManager::signup() {
    this->addNewPlayer(Player());
}

const Player GameManager::login(const std::string &name, const std::string &email) {
    return this->getPlayerByNameEmail(name, email);
}

void GameManager::deleteAccount(const Player &player) {
    auto it = std::find_if(players.begin(), players.end(),
                           [&](const Player &p) {
                               return p.getName() == player.getName() &&
                                      p.getEmail() == player.getEmail();
                           });
    if(it != players.end()) {
        players.erase(it);
    }
}

bool GameManager::changeName(Player &player, const std::string &name) {
    auto it = std::find_if(players.begin(), players.end(),
                           [&](const Player &p) {
                               return p.getName() == player.getName() &&
                                      p.getEmail() == player.getEmail();
                           });
    if(it != players.end()) {
        (*it).setName(name);
        player.setName(name);
        return true;
    }
    return false;
}

bool GameManager::changeEmail(Player &player, const std::string &email) {
    auto it = std::find_if(players.begin(), players.end(),
                           [&](const Player &p) {
                               return p.getName() == player.getName() &&
                                      p.getEmail() == player.getEmail();
                           });
    if(it != players.end()) {
        (*it).setEmail(email);
        player.setEmail(email);
        return true;
    }
    return false;
}

bool GameManager::resetGame(Player &player) {
    auto it = std::find_if(players.begin(), players.end(),
                           [&](const Player &p) {
                               return p.getName() == player.getName() &&
                                      p.getEmail() == player.getEmail();
                           });
    if(it != players.end()) {
        (*it).unlockNewLevel(Level()); // reset level
        (*it).resetCompletedLevelCount();
        player.unlockNewLevel(Level());
        player.resetCompletedLevelCount();
        return true;
    }
    return false;
}

std::size_t GameManager::getPoints(const Player &player) {
    auto it = std::find_if(players.begin(), players.end(),
                           [&](const Player &p) {
                               return p.getName() == player.getName() &&
                                      p.getEmail() == player.getEmail();
                           });
    if(it != players.end()) {
        return (*it).getCompletedLevelCount();
    }
    return 0;
}

void GameManager::startGame(Player &player) {

    /* allow only one level */
    if(player.isGuest()) {
        player.unlockNewLevel(levels.at(1));
        Level level = player.getUnlockedLevel();

        std::cout << "\n\tLet's start game..." << std::endl;
        if(level.play()) {
            std::cout << "\n\tCONGRATULATIONS!, you won the game..." << std::endl;
        } else {
            std::cout << "\tOOPs!, you lost the game.!" << std::endl;
        }

        return; // end the function for guest player.
    }

    // continue playing until user ends the game
    int wantContinue = 0;
    do {
        // set new level
        int current_level = player.getCompletedLevelCount();
        auto it = levels.find(current_level + 1);
        if (it == levels.end()) {
            std::cout << "\n\tNo more levels available.\n";
            break;
        }
        Level &level = it->second;
        player.unlockNewLevel(Level(level.getChallenge(), level.getFigure()));

        std::cout << "\tEnter to start level: " << (current_level + 1) << " ...";
        getc(stdin);

        std::cout << "\tLet's start game..." << std::endl;
        if(level.play()) {
            std::cout << "\n\tCONGRATULATIONS!, you won the game..." << std::endl;
            player.setCompletedLevelCount((current_level+1)); // update current level count for player

            // sync updated count back to manager's stored players list
            std::vector<Player>::iterator it = std::find_if(players.begin(), players.end(),
                                    [&](const Player &p) {
                                        return p.getName() == player.getName() &&
                                               p.getEmail() == player.getEmail();
                                    });
            if(it != players.end()) {
                (*it).setCompletedLevelCount(player.getCompletedLevelCount());
            }

            std::cout << "\tdo you want to continue playing (1/0)? ";
            std::cin >> wantContinue;
        } else {
            std::cout << "\tOOPs!, you lost the game.!" << std::endl;

            std::cout << "\tdo you want to restart playing (1/0)? ";
            std::cin >> wantContinue;
        }
        std::cin.ignore();
    } while (wantContinue);
}
