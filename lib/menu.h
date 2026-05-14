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

struct Button {
    sf::Text text;
    sf::RectangleShape background;
};

struct Menu {
    ObjData data;

    int activeButtonIndex;

    std::string name;

    sf::RectangleShape backgroundRect;

    std::vector<Button> buttons;
};

extern std::stack<Menu> MENUS;

sf::Color ParseColorString(const std::string& colorStr);

VOID BounceBackgroundTextureRect(Menu& menu, const std::string& backgroundName);
 
VOID RenderMenu(sf::RenderWindow& window, Menu& menu);

VOID RenderButton(sf::RenderWindow& window, const Button& button);

VOID CheckMouseCollisions(Menu& menu, float mouseX, float mouseY);

Button CreateButton(
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

Menu GenerateTestMenu(float width, float height);

Menu LoadMenu(const std::filesystem::path& filePath);

#endif