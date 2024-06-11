#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

class Leaderboard {
public:
    Leaderboard();
    ~Leaderboard();
    void addEntry(int points, float time);
    void draw(sf::RenderWindow& window, sf::Font& font);
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);

private:
    struct Entry {
        int points;
        float time;
        bool operator<(const Entry& other) const {
            return time < other.time; // Sort by time (ascending)
        }
    };

    std::vector<Entry> entries;
    const unsigned int maxEntries = 5; // Maximum number of leaderboard entries
};