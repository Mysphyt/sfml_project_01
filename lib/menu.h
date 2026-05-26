#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <string>
#include <Windows.h>
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

    VOID Update(sf::RenderWindow& window, float deltaTime);

    VOID Render(sf::RenderWindow& window);
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

    VOID BounceBackgroundTextureRect(const std::string& backgroundName);
     
    VOID Update(sf::RenderWindow& window, float deltaTime);

    VOID Render(sf::RenderWindow& window);

    VOID CheckMouseCollisions(float mouseX, float mouseY);

};

Menu GenerateTestMenu(float width, float height);

Menu LoadMenuFromFile(const std::filesystem::path& filePath);

extern std::stack<Menu> MENUS;

sf::Color ParseColorString(const std::string& colorStr);

#endif