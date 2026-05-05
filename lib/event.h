#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <format>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "log.h"

const void onClose (sf::RenderWindow& window, const sf::Event::Closed& closed);

const void onResized (sf::RenderWindow& window, const sf::Event::Resized& resized);

const void onKeyPressed (sf::RenderWindow &window, const sf::Event::KeyPressed& keyPressed);

const void onKeyReleased (sf::RenderWindow &window, const sf::Event::KeyReleased& keyReleased);

const void onMouseWheelScrolled (sf::RenderWindow &window, const sf::Event::MouseWheelScrolled& mouseWheelScrolled);

const void onMouseButtonPressed (sf::RenderWindow &window, const sf::Event::MouseButtonPressed& mouseButtonPressed);

const void onMouseMoved (sf::RenderWindow &window, const sf::Event::MouseMoved& mouseMoved);

#endif