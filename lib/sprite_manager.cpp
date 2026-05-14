#include "sprite_manager.h"
#include "texture_manager.h"

std::map<unsigned int, std::map<std::string, sf::Sprite*>> SpriteManager::spritesByID; // Map to store textures

// Load a texture from file and store it with a name
void SpriteManager::createSprite(std::string spriteName, const unsigned int& id, const std::string& textureName)
{
    // 
    if (spritesByID.find(id) == spritesByID.end()) {
        spritesByID[id] = {};
    }
    sf::Texture* texture = TextureManager::getTexture(textureName);
    if(texture != nullptr)
    {
        sf::Sprite* sprite = new sf::Sprite(*texture);
        spritesByID[id][spriteName] = sprite;
    }
}

void SpriteManager::addSprite(std::string spriteName, sf::Sprite* sprite, const unsigned int& id)
{
    if (spritesByID.find(id) == spritesByID.end()) {
        spritesByID[id] = {};
    }
    spritesByID[id][spriteName] = sprite;
}

// Retrieve a texture by its name
std::map<std::string, sf::Sprite*> SpriteManager::getObjSpriteMap(const unsigned int& id)
{
    if (spritesByID.find(id) != spritesByID.end()) {
        return spritesByID[id];
    }
    return {};
}

// Clean up all loaded textures
void SpriteManager::cleanup()
{
    for (auto& pair : spritesByID) {
        for (auto& sprite : pair.second)
            delete sprite.second;
    }
    spritesByID.clear();
}