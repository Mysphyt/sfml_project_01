#ifndef sprite_chopper_H
#define sprite_chopper_H

#include "module.h"

enum class ChopperMode {
    SET_ANIM_FLOOR,
    SET_NEXT_ANIM_VERT,
    SET_ANIM_END
};

class SpriteChopper : public Module {
public:    
    SpriteChopper(
        const std::string& moduleName,
        sf::RenderWindow& window,
        std::string textureName,
        std::string textureFile);

    void update(sf::RenderWindow& window, float deltaTime) override;

    void render(sf::RenderWindow& window) override;

    void saveSpriteData();

    void onClose (sf::RenderWindow& window, const sf::Event::Closed& closed) override;
    
    void onResized (sf::RenderWindow& window, const sf::Event::Resized& resized) override;
    
    void onKeyPressed (sf::RenderWindow &window, const sf::Event::KeyPressed& keyPressed) override;
    
    void onKeyReleased (sf::RenderWindow &window, const sf::Event::KeyReleased& keyReleased) override;
    
    void onMouseWheelScrolled (sf::RenderWindow &window, const sf::Event::MouseWheelScrolled& mouseWheelScrolled) override;
    
    void onMouseButtonPressed (sf::RenderWindow &window, const sf::Event::MouseButtonPressed& mouseButtonPressed) override;
    
    void onMouseMoved (sf::RenderWindow &window, const sf::Event::MouseMoved& mouseMoved) override;

protected:
    // Vector of {x,y}(vector2i) positions 
    // SPRITE_SHEET-->
    //    { ANIMATION_1-->
    //      {0,0},{100,0}
    //    }
    //    { ANIMATION_2-->
    //      {0,100},{100,100}
    //    }

    std::vector<std::vector<sf::Vector2i>> spriteSheetAnimationVertices;
    std::vector<unsigned int> spriteSheetAnimationFloors;
    std::vector<unsigned int> spriteSheetAnimationXBounds;

    unsigned int currAnimIndex, currVertIndex;

    std::string spriteSheetName;

    sf::Text positionText, animNumText, modeText;

    sf::Vector2i currMousePos;

    ChopperMode currMode;
};

#endif