#include "font_manager.h"

std::map<std::string, sf::Font*> FontManager::fonts;

sf::Font* FontManager::loadFont(const std::string& name, const std::string& path) {
    // Check if the texture is already loaded
    if (fonts.find(name) != fonts.end()) {
        return fonts[name];
    }

    // Load the texture
    sf::Font* font = new sf::Font();
        if (font->openFromFile("data/fonts/" + path)) {
        fonts[name] = font;
        return font;
    }

    // If loading fails, clean up and return nullptr
    delete font;
    return nullptr;
};

sf::Font* FontManager::getFont(const std::string& name) {
    if (fonts.find(name) != fonts.end()) {
        return fonts[name];
    }
    return nullptr;
};

void FontManager::cleanup() {
    for (auto& pair : fonts) {
        delete pair.second;
    }
    fonts.clear();
};