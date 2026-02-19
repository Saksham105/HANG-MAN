#include "Player.hpp"
#include <stdexcept>
#include <regex>

std::size_t Player::player_count = 0;

Player :: Player() : name("Guest-user") {
    this->id = ++player_count;
    this->completed_level_count = 0;
    this->email = generateGuestEmail();
}

Player::Player(const std::string &name, const std::string &email) : name(name) {
    this->id = ++player_count;
    this->completed_level_count = 0;
    if(isValidEmail(email)) {
        this->email = email;
    } else {
        throw std::runtime_error("invalid email address.!");
    }
}

Player::Player(const Player& player) {
    this->id = player.id;
    this->name = player.name;
    this->email = player.email;
    this->completed_level_count = player.completed_level_count;
    this->unlocked_level = player.unlocked_level;
}

std::string Player::generateGuestEmail() {
    return "";
}

bool Player::isValidEmail(const std::string &email) {
    const std::regex pattern(R"([a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*)");

    return std::regex_match(email, pattern);
}

bool Player::isGuest() {
    return (this->name == "Guest-user");
}

void Player::setName(const std::string &name) {
    this->name = name;
}

std::string Player::getName() const {
    return name;
}

void Player::setEmail(const std::string &email) {
    if(isValidEmail(email)) {
        this->email = email;
    } else {
        throw std::runtime_error("invalid email address.!");
    }
}

std::string Player::getEmail() const {
    return email;
}

void Player::unlockNewLevel(Level level) {
    unlocked_level = level;
}

const Level& Player::getUnlockedLevel() const {
    return unlocked_level;
}

int Player::getCompletedLevelCount() const {
    return completed_level_count;
}

void Player::setCompletedLevelCount(int completed_level_count) {
    this->completed_level_count = completed_level_count;
}

void Player::resetCompletedLevelCount() {
    this->completed_level_count = 0;
}

std::size_t Player::getTotalPlayerCount() {
    return player_count;
}

std::ostream& operator<<(std::ostream &out, const Player &player) {
    out << "\n\t\tPlayer name: " << player.name << std::endl
        << "\t\tPlayer email: " << player.email << std::endl
        << "\t\tScore: " << player.completed_level_count << std::endl;
    return out;
}