#include "event.h"
#include "log.h"
#include "menu.h"
#include "module.h"
#include "dvd_logo.h"
#include "sprite_chopper.h"

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

    window.close();

    window.create(sf::VideoMode({static_cast<unsigned int>(visibleArea.size.x), static_cast<unsigned int>(visibleArea.size.y)}), "window");

    window.setView(sf::View(sf::FloatRect({0.f, 0.f}, {BASE_WIN_WIDTH, BASE_WIN_HEIGHT})));
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
    if (CURR_MODULE != nullptr)
    {
        CURR_MODULE->onKeyPressed(window, keyPressed);
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

    // Branching logic for different menu buttons
    if(CURR_PROGRAM_STATE == ProgramState::MENU & MENUS.top().activeButtonIndex != -1)  // Check if there is an active button
    {
        std::string buttonString = MENUS.top().buttons[MENUS.top().activeButtonIndex].text.getString();
        std::cout << "Clicked Button: " << buttonString << std::endl;

        // TODO: figure out callback system for specific buttons
        if(buttonString == "DVD Logo") 
        {
            CURR_MODULE = new DvDLogo("dvd_logo");
            CURR_PROGRAM_STATE = ProgramState::MODULE;
        }
        else if(buttonString == "Sprite Chopper") 
        {
            CURR_MODULE = new SpriteChopper("sprite_chopper", window, "Halberdier", "Halberdier.png");
            CURR_PROGRAM_STATE = ProgramState::MODULE;
        }
        else if(buttonString == "Quit") 
        {
            window.close();
        }
        else if(buttonString == "Back") 
        {
            if(MENUS.size() > 1)
            {
                MENUS.pop();
            }
        }
    }
    else if(CURR_PROGRAM_STATE == ProgramState::MODULE & CURR_MODULE != nullptr)
    {
        CURR_MODULE->onMouseButtonPressed(window, mouseButtonPressed);
    }
};

const void onMouseMoved (sf::RenderWindow &window, const sf::Event::MouseMoved& mouseMoved)
{
    // Debug("new mouse x: "+std::to_string(mouseMoved.position.x));
    // Debug("new mouse y: "+std::to_string(mouseMoved.position.y));   
    sf::Vector2f mouseViewPos = window.mapPixelToCoords(mouseMoved.position);

    if (MENUS.size() > 0)
    {
        MENUS.top().CheckMouseCollisions(mouseViewPos.x, mouseViewPos.y);
    }

    if (CURR_MODULE != nullptr)
    {
        CURR_MODULE->onMouseMoved(window, mouseMoved);
    }
};
