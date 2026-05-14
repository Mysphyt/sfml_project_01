#include "texture_manager.h"

std::map<std::string, sf::Texture*> TextureManager::textures;

sf::Texture* TextureManager::loadTexture(const std::string& name, const std::string& path) {
    // Check if the texture is already loaded
    if (textures.find(name) != textures.end()) {
        return textures[name];
    }

    // Load the texture
    sf::Texture* texture = new sf::Texture();
        if (texture->loadFromFile("data/textures/" + path)) {
        textures[name] = texture;
        return texture;
    }

    // If loading fails, clean up and return nullptr
    delete texture;
    return nullptr;
}

// Retrieve a texture by its name
sf::Texture* TextureManager::getTexture(const std::string& name) {
        if (textures.find(name) != textures.end()) {
        return textures[name];
    }
    return nullptr;
}

// Clean up all loaded textures
void TextureManager::cleanup() {
    for (auto& pair : textures) {
        delete pair.second;
    }
    textures.clear();
}
