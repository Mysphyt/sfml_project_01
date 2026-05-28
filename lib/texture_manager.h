#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "data.h"

struct SimpleRect {
    unsigned int xPos;     
    unsigned int yPos;
    unsigned int height;
    unsigned int width;
};

class TextureManager {
public:
    // Load a texture from file and store it with a name
    static sf::Texture* loadTexture(const std::string& name, const std::string& path);

    // Retrieve a texture by its name
    static sf::Texture* getTexture(const std::string& name);

    // Clean up all loaded textures
    static void cleanup();

    static void loadMetadata();

private:
    static std::map<std::string, sf::Texture*> TEXTURES; // Map to store textures

    // { texture_name : { animation_name:animation_bounds }, ... }
    static std::map<std::string, std::map<std::string, std::vector<SimpleRect>>> SPRITE_SHEET_DATA; // 
};

#endif