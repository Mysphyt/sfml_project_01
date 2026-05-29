#ifndef MODULE_H
#define MODULE_H

#include "data.h"

class Module : public ObjData {
protected:
public:
    std::string name;

    Module(const std::string& moduleName) : ObjData() {
        name = moduleName;
    };

    virtual void update(sf::RenderWindow& window, float deltaTime);

    virtual void render(sf::RenderWindow& window);

    virtual void onClose (sf::RenderWindow& window, const sf::Event::Closed& closed);
    
    virtual void onResized (sf::RenderWindow& window, const sf::Event::Resized& resized);
    
    virtual void onKeyPressed (sf::RenderWindow &window, const sf::Event::KeyPressed& keyPressed);
    
    virtual void onKeyReleased (sf::RenderWindow &window, const sf::Event::KeyReleased& keyReleased);
    
    virtual void onMouseWheelScrolled (sf::RenderWindow &window, const sf::Event::MouseWheelScrolled& mouseWheelScrolled);
    
    virtual void onMouseButtonPressed (sf::RenderWindow &window, const sf::Event::MouseButtonPressed& mouseButtonPressed);
    
    virtual void onMouseMoved (sf::RenderWindow &window, const sf::Event::MouseMoved& mouseMoved);
};

extern Module* CURR_MODULE;

#endif