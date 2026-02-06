#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "../Level/Level.hpp"

/*
    class will represent one player
    contains:
        id: unique and auto-generated
        name: (nick name) player want to display on its score card
        email: to notify player about further updates
*/
class Player {
private:
    // player details
    long int id; // unique id for each user (auto-generated)
    std::string name; // nick name which displays on score card
    std::string email; // stores email address for further communication

    // static count for auto generation
    static std::size_t player_count;

    // unnlocked level
    Level unlocked_level;
    int completed_level_count;

public:
    /* for guest user (no registration - limited access to levels) */
    Player();

    /**
     * @brief stores all details of player
     * @param name user nickname
     * @param email user email address
     */
    Player(const std::string &name, const std::string &email);

    Player(const Player& player);

    /* helper functions for email verification and generation */
    std::string generateGuestEmail();
    bool isValidEmail(const std::string &email);

    /* check for guest user */
    bool isGuest();

    /* Setter for name */
    void setName(const std::string &name);

    /* Gtter for name */
    std::string getName() const ;

    /* Setter for email */
    void setEmail(const std::string &email);

    /* Gtter for email */
    std::string getEmail() const ;

    /* Setter for level */
    void unlockNewLevel(Level level);

    /* Gtter for level */
    const Level& getUnlockedLevel() const ;

    /* Gtter for current level count */
    int getCompletedLevelCount() const ;

    /* Setter for current level count */
    void setCompletedLevelCount(int completed_level_count);

    /* Setter for current level count */
    void resetCompletedLevelCount();

    /* Gtter for total players count */
    static std::size_t getTotalPlayerCount();

    friend std::ostream& operator<<(std::ostream &out, const Player &player);
};

#endif