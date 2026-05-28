#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "data.h"

class SpriteSheetAnimation {
    // 
public:
    SpriteSheetAnimation(std::string filePath);
    void Update(sf::RenderWindow& window, float deltaTime);
private:
    std::string textureName; // to index SPRITE_SHEET_DATA from texture_manager
    std::string animationName; // to index the map of animations for this textureName in SPRITE_SHEET_DATA

    unsigned int startIt, endIt, currIt, duration, frameTime;

    sf::Sprite* spriteSheet;
};

class SpriteManager {
public:
    // Load a texture from file and store it with a name
    static void createSprite(std::string spriteName, const unsigned int& id, const std::string& textureName);

    static void addSprite(std::string spriteName, sf::Sprite* sprite, const unsigned int& id);

    // Retrieve a texture by its Object ID
    static std::map<std::string, sf::Sprite*> getObjSpriteMap(const unsigned int& id);

    // Clean up all loaded textures
    static void cleanup();

private:
    // Sprites by object id
    // => { object_id : { sprite_name : sprite }, ... }
    static std::map<unsigned int, std::map<std::string, sf::Sprite*>> SPRITES_BY_ID; // Map to store textures
};

#endif