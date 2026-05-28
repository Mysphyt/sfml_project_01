#include "sprite_manager.h"
#include "texture_manager.h"

std::map<unsigned int, std::map<std::string, sf::Sprite*>> SpriteManager::SPRITES_BY_ID; // Map to store textures
std::map<std::string, std::map<std::string, std::string>> TEXTURE_METADATA; // Map to store animated texture metadata

SpriteSheetAnimation::SpriteSheetAnimation(std::string filePath) 
{
    sf::Texture* texture = TextureManager::getTexture(filePath);
    if(texture != nullptr)
    {
        spriteSheet = new sf::Sprite(*texture);
    }
}

void SpriteSheetAnimation::Update(sf::RenderWindow& window, float detaTime) 
{

}

// Load a texture from file and store it with a name
void SpriteManager::createSprite(std::string spriteName, const unsigned int& id, const std::string& textureName)
{
    // 
    if (SPRITES_BY_ID.find(id) == SPRITES_BY_ID.end()) {
        SPRITES_BY_ID[id] = {};
    }
    sf::Texture* texture = TextureManager::getTexture(textureName);
    if(texture != nullptr)
    {
        sf::Sprite* sprite = new sf::Sprite(*texture);
        SPRITES_BY_ID[id][spriteName] = sprite;
    }
}

void SpriteManager::addSprite(std::string spriteName, sf::Sprite* sprite, const unsigned int& id)
{
    if (SPRITES_BY_ID.find(id) == SPRITES_BY_ID.end()) {
        SPRITES_BY_ID[id] = {};
    }
    SPRITES_BY_ID[id][spriteName] = sprite;
}

// Retrieve a texture by its name
std::map<std::string, sf::Sprite*> SpriteManager::getObjSpriteMap(const unsigned int& id)
{
    if (SPRITES_BY_ID.find(id) != SPRITES_BY_ID.end()) {
        return SPRITES_BY_ID[id];
    }
    return {};
}

// Clean up all loaded textures
void SpriteManager::cleanup()
{
    for (auto& pair : SPRITES_BY_ID) {
        for (auto& sprite : pair.second)
            delete sprite.second;
    }
    SPRITES_BY_ID.clear();
}