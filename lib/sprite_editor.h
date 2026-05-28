#ifndef SPRITE_EDITOR_H
#define SPRITE_EDITOR_H

#include "module.h"

class SpriteEditor : public Module {
public:    
    SpriteEditor(
        const std::string& moduleName,
        sf::RenderWindow& window,
        std::string textureName,
        std::string textureFile);

    void update(sf::RenderWindow& window, float deltaTime) override;

    void render(sf::RenderWindow& window) override;

    void saveSpriteData();

    void addSpritePosition(std::string animationName);
protected:
    std::map<std::string, std::vector<sf::Vector2i>> spritePositions;
};

#endif