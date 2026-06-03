#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include <map>

#include "data.h"

class Button : public ObjData {
public:
    Button(
        float xpos, float ypos, 
        float width, float height, 
        int textSize,
        const std::string& textString, 
        sf::Color textColor,
        sf::Color buttonColor,
        bool centerText,
        bool boldText,
        bool underlineText
    );

    sf::Text text;
    sf::RectangleShape background;

    void Update(sf::RenderWindow& window, float deltaTime);

    void Render(sf::RenderWindow& window);
};

class Menu : public ObjData {
public:
    std::string name;

    sf::RectangleShape backgroundRect;

    std::vector<Button> buttons;

    int activeButtonIndex;

    Menu(
        int _activeButtonIndex,
        std::string _name,
        sf::RectangleShape _backgroundRect,
        std::vector<Button> _buttons) {
            activeButtonIndex = _activeButtonIndex;
            name = _name;
            buttons = _buttons;
            backgroundRect = _backgroundRect;
    };

    void BounceBackgroundTextureRect(const std::string& backgroundName);
     
    void Update(sf::RenderWindow& window, float deltaTime);

    void Render(sf::RenderWindow& window);

    void CheckMouseCollisions(float mouseX, float mouseY);

};

Menu GenerateTestMenu(float width, float height);

Menu LoadMenuFromFile(const std::filesystem::path& filePath);

extern std::stack<Menu> MENUS;

sf::Color ParseColorString(const std::string& colorStr);

#endif
