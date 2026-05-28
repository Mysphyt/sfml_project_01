#include "sprite_editor.h"
#include "sprite_manager.h"
#include "texture_manager.h"
#include "globals.h"

SpriteEditor::SpriteEditor(
    const std::string& moduleName,
    sf::RenderWindow& window,
    std::string textureName,
    std::string textureFile) : Module(moduleName) 
{
    sf::Texture* testTexture = TextureManager::loadTexture(textureName, textureFile);
    sf::Sprite* testSprite = new sf::Sprite(*testTexture);

    testSprite->setPosition({0,0});

    sf::Vector2u testTextureSize = testTexture->getSize();

    // Scale the test texture to the current resolution
    float scaleX = static_cast<float>(BASE_WIN_WIDTH) / testTextureSize.x;
    float scaleY = static_cast<float>(BASE_WIN_HEIGHT) / testTextureSize.y;

    testSprite->setScale({scaleX, scaleY});    
    SpriteManager::addSprite(textureName, testSprite, getId());

    // Resize the current window to the size of the loaded texture
    // TODO: determine if this is necessary or if the sprite can be scaled & use global coordinates
    sf::Vector2u resized = testTexture->getSize();

    sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized));
    window.close();
    window.create(sf::VideoMode({static_cast<unsigned int>(visibleArea.size.x), static_cast<unsigned int>(visibleArea.size.y)}), "window");
    window.setView(sf::View(sf::FloatRect({0.f, 0.f}, {BASE_WIN_WIDTH, BASE_WIN_HEIGHT})));
}

void SpriteEditor::update(sf::RenderWindow& window, float DeltaTime) 
{

}

void SpriteEditor::render(sf::RenderWindow& window) 
{
    for(auto& sprite : SpriteManager::getObjSpriteMap(getId()))
    {
        window.draw(*sprite.second);
    }
}