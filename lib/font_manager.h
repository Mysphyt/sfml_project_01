#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class FontManager {
public:
    // Load a texture from file and store it with a name
    static sf::Font* loadFont(const std::string& name, const std::string& path);

    // Retrieve a texture by its name
    static sf::Font* getFont(const std::string& name);

    // Clean up all loaded textures
    static void cleanup();

private:
    static std::map<std::string, sf::Font*> fonts; // Map to store textures
};