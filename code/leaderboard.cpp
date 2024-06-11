#include "leaderboard.h"
#include <iostream>
#include <cmath>
Leaderboard::Leaderboard() {
    loadFromFile("code/leaderboard.txt");
}

void Leaderboard::addEntry(int points, float time) {
    time = std::round(time * 1000) / 1000;  // Zaokrągla do 3 miejsc po przecinku
    Entry newEntry = { points, time };
    entries.push_back(newEntry);
    std::sort(entries.begin(), entries.end());
    if (entries.size() > maxEntries) {
        entries.pop_back();
    }
    saveToFile("code/leaderboard.txt");
}

void Leaderboard::draw(sf::RenderWindow& window, sf::Font& font) {
    sf::Vector2u windowSize = window.getSize();
    float titleFontSize = static_cast<float>(windowSize.y) / 20.0f; // Title font size based on window height
    float entryFontSize = static_cast<float>(windowSize.y) / 30.0f; // Entry font size based on window height
    float yOffset = static_cast<float>(windowSize.y) / 15.0f; // Vertical offset for entries

    sf::Text title("Leaderboard", font, static_cast<unsigned int>(titleFontSize));
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(1);
    title.setPosition(windowSize.x / 2.0f - title.getGlobalBounds().width / 2.0f, windowSize.y * 0.1f); // Center title horizontally
    window.draw(title);

    for (size_t i = 0; i < entries.size() && i < 10; ++i) { // Display top 10 entries
        sf::Text entryText(std::to_string(i + 1) + ". Points: " + std::to_string(entries[i].points) + " Time: " + std::to_string(entries[i].time), font, static_cast<unsigned int>(entryFontSize));
        entryText.setFillColor(sf::Color::White);
        entryText.setOutlineColor(sf::Color::Black);
        entryText.setOutlineThickness(1);
        entryText.setPosition(windowSize.x / 2.0f - entryText.getGlobalBounds().width / 2.0f, windowSize.y * 0.1f + titleFontSize + i * yOffset); // Center entries horizontally
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
        time = std::round(time * 1000) / 1000;
        while (file >> points >> time) {
            entries.push_back({ points, time });
        }
    }
}
Leaderboard::~Leaderboard() {
    saveToFile("code/leaderboard.txt");
    std::cout<<"leaderboard destructor\n";
}
