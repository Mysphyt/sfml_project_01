#include "sprite_manager.h"
#include "texture_manager.h"

std::map<unsigned int, std::map<std::string, sf::Sprite*>> SpriteManager::SPRITES_BY_ID; // Map to store textures
std::map<std::string, std::map<std::string, std::string>> TEXTURE_METADATA; // Map to store animated texture metadata

SpriteSheetAnimation::SpriteSheetAnimation(std::string filePath) : animIt(0), frameIt(0), frameDuration(16), frameTime(0)
{
    sf::Texture* texture = TextureManager::loadTexture("Halberdier", filePath+".png");
    if(texture != nullptr)
    {
        spriteSheet = new sf::Sprite(*texture);
    }
    else
    {
        std::cout << "FAILED TO LOAD TEXTURE";
    }
    std::unordered_map<std::string, std::vector<std::string>> spriteDataRaw = LoadDataCSV("data\\textures\\"+filePath+"_metadata");
    for(const auto& animDataStr : spriteDataRaw)
    {
        // New animation within the spritesheet

        int animNum = stoi(animDataStr.first);
        animFrameRects.push_back({});

        std::vector<std::string> animFrames = SplitString(animDataStr.second[0], '|');

        int frameNum = 0;
        for(const auto& rectDataStr : animFrames) 
        {
            std::vector<std::string> rectData = SplitString(rectDataStr, ',');
            // 
            sf::IntRect frameRect;

            frameRect.size.x = stoi(rectData[0]);
            frameRect.size.y = stoi(rectData[1]);
            frameRect.position.x = stoi(rectData[2]);
            frameRect.position.y = stoi(rectData[3]);

            std::cout << "Anim Frame: " << frameRect.position.x << "," << frameRect.position.y << std::endl;

            animFrameRects[animNum].push_back(frameRect);
            frameNum++;
        }
    }
}

void SpriteSheetAnimation::Update(sf::RenderWindow& window, float deltaTime) 
{
    frameTime += deltaTime;
    if (frameTime >= frameDuration)
    {
        frameTime = 0;
        if (frameIt == animFrameRects[animIt].size() - 1)
        {
            frameIt = 0;
        }
        else
        {
            frameIt++;
            spriteSheet->setTextureRect(animFrameRects[animIt][frameIt]);
        }
    }
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