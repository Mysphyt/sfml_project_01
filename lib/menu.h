#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <list>

#include "globals.h"
#include "log.h"

struct Button {
    sf::Text text;
    sf::RectangleShape background;
};

struct Menu {
    sf::RectangleShape background;
    std::list<Button> buttons;
};

extern Menu CURRENT_MENU;

VOID RenderMenu(sf::RenderWindow&, Menu);

VOID RenderButton(sf::RenderWindow&, Button);

VOID CheckMouseCollisions(Menu& menu, float mouseX, float mouseY);

Menu GenerateTestMenu(float width, float height);

#endif