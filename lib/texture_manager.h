#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class TextureManager {
public:
    // Load a texture from file and store it with a name
    static sf::Texture* loadTexture(const std::string& name, const std::string& path);

    // Retrieve a texture by its name
    static sf::Texture* getTexture(const std::string& name);

    // Clean up all loaded textures
    static void cleanup();

private:
    static std::map<std::string, sf::Texture*> textures; // Map to store textures
};