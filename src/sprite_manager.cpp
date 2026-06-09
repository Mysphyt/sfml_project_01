#include "sprite_manager.h"
#include "texture_manager.h"

std::map<unsigned int, std::map<std::string, sf::Sprite*>> SpriteManager::SPRITES_BY_ID; // Map to store textures
std::map<std::string, std::map<std::string, std::string>> TEXTURE_METADATA; // Map to store animated texture metadata

SpriteSheetAnimation::SpriteSheetAnimation(std::string filePath) : animIt(0), frameIt(0), frameDuration(128), frameTime(0)
{
    sf::Texture* texture = TextureManager::loadTexture("Halberdier", filePath+".png");
    std::cout << "TEXTURE SIZE :: " << texture->getSize().x << "," << texture->getSize().y << std::endl;
    if(texture != nullptr)
    {
        spriteSheet = new sf::Sprite(*texture);
        // TODO: Remove this
        spriteSheet->setPosition({650,500});
    }
    else
    {
        std::cout << "FAILED TO LOAD TEXTURE";
    }
    std::map<std::string, std::vector<std::string>> spriteDataRaw = LoadDataCSV("data/textures/"+filePath+"_metadata");
    std::vector<std::vector<sf::Vector2i>> animationList;

    std::cout << "Initializing animation for " << filePath << std::endl;

    int animIt = 0, vertIt = 0;
    for(const auto& animDataStr : spriteDataRaw)
    {
        // New animation within the spritesheet
        int animNum = stoi(animDataStr.first);

        std::cout << "Anim#" << animIt;
        std::cout << animDataStr.second[0] << std::endl;

        std::vector<std::string> animFrames = SplitString(animDataStr.second[0], '|');
        animationList.push_back({});

        for(const auto& vertDataStr : animFrames) 
        {
            std::cout << "vertex#" << vertIt;
            std::vector<std::string> vertData = SplitString(vertDataStr, ',');

            int vertX = stoi(vertData[0]);
            int vertY = stoi(vertData[1]);

            std::cout << " " << vertData[0] << "," << vertData[1] << std::endl;
            animationList[animIt].push_back({vertX, vertY});
            vertIt++;
        }
        animIt++;
    }
    std::cout << "generating frame data..." << std::endl;
    for (animIt = 0; animIt < animationList.size(); animIt++) // For each animation
    {
        animFrameRects.push_back({});

        auto animVerts = animationList[animIt];

        sf::Vector2i anchorVert;
        if (animVerts.size() > 0)
        {
            anchorVert = animVerts[0];
        }
        else
        {
            continue;
        }

        for (vertIt = 0; vertIt < animVerts.size(); vertIt++)
        {
            sf::Vector2i currAnimVert, nextAnimVert = {0,0};
            float rectWidth, rectHeight, rectPosX, rectPosY = 0;

            std::cout << "vertex#" << vertIt << " " << animVerts[vertIt].x << "," << animVerts[vertIt].y << std::endl;

            if(vertIt < animVerts.size() - 1) // Not the last index
            {
                currAnimVert = animVerts[vertIt];  
                nextAnimVert = animVerts[vertIt+1];
            }
            else
            {
                continue;
            }

            rectWidth = nextAnimVert.x - currAnimVert.x;
            rectHeight = anchorVert.y - nextAnimVert.y;

            rectPosX = currAnimVert.x;
            rectPosY = nextAnimVert.y;

            sf::IntRect frameRect;

            frameRect.size.x = rectWidth;
            frameRect.size.y = rectHeight;
            frameRect.position.x = rectPosX;
            frameRect.position.y = rectPosY;

            std::cout << "Rect#" << vertIt << " " << rectPosX << "," << rectPosY << "|" << rectWidth << "," << rectHeight << std::endl;
            animFrameRects[animIt].push_back(frameRect);
        }
    }
    /*
    for(const auto& animDataStr : spriteDataRaw)
    {
        // New animation within the spritesheet
        int animNum = stoi(animDataStr.first);
        animFrameRects.push_back({});

        std::vector<std::string> animFrames = SplitString(animDataStr.second[0], '|');

        for(const auto& rectDataStr : animFrames) 
        {
            std::vector<std::string> rectData = SplitString(rectDataStr, ',');
            sf::IntRect frameRect;

            frameRect.size.x = stoi(rectData[0]);
            frameRect.size.y = stoi(rectData[1]);
            frameRect.position.x = stoi(rectData[2]);
            frameRect.position.y = stoi(rectData[3]);

            animFrameRects[animNum].push_back(frameRect);
        }
    }
    */
    if(animFrameRects.size() > 0 && animFrameRects[0].size() > 0)
    {
         spriteSheet->setTextureRect(animFrameRects[0][0]);
    }
    std::cout << "Done loading metadata for " << filePath << std::endl;
}

void SpriteSheetAnimation::Update(sf::RenderWindow& window, float deltaTime) 
{
    frameTime += deltaTime;
    if (frameTime >= frameDuration)
    {
        frameTime = 0;
        if(animFrameRects.size() == 0 || animFrameRects[animIt].size() == 0)
        {
            return;
        }
        // std::cout << "FRAMEIT " << frameIt << std::endl;
        // std::cout << "ANIMSIZE " << animFrameRects[animIt].size() << std::endl;

        if(frameIt <= animFrameRects[animIt].size() - 1)
        {
            //std::cout << "FRAME# " << frameIt << std::endl;
            sf::IntRect frameRect = animFrameRects[animIt][frameIt];
            // std::cout << "FRAME DEBUG: " << frameIt << "| " << frameRect.position.x << ", " << frameRect.position.y << ", " << frameRect.size.x << ", " << frameRect.size.y << std::endl;
            spriteSheet->setTextureRect(frameRect);
            spriteSheet->setOrigin({0,frameRect.size.y});
            frameIt++;
        }
        else
        {
            frameIt = 0;
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
