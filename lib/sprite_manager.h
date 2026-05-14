#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class SpriteManager {
public:
    // Load a texture from file and store it with a name
    static void createSprite(std::string spriteName, const unsigned int& id, const std::string& textureName);

    static void addSprite(std::string spriteName, sf::Sprite* sprite, const unsigned int& id);

    // Retrieve a texture by its name
    static std::map<std::string, sf::Sprite*> getObjSpriteMap(const unsigned int& id);

    // Clean up all loaded textures
    static void cleanup();

private:
    // Sprites by object id
    // => { object_id : { sprite_name : sprite }, ... }
    static std::map<unsigned int, std::map<std::string, sf::Sprite*>> spritesByID; // Map to store textures
};