#include "leaderboard.h"

Leaderboard::Leaderboard() {
    loadFromFile("leaderboard.txt");
}

void Leaderboard::addEntry(int points, float time) {
    Entry newEntry = { points, time };
    entries.push_back(newEntry);
    std::sort(entries.begin(), entries.end());
    if (entries.size() > maxEntries) {
        entries.pop_back();
    }
    saveToFile("leaderboard.txt");
}

void Leaderboard::draw(sf::RenderWindow& window, sf::Font& font) {
    sf::Text title("Leaderboard", font, 32);
    title.setFillColor(sf::Color::White);
    title.setPosition(50, 50);
    window.draw(title);

    for (size_t i = 0; i < entries.size(); ++i) {
        sf::Text entryText(std::to_string(i + 1) + ". Points: " + std::to_string(entries[i].points) + " Time: " + std::to_string(entries[i].time), font, 24);
        entryText.setFillColor(sf::Color::White);
        entryText.setPosition(50, 100 + i * 30);
        window.draw(entryText);
    }
}

void Leaderboard::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& entry : entries) {
            file << entry.points << " " << entry.time << "\n";
        }
    }
}

void Leaderboard::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        entries.clear();
        int points;
        float time;
        while (file >> points >> time) {
            entries.push_back({ points, time });
        }
    }
}
