#include "texture_manager.h"

std::map<std::string, sf::Texture*> TextureManager::TEXTURES;

std::map<std::string, std::map<std::string, std::vector<SimpleRect>>> TextureManager::SPRITE_SHEET_DATA; 

sf::Texture* TextureManager::loadTexture(const std::string& name, const std::string& path) {
    // Check if the texture is already loaded
    if (TEXTURES.find(name) != TEXTURES.end()) {
        return TEXTURES[name];
    }

    // Load the texture
    sf::Texture* texture = new sf::Texture();
        if (texture->loadFromFile("data/textures/" + path)) {
        TEXTURES[name] = texture;
        return texture;
    }

    // If loading fails, clean up and return nullptr
    delete texture;
    return nullptr;
}

// Retrieve a texture by its name
sf::Texture* TextureManager::getTexture(const std::string& name) {
        if (TEXTURES.find(name) != TEXTURES.end()) {
        return TEXTURES[name];
    }
    return nullptr;
}

// Clean up all loaded textures
void TextureManager::cleanup() {
    for (auto& pair : TEXTURES) {
        delete pair.second;
    }
    TEXTURES.clear();
}

void TextureManager::loadMetadata() 
{
    std::filesystem::path metadataFilePath = "data/textures/texture_metadata.csv";

    std::unordered_map<std::string, std::vector<std::string>> metadata = LoadDataCSV(metadataFilePath);

    for (auto it = metadata.begin(); it != metadata.end(); it++)
    {
        std::vector<SimpleRect> spriteBounds;
        std::string animationName;
        for (std::string boundsStr : it->second) 
        {
            if(boundsStr == it->second[0]) // first value is the name of the animation
            {
                animationName = boundsStr;
                continue;
            }
            std::vector<std::string> boundsValues = SplitString(boundsStr, ',');
            uint8_t boundsX = stoi(boundsValues[0]);
            uint8_t boundsY = stoi(boundsValues[1]);
            uint8_t boundsWidth = stoi(boundsValues[2]);
            uint8_t boundsHeight = stoi(boundsValues[3]);

            spriteBounds.push_back(SimpleRect({boundsX,boundsY,boundsHeight,boundsWidth}));
        }
        SPRITE_SHEET_DATA[it->first][animationName] = spriteBounds;
    }
}
