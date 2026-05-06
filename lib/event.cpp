#include "event.h"
#include "menu.h"

const void onClose (sf::RenderWindow& window, const sf::Event::Closed& closed)
{
    window.close();
};

const void onResized (sf::RenderWindow& window, const sf::Event::Resized& resized)
{
    Debug("new width: "+std::to_string(resized.size.x));
    Debug("new height: "+std::to_string(resized.size.y));

    // update the view to the new size of the window
    sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized.size));
    window.setView(sf::View(visibleArea));
};

const void onKeyPressed (sf::RenderWindow &window, const sf::Event::KeyPressed& keyPressed)
{
    if (keyPressed.scancode == sf::Keyboard::Scancode::Escape)
    {
        // Close the window
        window.close();
    }
    else 
    {
        Debug("Key Pressed: "+sf::Keyboard::getDescription(keyPressed.scancode).toAnsiString());
    }
};

const void onKeyReleased (sf::RenderWindow &window, const sf::Event::KeyReleased& keyReleased)
{
    Debug("Key Released: "+sf::Keyboard::getDescription(keyReleased.scancode).toAnsiString());
};

const void onMouseWheelScrolled (sf::RenderWindow &window, const sf::Event::MouseWheelScrolled& mouseWheelScrolled)
{
    switch (mouseWheelScrolled.wheel)
    {
        case sf::Mouse::Wheel::Vertical:
            Debug("wheel type: vertical");
            break;
        case sf::Mouse::Wheel::Horizontal:
            Debug("wheel type: horizontal");
            break;
    }
    Debug("wheel movement: "+std::to_string(mouseWheelScrolled.delta));
    Debug("mouse x: "+std::to_string(mouseWheelScrolled.position.x));
    Debug("mouse y: "+std::to_string(mouseWheelScrolled.position.y));
};

const void onMouseButtonPressed (sf::RenderWindow &window, const sf::Event::MouseButtonPressed& mouseButtonPressed)
{

    if (mouseButtonPressed.button == sf::Mouse::Button::Right)
    {
        Debug("the right button was pressed");
        Debug("mouse x: "+std::to_string(mouseButtonPressed.position.x));
        Debug("mouse y: "+std::to_string(mouseButtonPressed.position.y));
    }
    else if (mouseButtonPressed.button == sf::Mouse::Button::Left)
    {
        Debug("the left button was pressed");
        Debug("mouse x: "+std::to_string(mouseButtonPressed.position.x));
        Debug("mouse y: "+std::to_string(mouseButtonPressed.position.y));
    }

};

const void onMouseMoved (sf::RenderWindow &window, const sf::Event::MouseMoved& mouseMoved)
{
    Debug("new mouse x: "+std::to_string(mouseMoved.position.x));
    Debug("new mouse y: "+std::to_string(mouseMoved.position.y));   

    CheckMouseCollisions(CURRENT_MENU, mouseMoved.position.x, mouseMoved.position.y);
};
