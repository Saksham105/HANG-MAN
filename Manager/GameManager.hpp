#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <vector>
#include <map>
#include <algorithm>
#include "../Level/Level.hpp"
#include "../Player/Player.hpp"

/*
    Class represents the middleware which handles the players data and the levels in the game
    Class contains:
        list of levels available in the game
        list of players downloaded (registered in) the game
        logic for players (client-side) and admin (server-side) functionalities
*/
class GameManager {
private:
    std::string admin_password = "ADMN#456@JP"; // by default

    std::map<int, Level> levels;
    std::vector<Player> players;

public:

    bool verifyAdmin(const std::string password);
    bool setAdminPassword(const std::string newPassword);

    GameManager(); // default constructor

    /* Gtter for players */
    std::vector<Player> getAllPlayers() const ;

    /* Gtter for levels */
    std::map<int, Level> getAllLevels() const ;

    /* ------------- admin functionalities -------------*/

    // Level related functions
    /**
     * @brief adds new level in the game
     * @param level represents one level object
     */
    void addNewLevel(Level &level);

    /**
     * @brief removes one level by searching the @a id
     * @param id key for level map
     */
    void removeLevel(int id);

    /**
     * @brief returns how many levels present in game
     * @return total number of levels
     */
    std::size_t getLevelCount();

    // Game (Challenge) related functions
    /**
     * @brief update keyword for a challnge in one level
     * @param id key for level map
     * @param keyword new keyword to set in challenge
     */
    void changeKeyword(int id, const std::string &keyword);

    /**
     * @brief update word in a challnge in one level
     * @param id key for level map
     * @param word new word to set in challenge
     */
    void changeWord(int id, const std::string &word);

    /**
     * @brief update hint for a challnge in one level
     * @param id key for level map
     * @param hint new hint to set in challenge
     */
    void changeHint(int id, const std::string &hint);

    /**
     * @brief update figure for a challnge in one level
     * @param id key for level map
     * @param newFigure new figure to set in challenge
     */
    void changeFigure(int id, Figure *newFigure);

    // Player related functions
    /**
     * @brief registers new Player in the game 
     * @param player reference to the new player
     */
    void addNewPlayer(const Player &player);

    /**
     * @brief removes a specific player
     * @param player reference to the player to be deleted
     */
    void removePlayer(const Player &player);

    /**
     * @brief removes all players registered in game as guest
     */
    void removeAllGuestPlayers();

    /**
     * @brief returns total players registered in the game
     * @return total number of players
     */
    std::size_t getPlayerCount();

    /**
     * @brief returns a player object
     * @param name player name
     * @param email player email
     * @return Player object
     */
    const Player getPlayerByNameEmail(const std::string &name, const std::string &email);

    // audit function
    /**
     * @brief generate a report representing total levels and players in the game
     * @return string represents the report data (text)
     */
    std::string generateReport();

    /**
     * @brief save all levels in file.
     * @param filename file name to which all levels are being saved
     */
    void uploadLevels(const char *filename);

    /**
     * @brief reload level's file content in level's list
     * @param filename file name from which level data is being retrived
     */
    void downloadLevels(const char *filename);

    /**
     * @brief save all players in file.
     * @param filename file name to which all players are being saved
     */
    void uploadPlayers(const char *filename);

    /**
     * @brief reload player's file content in player's list
     * @param filename file name from which player data is being retrived
     */
    void downloadPlayers(const char *filename);
    














    /* ------------- player functionalities -------------*/
    /**
     * @brief creats new Player and add into the game register
     * @param name name of player
     * @param email email of player
     */
    void signup(const std::string &name, const std::string &email);

    /**
     * @brief creats new Player and add into the game register as a guest player
     */
    void signup();

    /**
     * @brief verify player and returns its instance
     * @param name name of player
     * @param email email of player
     */
    const Player login(const std::string &name, const std::string &email);

    /**
     * @brief delets player from game register
     * @param name name of player
     * @param email email of player
     */
    void deleteAccount(const Player &player);

    /**
     * @brief update player name
     * @param player reference to Player
     * @param name new name for player
     */
    bool changeName(Player &player, const std::string &name);

    /**
     * @brief update player email
     * @param player reference to Player
     * @param name new email for player
     */
    bool changeEmail(Player &player, const std::string &email);

    /**
     * @brief reset the game for a player
     * @param player reference to Player
     */
    bool resetGame(Player &player);

    /**
     * @brief returns points of a player
     * @param player reference to Player
     * @return total points a player have
     */
    std::size_t getPoints(const Player &player);

    /**
     * @brief start the gameplay for a player
     * @param player reference to Player
     */
    void startGame(Player &player);
};

#endif
